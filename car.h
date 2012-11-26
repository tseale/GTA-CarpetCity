// car.h
// Taylor Seale
// header file for a car object

#ifndef CAR_H
#define CAR_H

class car {
	public:
		virtual void drawCar()=0;
		virtual void chase(float,float)=0;
		virtual bool collide(float,float,float)=0;
		float getX();
		float getY();
		float getZ();
		float getTheta();
		void setX(float);
		void setY(float);
		void setZ(float);
		void setTheta(float);
	protected:
		float carX,carY,carZ;
		float carTheta;
		float carSize;
};

#endif