#include<IL\il.h>
#include<IL\ilu.h>
#include<IL\ilut.h>
#include <GL/glut.h>
#include "texturas.h"

GLuint texture[10] = {};
GLUquadric * Qplanetas[10] = {};

int LoadBitmap(char *filename)
{
    FILE * file;
    char temp;
    long i;

    // own version of BITMAPINFOHEADER from windows.h for Linux compile
    struct {
      int biWidth;
      int biHeight;
      short int biPlanes;
      unsigned short int biBitCount;
      unsigned char *data;
    } infoheader;

    GLuint num_texture;

    if( (file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading

    fseek(file, 18, SEEK_CUR);  /* start reading width & height */
    fread(&infoheader.biWidth, sizeof(int), 1, file);

    fread(&infoheader.biHeight, sizeof(int), 1, file);

    fread(&infoheader.biPlanes, sizeof(short int), 1, file);
    if (infoheader.biPlanes != 1) {
      printf("Planes from %s is not 1: %u\n", filename, infoheader.biPlanes);
      return 0;
    }

    // read the bpp
    fread(&infoheader.biBitCount, sizeof(unsigned short int), 1, file);
    if (infoheader.biBitCount != 24) {
      printf("Bpp from %s is not 24: %d\n", filename, infoheader.biBitCount);
      return 0;
    }

    fseek(file, 24, SEEK_CUR);

    // read the data
    if(infoheader.biWidth<0){
      infoheader.biWidth = -infoheader.biWidth;
    }
    if(infoheader.biHeight<0){
      infoheader.biHeight = -infoheader.biHeight;
    }
    infoheader.data = (unsigned char *) malloc(infoheader.biWidth * infoheader.biHeight * 3);
    if (infoheader.data == NULL) {
      printf("Error allocating memory for color-corrected image data\n");
      return 0;
    }

    if ((i = fread(infoheader.data, infoheader.biWidth * infoheader.biHeight * 3, 1, file)) != 1) {
      printf("Error reading image data from %s.\n", filename);
      return 0;
    }

    for (i=0; i<(infoheader.biWidth * infoheader.biHeight * 3); i+=3) { // reverse all of the colors. (bgr -> rgb)
      temp = infoheader.data[i];
      infoheader.data[i] = infoheader.data[i+2];
      infoheader.data[i+2] = temp;
    }


    fclose(file); // Closes the file stream

    glGenTextures(1, &num_texture);
    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, infoheader.biWidth, infoheader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, infoheader.data);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, infoheader.biWidth, infoheader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, infoheader.data);
    
    free(infoheader.data); // Free the memory we used to load the texture

    return (num_texture); // Returns the current texture OpenGL ID
}