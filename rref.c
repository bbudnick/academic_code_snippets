//Liam Rotchford and Brita Hill
//Numerical Computation Fall 2019
//This program reduces an n x n+1 matrix to Reduced Row Echelon Form (RREF) 
//using Gaussian Elimination. This algorithm employs partial pivoting to ensure 
//that later calculations will avoid divide-by-zero errors (and fail fast). 
//It then puts the matrix in upper triangular form and uses back substitution 
//to get a final solution vector. 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// row reduces an n by n+1 matrix 

#define M 20


void print_matrix (double m[M][M+1], int n)
{
   int r,c ;

   for (r = 0 ; r < n ; r++) {
     for (c = 0 ; c <= n ; c++) {
        printf("%.16lf ",m[r][c]) ;
     }
     printf("\n") ;

   }
   printf("\n") ;
}

int gaussian_elimination(double m[M][M+1], int n, double x[M])
{
  double temp, divisible_by, pivot_value, eliminator;
  int pivot_loc;

  // Step 1: reduce matrix to upper triangular form 
  // NOTE:  During step 1, perform partial pivot_locing as necessary.
  //        If partial pivot_locing fails to "fix" your system, return 0

  for(int col = 0; col <= n-1; col++){          //move through the columns of the matrix
    pivot_loc = col;                            //store current pivot index
    pivot_value = m[pivot_loc][col];            //store the current col index (EX: on first instance it is m[0][0])

    for(int row = col+1; row <= n-1; row++) {   //move through the rows of the matrix one row index ahead of the current col index

      if( fabs(m[row][col]) > pivot_value) {    //determine if there is a greater value in the current col index for our pivot
        pivot_value = m[row][col];              //if larger value found for pivot update the pivot value
        pivot_loc = row;                        //update what index the pivot is on
      }
    }

    //PARTIAL PIVOTING ROW SWAPPING: swap greatest value row (pivot) with current row 
    for(int curr = 0; curr <= n; curr++){
      temp = m[col][curr];                      //store current value on col.current
      m[col][curr] = m[pivot_loc][curr];        //update our current value in matrix with new row values that we determined to be the pivot to be swapped
      m[pivot_loc][curr] = temp;                //update the old pivoted row with the old row that was replaced
    }

    if(m[col][pivot_loc] == 0)                  // Avoid divide by zero error before attempting to solve into upper right triangle form
      return 0;

    //UPPER RIGHT TRIANGLE FORM
    for(int tri_row = col+1; tri_row <= n-1; tri_row++){
      
      if(m[col][col] == 0){                     //Double check in case of divide by zero instance
        return 0;
      }

      divisible_by = m[tri_row][col] / m[col][col];       //determine the divisor to multiply value by

      for(int tri_col = col; tri_col <= n; tri_col++) {   //Cycle through the pivoted col and set up triangle form for col
        eliminator = m[col][tri_col] * divisible_by;      //determine value to subtract from the current row being solved
        m[tri_row][tri_col] -= eliminator;                //solve the row and set the 0's and remainder values
      }
    }
  }

  printf("\n\n\no Upper Right Triangle Form: \n");
  print_matrix(m, n);
  
  // Step 2: Now do the back substitution, leaving the solution in the array 'x'
  //         and return 1 as a sign of success.

  //Back Sub, start at last row and solve bottom up
  double hold[n], value;

  for(int row = n-1; row >= 0; row--)         // start at bottom right index of the Upper right triangle form matrix
  {
    hold[row] = m[row][n];                    //Store current row constant (i.e the constant value on the other side of the " = " sign)              
    
    for(int col = row+1; col <= n-1 ; col++)  //move through the matrix backwards up the triangle (bottom right to top left)
    {
      value = m[row][col] * hold[col];        //sub in the previously solved coeffcient value and multiply it by its matching matrix value on the next row up
      hold[row] = hold[row] - value;          //determine constant (i.e move all constants to other side of " = " sign)
    }
 
    hold[row] = hold[row] / m[row][row] ;     //divide the coeffcient to the constant (12x1 = 24 => x1 = 24 / 12 => x1 = 2)
  }
  
  //Transfer solved coeffcients solution to the solution array
  for(int i = 0; i < n; i++){
    x[i] = hold[i];
  }
  
}

int main()
{

   double m[M][M+1] ;  //matrix to solve
   int n,r,c ;         //n = number of equations / rows
   double x[M] ;        //solution matrix
   int s ;              //s = result of sucess or failure for guassian

   scanf("%d",&n) ; ;   // n = number of equations 

   // Input data defining your equations 

   for (r = 0 ; r < n ; r++) {
     for (c = 0 ; c <= n ; c++) {
       scanf("%lf",&m[r][c]) ;
     }
   }

   // Output the original form 
   printf("\n\n\no Original Form: \n");
   print_matrix(m,n) ;

   s =  gaussian_elimination(m, n, x) ;
   if (s == 0) {

     // printf("simple gaussian_elimination fails, a smarter version might succeed\n") ;

     printf("gaussian_elimination with partial pivot_locing fails.\n") ;
     printf("There is no unique solution.\n") ;
     printf("The system may be inconsistent or underdetermined.\n") ;
     printf("This code does not distinguish between these last two situations.\n") ;
     exit(0) ;

   }

   // Ouptut the solution
   printf("\n\n\no Final Solution For System: \n");
   for (r = 0 ; r <n ; r++) {
     printf("%.16lf\n",x[r]) ;
   }
   printf("\n") ;

}


