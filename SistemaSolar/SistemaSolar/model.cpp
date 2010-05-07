/*
 * main.cpp
 *
 *  Created on: 23/Abr/2009
 *      Author: nuno
 */

#include "3dsloader.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <string.h>


#include "model.h"
#include "texture.h"
#include <iostream>
#include <string.h>

int screen_width=1024;
int screen_height=1024;
float rotChave = 0.0f;


obj_type modelo;

void drawModel(){
	glPushMatrix();

	//glRotatef(180,0,1,0);

		
	glRotatef(-90,1,0,0);
	glRotatef(180,0,0,1);
	//glScalef (1.030, 3.030, 3.030);

	glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping

	glBindTexture(GL_TEXTURE_2D, modelo.id_texture); // We set the active texture

	int l_index=0;

	glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)

		for (l_index=0;l_index<modelo.polygons_qty;l_index++)
		{
			//----------------- FIRST VERTEX -----------------
			// Texture coordinates of the first vertex

			glTexCoord2f( modelo.mapcoord[ modelo.polygon[l_index].a ].u,

			              modelo.mapcoord[ modelo.polygon[l_index].a ].v);

			// Coordinates of the first vertex

			glVertex3f( modelo.vertex[ modelo.polygon[l_index].a ].x,

						modelo.vertex[ modelo.polygon[l_index].a ].y,

						modelo.vertex[ modelo.polygon[l_index].a ].z); //Vertex definition

			//printf("[%f][%f][%f]\n",

			//		modelo.vertex[ modelo.polygon[l_index].a ].x,

			//        modelo.vertex[ modelo.polygon[l_index].a ].y,

			//        modelo.vertex[ modelo.polygon[l_index].a ].z);



			//----------------- SECOND VERTEX -----------------

			// Texture coordinates of the second vertex

			glTexCoord2f( modelo.mapcoord[ modelo.polygon[l_index].b ].u,

			              modelo.mapcoord[ modelo.polygon[l_index].b ].v);

			// Coordinates of the second vertex

			glVertex3f( modelo.vertex[ modelo.polygon[l_index].b ].x,

						modelo.vertex[ modelo.polygon[l_index].b ].y,

						modelo.vertex[ modelo.polygon[l_index].b ].z);



			//----------------- THIRD VERTEX -----------------

			// Texture coordinates of the third vertex

			glTexCoord2f( modelo.mapcoord[ modelo.polygon[l_index].c ].u,

			              modelo.mapcoord[ modelo.polygon[l_index].c ].v);

			// Coordinates of the Third vertex

			glVertex3f( modelo.vertex[ modelo.polygon[l_index].c ].x,

						modelo.vertex[ modelo.polygon[l_index].c ].y,

						modelo.vertex[ modelo.polygon[l_index].c ].z);

		}

	glEnd();

	//glDeleteTextures(GL_TEXTURE_2D,modelo.id_texture);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}

void initModels()
{
	printf("initModels\n");

    glClearColor(0.0, 0.0, 0.0, 0.0); // This clear the background color to black

    glShadeModel(GL_SMOOTH); // Type of shading for the polygons

    // Viewport transformation

    glViewport(0,0,screen_width,screen_height);

    // Projection transformation

    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations

    glLoadIdentity(); // We initialize the projection matrix as identity

    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f); // We define the "viewing volume"

    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)

    //glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping

    Load3DS (&modelo,"Resource/modelo_actor.3DS");

    //Aqui vai ser para carregar texturas, mais tarde

    modelo.id_texture=LoadTextura("Resource/spaceshiptexture.bmp"); // The Function LoadBitmap() return the current texture ID

    // If the last function returns -1 it means the file was not found so we exit from the program

    if (modelo.id_texture==-1)
    {
        //MessageBox(NULL,"Image file: spaceshiptexture.bmp not found", "Zetadeck",MB_OK | MB_ICONERROR);

    	printf("textura da navenao encontrada\n");

        exit (0);
    }

    
    // glDisable(GL_TEXTURE_2D);
}





