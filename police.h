// police.h
// Taylor Seale
// header file for a police car

#include "car.h"

class police : public car {
	public:
		police(float,float,float,float,float,int);
		virtual void drawCar();
		virtual void chase(float,float);
		virtual bool collide(float,float,float);
		float getVel();
		void setVel(float);
		float engagePursuit(float,float);
		bool caught;
		int bounce;
		bool inPursuit;
		bool hit;
		bool dead;
		int stage;
		int r,b;
	private:
		void drawBody(float);
		void drawTire(float);
		void drawHubcap(float,float,float,float);
		void drawWheel(float,float,float,float);
		void drawSiren(float,float,float,float);
		bool isCorrect;
		float velocity;
};