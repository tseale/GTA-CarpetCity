// Taylor Seale
// skybox.cpp
// implementation for a skybox class

#include "skybox.h"
#include "texture.h"
#include <iostream>
using namespace std;

skybox::skybox(string topFile, string leftFile, string rightFile, string frontFile, string backFile, string bottomFile){
	int texWidth,texHeight;
	unsigned char *texData;
    // read and register the top texture
	readPPM(topFile, texWidth, texHeight, texData);
	registerOpenGLTexture(texData, texWidth, texHeight, topTexHandle);
    // read and register the left texture
    readPPM(leftFile, texWidth, texHeight, texData);
    registerOpenGLTexture(texData, texWidth, texHeight, leftTexHandle);
    // read and register the right texture
    readPPM(rightFile, texWidth, texHeight, texData);
    registerOpenGLTexture(texData, texWidth, texHeight, rightTexHandle);
    // read and register the front texture
    readPPM(frontFile, texWidth, texHeight, texData);
    registerOpenGLTexture(texData, texWidth, texHeight, frontTexHandle);
     // read and register the back texture
    readPPM(backFile, texWidth, texHeight, texData);
    registerOpenGLTexture(texData, texWidth, texHeight, backTexHandle);
    // read and register the bottom texture
    readPPM(bottomFile, texWidth, texHeight, texData);
    registerOpenGLTexture(texData, texWidth, texHeight, bottomTexHandle);
}

void skybox::drawSkybox(int length, int width, int height){
    glPushMatrix();
 // Enable/Disable features
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
 
    // Just in case we set all vertices to white.
    glColor4f(1,1,1,1);
 
    // Render the front quad
    glBindTexture(GL_TEXTURE_2D, frontTexHandle);
    glBegin(GL_QUADS);
        glTexCoord2f(1, 1); glVertex3f(  width, -height, -length );
        glTexCoord2f(0, 1); glVertex3f( -width, -height, -length);
        glTexCoord2f(0, 0); glVertex3f( -width,  height, -length );
        glTexCoord2f(1, 0); glVertex3f(  width,  height, -length );
    glEnd();
 
    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, rightTexHandle);
    glBegin(GL_QUADS);
        glTexCoord2f(1, 1); glVertex3f(  width, -height,  length );
        glTexCoord2f(0, 1); glVertex3f(  width, -height, -length );
        glTexCoord2f(0, 0); glVertex3f(  width,  height, -length );
        glTexCoord2f(1, 0); glVertex3f(  width,  height,  length );
    glEnd();
 
    // Render the back quad
    glBindTexture(GL_TEXTURE_2D, backTexHandle);
    glBegin(GL_QUADS);
        glTexCoord2f(1, 1); glVertex3f( -width, -height,  length );
        glTexCoord2f(0, 1); glVertex3f(  width, -height,  length );
        glTexCoord2f(0, 0); glVertex3f(  width,  height,  length );
        glTexCoord2f(1, 0); glVertex3f( -width,  height,  length );
    glEnd();
 
    // Render the right quad
    glBindTexture(GL_TEXTURE_2D, leftTexHandle);
    glBegin(GL_QUADS);
        glTexCoord2f(1, 1); glVertex3f( -width, -height, -length );
        glTexCoord2f(0, 1) ; glVertex3f( -width, -height,  length );
        glTexCoord2f(0, 0); glVertex3f( -width,  height,  length );
        glTexCoord2f(1, 0); glVertex3f( -width,  height, -length );
    glEnd();
 
    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, topTexHandle);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f( -width,  height, -length );
        glTexCoord2f(0, 0); glVertex3f( -width,  height,  length );
        glTexCoord2f(1, 0); glVertex3f(  width,  height,  length );
        glTexCoord2f(1, 1); glVertex3f(  width,  height, -length );
    glEnd();
 
    // Render the bottom quad
    glBindTexture(GL_TEXTURE_2D, bottomTexHandle);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f( -width,  -height, -length );
        glTexCoord2f(0, 0); glVertex3f( -width,  -height,  length );
        glTexCoord2f(1, 0); glVertex3f(  width,  -height,  length );
        glTexCoord2f(1, 1); glVertex3f(  width,  -height, -length );
    glEnd();
 
    // Restore enable bits and matrix
    glPopAttrib();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);
}