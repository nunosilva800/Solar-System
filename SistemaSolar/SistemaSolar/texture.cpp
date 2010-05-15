/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli <info@spacesimulator.net>
 *
 * ALL RIGHTS RESERVED
 *
 *
 * Tutorial 4: 3d engine - 3ds models loader
 *
 * Include File: texture.cpp
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
//#include <GL/gl.h>
#include "texture.h"
#include <iostream>



/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

int num_texture=-1; //Counter to keep track of the last loaded texture



/**********************************************************
 *
 * FUNCTION LoadBitmap(char *)
 *
 * This function loads a bitmap file and return the OpenGL reference ID to use that texture
 *
 *********************************************************/

int LoadTextura(char *filename)
{
    unsigned int i, j=0; //Index variables
    FILE *l_file; //File pointer
    /*unsigned*/ char *l_texture; //The pointer to the memory zone in which we will load the texture

    // As we are not using windows we need to read the bitmap header stuff manually
	// under windows there are predefined commands to do this.
    unsigned char fileheader[0x27]; // holds the entire file and info headers
	unsigned long width,height; // fairly self explanatory
	unsigned char rgb[3];

    num_texture++; // The counter of the current texture is increased

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading

    fread(&fileheader, 0x27, 1, l_file); // Read the fileheader

	// The width and height can be extracted and endian-corrected at the same time
	// For more information on the bitmap file format, do a search on google for bitmap file format
	// It should return lots of info
	width  = fileheader[0x12] + (fileheader[0x13] * 0x100) + (fileheader[0x14] * 0x10000) + (fileheader[0x15] * 0x1000000);
	height = fileheader[0x16] + (fileheader[0x17] * 0x100) + (fileheader[0x18] * 0x10000) + (fileheader[0x19] * 0x1000000);

	std::cout << "read width as " << width << std::endl;
	std::cout << "read height as " << height << std::endl;

    // Now we need to allocate the memory for our image (width * height * color deep)
    l_texture = (char *) malloc(width * height * 4);
    // And fill it with zeros
    memset(l_texture, 0, width * height * 4);

    // At this point we can read every pixel of the image
    for (i=0; i < width*height; i++)
    {
            // We load an RGB value from the file
            fread(&rgb, 3, 1, l_file);

			// Note that bitmaps store the colour information in the order BGR not RGB

            // And store it
            l_texture[j+0] = rgb[2]; // Red component
            l_texture[j+1] = rgb[1]; // Green component
            l_texture[j+2] = rgb[0]; // Blue component
            l_texture[j+3] = 255; // Alpha value
            j += 4; // Go to the next position
    }

    fclose(l_file); // Closes the file stream

    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture); // Free the memory we used to load the texture

    return (num_texture); // Returns the current texture OpenGL ID
}

