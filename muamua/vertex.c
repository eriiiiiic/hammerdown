/*
 * This code was created by Jeff Molofee '99 
 * (ported to Linux/SDL by Ti Leggett '01)
 *
 * If you've found this code useful, please let me know.
 *
 * Visit Jeff at http://nehe.gamedev.net/
 * 
 * or for port-specific comments, questions, bugreports etc. 
 * email to leggett@eecs.tulane.edu
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

/* screen width, height, and bit depth */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

/* Define our booleans */
#define TRUE  1
#define FALSE 0

#define X .525731112119133606
#define Z .850650808352039932

/* This is our SDL surface */
SDL_Surface *surface;

/* function to release/destroy our resources and restoring the old desktop */
void Quit( int returnCode )
{
    /* clean up the window */
    SDL_Quit( );

    /* and exit appropriately */
    exit( returnCode );
}

/* function to reset our viewport after a window resize */
int resizeWindow( int width, int height )
{
    /* Height / width ration */
    GLfloat ratio;
 
    /* Protect against a divide by zero */
   if ( height == 0 )
	height = 1;

    ratio = ( GLfloat )width / ( GLfloat )height;

    /* Setup our viewport. */
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );

    return( TRUE );
}

/* function to handle key press events */
void handleKeyPress( SDL_keysym *keysym )
{
    switch ( keysym->sym )
	{
	case SDLK_ESCAPE:
	    /* ESC key was pressed */
	    Quit( 0 );
	    break;
	case SDLK_F1:
	    /* F1 key was pressed
	     * this toggles fullscreen mode
	     */
	    SDL_WM_ToggleFullScreen( surface );
	    break;
	default:
	    break;
	}

    return;
}

/* general OpenGL initialization function */
int initGL( GLvoid )
{

    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Depth buffer setup */
    glClearDepth( 1.0f );

    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    return( TRUE );
}
/*
void get_dual( float vertices[][], int vindex[][], float vdual[][] ){
	
	int i=0;
	for (i = 0; i < 20; i++) {
           vdual[i][0] = (vdata[tindices[i][0]][0] + vdata[tindices[i][1]][0] + vdata[tindices[i][2]][0])/3;
           vdual[i][1] = (vdata[tindices[i][0]][0] + vdata[tindices[i][1]][0] + vdata[tindices[i][2]][0])/3;
           vdual[i][2] = (vdata[tindices[i][0]][0] + vdata[tindices[i][1]][0] + vdata[tindices[i][2]][0])/3;
    	}
}*/

