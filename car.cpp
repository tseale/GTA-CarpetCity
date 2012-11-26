// car.cpp
// Taylor Seale
// implementation for car object

#include "car.h"

float car::getX(){
	return carX;
}

float car::getY(){
	return carY;
}

float car::getZ(){
	return carZ;
}

float car::getTheta(){
	return carTheta;
}

void car::setX(float num){
	carX = num;
}

void car::setY(float num){
	carY = num;
}

void car::setZ(float num){
	carZ = num;
}

void car::setTheta(float num){
	carTheta = num;
}