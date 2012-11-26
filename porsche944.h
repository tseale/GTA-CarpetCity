// porsche944.h
// Taylor Seale
// header file for a Porsche 944

#include "car.h"

class porsche944 : public car {
	public:
		porsche944(float,float,float,float,float);
		virtual void drawCar();
		virtual void chase(float,float);
		virtual bool collide(float,float,float);
	private:
		void drawBody(float);
		void drawTire(float);
		void drawHubcap(float,float,float,float);
		void drawWheel(float,float,float,float);
};