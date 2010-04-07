#include "planetas.h"

//falta isto!

GLfloat rotDemios = 0;


GLfloat angMercurio = 0;
GLfloat angVenus = 0;
GLfloat angTerra = 0;
GLfloat angMarte = 0;
GLfloat angJupiter = 0;
GLfloat angSaturno = 0;
GLfloat angUrano = 0;
GLfloat angNeptuno = 0;
GLfloat angLua = 0;

GLfloat angRotSol = 0;
GLfloat angRotMercurio = 0;
GLfloat angRotVenus = 0;
GLfloat angRotTerra = 0;
GLfloat angRotMarte = 0;
GLfloat angRotJupiter = 0;
GLfloat angRotSaturno = 0;
GLfloat angRotUrano = 0;
GLfloat angRotNeptuno = 0;
GLfloat angRotLua = 0;

float scale = 50;
float scalesol = scale*0.5;
bool orbitas = true;

bool drawCintura = true;
float distFactor = 0.1;

float timeFactor = 0.05;

GLuint cintura;
GLuint estrelas;

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

void desenharSol()
{
	glPushMatrix();
	glColor3f(1,1,0);//amarelo

	rotSol += velRSol*timeFactor;
	rotacao(scalesol*rotSol,0.0);

	glutWireSphere(raioSol,32,32);
	glPopMatrix();
}

void desenharMercurio()
{
	glPushMatrix();
	glRotatef(orbitalTiltMercurio,0.0,0.0,1.0);

	angMercurio += ((2*PI)/velMercurio)*timeFactor;
	glTranslatef(distFactor*distSolMercurio*sin(angMercurio), 0, distFactor*distSolMercurio*cos(angMercurio));
	
	glColor3f(0.5,0.5,0.5);//cinza
	angRotMercurio += (360/velRMercurio)*timeFactor;
	rotacao(angRotMercurio,axisTiltMercurio);
	glutWireSphere(scale*raioMercurio,32,32);
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolMercurio,90,0.0,orbitalTiltMercurio);
}

void desenharVenus()
{
	glPushMatrix();
	glRotatef(orbitalTiltVenus,0.0,0.0,1.0);
	angVenus += ((2*PI)/velVenus)*timeFactor;
	glTranslatef(distFactor*distSolVenus*sin(angVenus), 0, distFactor*distSolVenus*cos(angVenus));
	
	glColor3f(0.6,0.5,0.1);//castanho
	angRotVenus += (360/velRVenus)*timeFactor;
	rotacao(angRotVenus,axisTiltVenus);
	glutWireSphere(scale*raioVenus,32,32);
	glPopMatrix();
	if(orbitas)draw_orbita(distFactor*distSolVenus,90,0.0,orbitalTiltVenus);
}

void desenharLua()
{
	glPushMatrix();
	if(orbitas)draw_orbita(distFactor*scale*distTerraLua,90,0.0,0.0);
	angLua += ((2*PI)/velLua)*timeFactor;
	glTranslatef(distFactor*scale*distTerraLua*sin(angLua), 0, distFactor*scale*distTerraLua*cos(angLua));

	glColor3f(1,1,1);//branco
	angRotLua += (360/velRLua)*timeFactor;
	rotacao(angRotLua,0.0);
	glutWireSphere(scale*raioLua,32,32);
	glPopMatrix();
}

void desenharTerra()
{
	glPushMatrix();
	glRotatef(orbitalTiltTerra,0.0,0.0,1.0);
	angTerra += ((2*PI)/velTerra)*timeFactor;
	glTranslatef(distFactor*distSolTerra*sin(angTerra), 0, distFactor*distSolTerra*cos(angTerra));
	
	glColor3f(0,0,1);//azul
	//angRotTerra += ((0.25*360)/velRTerra)*timeFactor;
	angRotTerra += (360/velRTerra)*timeFactor;

	//experiencia
	//printf("angTransTerra: %f      angRotTerra: %f\n",(angTerra*(180/PI)),angRotTerra/360);
	
	rotacao(angRotTerra,axisTiltTerra);
	glutWireSphere(scale*raioTerra,32,32);
	desenharLua();
	glPopMatrix();
	glColor3f(0,0,1);//azul
	
	if(orbitas)draw_orbita(distFactor*distSolTerra,90,0.0,orbitalTiltTerra);
}

