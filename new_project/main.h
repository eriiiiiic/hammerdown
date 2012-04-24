#ifndef MAINH
#define MAINH

#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

//Dimensiones de los tiles
#define TILE_ANCHO	32
#define TILE_ALTO	32

//Buffer de la Pantalla
SDL_Surface *pantalla = NULL;

//Superficie con los tiles
SDL_Surface *tiles = NULL;

//Superficie con el cursor
SDL_Surface *flecha = NULL;

//Numero de tiles en la superficie
int nTilesX, nTilesY;
int iniciar ();
void limpiar ();
void dibujar ();
void dibujarMapa ();
void blitTile (SDL_Surface *dest, int x, int y, int nTile);
void drawPlayer ();
void hardcodelvl();

#endif
