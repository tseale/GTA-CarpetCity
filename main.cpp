/*
 *  CSE 40166 / 60166, Computer Graphics, Fall 2012
 *
 *  Project: Sweet Ride Bro
 *  File: main.cpp
 *
 *  Description:
 *      Drive your new whip around a parking lot
 *
 *  Author:
 *      Taylor Seale, University of Notre Dame.
 */

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

 #include "porsche944.h"
 #include "police.h"
 #include "skybox.h"
 #include "camera.h"
 #include "texture.h"
 #include "moneyCrate.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 #include <time.h>
 #include <vector>
#include <iostream>
using namespace std;
#define PI 3.14159265

int windowWidth = 512, windowHeight = 512;
bool keysPressed[255]; // array containing all of the currently pressed keys
int bounds=50; // size of the world
bool gameOver=false;
int score=0;
int health=100;
float healthR=0,healthG=1;
float targsize=10;
int stage=0;
bool stageUp=false;
int transition=30;
bool carCollide=false;
bool moveForward=true,moveBack=true;

camera myCam(50.0, -PI/2, 3*PI/4 ,0,0,0); // create a camera object
camera overheadCam(150.0, -PI/2, PI,0,0,0);  // first person camera object

porsche944 porsche(5,0.5,5,0,1);
skybox *sky;
vector<moneyCrate*> cash;
vector<police*> fuzz; // vector containing all police cars
GLuint groundTexHandle;

void drawGround() {
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, groundTexHandle);
        glColor3f(1,1,1);
        glBegin(GL_QUADS);{
            glTexCoord2f( 0, 0 ); glVertex3f(-bounds,0.0,-bounds);
            glTexCoord2f( 1, 0 ); glVertex3f(bounds,0.0,-bounds);
            glTexCoord2f( 1, 1 ); glVertex3f(bounds,0.0,bounds);
            glTexCoord2f( 0, 1 ); glVertex3f(-bounds,0.0,bounds);
        };glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void overhead(){
  glMatrixMode(GL_MODELVIEW);             
  glLoadIdentity(); 
  glDrawBuffer( GL_BACK );
  glViewport(windowHeight-windowHeight/3,windowWidth-windowWidth/3,windowWidth/3,windowHeight/3);
  glScissor(windowHeight-windowHeight/3,windowWidth-windowWidth/3,windowWidth/3,windowHeight/3);
  glEnable(GL_SCISSOR_TEST);
  glClearDepth(1.0);
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glDisable(GL_SCISSOR_TEST);
      glPushMatrix();
        overheadCam.update_pos_arcball();
        glPushMatrix(); {
            sky->drawSkybox(200, 200, 200);               // draw our axes so we know how we are oriented
        }; glPopMatrix();
        // draw ground
        glPushMatrix(); {
            drawGround();
        }; glPopMatrix();

        // draw the car based on the world object coordinates controlled by user interaction
        glPushMatrix(); {
            glTranslatef(porsche.getX(), porsche.getY(), porsche.getZ());
            glColor3f(1,1,1);
            glutSolidSphere(3, 10, 10);
        };glPopMatrix();

        for (unsigned int i=0; i<cash.size(); i++){
            glPushMatrix(); {
                glTranslatef(cash.at(i)->getX(),cash.at(i)->getY(),cash.at(i)->getZ());
                glColor3f(0.6,0.4,0.2);
                glutSolidCube(targsize);
            };glPopMatrix();
        }

        for (unsigned int i=0; i<fuzz.size(); i++){
            if (fuzz.at(i)->getY()>-10){
                glPushMatrix(); {
                  glTranslatef(fuzz.at(i)->getX(), fuzz.at(i)->getY(), fuzz.at(i)->getZ());
                  if (fuzz.at(i)->inPursuit){
                    glColor3f(fuzz.at(i)->r,0,fuzz.at(i)->b);
                  }else{
                    glColor3f(0,0,0);
                  }
                  glutSolidSphere(3, 10, 10);
                }; glPopMatrix();
            }
        }

      glPopMatrix();
  glMatrixMode(GL_PROJECTION);
}

void resizeWindow(int w, int h){
    float aspectRatio = w / (float)h;
	
    windowWidth = w;
    windowHeight = h;

    //update the viewport to fill the window
    glViewport( 0, 0, w, h );

    //update the projection matrix with the new window properties
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    /* TODO: set up the proper projection */
	// gluPerspective( fovy, a, near, far );
	// glOrtho( left, right, bottom, top, near, far );
	
	/* Questions to consider */
	/* ? What happens if you alter the vertical field of view?
	 * ? What happens if you alter the aspect ratio?
	 * ? What happens if you alter the near or far clipping planes?
	 */
	gluPerspective( 45.0f, aspectRatio, 0.1, 1000 );
}

