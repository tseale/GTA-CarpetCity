// Taylor Seale
// skybox.h
// header file for a skybox class

#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <string>
using namespace std;

class skybox{
	public:
		skybox(string,string,string,string,string,string); // top,left,right,front,back,bottom
		void drawSkybox(int,int,int); // length,width,height
	private:
		GLuint topTexHandle;
		GLuint leftTexHandle;
		GLuint rightTexHandle;
		GLuint frontTexHandle;
		GLuint backTexHandle;
		GLuint bottomTexHandle;
};