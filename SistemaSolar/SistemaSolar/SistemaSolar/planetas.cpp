#include <GL/glut.h>

#include <math.h>
#include "planetas.h"

//velocidades de rotação em dias
GLfloat rotSol = 0;
GLfloat rotMercurio = 0;
GLfloat rotVenus = 0;
GLfloat rotTerra = 0;
GLfloat rotLua = 0;
GLfloat rotMarte = 0;
GLfloat rotJupiter = 0;
GLfloat rotSaturno = 0;
GLfloat rotUrano = 0;
GLfloat rotNeptuno = 0;

float scale = 1;

float time = 0;

void rotacao(GLfloat rotacao,float tilt)
{
	glRotatef(tilt,0.0,0.0,1.0);
	glRotated(rotacao,0.0,1.0,0.0);
	
	glutPostRedisplay();
}

void draw_Orbita(float raio, float angleX,float angleY, float angleZ){
	glPushMatrix();
	
	glRotatef(angleZ,0.0,0.0,1.0);
	glRotatef(angleX,1.0,0.0,0.0);
	glRotatef(angleY,0.0,1.0,0.0);
	

	float xx=0;
	float yy=0;
	glBegin(GL_LINES);
	for (int i = 0; i < 180; i++)
	{
		xx = raio * cos((float)i);
		yy = raio * sin((float)i);
		glVertex3f(xx,yy,0);
		xx = raio * cos(i + 0.1);
		yy = raio * sin(i + 0.1);
		glVertex3f(xx,yy,0);
	}
	glEnd();

	glPopMatrix();	
}

void desenharAnel(float raio1, float raio2){
	glColor3f(1,0,0);
	glutSolidTorus(raio1,raio2,360,150);
}


void desenharSol()
{
	glPushMatrix();
	glColor3f(1,1,0);
	rotSol+=25.38;
	rotacao(rotSol,0.0);
	glutWireSphere(raioSol*(1/scale),32,32);
	glPopMatrix();
}

void desenharMercurio()
{
	glPushMatrix();
	glTranslatef(1000*cos(0.0)*sin(time*0.2),1000*sin(0.0),1000*cos(0.0)*cos(time*0.2));
	glColor3f(0.5,0.5,0.5);//cinza
	rotMercurio += 58.646;
	rotacao(rotMercurio,0.0);
	glutWireSphere(raioMercurio,32,32);
	glPopMatrix();
	draw_Orbita(1000,90,0.0,0.0);
}

void desenharVenus()
{
	glPushMatrix();
	glTranslatef(1100*cos(0.0)*sin(time*0.6),1100*sin(0.0),1100*cos(0.0)*cos(time*0.6));
	glColor3f(0.6,0.5,0.1);//castanho
	rotVenus += -243.0185;
	rotacao(rotVenus,0.0);
	glutWireSphere(raioVenus,32,32);
	glPopMatrix();
	draw_Orbita(1100,90,0.0,0.0);
}

void desenharLua()
{
	draw_Orbita(25,90,0.0,0.0);
	glTranslatef(25,0,0);
	glColor3f(1,1,1);//branco
	rotLua += 27.321582;
	rotacao(rotLua,0.0);
	glutWireSphere(raioLua,32,32);
	
}

void desenharTerra()
{
	glPushMatrix();
	glTranslatef(1200*cos(0.0)*sin(time),1200*sin(0.0),1200*cos(0.0)*cos(time));
	glColor3f(0,0,1);//azul
	rotTerra += 1;
	rotacao(rotTerra,0.0);
	glutWireSphere(raioTerra,32,32);
	desenharLua();
	glPopMatrix();
	glColor3f(0,0,1);//azul
	draw_Orbita(1200,90,0.0,0.0);
}

void desenharMarte()
{
	glPushMatrix();
	glTranslatef(1300*cos(0.0)*sin(time),1300*sin(0.0),1300*cos(0.0)*cos(time));
	glColor3f(1,0,0);//vermelho
	rotMarte += 1.025957;
	rotacao(rotMarte,0.0);
	glutWireSphere(raioMarte,32,32);
	glPopMatrix();
	draw_Orbita(1300,90,0.0,0.0);
}
void desenharJupiter()
{
	glPushMatrix();
	glRotatef(orbitalTiltJupiter,0.0,0.0,1.0);
	glTranslatef(2000*cos(0.0)*sin(time),2000*sin(0.0),2000*cos(0.0)*cos(time));
	glColor3f(1,1,0);//amarelo
	rotJupiter += 0.413541667;
	rotacao(rotJupiter,axisTiltJupiter);
	glutWireSphere(raioJupiter,32,32);
	glPopMatrix();
	draw_Orbita(2000,90,0.0,orbitalTiltJupiter);
}
void desenharSaturno()
{
	glPushMatrix();
	glTranslatef(2300*cos(0.0)*sin(time),2300*sin(0.0),2300*cos(0.0)*cos(time));
	glColor3f(1,0,1);//rosa
	rotSaturno += 0.440416667;
	rotacao(rotSaturno,0.0);
	glutWireSphere(raioSaturno,32,32);
	glPushMatrix();
	glRotatef(90.0,1.0,0.0,0.0);
	glScalef(1,1,0.1);
	desenharAnel(43,150);
	glPopMatrix();
	glPopMatrix();
	draw_Orbita(2300,90,0.0,0.0);
}
void desenharUrano()
{
	glPushMatrix();
	glTranslatef(2800*cos(0.0)*sin(time),2800*sin(0.0),2800*cos(0.0)*cos(time));
	glColor3f(0.8,0.1,0.4);//roxo
	rotUrano += -0.71833;
	rotacao(rotUrano,0.0);
	glutWireSphere(raioUrano,32,32);
	glPopMatrix();
	draw_Orbita(2800,90,0.0,0.0);
}

void desenharNeptuno()
{
	glPushMatrix();
	glColor3f(0.12,0.432,0.123);//verde
	rotNeptuno += 0.6713;
	glTranslatef(3200*cos(0.0)*sin(time),3200*sin(0.0),3200*cos(0.0)*cos(time));
	rotacao(rotNeptuno,0.0);
	glutWireSphere(raioNeptuno,32,32);
	glPopMatrix();
	draw_Orbita(3200,90,0.0,0.0);
}

void planetas(){
	time +=0.005;
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