void renderScene(void){
    //update the modelview matrix based on the camera's position
    glMatrixMode(GL_MODELVIEW);             //make sure we aren't changing the projection matrix!
    glLoadIdentity();

    glDrawBuffer( GL_BACK );
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport( 0, 0, windowWidth, windowHeight);
    glPushMatrix();

        myCam.set_atx(porsche.getX());
        myCam.set_aty(porsche.getY());
        myCam.set_atz(porsche.getZ());
        myCam.set_eyex(porsche.getX());
        myCam.set_eyez(porsche.getZ());
        myCam.update_pos_arcball();

        glPushMatrix(); {
            sky->drawSkybox(200, 200, 200);               // draw our axes so we know how we are oriented
        }; glPopMatrix();

        // draw ground
        glPushMatrix(); {
            drawGround();
        }; glPopMatrix();

        for (unsigned int i=0; i<cash.size(); i++){
            glPushMatrix(); {
                cash.at(i)->drawCrate();
            };glPopMatrix();
        }

        // draw the car based on the world object coordinates controlled by user interaction
    	glPushMatrix(); {
      		glTranslatef(porsche.getX(), porsche.getY(), porsche.getZ());
      		glRotatef(porsche.getTheta(), 0.0, 1.0, 0.0);       //Rotate about the y-axis
      		glTranslatef(-porsche.getX(), -porsche.getY(), -porsche.getZ());
      		porsche.drawCar();	// draw our dodecahedron...or torus...teapot...or whatever
        }; glPopMatrix();

        // draw the car based on the world object coordinates controlled by user interaction
        for (unsigned int i=0; i<fuzz.size(); i++){
            glPushMatrix(); {
              glTranslatef(fuzz.at(i)->getX(), fuzz.at(i)->getY(), fuzz.at(i)->getZ());
              glRotatef(fuzz.at(i)->getTheta(), 0.0, 1.0, 0.0);
              glTranslatef(-fuzz.at(i)->getX(), -fuzz.at(i)->getY(), -fuzz.at(i)->getZ());
              fuzz.at(i)->drawCar();
            }; glPopMatrix();
        }
    glPopMatrix();

    glClear(GL_FRAMEBUFFER | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);

    glDisable(GL_LIGHTING);
    glPushMatrix();
      glOrtho(-1,1,-1,1,-1,1);
        int locationX,locationY;
        if (!gameOver){
            locationX=-15;
            locationY=windowHeight-windowHeight/12;
        }else{
            locationX=windowWidth/2;
            locationY=windowHeight-windowHeight/2;
        }
        glViewport(locationX, locationY, windowWidth/12, windowHeight/12);
        glLoadIdentity();
      glColor3f(1,1,1);
        char c[15];
        sprintf(c, "%d", score);
        string temp=string(c);
      glRasterPos3i(0,0,0);
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'C');
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    for (unsigned int i=0; i<temp.size(); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, temp[i] );
    } 
    glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glPushMatrix();
      glOrtho(-1,1,-1,1,-1,1);
        if (!gameOver){
            locationX=150;
            locationY=windowHeight-windowHeight/12;
        }else{
            locationX=windowWidth/2;
            locationY=windowHeight-windowHeight/2+windowWidth/12;
        }
        glViewport(locationX, locationY, windowWidth/12, windowHeight/12);
        glLoadIdentity();
      glColor3f(healthR,healthG,0);
        char h[15];
        sprintf(h, "%d", health);
        string hea=string(h);
      glRasterPos3i(0,0,0);
      if (!gameOver){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'H');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'L');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
         glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'H');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
        for (unsigned int i=0; i<hea.size(); i++){
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, hea[i] );
        } 
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '%');
    }else{
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'M');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'O');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'V');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
    }
    glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  if (stageUp&&!gameOver){
        glPushMatrix();
          glOrtho(-1,1,-1,1,-1,1);
            glViewport(windowWidth/2-75,windowHeight-windowHeight/2+windowWidth/12, windowWidth/12, windowHeight/12);
            glLoadIdentity();
          glColor3f(1,1,1);
            char s[3];
            sprintf(s, "%d", stage);
            string sta=string(s);
          glRasterPos3i(0,0,0);
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'G');
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
            for (unsigned int i=0; i<sta.size(); i++){
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, sta[i] );
            } 
        glMatrixMode(GL_PROJECTION);
      glPopMatrix();
    }

  if (!gameOver){
    glPushMatrix();
        overhead();
    glPopMatrix();
  }
  glMatrixMode(GL_MODELVIEW);
  glFlush();
  //push the back buffer to the screen
  glutSwapBuffers();
}

