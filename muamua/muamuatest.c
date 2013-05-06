#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <string.h>

#define true 1;
#define false 0;


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
    

SDL_Surface *screen = NULL;
SDL_Surface *actor = NULL;
SDL_Surface *background = NULL;
    



int quit = true;

int init(char *title){
    
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1)
        return true;
    
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    
    if(!screen)
        return true;

    
    SDL_WM_SetCaption(title, NULL);

    
    return false;
}

SDL_Surface *load_image( char *filename ){
    
    SDL_Surface* loadedImage = NULL;

    
    SDL_Surface* optimizedImage = NULL;

    
    loadedImage = IMG_Load( filename );

    
  /*  if( loadedImage ){
        
        optimizedImage = SDL_DisplayFormat( loadedImage );

        
        SDL_FreeSurface( loadedImage );

        
        if( optimizedImage ){
            
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0, 0xFF );

            
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    }*/
    
    return loadedImage;
}
void move( int *x, int *y){
    
    SDL_Event event;  
    while(SDL_PollEvent( &event )){printf("lol"); } 
    int speed = 2;
/*event.key.keysym.sym mantiene el valor hasta que otra tecla sea presionada y aunque se redeclare la variable event*/
    if( event.key.keysym.sym == SDLK_a )
       { *y -= speed;}
    /*if( keystates[SDLK_DOWN] )
        *y += speed;
    if( keystates[SDLK_LEFT] )
        *x -= speed;
    if( keystates[SDLK_RIGHT] )
        *x += speed;*/
}

void is_out(int *x, int *y){
    
    if(*x < 0)
        *x = 0;
    
    if(*x + 49 > SCREEN_WIDTH)
        *x = SCREEN_WIDTH - 49;
    
    if(*y < 0)
        *y = 0;
    
    if(*y + 104 > SCREEN_HEIGHT)
        *y = SCREEN_HEIGHT - 104;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ){
    
    SDL_Rect offset;

    
    offset.x = x;
    offset.y = y;

    
    SDL_BlitSurface( source, NULL, destination, &offset );
}

int load_files(){
    
    background = load_image( "background.png" );

    
    if(!background)
        return true;

    
    actor = load_image( "actor.png" );

    
    if(!actor)
        return true;

    return false;
}

void clean_up(){
    
    SDL_Quit();

    
    SDL_FreeSurface( actor );
    SDL_FreeSurface( background );
}

int main(){
    if (init("MUAMUAMUAMAMAMA")){
        printf("Error al Iniciar");
        return 1;
    }
    
    
    int x = 100, y = 100;

    if(load_files())
        return 1;
    
    
    while(quit){
        
        Uint8 *keystates = SDL_GetKeyState( NULL );
        if( keystates[ SDLK_ESCAPE ] )
            break;
            
        /*while( SDL_PollEvent( &event ) ){
           printf("lol"); 
            if( event.type == SDL_QUIT ){
                
                quit = false;
            }
        }*/
        
        move(&x, &y);
        
        is_out(&x, &y);
        apply_surface( 0, 0, background, screen );
        apply_surface( x, y, actor, screen );
        SDL_Flip( screen );
    }
    clean_up();   
    return 0;
}