void desenharFobos()
{
	glPushMatrix();

	if(orbitas)draw_orbita(distFactor*scale*distMarteFobos,90,0.0,0.0);
	glTranslatef(distFactor*scale*distMarteFobos*sin(velRFobos), 0, distFactor*scale*distMarteFobos*cos(velRFobos));

	glColor3f(1,1,1);//branco
	rotLua += velRFobos*timeFactor;
	rotacao(rotLua,0.0);
	glutWireSphere(scale*raioFobos,32,32);

	glPopMatrix();
}

void desenharDeimos()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distMarteDeimos,90,0.0,0.0);
	glTranslatef(distFactor*scale*distMarteDeimos*sin(velRDeimos), 0, distFactor*scale*distMarteDeimos*cos(velRDeimos));

	rotDemios += velRDeimos*timeFactor;
	rotacao(rotDemios,0.0);
	glutWireSphere(scale*raioDeimos,32,32);
	glPopMatrix();
}

void desenharMarte()
{
	glPushMatrix();
	glRotatef(orbitalTiltMarte,0.0,0.0,1.0);
	angMarte+= ((2*PI)/velMarte)*timeFactor;
	glTranslatef(distFactor*distSolMarte*sin(angMarte), 0, distFactor*distSolMarte*cos(angMarte));
	
	glColor3f(1,0,0);//vermelho
	angRotMarte += (360/velRMarte)*timeFactor;
	rotacao(angRotMarte,axisTiltMarte);
	glutWireSphere(scale*raioMarte,32,32);
	
	desenharDeimos();
	desenharFobos();

	glPopMatrix();
	glColor3f(1.0,0.0,0.0);	
	if(orbitas)draw_orbita(distFactor*distSolMarte,90,0.0,orbitalTiltMarte);
}

void desenharIO()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distJupiterIo,90,0.0,0.0);
	glTranslatef(distFactor*scale*distJupiterIo*sin(velRIo), 0, distFactor*scale*distJupiterIo*cos(velRIo));

	glutWireSphere(scale*raioIo,32,32);
	glPopMatrix();
}

void desenharEuropa()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distJupiterEuropa,90,0.0,0.0);
	glTranslatef(distFactor*scale*distJupiterEuropa*sin(velREuropa), 0, distFactor*scale*distJupiterEuropa*cos(velREuropa));

	glutWireSphere(scale*raioEuropa,32,32);
	glPopMatrix();
}

void desenharGanimedes()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distJupiterGanymede,90,0.0,0.0);
	glTranslatef(distFactor*scale*distJupiterGanymede*sin(velRGanimedes), 0, distFactor*scale*distJupiterGanymede*cos(velRGanimedes));

	glutWireSphere(scale*raioGanymede,32,32);
	glPopMatrix();
}

void desenharCalisto()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distJupiterCalisto,90,0.0,0.0);
	glTranslatef(distFactor*scale*distJupiterCalisto*sin(velRCalisto), 0, distFactor*scale*distJupiterCalisto*cos(velRCalisto));

	glutWireSphere(scale*raioCalisto,32,32);
	glPopMatrix();
}

void desenharJupiter()
{
	glPushMatrix();
	glRotatef(orbitalTiltJupiter,0.0,0.0,1.0);
	angJupiter += ((2*PI)/velJupiter)*timeFactor;
	glTranslatef(distFactor*distSolJupiter*sin(angJupiter), 0, distFactor*distSolJupiter*cos(angJupiter));
	glColor3f(1,1,0);//amarelo
	
	angRotJupiter += (360/velRJupiter)*timeFactor;
	rotacao(angRotJupiter,axisTiltJupiter);
	glutWireSphere(scale*raioJupiter,32,32);
	
	desenharIO();
	desenharEuropa();
	desenharGanimedes();
	desenharCalisto();

	glPopMatrix();
	glColor3f(1,1,0);//amarelo
	if(orbitas)draw_orbita(distFactor*distSolJupiter,90,0.0,orbitalTiltJupiter);
}

