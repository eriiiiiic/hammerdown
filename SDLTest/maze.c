//vomitado por Eriiiiiic dominio público-púbico

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//declaraciones pendejas globales
//dimensiones cabronas 
#define columnas 10
#define renglones 10

//tamaño imbecil del laberinto a dibujar idiota
#define mazeCol 21
#define mazeRow 21

//puto laberinto y sus caminos
int maze[renglones][columnas][4]; 	

//inicialización de movimientos de mierda a dibujar
int row[4];
int column[4];


//puto arreglo para dibujar un inutil laberinto con pinche ASCII
int mazeDraw[mazeRow][mazeCol];
	
//puta posicion actual (x,y)
int posMazeX = 1;
int posMazeY = 0; 

void init(){

srand(time(NULL));

int i, j, k;
for (i = 0; i < renglones; i++){
	for (j = 0; j < columnas; j++){
		for (k = 0; k < 4; k++){
			maze[i][j][k] = -1;
		} 
	}
}

//reglon (en x de la chingada)
row[0] = -1;
row[1] = 0;
row[2] = 1;
row[3] = 0;
//columna (en y de la chingada)
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

//vómito de laberinto
void mazeFuck(int posX, int posY){
	//inicializa bandera de cagada validez 
	int flag = 1;
	int x = 0;
	int movPos=0;
	maze[posX][posY][0] = 5;
	
	//mientras hayan movimeintos de mierda válidos
	while(flag){
				
		int cuenta = 0;
		int valido[4];
		//chequeo de casillas válidas imbecil
		int i;
		for (i = 0; i < 4; i++){
			//verifica que este adentro del maldito arreglo
			if ( (posX + row[i] >= 0) && (posY + column[i] >= 0) && 
				(posX + row[i] < renglones) && 
			(posY + column[i] < columnas) ){
			//verifica que no este recorrida la puta posición
				if ( maze[posX + row[i]][posY + column[i]][0] == -1 ){
					//guarda movimientos de mierda válidos
					valido[cuenta++]=i;
				}
				
			}
		}
		// no me caso de poner comentarios de la verga
		//si hay movimientos de mierda válidos
		if (cuenta != 0){ 
			//elige un valor de mierda válido al chile (random)
			movPos = valido[rand() % cuenta];
			maze[posX][posY][x++] = movPos;
			
			//recursion!!!!
			mazeFuck(posX + row[movPos], posY + column[movPos]);
		
		}else{
			//si no hay, bla bla dice: "FLAG! no mames, eres falso, salte del puto while 
			
			flag = 0;
		}
	}
}


void printMaze(){
	//la recorro a la puta
	int i, j;
	for (i = 0; i < mazeRow; i++){
		for (j = 0; j < mazeCol; j++){
				printf("%d", mazeDraw[i][j]);
		}
		printf("\n");
	}
}

//dibuja perra!!!!
void drawMaze(){
	
	//genera el laberinto y sus caminos de la chingada
	mazeFuck(0, 0);
	//se inicializa con algun caracter cagada
	int i, j;
	for (i = 0; i < mazeRow; i++){
		for (j = 0; j < mazeCol;  j++){
			mazeDraw[i][j] = 0;			
		}
	}

	//harcodea entrada y salida, que pendejo y webon
	mazeDraw[1][0] = 1; 
	mazeDraw[mazeRow - 2][mazeCol - 1] = 1;
	
	//recorre al arreglo lameculos para dibujar el putillo recorrido
	int x, y, z;
	for (x = 0; x < renglones; x++){
		for (y = 0; y < columnas; y++){
			for(z = 0; z < 4; z++){
				//si el putin valor es -1 no tumba pared
				if(maze[x][y][z] != -1){
					//guarda el mierda de valor del movimiento
					int tempr = row[ maze[x][y][z] ]; 
	    				int tempc = column[ maze[x][y][z] ];
					int posR = 2*x + 1;
					int posC = 2*y + 1;
					//pinta caminillo hijo de puta en posicion actual, +1 y +2 en respecputamente
					mazeDraw[posR][posC] = 1;
					mazeDraw[ posR + tempr ][ posC + tempc ] = 1;
			  		mazeDraw[ posR + 2*tempr ][ posC + 2*tempc ] = 1;
				}
			}
		}
	}
	
	//imprime el laberinto pinche cabron
	printMaze();
}

void main(){
	init();
	drawMaze();
}