/* Here goes our drawing code */
int drawGLScene( GLvoid )
{
    /* rotational vars for the triangle and quad, respectively */
    static GLfloat rtri, rquad;
    /* These are to calculate our fps */
    static GLint T0     = 0;
    static GLint Frames = 0;


    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    glTranslatef( -1.5f, 0.0f, -6.0f );

    /* Rotate The Triangle On The Y axis ( NEW ) */
    glRotatef( rtri, 0.0f, 1.0f, 0.0f );	
	
    float vdual[20][3] = {0};
    
    /*float distance[1000] = {0}; fuck it 1000*/
    
    float vdata[12][3] = {
            {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
            {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
            {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}};
    int tindices[20][3] = {
            {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
            {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
            {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
            {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };
    
    float pentagon[12][8][3]= {0} ;
    int i;
    int j;
    int w;
    

    for (i = 0; i < 20; i++) {
       vdual[i][0] = (vdata[tindices[i][0]][0] + vdata[tindices[i][1]][0] + vdata[tindices[i][2]][0])/3;
       vdual[i][1] = (vdata[tindices[i][0]][1] + vdata[tindices[i][1]][1] + vdata[tindices[i][2]][1])/3;
       vdual[i][2] = (vdata[tindices[i][0]][2] + vdata[tindices[i][1]][2] + vdata[tindices[i][2]][2])/3;
    }

  /*  float x, y, z;
    for (w = 0; w < 12; w++){
        int vcont=0;
	for (i = 0; i < 20; i++) {
        	for(j = i + 1; j < 20; j++){
			x = vdual[j][0] - vdual[i][0];
			y = vdual[j][1] - vdual[i][1];
			z = vdual[j][2] - vdual[i][2];
			pentagon[w][vcont][0]=vdual[i][0];
                        pentagon[w][vcont][1]=vdual[i][1]; 
                        pentagon[w][vcont][2]=vdual[i][2];
			if ( ((vdata[w][0]*x) + (vdata[w][1]*y) + (vdata[w][2]*z)) == 0  ){ 
			    vcont++;
			    pentagon[w][vcont][0]=vdual[j][0];
		            pentagon[w][vcont][1]=vdual[j][1]; 
			    pentagon[w][vcont][2]=vdual[j][2];
			}
		}
	}
	 
    }*/

/*Saco distancias entre las combinaciones de pares de vertices
     for (i = 0; i < 20; i++) {
	for(j = i + 1, j < 20, j++)
	 distance[i][j] = sqrt(pow(vdual[i][0] - vdual[j][0], 2) +	 
	      pow(vdual[i][1] - vdual[j][1], 2) +  
              pow(vdual[i][2] - vdual[j][2], 2), 2);
     }


      int lower_distance=distance[0];
      for (i = 0; i < dcounter; i++) {
	if (distance[i+1] < lower_distance)
	       lower_distance = distance[i+1]; 		
      }
*/
   glBegin(GL_TRIANGLES);
    for (i = 0; i < 20; i++) {
            glColor3f(   1.0f,  0.0f,  0.0f ); // Red  
            glVertex3fv(&vdata[tindices[i][0]][0]);
             glColor3f(   0.0f,  1.0f,  0.0f ); // Green 
	    glVertex3fv(&vdata[tindices[i][1]][0]);
	     glColor3f(   0.0f,  0.0f,  1.0f ); // Blue
            glVertex3fv(&vdata[tindices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_POINTS);
    for (i = 0; i < 20; i++) {
            glColor3f(   1.0f,  1.0f,  1.0f );
            glVertex3f(vdual[i][0], vdual[i][1], vdual[i][2]);
    }
    glEnd();
    //printf("%f", pentagon[0][0][0]);

   /* glBegin(GL_POLYGON);
    for (i = 0; i < 2; i++) {
            glColor3f(   1.0f,  0.0f,  0.0f );
            glVertex3f(pentagon[i][0][0], pentagon[i][0][1], pentagon[i][0][2] );
             glColor3f(   0.0f,  1.0f,  0.0f );
            glVertex3f(pentagon[i][1][0], pentagon[i][1][1], pentagon[i][1][2] );
             glColor3f(   0.0f,  0.0f,  1.0f );
            glVertex3f(pentagon[i][2][0], pentagon[i][2][1], pentagon[i][2][2] );
             glColor3f(   0.0f,  1.0f,  0.0f ); 
            glVertex3f(pentagon[i][3][0], pentagon[i][3][1], pentagon[i][3][2] );
             glColor3f(   1.0f,  0.0f,  0.0f ); 
            glVertex3f(pentagon[i][4][0], pentagon[i][4][1], pentagon[i][4][2] );		
    }
    glEnd();

*/
    /* Draw it to the screen */
    SDL_GL_SwapBuffers( );

    /* Gather our frames per second */
    Frames++;
    {
	GLint t = SDL_GetTicks();
	if (t - T0 >= 5000) {
	    GLfloat seconds = (t - T0) / 1000.0;
	    GLfloat fps = Frames / seconds;
	    printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
	    T0 = t;
	    Frames = 0;
	}
    }

    /* Increase The Rotation Variable For The Triangle ( NEW ) */
    rtri  += 0.2f;
    /* Decrease The Rotation Variable For The Quad     ( NEW ) */
    rquad -=0.15f;

    return( TRUE );
}


int main( int argc, char **argv )
{
    /* Flags to pass to SDL_SetVideoMode */
    int videoFlags;
    /* main loop variable */
    int done = FALSE;
    /* used to collect events */
    SDL_Event event;
    /* this holds some info about our display */
    const SDL_VideoInfo *videoInfo;
    /* whether or not the window is active */
    int isActive = TRUE;

    /* initialize SDL */
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
	    fprintf( stderr, "Video initialization failed: %s\n",
		     SDL_GetError( ) );
	    Quit( 1 );
	}

    /* Fetch the video info */
    videoInfo = SDL_GetVideoInfo( );

    if ( !videoInfo )
	{
	    fprintf( stderr, "Video query failed: %s\n",
		     SDL_GetError( ) );
	    Quit( 1 );
	}

    /* the flags to pass to SDL_SetVideoMode */
    videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
    videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

    /* This checks to see if surfaces can be stored in memory */
    if ( videoInfo->hw_available )
	videoFlags |= SDL_HWSURFACE;
    else
	videoFlags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if ( videoInfo->blit_hw )
	videoFlags |= SDL_HWACCEL;

    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* get a SDL surface */
    surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
				videoFlags );

    /* Verify there is a surface */
    if ( !surface )
	{
	    fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
	    Quit( 1 );
	}

    /* initialize OpenGL */
    initGL( );

    /* resize the initial window */
    resizeWindow( SCREEN_WIDTH, SCREEN_HEIGHT );

    /* wait for events */ 
    while ( !done )
	{
	    /* handle the events in the queue */

	    while ( SDL_PollEvent( &event ) )
		{
		    switch( event.type )
			{
			case SDL_ACTIVEEVENT:
			    /* Something's happend with our focus
			     * If we lost focus or we are iconified, we
			     * shouldn't draw the screen
			     */
			    if ( event.active.gain == 0 )
				isActive = FALSE;
			    else
				isActive = TRUE;
			    break;			    
			case SDL_VIDEORESIZE:
			    /* handle resize event */
			    surface = SDL_SetVideoMode( event.resize.w,
							event.resize.h,
							16, videoFlags );
			    if ( !surface )
				{
				    fprintf( stderr, "Could not get a surface after resize: %s\n", SDL_GetError( ) );
				    Quit( 1 );
				}
			    resizeWindow( event.resize.w, event.resize.h );
			    break;
			case SDL_KEYDOWN:
			    /* handle key presses */
			    handleKeyPress( &event.key.keysym );
			    break;
			case SDL_QUIT:
			    /* handle quit requests */
			    done = TRUE;
			    break;
			default:
			    break;
			}
		}

	    /* draw the scene */
	    if ( isActive )
		drawGLScene( );
	}

    /* clean ourselves up and exit */
    Quit( 0 );

    /* Should never get here */
    return( 0 );
}
