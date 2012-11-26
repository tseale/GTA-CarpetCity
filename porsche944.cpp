// porsche944.cpp
// Taylor Seale
// implementation for a Porsche 944

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#define PI 3.14159
#include <math.h>
#include "porsche944.h"

porsche944::porsche944(float x,float y,float z,float theta,float size){
	carX=x;
	carY=y;
	carZ=z;
	carTheta=theta;
	carSize=size;
}

void porsche944::drawBody(float size) {
	// draw the body of the car
    glDisable(GL_LIGHTING);
        glColor3f(0.6,0.0,0.0);
        glBegin(GL_QUADS);{
  			// draw top right of body
  			glVertex3f(carX,carY+size,carZ-size/2);
  			glVertex3f(carX,carY,carZ-size/2);
  			glVertex3f(carX-size/2, carY, carZ-size/2);
  			glVertex3f(carX-size/2,carY+size,carZ-size/2.0);
        };glEnd();
        glBegin(GL_QUADS);{
  			// draw bottom right of body
			glVertex3f(carX+1.5*size,carY+size/2.0,carZ-size/2);
  			glVertex3f(carX+1.5*size,carY,carZ-size/2);
  			glVertex3f(carX-size,carY,carZ-size/2);
  			glVertex3f(carX-size,carY+size/2.0,carZ-size/2);
        };glEnd();
        glBegin(GL_QUADS);{
  			// draw top left of body
  			glVertex3f(carX,carY+size,carZ+size/2);
  			glVertex3f(carX,carY,carZ+size/2);
  			glVertex3f(carX-size/2, carY, carZ+size/2);
  			glVertex3f(carX-size/2,carY+size,carZ+size/2.0);
        };glEnd();
        glBegin(GL_QUADS);{
  			// draw bottom left of body
			glVertex3f(carX+1.5*size,carY+size/2.0,carZ+size/2);
  			glVertex3f(carX+1.5*size,carY,carZ+size/2);
  			glVertex3f(carX-size,carY,carZ+size/2);
  			glVertex3f(carX-size,carY+size/2.0,carZ+size/2);
        };glEnd();

        glBegin(GL_POLYGON);{
        	// draw rear
 			glVertex3f(carX-size,carY,carZ+size/2);
 			glVertex3f(carX-size,carY,carZ-size/2);
  			glVertex3f(carX-size,carY+size/2.0,carZ-size/2);
  			glVertex3f(carX-size,carY+size/2.0,carZ+size/2);
        };glEnd();

        glBegin(GL_POLYGON);{
        	// draw rear windshield
        	glColor3f(0.6,0.8,1.0);
        	glVertex3f(carX-size,carY+size/2.0,carZ+size/2);
  			glVertex3f(carX-size,carY+size/2.0,carZ-size/2);
  			glVertex3f(carX-size/2.0,carY+size,carZ-size/2);
  			glVertex3f(carX-size/2.0,carY+size,carZ+size/2);
        };glEnd();

        glBegin(GL_POLYGON);{
        	// draw roof
        	glColor3f(0.6,0.0,0.0);
        	glVertex3f(carX-size/2.0,carY+size,carZ+size/2);
        	glVertex3f(carX-size/2.0,carY+size,carZ-size/2);
        	glVertex3f(carX,carY+size,carZ-size/2);
        	glVertex3f(carX,carY+size,carZ+size/2);
        };glEnd();

        glBegin(GL_POLYGON);{
        	// draw windshield
        	glColor3f(0.6,0.8,1.0);
        	glVertex3f(carX,carY+size,carZ+size/2);
        	glVertex3f(carX,carY+size,carZ-size/2);
        	glVertex3f(carX+size/2.0,carY+size/2.0,carZ-size/2);
        	glVertex3f(carX+size/2.0,carY+size/2.0,carZ+size/2);
        };glEnd();

        glBegin(GL_POLYGON);{
        	// draw hood
        	glColor3f(0.6,0.0,0.0);
        	glVertex3f(carX+size/2.0,carY+size/2.0,carZ+size/2);
        	glVertex3f(carX+size/2.0,carY+size/2.0,carZ-size/2);
        	glVertex3f(carX+1.5*size,carY+size/2.0,carZ-size/2);
        	glVertex3f(carX+1.5*size,carY+size/2.0,carZ+size/2);
        };glEnd();

        glBegin(GL_POLYGON);{
        	// draw front
        	glColor3f(0.0,0.0,0.0);
			glVertex3f(carX+1.5*size,carY+size/2.0,carZ+size/2);
			glVertex3f(carX+1.5*size,carY+size/2.0,carZ-size/2);
			glVertex3f(carX+1.5*size,carY,carZ-size/2);
			glVertex3f(carX+1.5*size,carY,carZ+size/2);
        };glEnd();

        glBegin(GL_TRIANGLES);{
        	// draw windows
        	glColor3f(0.6,0.8,1.0);
 			glVertex3f(carX,carY+size,carZ-size/2);
  			glVertex3f(carX+size/2.0,carY+size/2.0,carZ-size/2);
  			glVertex3f(carX,carY+size/2.0,carZ-size/2);
  			glVertex3f(carX,carY+size,carZ+size/2);
  			glVertex3f(carX+size/2.0,carY+size/2.0,carZ+size/2);
  			glVertex3f(carX,carY+size/2.0,carZ+size/2);

  			glVertex3f(carX-size,carY+size/2.0,carZ-size/2);
  			glVertex3f(carX-size/2.0,carY+size,carZ-size/2);
  			glVertex3f(carX-size/2.0,carY+size/2.0,carZ-size/2);
  			glVertex3f(carX-size,carY+size/2.0,carZ+size/2);
  			glVertex3f(carX-size/2.0,carY+size,carZ+size/2);
  			glVertex3f(carX-size/2.0,carY+size/2.0,carZ+size/2);
        };glEnd();

        glBegin(GL_QUADS);{
        	// draw spoiler
        	glColor3f(0.0,0.0,0.0);
        	glVertex3f(carX-size,carY+size/2.0,carZ+size/2);
        	glVertex3f(carX-size,carY+size/2.0,carZ-size/2);
        	glVertex3f(carX-1.2*size,carY+size/1.5,carZ-size/2);
        	glVertex3f(carX-1.2*size,carY+size/1.5,carZ+size/2);
        };glEnd();
   glEnable(GL_LIGHTING);
}

