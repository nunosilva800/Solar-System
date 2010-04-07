#include "planetas.h"

//falta isto!
GLfloat rotSol = 0;
GLfloat rotLua = 0;


GLfloat angMercurio = 0;
GLfloat angVenus = 0;
GLfloat angTerra = 0;
GLfloat angMarte = 0;
GLfloat angJupiter = 0;
GLfloat angSaturno = 0;
GLfloat angUrano = 0;
GLfloat angNeptuno = 0;

GLfloat angRotMercurio = 0;
GLfloat angRotVenus = 0;
GLfloat angRotTerra = 0;
GLfloat angRotMarte = 0;
GLfloat angRotJupiter = 0;
GLfloat angRotSaturno = 0;
GLfloat angRotUrano = 0;
GLfloat angRotNeptuno = 0;

float scale = 100;
bool orbitas = true;
float distFactor = 0.1;
float timeFactor = 1;

GLuint cintura;


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
	glColor3f(1,1,0);//amarelo
	rotSol += velRSol*timeFactor;
	rotacao(rotSol,0.0);
	glutWireSphere(raioSol,32,32);
	glPopMatrix();
}

void desenharMercurio()
{
	glPushMatrix();
	glRotatef(orbitalTiltMercurio,0.0,0.0,1.0);

	angMercurio += (2*PI)/velMercurio*timeFactor;
	glTranslatef(distFactor*distSolMercurio*sin(angMercurio), 0, distFactor*distSolMercurio*cos(angMercurio));
	
	glColor3f(0.5,0.5,0.5);//cinza
	angRotMercurio += (2*PI)/velRMercurio*timeFactor;
	rotacao(angRotMercurio,axisTiltMercurio);
	glutWireSphere(scale*raioMercurio,32,32);
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolMercurio,90,0.0,orbitalTiltMercurio);
}

void desenharVenus()
{
	glPushMatrix();
	glRotatef(orbitalTiltVenus,0.0,0.0,1.0);
	angVenus += (2*PI)/velVenus*timeFactor;
	glTranslatef(distFactor*distSolVenus*sin(angVenus), 0, distFactor*distSolVenus*cos(angVenus));
	
	glColor3f(0.6,0.5,0.1);//castanho
	angRotVenus += (2*PI)/velRVenus*timeFactor;
	rotacao(angRotVenus,axisTiltVenus);
	glutWireSphere(scale*raioVenus,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distFactor*distSolVenus,90,0.0,orbitalTiltVenus);
}

void desenharLua()
{
	if(orbitas)draw_orbita(distFactor*scale*distTerraLua,90,0.0,0.0);
	glTranslatef(distFactor*scale*distTerraLua*sin(velLua), 0, distFactor*scale*distTerraLua*cos(velLua));

	glColor3f(1,1,1);//branco
	rotLua += velRLua*timeFactor;
	rotacao(rotLua,0.0);
	glutWireSphere(scale*raioLua,32,32);
	
}

void desenharTerra()
{
	glPushMatrix();
	glRotatef(orbitalTiltTerra,0.0,0.0,1.0);
	angTerra += (2*PI)/velTerra*timeFactor;
	glTranslatef(distFactor*distSolTerra*sin(angTerra), 0, distFactor*distSolTerra*cos(angTerra));
	
	glColor3f(0,0,1);//azul
	angRotTerra += (2*PI)/velRTerra*timeFactor;
	rotacao(angRotTerra,axisTiltTerra);
	glutWireSphere(scale*raioTerra,32,32);
	desenharLua();
	glPopMatrix();
	glColor3f(0,0,1);//azul
	
	if(orbitas)draw_orbita(distFactor*distSolTerra,90,0.0,orbitalTiltTerra);
}

