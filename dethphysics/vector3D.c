//headers
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdio.h>
#include <math.h>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//function prototypes
void draw_line(int, int, int, int vectores[][2]);
void draw_axis();
void draw_vectors(int, int vectores[][2]);
void dibuja_flecha(int, int);

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
    int cantidad = 0; // cantidad de vectores
    int vectores[1000][2]; //arreglo de vectores
    glRotatef(15, 1.0, 0.0, 0.0);
    glRotatef(-25, 0.0, 1.0, 0.0); 
    glBegin(GL_LINES);
    draw_axis();
    glEnd();
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
                x = x - SCREEN_WIDTH/2; 
		y = SCREEN_HEIGHT/2 - y;
		draw_line(x, y, cantidad, vectores);
            }
             
	    if (event.type == SDL_MOUSEBUTTONDOWN)
	    {   
	    	if( event.button.button == SDL_BUTTON_LEFT )
		{
	    	   vectores[cantidad][0] = event.button.x; 
		   vectores[cantidad][1] = event.button.y;
		   cantidad++;
		}
	    }
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
   
    //reset the viewport
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat) SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);
    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    glTranslatef( 0.0f, 0.0f, -500.0f );
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

void draw_line(int x, int y, int cantidad, int vectores [][2])
{
    // Clear the screen before drawing:
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  );
    
    // draw the line
    glBegin(GL_LINES);
     	
        draw_axis();
        draw_vectors(cantidad, vectores);
	
	//dibuja lineas
	glVertex3f( 0, 0, 0 );
     	glVertex3f( x, 0, -1*y );
        dibuja_flecha(x,y);
   
    glEnd();
}

void draw_vectors(int cantidad, int vectores[][2])
{
     int i=0; 
     while(i < cantidad && (cantidad != 0))
     {
	 glVertex3f( 0, 0, 0 ); 
	 glVertex3f( vectores[i][0], vectores[i][1], 0 );
	 i++;
     }
}

void draw_axis()
{	
	//eje x
        glVertex3f( SCREEN_WIDTH/2 - 100, 0, 0 );
        glVertex3f( -1*SCREEN_WIDTH/2 + 50, 0, 0 );

	//eje y
        glVertex3f( 0, SCREEN_HEIGHT/2 - 60 , 0 );
        glVertex3f( 0, -1*SCREEN_HEIGHT/2 + 30,0 );

	//eje z
	 glVertex3f( 0, 0, SCREEN_HEIGHT/2 - 50);
	 glVertex3f( 0, 0, -2*SCREEN_HEIGHT/2 );
	
}

void dibuja_flecha(int x1, int y1){
        int x = x1;
	int y = y1;
	float theta = atan2(y, x); //angulo del vector
        int magnitud = 20;//magnitud del vector
	float a1=0, b1 = 0; //
	float a2=0, b2 = 0; 
	
	//valores del vector flecha
	//obtengo los angulos
	float phi1 = theta + 210;
	float phi2 = theta - 210;

	//obtengo los puntos y le sumo el valor del punto P(x1,y1)
	//para obtener una representacion particular
	a1 = magnitud*cos( phi1 ) + x1; b1 = magnitud*sin( phi1 ) + y1;
	a2 = magnitud*cos( phi2 ) + x1; b2 = magnitud*sin( phi2 ) + y1;
	
       //dibuja la lineas de la flecha
       glVertex3f ( x1, 0, -y1);   
       glVertex3f ( a1, 0, -b1);  
       glVertex3f ( x1, 0, -y1);
       glVertex3f ( a2, 0, -b2);
}
