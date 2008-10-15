//headers
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdio.h>
#include <math.h>

//screen main attributes
const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int SCREEN_BPP = 32;

const float PI = 3.1416;

int DRAW_W = 800*3/4;
int DRAW_H = 600*3/4;

int init_GL()
{	
    //set clear color
    glClearColor( 0, 0, 0, 0 );
    
    //set the viewport
    glViewport(0, 0, SCREEN_W, SCREEN_H);
    
    //set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, SCREEN_W, SCREEN_H, 0, -1, 1 );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    //translada hacia el fondo
    glTranslatef( DRAW_W/8, DRAW_H, 0.0f );
    //rota en x 180 grados
    glRotatef(180,1,0,0);
    //if there was any errors
    if( glGetError() != GL_NO_ERROR )
    {
        return 0;    
    }
    
    //if everything initialized
    return 1;
}

int init()
{
    //initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return 0;    
    }
    
    //create Window
    if( SDL_SetVideoMode( SCREEN_W, SCREEN_H, SCREEN_BPP, SDL_OPENGL ) == NULL )
    {
        return 0;
    }
    
    //initialize OpenGL
    if( init_GL() == 0 )
    {
        return 0;    
    }
    
    //set caption
    SDL_WM_SetCaption( "OpenGL Test", NULL );
    
    return 1;    
}

void dibuja_plano(int x, int y)
{
    int baseX = 150;
    int baseY = 150;
    
    // clear the screen before drawing:
    glClear( GL_COLOR_BUFFER_BIT );
    
    // draw the line
    glBegin(GL_TRIANGLES);
        
		//dibuja plano
		glVertex3f( 0, 1, 0 );
		glVertex3f( x, y, 0 );
    glVertex3f( x, 1, 0 );
    
    glEnd();
}

void dibuja_limites()
{
  // draw the line
    glBegin(GL_LINES);
        
		//dibuja plano
		glVertex3f( -DRAW_W/8, 0, 0 );
		glVertex3f( DRAW_W, 0, 0 );
		glVertex3f( DRAW_W, 0, 0 );
    glVertex3f( DRAW_W, DRAW_H, 0 );

    glEnd();

}

void dibuja_cuadrado(double x, double y, int sq){
	float theta = atan2(y, x); //angulo del vector
	int magnitud = sq;				 //magnitud del vector
	int magnitud2 = sqrt(2)*magnitud;
	double a1[4], b1[4];	

	//obtengo los puntos
	a1[0] = magnitud*cos( theta ); 
	b1[0] = magnitud*sin( theta );
	
	//obtengo los angulos
	theta += PI/4;
        
	//obtengo los puntos
	a1[1] = magnitud2*cos( theta ); 
	b1[1] = magnitud2*sin( theta );

  //obtengo los angulos
	theta += PI/4;
	//obtengo los puntos
	a1[2] = magnitud*cos( theta ); 
	b1[2] = magnitud*sin( theta );
	
	//obtengo los puntos
	a1[3] = 0;
	b1[3] = 0;


  //dibuja cuadrado
  glBegin(GL_QUADS);

	glColor3f( 1.0f, 0.0f, 0.0f ); /* Red                           */
  int i;
  for(i = 0; i < 4; i++)
	{     
		glVertex3f( a1[i] + x , b1[i] + y, 0 );
	}
	glColor3f( 1.0f,  1.0f,  1.0f ); /* White                         */

  glEnd();
}

void dibuja_flecha(int x1, int y1){
	float theta = atan2(y1, x1); //angulo del vector
  int magnitud = 20;//magnitud del vector
	float a1=0, b1 = 0;
	float a2=0, b2 = 0; 
	
	//valores del vector flecha
	//obtengo los angulos en radianes
	float phi1 = theta + 210;
	float phi2 = theta - 210;

	//obtengo los puntos y le sumo el valor del punto P(x1,y1)
	//para obtener una representacion particular
	a1 = magnitud*cos( phi1 ) + x1; b1 = magnitud*sin( phi1 ) + y1;
	a2 = magnitud*cos( phi2 ) + x1; b2 = magnitud*sin( phi2 ) + y1;
	
       //dibuja la lineas de la flecha
       glVertex3f ( x1, y1, 0);   
       glVertex3f ( a1, b1, 0);  
       glVertex3f ( x1, y1, 0);
       glVertex3f ( a2, b2, 0);
}

void draw_line(int x, int y)
{
  glBegin(GL_LINES);    
		//dibuja lineas
		glVertex3f( x, y+30, 0 );
    glVertex3f( x, y, 0 );
    dibuja_flecha(x,y);
  glEnd();
}

int main(int argc, char *argv[])
{
    int quit = 0;
		int x = 415, y= 245;
		double posX=x*0.85	, posY=y*0.85; 
    int square_size=50;
		//initialize
    if( init() == 0 )
    {
        return 1;    
    }    

    SDL_Surface *screen;
    SDL_Event event; //the event structure
    //while the user hasn't quit
    while( quit == 0 )
    {

		//if there's events to handle
        if( SDL_PollEvent( &event ) )
        {
            //if the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //quit the program
                quit = 1;
            }    
    	}
     
     dibuja_plano(x, y);
     dibuja_limites();
		 if( posY > 1 && posX > 1)
		 {
		 	if(y > x){
				posX-= 0.1*y/x;	
				posY-= 0.1;
			}else{
				posX-= 0.1;	
				posY-= 0.1*y/x;
	 	  }
		 }
		 dibuja_cuadrado( posX, posY, square_size );
     SDL_GL_SwapBuffers(); 
     
     }
    
    
    SDL_Quit();
    
    return 0;
}
