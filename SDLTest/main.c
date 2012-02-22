#include "main.h"
#include "maze.h"

int main (int argc, char *argv[]) {

	/*Inicializa SDL*/
	if (SDL_Init (SDL_INIT_VIDEO) < 0) {
		printf ("SDL_INIT ha fallado\n");
		exit (1);
	}

	atexit (SDL_Quit);

	/*Usamos HW si disponible, double buffering, y pantalla completa*/
	pantalla = SDL_SetVideoMode ( 800, 600, 16, SDL_SWSURFACE | SDL_DOUBLEBUF );

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


		/*Actualizamos la pos. de la camara a partir del cursor*/
		if (cursorX < 8)
			scrollX -= (8 - cursorX);
		if (cursorX > 792)
			scrollX += (cursorX - 792);

		if (cursorY < 8)
			scrollY-= (8 - cursorY);
		if (cursorY > 592)
			scrollY += (cursorY - 592);

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

			/*Movimiento del raton*/
			case SDL_MOUSEMOTION:
				cursorX = ev.motion.x;
				cursorY = ev.motion.y;
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
	SDL_Surface *temp;

	/* Muestra alguna informacion sobre el sistema */ 

	const SDL_VideoInfo *vi;
	vi = SDL_GetVideoInfo ();

	printf ("hw_available: %d\nblit_hw: %d\nblit_hw_CC: %d\nblit_hw_A: %d\nblit_sw: %d\nblit_sw_CC: %d\n"
				"blit_SW_A: %d\nVideo_mem: %d Kb\n",
				vi->hw_available,
				vi->blit_hw,
				vi->blit_hw_CC,
				vi->blit_hw_A,
				vi->blit_sw,
				vi->blit_sw_CC,
				vi->blit_sw_A,
				vi->video_mem);

	/**/

	/*Definimos el clipper*/
	SDL_SetClipRect (pantalla, NULL);

	/*Cargamos los tiles*/
	temp = SDL_LoadBMP ("tiles.bmp");

	if (temp == NULL)
		return 0;

	tiles = SDL_CreateRGBSurface (SDL_HWSURFACE, temp->w, temp->h, vi->vfmt->BitsPerPixel, 
									vi->vfmt->Rmask, vi->vfmt->Gmask, vi->vfmt->Bmask,
									vi->vfmt->Amask);


	SDL_SetColorKey (tiles, SDL_SRCCOLORKEY, 0);

	SDL_BlitSurface (temp, NULL, tiles, NULL);

	SDL_FreeSurface (temp);


	/*Calculamos el total de tiles*/
	nTilesX = tiles->w / TILE_ANCHO;
	nTilesY = tiles->h / TILE_ALTO;


	/*Cargamos la flecha para el cursor*/
	temp = SDL_LoadBMP ("cursor.bmp");

	if (temp == NULL)
		return 0;

	flecha = SDL_CreateRGBSurface (SDL_SWSURFACE, temp->w, temp->h, vi->vfmt->BitsPerPixel, 
									vi->vfmt->Rmask, vi->vfmt->Gmask, vi->vfmt->Bmask,
									vi->vfmt->Amask);


	SDL_SetColorKey (flecha, SDL_SRCCOLORKEY, 0);

	SDL_BlitSurface (temp, NULL, flecha, NULL);

	SDL_FreeSurface (temp);


	/*Muestra informacion indicando en que memoria estan las superficies*/

	if ((tiles->flags & SDL_HWSURFACE) == 1)
		printf ("TILES en HW\n");
	else
		printf ("TILES en SW\n");

	if ((flecha->flags & SDL_HWSURFACE) == 1)
		printf ("FLECHA en HW\n");
	else
		printf ("FLECHA en SW\n");
	
	return 1;
}


/*Limpia la memoria*/
void limpiar () {

	printf ("Limpiando...\n");

	if (tiles != NULL) {
		SDL_FreeSurface (tiles);
		tiles = NULL;
	}
	if (flecha != NULL) {
		SDL_FreeSurface (flecha);
		flecha = NULL;
	}

}


/*Dibuja el mapa y el cursor*/
void dibujar () {

	/*Limpia la pantalla*/
	SDL_FillRect (pantalla, NULL, 0);


	dibujarMapa();
	dibujarCursor (cursorX, cursorY);

	/*Intercambia los buffers*/
	SDL_Flip (pantalla);

}


/*Dibuja los tiles del mapa*/
void dibujarMapa () {

	int x, y;	/*Casilla del mapa*/
	int px, py; /*Coordenadas en pantalla*/


	/*Por cada casilla del mapa*/
	for (y = 0; y < mazeRow; y++) {
		for (x = 0; x < mazeCol; x++) {

			/*Calculamos las coordenadas de pantalla a partir de las de la casilla*/
			/*y el desplazamiento de la camara (scrollX, scrollY)*/
			px = (x - y)*(TILE_ANCHO/2) - scrollX;
			py = (x + y)*(TILE_ALTO/2) - scrollY;

			/*Dibuja el tile en la pantalla*/
			blitTile (pantalla, px, py, mazeDraw[x][y]);

		}
	}
}


/*Dibuja la flecha del cursor*/
void dibujarCursor (int x, int y) {

	SDL_Rect dRect;
	dRect.x = x; dRect.y = y;
	dRect.w = dRect.h = 16;

	SDL_BlitSurface (flecha, NULL, pantalla, &dRect);

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
