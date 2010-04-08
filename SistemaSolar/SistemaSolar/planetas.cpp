#include "planetas.h"
#include "texturas.h"

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

GLfloat angFobos = 0;
GLfloat angDeimos =0;
GLfloat angIO = 0;
GLfloat angEuropa = 0;
GLfloat angGanimedes = 0;
GLfloat angCalisto = 0;

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

GLfloat angRotFobos =0;
GLfloat angRotDeimos =0;
GLfloat angRotIO =0;
GLfloat angRotEuropa =0;
GLfloat angRotGanimedes =0;
GLfloat angRotCalisto =0;
GLfloat angRotRhea =0;
GLfloat angRotTitan =0;
GLfloat angRotIapetus =0;


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

void desenharSol(GLuint texture, GLUquadric *  Q)
{
	glPushMatrix();
	//glColor3f(1,1,0);//amarelo
	angRotSol += (360/velRSol)*timeFactor;
	rotacao(angRotSol,0.0);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);
	gluSphere (Q,raioSol,32,32);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void desenharMercurio(GLuint texture, GLUquadric *  Q)
{
	glPushMatrix();
	glRotatef(orbitalTiltMercurio,0.0,0.0,1.0);

	angMercurio += ((2*PI)/velMercurio)*timeFactor;
	glTranslatef(distFactor*distSolMercurio*sin(angMercurio), 0, distFactor*distSolMercurio*cos(angMercurio));
	
	//glColor3f(0.5,0.5,0.5);//cinza
	angRotMercurio += (360/velRMercurio)*timeFactor;
	rotacao(angRotMercurio,axisTiltMercurio);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);
	gluSphere (Q,scale*raioMercurio,32,32);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolMercurio,90,0.0,orbitalTiltMercurio);
}

void desenharVenus(GLuint texture, GLUquadric *  Q)
{
	glPushMatrix();
	glRotatef(orbitalTiltVenus,0.0,0.0,1.0);
	angVenus += ((2*PI)/velVenus)*timeFactor;
	glTranslatef(distFactor*distSolVenus*sin(angVenus), 0, distFactor*distSolVenus*cos(angVenus));
	//glColor3f(0.6,0.5,0.1);//castanho
	angRotVenus += (360/velRVenus)*timeFactor;
	rotacao(angRotVenus,axisTiltVenus);
	glRotatef(90,1,0,0);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	gluSphere (Q,scale*raioVenus,32,32);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	if(orbitas)draw_orbita(distFactor*distSolVenus,90,0.0,orbitalTiltVenus);
}

void desenharLua(GLuint texture, GLUquadric * Q)
{
	glPushMatrix();
	if(orbitas)draw_orbita(distFactor*scale*distTerraLua,90,0.0,0.0);
	angLua += (((2*PI)/velLua)-((360/velRTerra)*(PI/180)))*timeFactor;
	glTranslatef(distFactor*scale*distTerraLua*sin(angLua), 0, distFactor*scale*distTerraLua*cos(angLua));
    glRotatef(-90,1,0,0);
	//glColor3f(1,1,1);//branco
	angRotLua += (360/velRLua)*timeFactor;
	rotacao(angRotLua,axisTiltLua);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	gluSphere (Q,scale*raioLua,32,32);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void desenharTerra(GLuint texture, GLUquadric *  Q, GLuint texture2, GLUquadric *  Q2)
{
	glPushMatrix();
	glRotatef(orbitalTiltTerra,0.0,0.0,1.0);
	angTerra += ((2*PI)/velTerra)*timeFactor;
	glTranslatef(distFactor*distSolTerra*sin(angTerra), 0, distFactor*distSolTerra*cos(angTerra));
	
	//glColor3f(0,0,1);//azul
	//angRotTerra += ((0.25*360)/velRTerra)*timeFactor;
	angRotTerra += (360/velRTerra)*timeFactor;

	//experiencia
	//printf("angTransTerra: %f      angRotTerra: %f\n",(angTerra*(180/PI)),angRotTerra/360);
	
	rotacao(angRotTerra,axisTiltTerra);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);
	gluSphere (Q,scale*raioTerra,32,32);
	glDisable(GL_TEXTURE_2D);
	glRotatef(90,1,0,0);
	desenharLua(texture2, Q2);
	glPopMatrix();
	//glColor3f(0,0,1);//azul
	
	if(orbitas)draw_orbita(distFactor*distSolTerra,90,0.0,orbitalTiltTerra);
}

