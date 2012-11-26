// moneyCrate.cpp
// Taylor Seale
// implementation for a money crate

#include "moneyCrate.h"
#include "texture.h"

moneyCrate::moneyCrate(float x, float y, float z){
	crateX=x;
	crateY=y;
	crateZ=z;
}

void moneyCrate::drawCrate(){
	glPushMatrix();{
		glTranslatef(crateX,crateY,crateZ);
		glColor3f(0.6,0.4,0.2);
	   	glutSolidCube(2);
    };glPopMatrix();
}

bool moneyCrate::collide(float x, float y, float z){
	if ((x<(crateX+2))&&(x>(crateX-2))&&(z>(crateZ-2))&&(z<(crateZ+2))){
		return true;
	}
	return false;
}

float moneyCrate::getX(){
	return crateX;
}

float moneyCrate::getY(){
	return crateY;
}

float moneyCrate::getZ(){
	return crateZ;
}