//headers
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdio.h>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//function prototypes
void draw_line(int, int);
void maneja_eventos();

int main(int argc, char *argv[])
{
    int quit = 0;

    //Initialize
    if( init() == 0 )
    {
        return 1;    
    }    

    SDL_Surface *screen;
    SDL_Event event; //The event structure
	
    //escucha de eventos    
    //While the user hasn't quit
    while( quit == 0 )
    {
        //If there's events to handle
        if( SDL_PollEvent( &event ) )
        {
            //The mouse offsets
	    int x = 0, y = 0;
    
            //If the mouse moved
            if( event.type == SDL_MOUSEMOTION )
            { 
                //Get the mouse offsets
                x = event.motion.x;
                y = event.motion.y;    
                draw_line(x,y);
            }
             
	  //  if (even.type == SDL_MOUSEBUTTONDOWN)

            SDL_GL_SwapBuffers(); 
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = 1;
            }    
        }
    }	
    
    SDL_Quit();
    
    return 0;
}

int init_GL()
{	
    //Set clear color
    glClearColor( 0, 0, 0, 0 );
    
    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1 );
    
    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    //If there was any errors
    if( glGetError() != GL_NO_ERROR )
    {
        return 0;    
    }
    
    //If everything initialized
    return 1;
}

int init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return 0;    
    }
    
    //Create Window
    if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL ) == NULL )
    {
        return 0;
    }
    
    //Initialize OpenGL
    if( init_GL() == 0 )
    {
        return 0;    
    }
    
    //Set caption
    SDL_WM_SetCaption( "OpenGL Test", NULL );
    
    return 1;    
}

void draw_line(int x, int y)
{
    // Clear the screen before drawing
    glClear( GL_COLOR_BUFFER_BIT );
    
    float lineWidth = 1.0;
    // set the line width
    glLineWidth(lineWidth);

    // draw the line
    glBegin(GL_LINES);
     	
	//eje x
	glVertex3f( SCREEN_WIDTH/2, 20, 0 );
	glVertex3f( SCREEN_WIDTH/2,SCREEN_HEIGHT - 20, 0 );
	//eje y
	glVertex3f( SCREEN_WIDTH - 20, SCREEN_HEIGHT/2, 0 );
	glVertex3f( 20, SCREEN_HEIGHT/2,0 );
	
	//dibuja lineas
	glVertex3f( 100, 100, 0 );
     	glVertex3f( x, y, 0 );
    glEnd();
}