void desenharMarte()
{
	glPushMatrix();
	glRotatef(orbitalTiltMarte,0.0,0.0,1.0);
	angMarte+= (2*PI)/velMarte*timeFactor;
	glTranslatef(distFactor*distSolMarte*sin(angMarte), 0, distFactor*distSolMarte*cos(angMarte));
	
	glColor3f(1,0,0);//vermelho
	angRotMarte += (2*PI)/velRMarte*timeFactor;
	rotacao(angRotMarte,axisTiltMarte);
	glutWireSphere(scale*raioMarte,32,32);
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolMarte,90,0.0,orbitalTiltMarte);
}
void desenharJupiter()
{
	glPushMatrix();
	glRotatef(orbitalTiltJupiter,0.0,0.0,1.0);
	angJupiter += 6.28318531/velJupiter*timeFactor;
	glTranslatef(distFactor*distSolJupiter*sin(angJupiter), 0, distFactor*distSolJupiter*cos(angJupiter));
	glColor3f(1,1,0);//amarelo
	
	angRotJupiter += (2*PI)/velRJupiter*timeFactor;
	rotacao(angRotJupiter,axisTiltJupiter);
	glutWireSphere(scale*raioJupiter,32,32);
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolJupiter,90,0.0,orbitalTiltJupiter);
}
void desenharSaturno()
{
	glPushMatrix();
	glRotatef(orbitalTiltSaturno,0.0,0.0,1.0);
	angSaturno+= (2*PI)/velSaturno*timeFactor;
	glTranslatef(distFactor*distSolSaturno*sin(angSaturno), 0, distFactor*distSolSaturno*cos(angSaturno));
	
	glColor3f(1,0,1);//rosa
	angRotSaturno += (2*PI)/velRSaturno*timeFactor;
	rotacao(angRotSaturno,axisTiltSaturno);
	glutWireSphere(scale*raioSaturno,32,32);
	
	glPushMatrix();
	glRotatef(90.0,1.0,0.0,0.0);
	glScalef(1,1,0.1);
	desenharAnel(43,150);
	glPopMatrix();
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolSaturno,90,0.0,orbitalTiltSaturno);
}
void desenharUrano()
{
	glPushMatrix();
	glRotatef(orbitalTiltUrano,0.0,0.0,1.0);
	angUrano+= (2*PI)/velUrano*timeFactor;
	glTranslatef(distFactor*distSolUrano*sin(angUrano), 0, distFactor*distSolUrano*cos(angUrano));
	
	glColor3f(0.8,0.1,0.4);//roxo
	angRotUrano += (2*PI)/velRUrano*timeFactor;
	rotacao(angRotUrano,axisTiltUrano);
	glutWireSphere(scale*raioUrano,32,32);
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolUrano,90,0.0,orbitalTiltUrano);
}

void desenharNeptuno()
{
	glPushMatrix();
	glRotatef(orbitalTiltNeptuno,0.0,0.0,1.0);
	angNeptuno += (2*PI)/velNeptuno*timeFactor;
	glTranslatef(distFactor*distSolNeptuno*sin(angNeptuno), 0, distFactor*distSolNeptuno*cos(angNeptuno));
	
	glColor3f(0.12,0.432,0.123);//verde
	angRotNeptuno = (2*PI)/velRNeptuno*timeFactor;
	rotacao(angRotNeptuno,axisTiltNeptuno);
	glutWireSphere(scale*raioNeptuno,32,32);
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolNeptuno,90,0.0,orbitalTiltNeptuno);
}

void desenharCintura(){
	int i=0;
	float dist, ang, x, z;
	
	cintura = glGenLists( 1 );
	glNewList( cintura, GL_COMPILE );
	
	srand(30);
	glColor3f(0.5,0.5,0.2);
	glBegin(GL_POINTS);
	//existem 700,000 a 1.7 milhoens... mas para simplificar...
	for(i=0; i<100000; i++){
		dist = rand();
		ang = rand() / 3.1415;
		x = cos(ang) * (dist + distSolMarte*1.2*distFactor);
		z = sin(ang) * (dist + distSolMarte*1.2*distFactor);
		if(sqrt(x*x+z*z) < distSolJupiter*0.7*distFactor)
			glVertex3f(x, 0, z);
		else i--;
	}
	glEnd();

	glEndList();
}

void planetas(){
	desenharSol();
	desenharMercurio();
	desenharVenus();
	desenharTerra();
	desenharMarte();
	desenharJupiter();
	desenharSaturno();
	desenharUrano();
	desenharNeptuno();

	//glCallList(cintura);

}
