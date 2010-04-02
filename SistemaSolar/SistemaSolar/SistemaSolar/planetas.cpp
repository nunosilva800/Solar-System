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

float scale = 1;

float time =0;

void rotacao(GLfloat rotacao)
{
	glRotated(rotacao,0.0,1.0,0.0);
	glutPostRedisplay();
}

void draw_Orbita(float raio, float angle){
	glPushMatrix();
	glRotatef(angle,1,0,0);

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

void desenharSol()
{
	glPushMatrix();
	glColor3f(1,1,0);
	rotSol+=1;
	rotacao(rotSol);
	glutWireSphere(raioSol*(1/scale),32,32);
	glPopMatrix();
}

void desenharMercurio()
{
	glPushMatrix();
	glTranslatef(1000*cos(0.0)*sin(time*0.2),1000*sin(0.0),1000*cos(0.0)*cos(time*0.2));
	glColor3f(0.5,0.5,0.5);//cinza
	rotMercurio+=0.2;
	rotacao(rotMercurio);
	glutWireSphere(raioMercurio,32,32);
	glPopMatrix();
	draw_Orbita(1000,90);
}

void desenharVenus()
{
	glPushMatrix();
	glTranslatef(1100*cos(0.0)*sin(time*0.6),1100*sin(0.0),1100*cos(0.0)*cos(time*0.6));
	glColor3f(0.6,0.5,0.1);//castanho
	rotVenus-=0.4;
	rotacao(rotVenus);
	glutWireSphere(raioVenus,32,32);
	glPopMatrix();
	draw_Orbita(1100,90);
}

void desenharLua()
{
	draw_Orbita(25,90);
	glTranslatef(25,0,0);
	glColor3f(1,1,1);//branco
	rotLua+=0.34;
	rotacao(rotLua);
	glutWireSphere(raioLua,32,32);
	
}

void desenharTerra()
{
	glPushMatrix();
	glTranslatef(1200*cos(0.0)*sin(time),1200*sin(0.0),1200*cos(0.0)*cos(time));
	glColor3f(0,0,1);//azul
	rotTerra+=0.34;
	rotacao(rotTerra);
	glutWireSphere(raioTerra,32,32);
	glPushMatrix();
	desenharLua();
	glPopMatrix();
	glPopMatrix();
	glColor3f(0,0,1);//azul
	draw_Orbita(1200,90);
}

void desenharMarte()
{
	glPushMatrix();
	glTranslatef(1300*cos(0.0)*sin(time),1300*sin(0.0),1300*cos(0.0)*cos(time));
	glColor3f(1,0,0);//vermelho
	rotMarte += 0.6;
	rotacao(rotMarte);
	glutWireSphere(raioMarte,32,32);
	glPopMatrix();
	draw_Orbita(1300,90);
}
void desenharJupiter()
{
	glPushMatrix();
	glTranslatef(2000*cos(0.0)*sin(time),2000*sin(0.0),2000*cos(0.0)*cos(time));
	glColor3f(1,1,0);//amarelo
	rotJupiter+=0.87;
	rotacao(rotJupiter);
	glutWireSphere(raioJupiter,32,32);
	glPopMatrix();
	draw_Orbita(2000,90);
}
void desenharSaturno()
{
	glPushMatrix();
	glTranslatef(2300*cos(0.0)*sin(time),2300*sin(0.0),2300*cos(0.0)*cos(time));
	glColor3f(1,0,1);//rosa
	rotSaturno+=0.65;
	rotacao(rotSaturno);
	glutWireSphere(raioSaturno,32,32);
	glPopMatrix();
	draw_Orbita(2300,90);
}
void desenharUrano()
{
	glPushMatrix();
	glTranslatef(2800*cos(0.0)*sin(time),2800*sin(0.0),2800*cos(0.0)*cos(time));
	glColor3f(0.8,0.1,0.4);//roxo
	rotUrano+=0.543;
	rotacao(rotUrano);
	glutWireSphere(raioUrano,32,32);
	glPopMatrix();
	draw_Orbita(2800,90);
}

void desenharNeptuno()
{
	glPushMatrix();
	glColor3f(0.12,0.432,0.123);//verde
	rotNeptuno+=1.23;
	glTranslatef(3200*cos(0.0)*sin(time),3200*sin(0.0),3200*cos(0.0)*cos(time));
	rotacao(rotNeptuno);
	glutWireSphere(raioNeptuno,32,32);
	glPopMatrix();
	draw_Orbita(3200,90);
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
