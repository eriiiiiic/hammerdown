#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define columnas 10
#define renglones 10
#define mazeCol 21
#define mazeRow 21

int maze[renglones][columnas][4]; 	
int row[4];
int column[4];

int mazeDraw[mazeRow][mazeCol];	

int posMazeX = 1;
int posMazeY = 0; 

void init_arrays(){

	srand(time(NULL));
	int i, j, k;
	for (i = 0; i < renglones; i++){
        	for (j = 0; j < columnas; j++){
                	for (k = 0; k < 4; k++){
                        	maze[i][j][k] = -1;
                	}
        	}
	}

	row[0] = -1;
	row[1] = 0;
	row[2] = 1;
	row[3] = 0;

	column[0] = 0;
	column[1] = 1;
	column[2] = 0;
	column[3] = -1;

	for (i = 0; i < mazeRow; i++){
		for (j = 0; j < mazeCol; j++){
			mazeDraw[i][j] = 0;
		}
	}

}
void createMaze(int posX, int posY){
	
	int flag = 1;
	int x = 0;
	int movPos=0;
	maze[posX][posY][0] = 5;
		
	while(flag){
				
		int cuenta = 0;
		int valido[4];
		
		int i;	
		for (i = 0; i < 4; i++){
			
			if ( (posX + row[i] >= 0) && (posY + column[i] >= 0) && 
			(posX + row[i] < renglones) && 
			(posY + column[i] < columnas) ){
			
				if ( maze[posX + row[i]][posY + column[i]][0] == -1 ){
					valido[cuenta++]=i;
				}
				
			}
		}
		
		if (cuenta != 0){ 
			
			movPos = valido[rand() % cuenta];
			maze[posX][posY][x++] = movPos;
			createMaze(posX + row[movPos], posY + column[movPos]);
		
		}else{
			flag = 0;
		}
	}
}

void drawMaze(){
	
	int i, j;
	for (i = 0; i < mazeRow; i++){
		for (j = 0; j < mazeCol;  j++){
			mazeDraw[i][j] = 0;			
		}
	}

	mazeDraw[1][0] = 1; 
	mazeDraw[mazeRow - 2][mazeCol - 1] = 1;
	
	int x, y, z;	
	for (x = 0; x < renglones; x++){
		for (y = 0; y < columnas; y++){
			for(z = 0; z < 4; z++){
				
				if(maze[x][y][z] != -1){
					
					int tempr = row[ maze[x][y][z] ]; 
	    				int tempc = column[ maze[x][y][z] ];
					int posR = 2*x + 1;
					int posC = 2*y + 1;
					
					mazeDraw[posR][posC] = 1;
					mazeDraw[ posR + tempr ][ posC + tempc ] = 1;
			  		mazeDraw[ posR + 2*tempr ][ posC + 2*tempc ] = 1;
				}
			}
		}
	}
}

void printMaze(){
        int i, j;
        for (i = 0; i < mazeRow; i++){
                for (j = 0; j < mazeCol; j++){
                                printf("%d", mazeDraw[i][j]);
                }
                printf("\n");
        }
}