void porsche944::drawTire(float size){
	// use GLUT primative to draw tire
	glColor3f(0.0,0.0,0.0);
	glutSolidTorus(size/8.0,size/4.0,8,8);
}

void porsche944::drawHubcap(float size, float x, float y, float z){
	// draw hubcap that will spin as car moves
	glDisable(GL_LIGHTING);
	glColor3f(0.8,0.8,0.8);
	glVertex3f(x,y,z);
	glBegin(GL_TRIANGLE_FAN);{
		for (float angle=0.0; angle<(2*PI); angle+=0.01){
			glVertex3f(x+(cos(angle)*size/8),y+(sin(angle)*size/8),z+0.01);
		}
	};glEnd();
	// cross on hubcap to make movement obvious
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);{ // black
		glVertex3f(x+size/8,y+size/8,z+0.02);
		glVertex3f(x-size/8,y-size/8,z+0.02);
	}glEnd();
	glBegin(GL_LINES);{
		glVertex3f(x-size/8,y+size/8,z+0.02);
		glVertex3f(x+size/8,y-size/8,z+0.02);
	}glEnd();
	glEnable(GL_LIGHTING);
}

void porsche944::drawWheel(float size, float x, float y, float z){
	// combine the hubcap and the tire
	glPushMatrix();{
		glTranslatef(x,y,z);
		drawTire(size);
	};glPopMatrix();
	glPushMatrix();{
		/*if (moving){ // if the car is moving rotate the wheel
			glTranslatef(x, y, z);
			glRotatef(wheelTheta, 0.0, 0.0, 1.0);       //Rotate about the y-axis
			glTranslatef(-x, -y, -z);
		}*/
		drawHubcap(size,x,y,z);
	};glPopMatrix();
}

void porsche944::drawCar(){
	// put everthing together to draw a car
	glPushMatrix();{
		drawBody(carSize);
	};glPopMatrix();
	glPushMatrix();{
		drawWheel(carSize,carX-carSize/2.0,carY,carZ+carSize/1.9);
	};glPopMatrix();
	glPushMatrix();{
		glTranslatef(carX-carSize/2.0, carY, carZ-carSize/1.9);
		glRotatef(180.0, 0.0, 1.0, 0.0);       //Rotate about the y-axis
		glTranslatef(-(carX-carSize/2.0), -carY, -(carZ-carSize/1.9));
		drawWheel(carSize,carX-carSize/2.0,carY,carZ-carSize/1.9);
	};glPopMatrix();
	glPushMatrix();{
		drawWheel(carSize,carX+carSize/1.5,carY,carZ+carSize/1.9);
	};glPopMatrix();
	glPushMatrix();{
		glTranslatef(carX+carSize/1.5, carY, carZ-carSize/1.9);
		glRotatef(180.0, 0.0, 1.0, 0.0);       //Rotate about the y-axis
		glTranslatef(-(carX+carSize/1.5), -carY, -(carZ-carSize/1.9));
		drawWheel(carSize,carX+carSize/1.5,carY,carZ-carSize/1.9);
	};glPopMatrix();
}

void porsche944::chase(float x, float z){}

bool porsche944::collide(float x, float z, float r){
  if ((x<(carX+r))&&(x>(carX-r))&&(z<(carZ+r))&&(z>(carZ-r))){
    return true;
  }
  return false;
}