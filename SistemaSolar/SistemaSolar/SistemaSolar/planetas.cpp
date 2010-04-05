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

float scale = 10;
bool orbitas = true;
float distFactor = 1.0;
float time = 0;
float timeFactor = 0.0001;

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
	glutWireSphere(scale*raioSol*(1/scale),32,32);
	glPopMatrix();
}

void desenharMercurio()
{
	glPushMatrix();
	glTranslatef(distFactor*distSolMercurio*sin(velMercurio*time), 0, distFactor*distSolMercurio*cos(velMercurio*time));
	glColor3f(0.5,0.5,0.5);//cinza
	rotMercurio += 58.646;
	rotacao(rotMercurio,0.0);
	glutWireSphere(scale*raioMercurio,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distFactor*distSolMercurio,90,0.0,0.0);
}

void desenharVenus()
{
	glPushMatrix();
	glTranslatef(distFactor*distSolVenus*sin(velVenus*time), 0, distFactor*distSolVenus*cos(velVenus*time));
	glColor3f(0.6,0.5,0.1);//castanho
	rotVenus += -243.0185;
	rotacao(rotVenus,0.0);
	glutWireSphere(scale*raioVenus,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distFactor*distSolVenus,90,0.0,0.0);
}

void desenharLua()
{
	if(orbitas)draw_orbita(distFactor*distTerraLua,90,0.0,0.0);
	glTranslatef(distFactor*distTerraLua*sin(velLua*time), 0, distFactor*distTerraLua*10*sin(velLua*time));
	glColor3f(1,1,1);//branco
	rotLua += 27.321582;
	rotacao(rotLua,0.0);
	glutWireSphere(scale*raioLua,32,32);
	
}

void desenharTerra()
{
	glPushMatrix();
	glTranslatef(distFactor*distSolTerra*sin(velTerra*time), 0, distFactor*distSolTerra*cos(velTerra*time));
	glColor3f(0,0,1);//azul
	rotTerra += 1;
	rotacao(rotTerra,0.0);
	glutWireSphere(scale*raioTerra,32,32);
	desenharLua();
	glPopMatrix();
	glColor3f(0,0,1);//azul
	if(orbitas)draw_orbita(distFactor*distSolTerra,90,0.0,0.0);
}

void desenharMarte()
{
	glPushMatrix();
	glTranslatef(distFactor*distSolMarte*sin(velMarte*time), 0, distFactor*distSolMarte*cos(velMarte*time));
	glColor3f(1,0,0);//vermelho
	rotMarte += 1.025957;
	rotacao(rotMarte,0.0);
	glutWireSphere(scale*raioMarte,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distFactor*distSolMarte,90,0.0,0.0);
}
void desenharJupiter()
{
	glPushMatrix();
	glRotatef(orbitalTiltJupiter,0.0,0.0,1.0);
	glTranslatef(distFactor*distSolJupiter*sin(velJupiter*time), 0, distFactor*distSolJupiter*cos(velJupiter*time));
	glColor3f(1,1,0);//amarelo
	rotJupiter += 0.413541667;
	rotacao(rotJupiter,axisTiltJupiter);
	glutWireSphere(scale*raioJupiter,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distFactor*distSolJupiter,90,0.0,orbitalTiltJupiter);
}
void desenharSaturno()
{
	glPushMatrix();
	glTranslatef(distFactor*distSolSaturno*sin(velSaturno*time), 0, distFactor*distSolSaturno*cos(velSaturno*time));
	glColor3f(1,0,1);//rosa
	rotSaturno += 0.440416667;
	rotacao(rotSaturno,0.0);
	glutWireSphere(scale*raioSaturno,32,32);
	glPushMatrix();
	glRotatef(90.0,1.0,0.0,0.0);
	glScalef(1,1,0.1);
	desenharAnel(43,150);
	glPopMatrix();
	glPopMatrix();
	if(orbitas)draw_orbita(distFactor*distSolSaturno,90,0.0,0.0);
}
void desenharUrano()
{
	glPushMatrix();
	glTranslatef(distFactor*distSolUrano*sin(velUrano*time), 0, distFactor*distSolUrano*cos(velUrano*time));
	glColor3f(0.8,0.1,0.4);//roxo
	rotUrano += -0.71833;
	rotacao(rotUrano,0.0);
	glutWireSphere(scale*raioUrano,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distFactor*distSolUrano,90,0.0,0.0);
}

void desenharNeptuno()
{
	glPushMatrix();
	glColor3f(0.12,0.432,0.123);//verde
	rotNeptuno += 0.6713;
	glTranslatef(distFactor*distSolNeptuno*sin(velNeptuno*time), 0, distFactor*distSolNeptuno*cos(velNeptuno*time));
	rotacao(rotNeptuno,0.0);
	glutWireSphere(scale*raioNeptuno,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distFactor*distSolNeptuno,90,0.0,0.0);
}

void desenharCintura(){
	int i=0;
	float dist, ang, x, z;
	
	srand(30);

	glColor3f(0.5,0.5,0.2);
	glBegin(GL_POINTS);
	for(i=0; i<10000; i++){
		dist = rand();
		ang = rand();
		x = cos(ang) * (dist + distSolMarte*1.2);
		z = sin(ang) * (dist + distSolMarte*1.2);
		if(fabs(x) < distSolJupiter && fabs(z) < distSolJupiter)
			glVertex3f(x, 0, z);
	}
	glEnd();
	
}

void planetas(){
	time += timeFactor;
	desenharSol();
	desenharMercurio();
	desenharVenus();
	desenharTerra();
	desenharMarte();
	desenharJupiter();
	desenharSaturno();
	desenharUrano();
	desenharNeptuno();
	desenharCintura();
}