void keysDown(unsigned char key, int x, int y){
	// they can exit regardless using the 'ESC' key
	if (key==27){
		exit(0);
	}
	// if a key is pressed, set the index value in keysPressed to TRUE
	keysPressed[ key ] = true;
}

void keysUp(unsigned char key, int x, int y){
	// if a key is up set the index value in keysPressed to FALSE
	keysPressed[ key ] = false;
}

void myTimer(int value){
    if (!gameOver){

        if (targsize==10){
            targsize*=1.1;
        }else{
            targsize=10;
        }

        for (unsigned int i=0; i<fuzz.size(); i++){
            fuzz.at(i)->chase(porsche.getX(), porsche.getZ());
            for (unsigned int j=0; j<fuzz.size(); j++){
                if (i==j){continue;}
                if (fuzz.at(i)->collide(fuzz.at(j)->getX(),fuzz.at(j)->getZ(),5)){
                    fuzz.at(i)->setTheta(-1*(fuzz.at(i)->getTheta()));
                    fuzz.at(i)->hit=true;
                    fuzz.at(i)->inPursuit=false;
                }
                if (fuzz.at(i)->hit==true){
                    if ((fuzz.at(i)->engagePursuit(porsche.getX(), porsche.getZ()))<10){
                        fuzz.at(i)->inPursuit=true;
                        fuzz.at(i)->hit=false;
                    }
                }
            }
            if (porsche.collide(fuzz.at(i)->getX(),fuzz.at(i)->getZ(),2)){
                carCollide=true;
                if (health>0){
                    fuzz.at(i)->caught=true;
                    health--;
                    healthR+=0.01;
                    healthG-=0.01;
                }else{
                    gameOver=true;
                }
            }
            if (!porsche.collide(fuzz.at(i)->getX(),fuzz.at(i)->getZ(),2)){
                fuzz.at(i)->caught=false;
            }
        }
    	// if 'a' or 'd' are pressed change the cars heading
    	if (keysPressed[97]){
            porsche.setTheta(porsche.getTheta()+20.0);
    	}
    	if (keysPressed[100]){
    		porsche.setTheta(porsche.getTheta()-20.0);
    	}

    	// if 'w' or 's' are pressed move the car forward or backwards along its heading, but don't let it leave the bounds
        if ((porsche.getX()<bounds)&&(porsche.getX()>-bounds)&&(porsche.getZ()<bounds)&&(porsche.getZ()>-bounds)){
            for (unsigned int i=0; i<fuzz.size(); i++){
                if (fuzz.at(i)->collide(porsche.getX()+cos(-PI*porsche.getTheta()/180.0)*1.25,porsche.getZ()+sin(-PI*porsche.getTheta()/180.0)*1.35,2)){
                    moveForward=false;
                    break;
                }else{
                    moveForward=true;
                }
                if (fuzz.at(i)->collide(porsche.getX()-cos(-PI*porsche.getTheta()/180.0)*1.25,porsche.getZ()-sin(-PI*porsche.getTheta()/180.0)*1.35,2)){
                    moveBack=false;
                    break;
                }else{
                    moveBack=true;
                }
            }
            if (keysPressed[119]&&moveForward){
                porsche.setX(porsche.getX()+cos(-PI*porsche.getTheta()/180.0)*1.35);
                porsche.setZ(porsche.getZ()+sin(-PI*porsche.getTheta()/180.0)*1.35);
            }
            if (keysPressed[115]&&moveBack){
                porsche.setX(porsche.getX()-cos(-PI*porsche.getTheta()/180.0)*1.35);
                porsche.setZ(porsche.getZ()-sin(-PI*porsche.getTheta()/180.0)*1.35);
            }
        }else{
            if (porsche.getY()>-210){
                porsche.setY(porsche.getY()-10);
            }else{
                gameOver=true;
            }
        }

        for (unsigned int i=0; i<fuzz.size(); i++){
            if (!((fuzz.at(i)->getX()<bounds)&&(fuzz.at(i)->getX()>-bounds)&&(fuzz.at(i)->getZ()<bounds)&&(fuzz.at(i)->getZ()>-bounds))){
                // if it has bounced less than twice
                if (fuzz.at(i)->stage==stage){
                    // turn it around
                    fuzz.at(i)->setTheta((fuzz.at(i)->getTheta())+180);
                    // increase bounce counter
                    fuzz.at(i)->bounce++;
                }else{ // if it has bounced more than twice and it hits the boundary
                    // fall off the map
                    if (fuzz.at(i)->getY()>-200){
                        fuzz.at(i)->setY(fuzz.at(i)->getY()-25);
                    }else{
                        fuzz.at(i)->dead=true;
                        fuzz.at(i)->inPursuit=false;
                    }
                }  
            }
        }

        for (unsigned int i=0; i<cash.size(); i++){
            if (cash.at(i)->collide(porsche.getX(),porsche.getY(),porsche.getZ())){
                delete cash.at(i);
                cash.erase(cash.begin()+i);
                score+=100;
            }
        }

        if (cash.size()==0 && stageUp==false){
            stage++;
            stageUp=true;
        }

        if (stageUp){
            transition--;
            if (transition==0){
                stageUp=false;
                transition=30;
                int x,z,xNegRand,zNegRand;
                for (int i=0; i<stage; i++){
                    x=rand()%bounds-2;
                    z=rand()%bounds-2;
                    xNegRand=rand()%2;
                    zNegRand=rand()%2;
                    if (xNegRand==1){x=x*(-1);}
                    if (zNegRand==1){z=z*(-1);}
                    police *cop = new police(x,0.5,z,15,1,stage);
                    fuzz.push_back(cop);
                    moneyCrate *monay = new moneyCrate(x,1,z);
                    cash.push_back(monay);
                }
            }
        }
    }
	// tell GLUT to update the display
    glutPostRedisplay();
	// and register our timer again
    glutTimerFunc((unsigned int)(1000.0 / 15.0), myTimer, 0);
}

