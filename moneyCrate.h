// moneyCrate.h
// Taylor Seale
// header file for a crate of money

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

class moneyCrate {
	public:
		moneyCrate(float,float,float);
		void drawCrate();
		bool collide(float, float, float);
		float getX();
		float getY();
		float getZ();
	private:
		float crateX,crateY,crateZ;	
};