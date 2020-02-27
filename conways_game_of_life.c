#include <stdio.h>
#include <stdlib.h>


/*********************

  This program emulates Conway's Game of Life. Torus is a 2D array (sort of a misnomer here
  since a torus is a donut shape made by connecting the left and right sides of a 2D array 
  and the top and bottom sides). Conway's Game of Life (CGoL) emulates automata, so each index
  represents a cell and its surrounding indices represent surrounding cells. Each cell is 
  affected by its neighborhood, the 8 surrounding indices. There are 4 rules in CGoL: 
  1. The cell is lonely (surrounded by less than 2 live neighbors)
  2. The cell is surrounded by too many live cells (more than 3 live neighbors)
  3. The cell is reborn if surrounded by exactly 3 live neighbors 
  4. The cell is unchanged if its neighborhood has only 2 or 3 live neighbors 

  This code emulates two generations and could be improved by 
  1. truly turning the Torus array into a torus shape
  2. updating generations infinitely to illustrate changes in cells  
  3. illustrating the array with a more interesting ASCII character than ^

 *********************/
#define SIZE 10

int input_vals(int Torus[SIZE][SIZE])
{
    int r = 0;
    int c = 0;

    for (r = 0 ; r < SIZE-1 ; r++) {
        for (c = 0 ; c <= SIZE-1 ; c++) {
            scanf("%d", &Torus[r][c]);  
        }
    }
    return 1; 
}

void print_matrix (int Torus[SIZE][SIZE])
{
    int r = 0; 
    int c = 0; 
    int num = 94;  //ASCII val 
    for (r = 0 ; r < SIZE-1 ; r++) {
        for (c = 0 ; c <= SIZE-1 ; c++) {
            if(Torus[r][c] == 1)
                printf("%c", num); 
            else 
                printf(" "); 
        }
        printf("\n") ;
    }
    printf("\n") ;
}

int generation_emulation(int Torus[SIZE][SIZE])
{
    int r, c, row, col, i, j = 0; 
    int neighbor_check = 0; 
    int Neighborhood[3][3];

    int next_generation[SIZE][SIZE]; 
    for (r = 1 ; r < SIZE-1 ; r++) {
        for (c = 1 ; c <= SIZE-1 ; c++) {
            for(i = -1; i <= 1; i++) {
                for(j = -1; j <=1; j++) {
                    neighbor_check += Neighborhood[r+i][c+j]; 
                }
                neighbor_check -= Neighborhood[i][j]; 

                //4 scenarios impacting life or death of cell 

                //lonely cell
                if((Neighborhood[i][j] == 1) && neighbor_check < 2){
                    next_generation[i][j] = 0; 
                }
                //overpopulated neighborhood 
                else if ((Neighborhood[i][j] == 1) && (neighbor_check > 3)){
                    next_generation[i][j] = 0; 
                }

                //reborn cell
                else if ((Neighborhood[i][j] == 0) && (neighbor_check == 3 || neighbor_check == 2)){
                    next_generation[i][j] = 1; 
                }

                //no change
                else
                    next_generation[i][j] = Neighborhood[i][j]; 
            }
        }
    }

    for (row = 1 ; row < SIZE-1 ; row++) {
        for (col = 1 ; col <= SIZE-1 ; col++) {
            Torus[row][col] = next_generation[row][col]; 
        }
    }

    print_matrix(Torus); 

    return 0; 
}

int main(){
    int Torus[SIZE][SIZE]; //2D array where top + bottom and left + right edges are "wrapped"
    input_vals(Torus); //populate the 2D array from external .txt file
    print_matrix(Torus); 
    generation_emulation(Torus);  
    return 0; 
}

