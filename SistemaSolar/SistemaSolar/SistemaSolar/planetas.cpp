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
bool orbitas = true;

float time = 0;

void rotacao(GLfloat rotacao,float tilt)
{
	glRotatef(tilt,0.0,0.0,1.0);
	glRotated(rotacao,0.0,1.0,0.0);
	
	glutPostRedisplay();
}

void draw_orbita(float raio, float angleX,float angleY, float angleZ){
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
	glTranslatef(distSolMercurio*sin(time), 0, distSolMercurio*cos(time));
	glColor3f(0.5,0.5,0.5);//cinza
	rotMercurio += 58.646;
	rotacao(rotMercurio,0.0);
	glutWireSphere(raioMercurio,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distSolMercurio,90,0.0,0.0);
}

void desenharVenus()
{
	glPushMatrix();
	glTranslatef(distSolMercurio*sin(time), 0, distSolMercurio*cos(time));
	glColor3f(0.6,0.5,0.1);//castanho
	rotVenus += -243.0185;
	rotacao(rotVenus,0.0);
	glutWireSphere(raioVenus,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distSolMercurio,90,0.0,0.0);
}

void desenharLua()
{
	if(orbitas)draw_orbita(distTerraLua,90,0.0,0.0);
	glTranslatef(distTerraLua*sin(time), 0, distTerraLua*sin(time));
	glColor3f(1,1,1);//branco
	rotLua += 27.321582;
	rotacao(rotLua,0.0);
	glutWireSphere(raioLua,32,32);
	
}

void desenharTerra()
{
	glPushMatrix();
	glTranslatef(distSolTerra*sin(time), 0, distSolTerra*cos(time));
	glColor3f(0,0,1);//azul
	rotTerra += 1;
	rotacao(rotTerra,0.0);
	glutWireSphere(raioTerra,32,32);
	desenharLua();
	glPopMatrix();
	glColor3f(0,0,1);//azul
	if(orbitas)draw_orbita(distSolTerra,90,0.0,0.0);
}

void desenharMarte()
{
	glPushMatrix();
	glTranslatef(distSolMarte*sin(time), 0, distSolMarte*cos(time));
	glColor3f(1,0,0);//vermelho
	rotMarte += 1.025957;
	rotacao(rotMarte,0.0);
	glutWireSphere(raioMarte,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distSolMarte,90,0.0,0.0);
}
void desenharJupiter()
{
	glPushMatrix();
	glRotatef(orbitalTiltJupiter,0.0,0.0,1.0);
	glTranslatef(distSolJupiter*sin(time), 0, distSolJupiter*cos(time));
	glColor3f(1,1,0);//amarelo
	rotJupiter += 0.413541667;
	rotacao(rotJupiter,axisTiltJupiter);
	glutWireSphere(raioJupiter,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distSolJupiter,90,0.0,orbitalTiltJupiter);
}
void desenharSaturno()
{
	glPushMatrix();
	glTranslatef(distSolSaturno*sin(time), 0, distSolSaturno*cos(time));
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
	if(orbitas)draw_orbita(distSolSaturno,90,0.0,0.0);
}
void desenharUrano()
{
	glPushMatrix();
	glTranslatef(distSolUrano*sin(time), 0, distSolUrano*cos(time));
	glColor3f(0.8,0.1,0.4);//roxo
	rotUrano += -0.71833;
	rotacao(rotUrano,0.0);
	glutWireSphere(raioUrano,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distSolUrano,90,0.0,0.0);
}

void desenharNeptuno()
{
	glPushMatrix();
	glColor3f(0.12,0.432,0.123);//verde
	rotNeptuno += 0.6713;
	glTranslatef(distSolNeptuno*sin(time), 0, distSolNeptuno*cos(time));
	rotacao(rotNeptuno,0.0);
	glutWireSphere(raioNeptuno,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distSolNeptuno,90,0.0,0.0);
}

void planetas(){
	time +=0.001;
	desenharSol();
	desenharMercurio();
	desenharVenus();
	desenharTerra();
	desenharMarte();
	desenharJupiter();
	desenharSaturno();
	desenharUrano();
	desenharNeptuno();
}
