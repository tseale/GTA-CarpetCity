
#ifndef TEXTURE_H
#define TEXTURE_H

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


inline bool registerOpenGLTexture(unsigned char *textureData, 
                           unsigned int texWidth, unsigned int texHeight, 
                           GLuint &textureHandle) {
    if(textureData == 0) {
        fprintf(stderr,"Cannot register texture; no data specified.");
        return false;
    }
    
    // TODO: Setup Step 2-3 generate texture handle and bind texture
    glGenTextures( 1, &textureHandle );
    glBindTexture( GL_TEXTURE_2D, textureHandle );

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    
    // TODO: Setup Step 4
    // TODO: set color mode
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);    // GL_MODULATE or GL_DECAL
    
    // TODO: set min/mag filters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // a MIN Filter MUST BE SET
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // TODO: set wrapping options
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // GL_REPEAT or GL_CLAMP
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
    GLenum errCode;
    const GLubyte *errString;
    
    if ((errCode = glGetError()) != GL_NO_ERROR) {
        errString = gluErrorString(errCode);
        fprintf(stderr,"Cannot register texture; OpenGL error: %s.", errString);
        return false;
    } 
    
    // TODO: Setup Step 5 register image
    glTexImage2D( GL_TEXTURE_2D,    // specifying a 2D texture
                 0,                 // level of the texture map - used for mipmapping
                 GL_RGB,            // internal format of image data
                 texWidth,          // texture width
                 texHeight,         // texture height
                 0,                 // border width - used for filtering
                 GL_RGB,            // type of texels to use
                 GL_UNSIGNED_BYTE,  // how is the data stored in array
                 textureData        // pointer to array of image data
                 );
    return true;
}

// function to register an image to use as the texture of the particle
inline bool registerTransparentOpenGLTexture(unsigned char *imageData, unsigned char *imageMask, int texWidth, int texHeight, GLuint &texHandle) {

    //combine the 'mask' array with the image data array into an RGBA array.
    unsigned char *fullData = new unsigned char[texWidth*texHeight*4];
    for(int j = 0; j < texHeight; j++) {
        for(int i = 0; i < texWidth; i++) {
            fullData[(j*texWidth+i)*4+0] = imageData[(j*texWidth+i)*3+0];
            fullData[(j*texWidth+i)*4+1] = imageData[(j*texWidth+i)*3+1];
            fullData[(j*texWidth+i)*4+2] = imageData[(j*texWidth+i)*3+2];
            fullData[(j*texWidth+i)*4+3] = imageMask[(j*texWidth+i)];
        }
    }

    //first off, get a real texture handle.
    glGenTextures(1, &texHandle);

    //make sure that future texture functions affect this handle
    glBindTexture(GL_TEXTURE_2D, texHandle);

    //set this texture's color to be multiplied by the surface colors -- 
    //  GL_MODULATE instead of GL_REPLACE allows us to take advantage of OpenGL lighting
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //set the minification ang magnification functions to be linear; not perfect
    //  but much better than nearest-texel (GL_NEAREST).
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Set the texture to repeat in S and T -- though it doesn't matter here
    //  because our texture coordinates are always in [0,0] to [1,1].
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //actually transfer the texture to the GPU!
    //note that this ISN'T using mipmapping.
    glTexImage2D( GL_TEXTURE_2D,                //still working with 2D textures, obv.
                    0,                          //not using mipmapping, so this is the highest level.
                    GL_RGBA,                    //we're going to provide OpenGL with R, G, B, and A components...
                    texWidth,                   //...of this width...
                    texHeight,                  //...and this height.
                    0,                          //give it a border of 0 pixels (none)
                    GL_RGBA,                    //and store it, internally, as RGBA (OpenGL will convert to floats between 0.0 and 1.0f)
                    GL_UNSIGNED_BYTE,           //this is the format our data is in, and finally,
                    fullData );                 //there's the data!

    delete fullData;

    //whoops! i guess this function can't fail. in an ideal world, there would
    //be checks with glGetError() that we could use to determine if this failed.
    return true;
}

// function to read in a PPM image
inline bool readPPM(string filename, int &imageWidth, int &imageHeight, unsigned char* &imageData) {
    FILE *fp = fopen(filename.c_str(), "r");
    int temp, maxValue;
    fscanf(fp, "P%d", &temp);
    if(temp != 3) {
        fprintf(stderr, "Error: PPM file is not of correct format! (Must be P3, is P%d.)\n", temp);
        fclose(fp);
        return false;
    }
	
    //got the file header right...
    fscanf(fp, "%d", &imageWidth);
    fscanf(fp, "%d", &imageHeight);
    fscanf(fp, "%d", &maxValue);
	
    //now that we know how big it is, allocate the buffer...
    imageData = new unsigned char[imageWidth*imageHeight*3];
    if(!imageData) {
        fprintf(stderr, "Error: couldn't allocate image memory. Dimensions: %d x %d.\n", imageWidth, imageHeight);
        fclose(fp);
        return false;
    }
	
    //and read the data in.
    for(int j = 0; j < imageHeight; j++) {
        for(int i = 0; i < imageWidth; i++) {
            int r, g, b;
            fscanf(fp, "%d", &r);
            fscanf(fp, "%d", &g);
            fscanf(fp, "%d", &b);
			
            imageData[(j*imageWidth+i)*3+0] = r;
            imageData[(j*imageWidth+i)*3+1] = g;
            imageData[(j*imageWidth+i)*3+2] = b;
        }
    }
    
    fclose(fp);
    return true;
}

inline bool readAlphaPPM(string filename, int &imageWidth, int &imageHeight, unsigned char* &imageData) {
    FILE *fp = fopen(filename.c_str(), "r");
    int temp, maxValue;
    fscanf(fp, "P%d", &temp);
    if(temp != 3) {
        fprintf(stderr, "Error: PPM file is not of correct format! (Must be P3, is P%d.)\n", temp);
        fclose(fp);
        return false;
    }

    //got the file header right...
    fscanf(fp, "%d", &imageWidth);
    fscanf(fp, "%d", &imageHeight);
    fscanf(fp, "%d", &maxValue);

    //now that we know how big it is, allocate the buffer...
    imageData = new unsigned char[imageWidth*imageHeight];
    if(!imageData) {
        fprintf(stderr, "Error: couldn't allocate image memory. Dimensions: %d x %d.\n", imageWidth, imageHeight);
        fclose(fp);
        return false;
    }

    //and read the data in.
    for(int j = 0; j < imageHeight; j++) {
        for(int i = 0; i < imageWidth; i++) {
            //read the data into integers (4 bytes) before casting them to unsigned characters
            //and storing them in the unsigned char array.
            int a;
            fscanf(fp, "%d", &a);
            imageData[j*imageWidth+i] = (unsigned char)a;
            fscanf(fp, "%d", &a);
            fscanf(fp, "%d", &a);
        }
    }
    
    fclose(fp);
    return true;
}

#endif