void desenharFobos()
{
	glPushMatrix();

	if(orbitas)draw_orbita(distFactor*scale*distMarteFobos,90,0.0,0.0);
	angFobos += (((2*PI)/velLua)-((360/velRMarte)*(PI/180)))*timeFactor;
	glTranslatef(distFactor*scale*distMarteFobos*sin(angFobos), 0, distFactor*scale*distMarteFobos*cos(angFobos));

	angRotFobos += (360/velRFobos)*timeFactor;
	rotacao(angRotFobos,0.0);
	
	glutWireSphere(scale*raioFobos,32,32);

	glPopMatrix();
}

void desenharDeimos()
{
	glPushMatrix();
	
	if(orbitas)draw_orbita(distFactor*scale*distMarteDeimos,90,0.0,0.0);
	angDeimos += (((2*PI)/velLua)-((360/velRMarte)*(PI/180)))*timeFactor;
	glTranslatef(distFactor*scale*distMarteDeimos*sin(angDeimos), 0, distFactor*scale*distMarteDeimos*cos(angDeimos));

	angRotDeimos += (360/velRDeimos)*timeFactor;
	rotacao(angRotDeimos,0.0);

	glutWireSphere(scale*raioDeimos,32,32);

	glPopMatrix();
}

void desenharMarte(GLuint texture, GLUquadric *  Q)
{
	glPushMatrix();
	glRotatef(orbitalTiltMarte,0.0,0.0,1.0);
	angMarte+= ((2*PI)/velMarte)*timeFactor;
	glTranslatef(distFactor*distSolMarte*sin(angMarte), 0, distFactor*distSolMarte*cos(angMarte));
	
	//glColor3f(1,0,0);//vermelho
	angRotMarte += (360/velRMarte)*timeFactor;
	rotacao(angRotMarte,axisTiltMarte);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);
	gluSphere (Q,scale*raioMarte,32,32);
	glDisable(GL_TEXTURE_2D);

	desenharDeimos();
	desenharFobos();
	
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolMarte,90,0.0,orbitalTiltMarte);
}

void desenharIO()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distJupiterIo,90,0.0,0.0);
	angIO += (((2*PI)/velLua)-((360/velRJupiter)*(PI/180)))*timeFactor;
	glTranslatef(distFactor*scale*distJupiterIo*sin(angIO), 0, distFactor*scale*distJupiterIo*cos(angIO));
	
	angRotIO += (360/velRIo)*timeFactor;
	rotacao(angRotIO,0.0);

	glutWireSphere(scale*raioIo,32,32);
	glPopMatrix();
}

void desenharEuropa()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distJupiterEuropa,90,0.0,0.0);
	angEuropa += (((2*PI)/velLua)-((360/velRJupiter)*(PI/180)))*timeFactor;
	glTranslatef(distFactor*scale*distJupiterEuropa*sin(angEuropa), 0, distFactor*scale*distJupiterEuropa*cos(angEuropa));

	angRotEuropa += (360/velREuropa)*timeFactor;
	rotacao(angRotEuropa,0.0);

	glutWireSphere(scale*raioEuropa,32,32);
	glPopMatrix();
}

void desenharGanimedes()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distJupiterGanymede,90,0.0,0.0);
	angGanimedes += (((2*PI)/velLua)-((360/velRJupiter)*(PI/180)))*timeFactor;
	glTranslatef(distFactor*scale*distJupiterGanymede*sin(angGanimedes), 0, distFactor*scale*distJupiterGanymede*cos(angGanimedes));

	angRotGanimedes += (360/velRGanimedes)*timeFactor;
	rotacao(angRotGanimedes,0.0);

	glutWireSphere(scale*raioGanymede,32,32);
	glPopMatrix();
}

void desenharCalisto()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distJupiterCalisto,90,0.0,0.0);
	angCalisto += (((2*PI)/velLua)-((360/velRJupiter)*(PI/180)))*timeFactor;
	glTranslatef(distFactor*scale*distJupiterCalisto*sin(angCalisto), 0, distFactor*scale*distJupiterCalisto*cos(angCalisto));

	angRotCalisto += (360/velRCalisto)*timeFactor;
	rotacao(angRotCalisto,0.0);

	glutWireSphere(scale*raioCalisto,32,32);
	glPopMatrix();
}

void desenharJupiter(GLuint texture, GLUquadric *  Q)
{
	glPushMatrix();
	glRotatef(orbitalTiltJupiter,0.0,0.0,1.0);
	angJupiter += ((2*PI)/velJupiter)*timeFactor;
	glTranslatef(distFactor*distSolJupiter*sin(angJupiter), 0, distFactor*distSolJupiter*cos(angJupiter));
	//glColor3f(1,1,0);//amarelo
	
	angRotJupiter += (360/velRJupiter)*timeFactor;
	rotacao(angRotJupiter,axisTiltJupiter);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);
	gluSphere (Q,scale*raioJupiter,32,32);
	glDisable(GL_TEXTURE_2D);
	glRotatef(90,1,0,0);
	desenharIO();
	desenharEuropa();
	desenharGanimedes();
	desenharCalisto();

	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolJupiter,90,0.0,orbitalTiltJupiter);
}

