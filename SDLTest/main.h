
#ifndef MAINH
#define MAINH

#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"

//Dimensiones de los tiles
#define TILE_ANCHO	64
#define TILE_ALTO	32

//Buffer de la Pantalla
SDL_Surface *pantalla = NULL;

//Superficie con los tiles
SDL_Surface *tiles = NULL;

//Superficie con el cursor
SDL_Surface *flecha = NULL;

//Posicion original de la camara
int scrollX = -350;
int scrollY = -80;

//Posicion original del cursor
int cursorX = 50;
int cursorY = 50;

//Numero de tiles en la superficie
int nTilesX, nTilesY;
int iniciar ();
void limpiar ();
void dibujar ();
void dibujarMapa ();
void dibujarCursor (int x, int y);
void blitTile (SDL_Surface *dest, int x, int y, int nTile);

#endif
