//maze.js 
//vomitado por Eriiiiiic dominio público-púbico

//Es momento de bailar la esponja
var esponja = false;

//declaraciones pendejas globales
//dimensiones cabronas 
var columnas = 30;
var renglones = 30;

//puto laberinto y sus caminos
var maze = new Array(renglones); 	
for (x = 0; x < maze.length; x++){
	maze[x] = new Array(columnas); 
}

//inicialización de movimientos de mierda a dibujar
var row = new Array(4);
var column = new Array(4);
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

//tamaño imbecil del laberinto a dibujar idiota
var mazeRow = 1 + 2*renglones;
var mazeCol = 1 + 2*columnas;

//puto arreglo para dibujar un inutil laberinto con pinche ASCII
var mazeDraw = new Array(mazeRow);
for (x = 0; x < mazeDraw.length; x++){
 	mazeDraw[x] = new Array(mazeCol);
}

//puta posicion actual (x,y)
var posMazeX = 1;
var posMazeY = 0; 

//vómito de laberinto
function mazeFuck(posX, posY){
	//inicializa bandera de cagada validez 
	var flag = true;
	
	//valor default de no moviemiento de mierda
	maze[posX][posY] = new Array();
	maze[posX][posY].push(-1);
	
	//mientras hayan movimeintos de mierda válidos
	while(flag){
		var valido = new Array();
		//chequeo de casillas válidas imbecil
		for (var i = 0; i < 4; i++){
			//verifica que este adentro del maldito arreglo
			if ( (posX + row[i] >= 0) && (posY + column[i] >= 0) && (posX + row[i] < maze.length) && (posY + column[i] < maze[0].length) ){
				//verifica que no este recorrida la puta posición
				if ( maze[posX + row[i]][posY + column[i]] == undefined ){
					//guarda movimientos de mierda válidos
					valido.push(i);
				}
			}
		}
		// no me caso de poner comentarios de la verga
		//si hay movimientos de mierda válidos
		if (valido.length != 0){ 
			//elige un valor de mierda válido al chile (random)
			var movPos = valido[  Math.floor( Math.random()*4)  % valido.length  ];
			
			//si es igual a -1 quito el valor a la chingada
			if(maze[posX][posY][0] == -1){
				maze[posX][posY].pop();
			}
			
			//guarda el movimeinto de mierda
			maze[posX][posY].push(movPos);
			
			//recursion!!!!
			mazeFuck(posX + row[movPos], posY + column[movPos]);
		
		}else{
			//si no hay, bla bla dice: "FLAG! no mames, eres falso, salte del puto while 
			flag = false;
		}
	}
}

//dibuja perra!!!!
function drawMaze(){
	
	//genera el laberinto y sus caminos de la chingada
	mazeFuck(0, 0);
	//se inicializa con algun caracter cagada
	for (i = 0; i < mazeDraw.length; i++){
		for (j = 0; j < mazeDraw[i].length; j++){
			mazeDraw[i][j] = "<div><img src=\"white.jpg\"></div>";			
		}
	}

	//pendejo color del camino
	var colorin_road = "<div><img src=\"black.jpg\"></div>";

	//harcodea entrada y salida, que pendejo y webon
	mazeDraw[1][0] = "<div><img src=\"yellow.jpg\"></div>"; 
	mazeDraw[mazeDraw.length - 2][mazeDraw[0].length - 1]= "<div><img src=\"red.jpg\"></div>";
	
	//recorre al arreglo lameculos para dibujar el putillo recorrido
	for (x = 0; x < maze.length; x++){
		for (y = 0; y < maze[x].length; y++){
			for	( z= 0; z < maze[x][y].length; z++){
				//si el putin valor es -1 no tumba pared
				if(maze[x][y][z] != "-1"){
					//guarda el mierda de valor del movimiento
					var tempr = row[ maze[x][y][z] ]; 
	    		var tempc = column[ maze[x][y][z] ];
					var posR = 2*x + 1;
					var posC = 2*y + 1;
					//pinta caminillo hijo de puta en posicion actual, +1 y +2 en respecputamente
					mazeDraw[posR][posC] = colorin_road;
					mazeDraw[ posR + tempr ][ posC + tempc ] = colorin_road;
			  	mazeDraw[ posR + 2*tempr ][ posC + 2*tempc ] = colorin_road;
				}
			}
		}
	}
	
	//imprime el laberinto pinche cabron
	printMaze(mazeDraw);
}

function printMaze(m){
	//inicializo cadenilla ogt
	var cadenilla= "";
	//la recorro a la puta
	for (i = 0; i < m.length; i++){
		for (j = 0; j < m[i].length; j++){
				cadenilla += m[i][j];
		}
		cadenilla += "</br>";
	}
	//la imprimo la chigandera a putazos hardcore id
	document.getElementById("666").innerHTML = cadenilla;
}

//funcion para checar validez de la pinch posicion y devolver su puto estado
function checaPosColorea(i){
	//usa "i" de mierda para saber a donde chingados se quiere mover
	//valida posicion y si es difrente a puta pared harcodeada = "0" se mueve
	if( (posMazeX + row[i] >= 0) && (posMazeY + column[i] >= 0) && (posMazeX + row[i] < mazeDraw.length) && 
	(posMazeY + column[i] < mazeDraw[0].length) ){
		if (mazeDraw[posMazeX + row[i]][posMazeY + column[i]] != "<div><img src=\"white.jpg\"></div>"){
			mazeDraw[posMazeX][posMazeY] = "<div><img src=\"red.jpg\"></div>";
			mazeDraw[posMazeX + row[i]][posMazeY + column[i]] = "<div><img src=\"yellow.jpg\"></div>";
			posMazeX+=row[i];
			posMazeY+=column[i];
			if ( ( posMazeX + row[i] == mazeDraw.length - 2) && ( posMazeY + column[i] == mazeDraw[0].length - 1) ){
				alert("Es momento de bailar la esponja");
				esponja = true;
			}
		}
	}	
}

//funcion para detectar si presiona las flechas el simio, 
//y luego mover la puta posicion
function handleKeyboard(e)
{
	if(e.keyCode == 37){//izquierda = 3
		checaPosColorea(3);	
	}else if(e.keyCode == 38){//arriba = 0
		checaPosColorea(0);
	}else if(e.keyCode == 39){//derecha = 1
		checaPosColorea(1);
	}else if(e.keyCode == 40){//abajo = 2
		checaPosColorea(2);
	}
 	
	printMaze(mazeDraw);
  	if(esponja){
		document.getElementById("esponja").innerHTML = "<img src=\"./dancethesponge1.jpg\"/><img src=\"./dancethesponge2.jpg\"/>";
	}

}