void desenharRhea()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distSaturnoRhea,90,0.0,0.0);
	glTranslatef(distFactor*scale*distSaturnoRhea*sin(velRReia), 0, distFactor*scale*distSaturnoRhea*cos(velRReia));

	angRotRhea += (360/velRReia)*timeFactor;
	rotacao(angRotRhea,0.0);

	glutWireSphere(scale*raioRhea,32,32);
	glPopMatrix();
}

void desenharTitan()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distSaturnoTitan,90,0.0,0.0);
	glTranslatef(distFactor*scale*distSaturnoTitan*sin(velRTita), 0, distFactor*scale*distSaturnoTitan*cos(velRTita));

	angRotTitan += (360/velRTita)*timeFactor;
	rotacao(angRotTitan,0.0);

	glutWireSphere(scale*raioTitan,32,32);
	glPopMatrix();
}

void desenharIapetus()
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distSaturnoIapetus,90,0.0,0.0);
	glTranslatef(distFactor*scale*distSaturnoIapetus*sin(velRJapeto), 0, distFactor*scale*distSaturnoIapetus*cos(velRJapeto));

	angRotIapetus += (360/velRJapeto)*timeFactor;
	rotacao(angRotIapetus,0.0);

	glutWireSphere(scale*raioIapetus,32,32);
	glPopMatrix();
}

void desenharSaturno(GLuint texture, GLUquadric *  Q)
{
	int i=0;
	float dist, ang, x, z;
	
	glPushMatrix();
	glRotatef(orbitalTiltSaturno,0.0,0.0,1.0);
	angSaturno+= ((2*PI)/velSaturno)*timeFactor;
	glTranslatef(distFactor*distSolSaturno*sin(angSaturno), 0, distFactor*distSolSaturno*cos(angSaturno));
	
	//glColor3f(1,0,1);//rosa
	angRotSaturno += (360/velRSaturno)*timeFactor;
	rotacao(angRotSaturno,axisTiltSaturno);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);
	gluSphere (Q,scale*raioSaturno,32,32);
	glDisable(GL_TEXTURE_2D);
	glRotatef(90,1,0,0);
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
	//glColor3f(1,0,1);//rosa
	if(orbitas)draw_orbita(distFactor*distSolSaturno,90,0.0,orbitalTiltSaturno);
}
void desenharUrano(GLuint texture, GLUquadric *  Q)
{
	glPushMatrix();
	glRotatef(orbitalTiltUrano,0.0,0.0,1.0);
	angUrano+= ((2*PI)/velUrano)*timeFactor;
	glTranslatef(distFactor*distSolUrano*sin(angUrano), 0, distFactor*distSolUrano*cos(angUrano));
	
	//glColor3f(0.8,0.1,0.4);//roxo
	angRotUrano += (360/velRUrano)*timeFactor;
	rotacao(angRotUrano,axisTiltUrano);
	glRotatef(90,1,0,0);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	gluSphere (Q,scale*raioUrano,32,32);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolUrano,90,0.0,orbitalTiltUrano);
}

void desenharNeptuno(GLuint texture, GLUquadric *  Q)
{
	glPushMatrix();
	glRotatef(orbitalTiltNeptuno,0.0,0.0,1.0);
	angNeptuno += ((2*PI)/velNeptuno)*timeFactor;
	glTranslatef(distFactor*distSolNeptuno*sin(angNeptuno), 0, distFactor*distSolNeptuno*cos(angNeptuno));
	
	//glColor3f(0.12,0.432,0.123);//verde
	angRotNeptuno += (360/velRNeptuno)*timeFactor;
	rotacao(angRotNeptuno,axisTiltNeptuno);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);
	gluSphere (Q,scale*raioNeptuno,32,32);
	glDisable(GL_TEXTURE_2D);
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
	desenharSol(texture[0], Qplanetas[0]);
	desenharMercurio(texture[1], Qplanetas[1]);
	desenharVenus(texture[2], Qplanetas[2]);
	desenharTerra(texture[3], Qplanetas[3],texture[9], Qplanetas[9]);
	desenharMarte(texture[4], Qplanetas[4]);
	desenharJupiter(texture[5], Qplanetas[5]);
	desenharSaturno(texture[6], Qplanetas[6]);
	desenharUrano(texture[7], Qplanetas[7]);
	desenharNeptuno(texture[8], Qplanetas[8]);

	if(drawCintura)	glCallList(cintura);

	glCallList(estrelas);

	
}
