
// Taylor Seale
// implementation for a police car

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
#include <vector>
#include <iostream>
#include "police.h"
using namespace std;

police::police(float x,float y,float z,float theta,float size,int s){
	carX=x;
	carY=y;
	carZ=z;
	carTheta=theta;
	carSize=size;
  r=1;
  b=0;
  hit=false;
  velocity=0.75;
  caught=false;
  bounce=0;
  inPursuit=true;
  dead=false;
  stage=s;
}

void police::setVel(float n){
  velocity=n;
}

float police::getVel(){
  return velocity;
}

void police::drawBody(float size) {
	// draw the body of the car
    glDisable(GL_LIGHTING);
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_QUADS);{
  			// draw top right of body
  			glVertex3f(carX,carY+size,carZ-size/2);
  			glVertex3f(carX,carY,carZ-size/2);
  			glVertex3f(carX-size/2, carY, carZ-size/2);
  			glVertex3f(carX-size/2,carY+size,carZ-size/2.0);
        };glEnd();
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_QUADS);{
  			// draw bottom right of body
			glVertex3f(carX+1.5*size,carY+size/2.0,carZ-size/2);
  			glVertex3f(carX+1.5*size,carY,carZ-size/2);
  			glVertex3f(carX-size,carY,carZ-size/2);
  			glVertex3f(carX-size,carY+size/2.0,carZ-size/2);
        };glEnd();
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_QUADS);{
  			// draw top left of body
  			glVertex3f(carX,carY+size,carZ+size/2);
  			glVertex3f(carX,carY,carZ+size/2);
  			glVertex3f(carX-size/2, carY, carZ+size/2);
  			glVertex3f(carX-size/2,carY+size,carZ+size/2.0);
        };glEnd();
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_QUADS);{
  			// draw bottom left of body
			glVertex3f(carX+1.5*size,carY+size/2.0,carZ+size/2);
  			glVertex3f(carX+1.5*size,carY,carZ+size/2);
  			glVertex3f(carX-size,carY,carZ+size/2);
  			glVertex3f(carX-size,carY+size/2.0,carZ+size/2);
        };glEnd();
        glColor3f(0.0,0.0,0.0);
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
        	glColor3f(0.0,0.0,0.0);
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
        	glColor3f(1,1,1);
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

void police::drawTire(float size){
	// use GLUT primative to draw tire
	glColor3f(0.0,0.0,0.0);
	glutSolidTorus(size/8.0,size/4.0,8,8);
}