void desenharRhea()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distSaturnoRhea,90,0.0,0.0);
	glTranslatef(distFactor*scale*distSaturnoRhea*sin(velRReia), 0, distFactor*scale*distSaturnoRhea*cos(velRReia));

	glutWireSphere(scale*raioRhea,32,32);
	glPopMatrix();
}

void desenharTitan()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distSaturnoTitan,90,0.0,0.0);
	glTranslatef(distFactor*scale*distSaturnoTitan*sin(velRTita), 0, distFactor*scale*distSaturnoTitan*cos(velRTita));

	glutWireSphere(scale*raioTitan,32,32);
	glPopMatrix();
}

void desenharIapetus()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distSaturnoIapetus,90,0.0,0.0);
	glTranslatef(distFactor*scale*distSaturnoIapetus*sin(velRJapeto), 0, distFactor*scale*distSaturnoIapetus*cos(velRJapeto));

	glutWireSphere(scale*raioIapetus,32,32);
	glPopMatrix();
}

void desenharSaturno()
{
	glPushMatrix();
	glRotatef(orbitalTiltSaturno,0.0,0.0,1.0);
	angSaturno+= ((2*PI)/velSaturno)*timeFactor;
	glTranslatef(distFactor*distSolSaturno*sin(angSaturno), 0, distFactor*distSolSaturno*cos(angSaturno));
	
	glColor3f(1,0,1);//rosa
	angRotSaturno += (360/velRSaturno)*timeFactor;
	rotacao(angRotSaturno,axisTiltSaturno);
	glutWireSphere(scale*raioSaturno,32,32);

	glPushMatrix();
	glRotatef(90.0,1.0,0.0,0.0);
	glScalef(1,1,0.1);
	
	glColor3f(1,0,0);
	glutSolidTorus(0.3*raioSaturno*scale,1.8*raioSaturno*scale,360,150);
	glPopMatrix();

	desenharRhea();
	desenharTitan();
	desenharIapetus();

	glPopMatrix();
	glColor3f(1,0,1);//rosa
	if(orbitas)draw_orbita(distFactor*distSolSaturno,90,0.0,orbitalTiltSaturno);
}
void desenharUrano()
{
	glPushMatrix();
	glRotatef(orbitalTiltUrano,0.0,0.0,1.0);
	angUrano+= ((2*PI)/velUrano)*timeFactor;
	glTranslatef(distFactor*distSolUrano*sin(angUrano), 0, distFactor*distSolUrano*cos(angUrano));
	
	glColor3f(0.8,0.1,0.4);//roxo
	angRotUrano += (360/velRUrano)*timeFactor;
	rotacao(angRotUrano,axisTiltUrano);
	glutWireSphere(scale*raioUrano,32,32);
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolUrano,90,0.0,orbitalTiltUrano);
}

void desenharNeptuno()
{
	glPushMatrix();
	glRotatef(orbitalTiltNeptuno,0.0,0.0,1.0);
	angNeptuno += ((2*PI)/velNeptuno)*timeFactor;
	glTranslatef(distFactor*distSolNeptuno*sin(angNeptuno), 0, distFactor*distSolNeptuno*cos(angNeptuno));
	
	glColor3f(0.12,0.432,0.123);//verde
	angRotNeptuno = (360/velRNeptuno)*timeFactor;
	rotacao(angRotNeptuno,axisTiltNeptuno);
	glutWireSphere(scale*raioNeptuno,32,32);
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolNeptuno,90,0.0,orbitalTiltNeptuno);
}

void desenharCintura(){
	if(!drawCintura) return;

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


void desenharEstrelas()
{
	float x, y, z, elevation, alt;
	srand(30);
	estrelas = glGenLists( 2 );
	glNewList ( estrelas, GL_COMPILE );

	glBegin ( GL_POINTS );
	for ( int i = 0; i < MAX_STARS; i++ ){
	   elevation  = rand ( );
	   alt    = rand ( );

        y = STAR_RADIUS * sin ( elevation );
        x = STAR_RADIUS * cos ( elevation ) * cos ( alt );
        z = STAR_RADIUS * cos ( elevation ) * sin ( alt );

        glColor3f(1,1,1);
		glVertex3f ( x, y, z );
	}
	glEnd ( );
	glEndList ( );
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

	if(drawCintura)	glCallList(cintura);

	glCallList(estrelas);
}
