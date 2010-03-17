#include <GL/glut.h>

#include <math.h>
#include "planetas.h"

GLfloat rotSol=0.0;
GLfloat rotMercurio=0.0;
GLfloat rotVenus=0.0;
GLfloat rotTerra=0.0;
GLfloat rotLua=0.0;
GLfloat rotMarte=0.0;
GLfloat rotJupiter=0.0;
GLfloat rotSaturno=0.0;
GLfloat rotUrano=0.0;
GLfloat rotNeptuno=0.0;

void rotacao(GLfloat rotacao)
{
	glRotated(rotacao,0.0,1.0,0.0);
	glutPostRedisplay();
}


void desenharSol()
{
	glPushMatrix();
	glColor3f(1,1,0);
	rotSol+=1;
	rotacao(rotSol);
	glutWireSphere(696,32,32);
	glPopMatrix();
}

void desenharMercurio()
{
	glPushMatrix();
	glTranslatef(1000,0,0);
	glColor3f(0.5,0.5,0.5);
	rotMercurio+=0.2;
	rotacao(rotMercurio);
	glutWireSphere(1.2195,32,32);
	glPopMatrix();
}

void desenharVenus()
{
	glPushMatrix();
	glTranslatef(1100,0,0);
	glColor3f(0.6,0.5,0.1);
	rotVenus+=0.4;
	rotacao(rotVenus);
	glutWireSphere(3.0259,32,32);
	glPopMatrix();
}

void desenharLua()
{
	glTranslatef(25,0,0);
	glColor3f(1,1,1);
	rotLua+=0.34;
	rotacao(rotLua);
	glutWireSphere((3.4742/2),32,32);
}

void desenharTerra()
{
	glPushMatrix();
	glTranslatef(1200,0,0);
	glColor3f(0,0,1);
	rotTerra+=0.34;
	rotacao(rotTerra);
	glutWireSphere(3.1855,32,32);
	desenharLua();
	glPopMatrix();
}



void desenharMarte()
{
	glPushMatrix();
	glTranslatef(1300,0,0);
	glColor3f(0,0,1);
	rotMarte += 0.6;
	rotacao(rotMarte);
	glutWireSphere((6.780/2),32,32);
	glPopMatrix();
}
void desenharJupiter()
{
	glPushMatrix();
	glTranslatef(2000,0,0);
	glColor3f(0,0,1);
	rotJupiter+=0.87;
	rotacao(rotJupiter);
	glutWireSphere((139.822/2),32,32);
	glPopMatrix();
}
void desenharSaturno()
{
	glPushMatrix();
	glTranslatef(2300,0,0);
	glColor3f(0.48,0.48,0.48);
	rotSaturno+=0.65;
	rotacao(rotSaturno);
	glutWireSphere((116.464/2),32,32);
	glPopMatrix();
}
void desenharUrano()
{
	glPushMatrix();
	glTranslatef(2800,0,0);
	glColor3f(0.8,0.1,0.4);
	rotUrano+=0.543;
	rotacao(rotUrano);
	glutWireSphere((50.724/2),32,32);
	glPopMatrix();
}

void desenharNeptuno()
{
	glPushMatrix();
	glTranslatef(3200,0,0);
	glColor3f(0.12,0.432,0.123);
	rotNeptuno+=1.23;
	rotacao(rotNeptuno);
	glutWireSphere((49.244/2),32,32);
	glPopMatrix();
}

void planetas(){
	//sol
	desenharSol();
	//mercurio
	desenharMercurio();
	//venus
	desenharVenus();
	//terra
	desenharTerra();
	//planeta marte
	desenharMarte();
	//planeta jupiter
	desenharJupiter();
	//planeta saturno
	desenharSaturno();
	//planeta urano
	desenharUrano();
	//planeta spock
	desenharNeptuno();
}