void police::drawHubcap(float size, float x, float y, float z){
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

void police::drawWheel(float size, float x, float y, float z){
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

void police::drawSiren(float size, float x, float y, float z){
  if (inPursuit){
	 float temp=r;
	 r=b;
	 b=temp;
  }
	glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);{
    	glColor3f(r,0,b);
    	glVertex3f(carX-size/2.0,carY+size+0.1,carZ+size/2);
    	glVertex3f(carX-size/2.0,carY+size+0.1,carZ);
    	glVertex3f(carX,carY+size+0.1,carZ);
    	glVertex3f(carX,carY+size+0.1,carZ+size/2);
    };glEnd();
    glBegin(GL_QUADS);{
    	glColor3f(b,0,r);
    	glVertex3f(carX-size/2.0,carY+size+0.1,carZ-size/2);
    	glVertex3f(carX-size/2.0,carY+size+0.1,carZ);
    	glVertex3f(carX,carY+size+0.1,carZ);
    	glVertex3f(carX,carY+size+0.1,carZ-size/2);
    };glEnd();
    glEnable(GL_LIGHTING);
}

void police::drawCar(){
	// put everthing together to draw a car
	glPushMatrix();{
		drawBody(carSize);
	};glPopMatrix();
	glPushMatrix();{
		drawWheel(carSize,carX-carSize/2.0,carY,carZ+carSize/1.9);
	};glPopMatrix();
	glPushMatrix();{
		drawSiren(carSize,carX,carY,carZ);
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

bool police::collide(float x, float z, float r){
  if ((x<(carX+r))&&(x>(carX-r))&&(z<(carZ+r))&&(z>(carZ-r))){
    return true;
  }
  return false;
}

void normalize(vector<float>& v){
  float length=0;
  for (unsigned int i=0; i<v.size(); i++){
    length+=pow(v.at(i),2);
  }
  length=sqrt(length);
  for (unsigned int j=0; j<v.size(); j++){
    v.at(j)=v.at(j)/length;
  }
}

bool vectorEqual(vector<float> &v1,vector<float> &v2){
  if (v1.size()!=v2.size()){
    return false;
  }else{
    for (unsigned int i=0; i<v1.size(); i++){
      if (v1.at(i)!=v2.at(i)){
        return false;
      }
    }
  }
  return true;
}

float calcAngle(vector<float> &v1,vector<float> &v2){
  return acos((v1.at(0)*v2.at(0)+v2.at(1)*v1.at(1))/(sqrt(v2.at(0)*v2.at(0)+v2.at(1)*v2.at(1))*sqrt(v1.at(0)*v1.at(0)+v1.at(1)*v1.at(1))));
}

float police::engagePursuit(float x, float z){
    float vX = carX-x;
    float vZ = carZ-z;
    return sqrt(pow(vX,2)+pow(vZ,2));
}

void police::chase(float x, float z){
  if (inPursuit){
    // vector of the police cars heading
    float xH = -cos(carTheta*(PI/180));
    float zH = sin(carTheta*(PI/180));
    // vector from the police car to the target
    float vX = carX-x;
    float vZ = carZ-z;
    // angle between the police car and its target
    float angle = acos((xH*vX+vZ*zH)/(sqrt(vX*vX+vZ*vZ)*sqrt(xH*xH+zH*zH)));
    // weird 'nan' value
    if (angle!=angle){
      isCorrect=true; // if angle==nan, the heading is correct
    }else{
      isCorrect=false;
    }

    // if the heading of the police car is not facing the target
    if (!isCorrect){
      float correct = angle*(180/PI); // correction we need to make
      // test to see whether angle needs to be added or subtracted
      // assume first that we need to add it
      // calculate the heading if we had added the angle to the carTheta
      xH = -cos((carTheta+correct)*(PI/180));
      zH = sin((carTheta+correct)*(PI/180));
      // calculate the new angle between the vectors
      float newAngle = acos((xH*vX+vZ*zH)/(sqrt(vX*vX+vZ*vZ)*sqrt(xH*xH+zH*zH)));
      if (newAngle!=newAngle){ // if newAngle is equal to nan
        carTheta+=correct; // then we did need to add it!
      }else{ // otherwise, subtracting puts the heading on track
        carTheta-=correct; 
      }
    }
  }
  // move the car along its new heading
  if (!caught && !dead){
    carX+=cos(-PI*carTheta/180.0)*velocity;
    carZ+=sin(-PI*carTheta/180.0)*velocity;
  }
} 


/*void police::chase(float x, float z){
  // vector of the police cars heading
  vector<float> H;
  H.push_back(cos(carTheta*(PI/180)));
  H.push_back(sin(carTheta*(PI/180)));
  cout << "Regular: " << H.at(0) << " " << H.at(1) << endl;
  normalize(H);
  cout << "Normalized: " << H.at(0) << " " << H.at(1) << endl;
  // vector from the police car to the target
  vector<float> S;
  S.push_back(x-carX);
  S.push_back(z-carZ);
  normalize(S);
  // angle between the police car and its target

  if (!vectorEqual(S,H)){
    float angle = calcAngle(S,H);
    if (angle<0){
      carTheta+=15;
    }
    else if (angle>0){
      carTheta-=15;
    }
  }

  // move the car along its new heading
  carX+=cos(-PI*carTheta/180.0)*0.75;
  carZ+=sin(-PI*carTheta/180.0)*0.75;
}*/