void onMouse(int button, int state, int x, int y){

}
 
void onMotion(int x, int y){

}

void registerCallbacks(){
	// ASCII key callback
    glutKeyboardFunc( keysDown );
    glutKeyboardUpFunc(keysUp);
    // Mouse callbacks
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
	// display to screen callback
    glutDisplayFunc( renderScene );
	// window reshape callback
    glutReshapeFunc( resizeWindow );
	// register our timer with GLUT
	glutTimerFunc( (unsigned int)(1000.0 / 15.0), myTimer, 0 );
}

void initScene(){
	// tell OpenGL to perform depth testing with the Z-Buffer to perform hidden
	//		surface removal.  We will discuss this more very soon.
    glEnable( GL_DEPTH_TEST );
	
	//******************************************************************
    // this is some code to enable a default light for the scene;
    // feel free to play around with this, but we won't talk about
    // lighting in OpenGL for another couple of weeks yet.
    float lightCol[4] = { 1, 1, 1, 1};
    float ambientCol[4] = { 0.0, 0.0, 0.0, 1.0 };
    float lPosition[4] = { 10, 10, 10, 1 };
    glLightfv( GL_LIGHT0, GL_POSITION,lPosition );
    glLightfv( GL_LIGHT0, GL_DIFFUSE,lightCol );
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientCol );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
	
    // tell OpenGL not to use the material system; just use whatever we 
    // pass with glColor*()
    glEnable( GL_COLOR_MATERIAL );
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    //******************************************************************

    // tells OpenGL to blend colors across triangles. Once lighting is
    // enabled, this means that objects will appear smoother - if your object
    // is rounded or has a smooth surface, this is probably a good idea;
    // if your object has a blocky surface, you probably want to disable this.
    glShadeModel( GL_SMOOTH );
        //and enable alpha blending once and for all.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char* argv[]){
    // create a double-buffered GLUT window with depth buffer at (50,50) with 
	// predefined windowsize

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition( 50, 50 );
    glutInitWindowSize( windowWidth, windowHeight );
    glutCreateWindow( "Grand Theft HotWheels: Carpet City" );

    sky = new skybox("top.ppm","left.ppm","right.ppm","front.ppm","back.ppm","bottom.ppm");

    unsigned char *groundTexData;
    int texWidth,texHeight;
    readPPM("carcarpetcity.ppm", texWidth, texHeight, groundTexData);
    registerOpenGLTexture(groundTexData, texWidth, texHeight, groundTexHandle);

    srand( time(NULL) );

	// register all of our callbacks with GLUT
	registerCallbacks();
	
    // do some basic OpenGL setup
    initScene();

    // and enter the GLUT loop, never to exit.
    glutMainLoop();

    return(0);
}
