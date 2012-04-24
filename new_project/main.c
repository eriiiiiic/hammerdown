#include "main.h"
#include "maze.h"
int hlvl[20][20] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

 int   CurrentFrame    = 0;
 int   MaxFrames       = 4;
 int   FrameInc        = 1;
 
 int   FrameRate       = 100; //Milliseconds
 int   OldTime         = 0;
 
 int   Oscillate       = 1;
void animacion();

SDL_Surface *player;

int main (int argc, char *argv[]) {

	/*Inicializa SDL*/
	if (SDL_Init (SDL_INIT_VIDEO) < 0) {
		printf ("SDL_INIT ha fallado\n");
		exit (1);
	}

	atexit (SDL_Quit);

	/*Usamos HW si disponible, double buffering, y pantalla completa*/
	pantalla = SDL_SetVideoMode ( 1200, 800, 16, SDL_SWSURFACE | SDL_DOUBLEBUF );

	if (pantalla == NULL) {
		printf ("Modo de video erroneo\n");
		exit (1);
	}

	/*Usaremos nuestro propio cursor*/
	SDL_ShowCursor (SDL_DISABLE);

	if (!iniciar()) {
		printf ("Error de inicializacion\n");
		exit (1);
	}
	
	init_arrays();
	createMaze(0, 0);
	drawMaze();
	printMaze();


	/*Bucle principal*/

	while (1) {


		/*Dibujamos*/
		dibujar ();


		/*Control de eventos SDL*/

		SDL_Event ev;

		while (SDL_PollEvent (&ev)) {

			switch (ev.type) {
			/*Pulsacion del teclado*/
			case SDL_KEYDOWN:
				if (ev.key.keysym.sym == SDLK_ESCAPE) {
					limpiar();
					return 0;
				}
				break;

			/*Fin del programa*/
			case SDL_QUIT:
				limpiar();
				return 0;
				break;

			}
		}

	}


	return 0;
}


/*Inicializa lo que haga falta y carga las superficies*/
int iniciar () {

	/*Definimos el clipper*/

	SDL_SetClipRect (pantalla, NULL);

	/*Cargamos los tiles*/
	tiles = IMG_Load( "tiles.png" );
	player = IMG_Load( "thespider.png" );

	if (tiles == NULL)
		return 0;

	SDL_SetColorKey (tiles, SDL_SRCCOLORKEY, 0);


	/*Calculamos el total de tiles*/
	nTilesX = tiles->w / TILE_ANCHO;
	nTilesY = tiles->h / TILE_ALTO;

	return 1;
}


/*Limpia la memoria*/
void limpiar () {

	printf ("Limpiando...\n");

	if (tiles != NULL) {
		SDL_FreeSurface (tiles);
		tiles = NULL;
	}

}


/*Dibuja el mapa y el cursor*/
void dibujar () {

	/*Limpia la pantalla*/
	SDL_FillRect (pantalla, NULL, 0);

	hardcodelvl();
	/*dibujarMapa();*/
	drawPlayer();
	/*Intercambia los buffers*/
	SDL_Flip (pantalla);

}


/*Dibuja los tiles del mapa*/
void dibujarMapa () {

	int x, y;	/*Casilla del mapa*/
	int px, py; /*Coordenadas en pantalla*/


	/*Por cada casilla del mapa*/
	for (x = 0; x < mazeRow; x++) {
		for (y = 0; y < mazeCol; y++) {

			/*Calculamos las coordenadas de pantalla a partir de las de la casilla*/
			/*y el desplazamiento de la camara (scrollX, scrollY)*/
			px = x*TILE_ANCHO;
			py = y*TILE_ALTO;

			/*Dibuja el tile en la pantalla*/
			blitTile (pantalla, px, py, mazeDraw[x][y]);

		}
	}
}


/*Dibuja un tile en la posicion (x, y)*/
void blitTile (SDL_Surface *dest, int x, int y, int nTile) {

	if (nTile >= nTilesX * nTilesY) return;


	SDL_Rect srcRect, destRect;
	destRect.x = x; destRect.y = y;

	srcRect.x = (nTile % nTilesX) * TILE_ANCHO;
	srcRect.y = (nTile / nTilesX) * TILE_ALTO;
	srcRect.w = TILE_ANCHO; srcRect.h = TILE_ALTO;

	SDL_BlitSurface (tiles, &srcRect, dest, &destRect);

}

void hardcodelvl() {
	 int x, y;       /*Casilla del mapa*/
        int px, py; /*Coordenadas en pantalla*/


        /*Por cada casilla del mapa*/
        for (x = 0; x < 20; x++) {
                for (y = 0; y < 20; y++) {

                        /*Calculamos las coordenadas de pantalla a partir de las de la casilla*/
                        /*y el desplazamiento de la camara (scrollX, scrollY)*/
                        px = x*TILE_ANCHO;
                        py = y*TILE_ALTO;

                        /*Dibuja el tile en la pantalla*/
                        blitTile (pantalla, py, px, hlvl[x][y]);

                }
        }

}

void drawPlayer(){
	
animacion();
	
	SDL_Rect srcRect, destRect;
        destRect.x = 50; destRect.y = 50;

        srcRect.x = CurrentFrame * 64;
        srcRect.y = 0;
        srcRect.w = 64; srcRect.h = 64;
	
	SDL_BlitSurface (player, &srcRect, pantalla, &destRect);
	
}

void animacion(){
if(OldTime + FrameRate > SDL_GetTicks()) {
        return;
    }
 
    OldTime = SDL_GetTicks();
 
    CurrentFrame += FrameInc;
	 
    if(CurrentFrame > MaxFrames-1) {
            CurrentFrame = 0;
    }

}
