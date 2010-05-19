#include "interface.h"
#include "planetas.h"
#include "texturas.h"
#include "colisoes.h"
#include "vfc.h"

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

GLint varfatias=32;

//vectores com as pos dos planetas
double posicoes[19][3];
double raios[19];

float scale = 30;
bool orbitas = true;

bool drawCintura = false;
float distFactor = 0.03;

float timeFactor = 0.05;

GLuint cintura;
GLuint estrelas;

GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat	lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat emissionSun[] = { 0.9f, 0.0f, 0.0f, 0.0f};
GLfloat nullv[] = { 0.0f, 0.0f, 0.0f, 1.0f};

void rotacao(GLfloat rotacao,float tilt)
{
	glRotatef(tilt,0.0,0.0,1.0);
	glRotated(rotacao,0.0,1.0,0.0);
}


int calcularFatias(int indice)
{
	double dist = sqrt(pow(camX-posicoes[indice][0],2)+pow(camY-posicoes[indice][1],2)+pow(camZ-posicoes[indice][2],2));
	
	double res =(dist / (raios[indice]*4*distFactor*scale) );
	if(res>24)
	{
		return 8;
	}
	return (32-res);
	

}

void draw_orbita(float raio, float angleX,float angleY, float angleZ){
	glPushMatrix();
	
	glRotatef(angleZ,0.0,0.0,1.0);
	glRotatef(angleX,1.0,0.0,0.0);
	glRotatef(angleY,0.0,1.0,0.0);

	float xx=0;
	float yy=0;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		xx = raio * cos(i*(PI/180));
		yy = raio * sin(i*(PI/180));
		//Usar VFC aqui custa mais desempenho do que simplesmente desenhar
		//double coord[3] = { xx, 0, yy };
		//if(sphereInFrustum(coord,1)){
			glVertex3f(xx,yy,0);	
		//	}
	}
	glEnd();

	glPopMatrix();	
}

void desenharSol(GLuint texture, GLUquadric *  Q)
{
	glPushMatrix();
	//posSOl
	posicoes[0][0]=0.0;
	posicoes[0][1]=0.0;
	posicoes[0][2]=0.0;
	raios[0]=raioSol;

	angRotSol += (360/velRSol)*timeFactor;
	rotacao(angRotSol,0.0);

	//desenhar cintura de asteroides aqui, so mesmo para ter um efeito de rotaçao
	if(drawCintura)	glCallList(cintura);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);

	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	
	glRotatef(-90,1,0,0);
	double vec[3];
	vec[0]= posicoes[0][0];
	vec[1]= posicoes[0][1];	
	vec[2]= posicoes[0][2];
	
	if(sphereInFrustum(posicoes[0],raios[00])){
		gluSphere (Q,raioSol,calcularFatias(0),32);
	}
	
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glMaterialfv(GL_FRONT, GL_SPECULAR, nullv);
	glMaterialfv(GL_FRONT, GL_EMISSION, nullv);
	glDisable(GL_TEXTURE_2D);
		
	glPopMatrix();
}

void desenharMercurio(GLuint texture, GLUquadric *  Q)
{
	glPushMatrix();
	glRotatef(orbitalTiltMercurio,0.0,0.0,1.0);

	posicoes[1][0]=distFactor*distSolMercurio*sin(angMercurio);
	posicoes[1][1]=0.0;
	posicoes[1][2]=distFactor*distSolMercurio*cos(angMercurio);
	raios[1]=raioMercurio*scale;

	angMercurio += ((2*PI)/velMercurio)*timeFactor;
	glTranslatef(distFactor*distSolMercurio*sin(angMercurio), 0, distFactor*distSolMercurio*cos(angMercurio));
	
	//glColor3f(0.5,0.5,0.5);//cinza
	angRotMercurio += (360/velRMercurio)*timeFactor;
	rotacao(angRotMercurio,axisTiltMercurio);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);
	
	if(sphereInFrustum(posicoes[1],raios[1]))
		gluSphere (Q,scale*raioMercurio,calcularFatias(1),32);
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolMercurio,90,0.0,orbitalTiltMercurio);
}

void desenharVenus(GLuint texture, GLUquadric *  Q)
{
	glPushMatrix();
	glRotatef(orbitalTiltVenus,0.0,0.0,1.0);
	angVenus += ((2*PI)/velVenus)*timeFactor;

	posicoes[2][0]=distFactor*distSolVenus*sin(angVenus);
	posicoes[2][1]=0.0;
	posicoes[2][2]=distFactor*distSolVenus*cos(angVenus);
	raios[2]=raioVenus*scale;

	glTranslatef(distFactor*distSolVenus*sin(angVenus), 0, distFactor*distSolVenus*cos(angVenus));

	//glColor3f(0.6,0.5,0.1);//castanho
	angRotVenus += (360/velRVenus)*timeFactor;
	rotacao(angRotVenus,axisTiltVenus);
	glRotatef(90,1,0,0);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	
	if(sphereInFrustum(posicoes[2],raios[2]))
		gluSphere (Q,scale*raioVenus,calcularFatias(2),32);
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	if(orbitas)draw_orbita(distFactor*distSolVenus,90,0.0,orbitalTiltVenus);
}

void desenharLua(GLuint texture, GLUquadric * Q)
{
	glPushMatrix();
	if(orbitas)draw_orbita(distFactor*scale*distTerraLua,90,0.0,0.0);
	angLua += (((2*PI)/velLua)-((360/velRTerra)*(PI/180)))*timeFactor;
	
	posicoes[3][0]=distFactor*scale*distTerraLua*sin(angLua);
	posicoes[3][1]=0.0;
	posicoes[3][2]=distFactor*scale*distTerraLua*cos(angLua);
	raios[3]=raioLua*scale;

	glTranslatef(distFactor*scale*distTerraLua*sin(angLua), 0, distFactor*scale*distTerraLua*cos(angLua));

    glRotatef(-90,1,0,0);
	//glColor3f(1,1,1);//branco
	angRotLua += (360/velRLua)*timeFactor;
	rotacao(angRotLua,axisTiltLua);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	
	if(sphereInFrustum(posicoes[3],raios[3]))
		gluSphere (Q,scale*raioLua,32,32);
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void desenharTerra(GLuint texture, GLUquadric *  Q, GLuint texture2, GLUquadric *  Q2)
{
	glPushMatrix();
	glRotatef(orbitalTiltTerra,0.0,0.0,1.0);
	angTerra += ((2*PI)/velTerra)*timeFactor;
	
	if(haColisao(camZ,camX,camY,4))printf("COLISAOAOOAOAOAO\n\n");

	posicoes[4][0]=distFactor*distSolTerra*sin(angTerra+((2*PI)/velTerra)*timeFactor);
	posicoes[4][1]=0.0;
	posicoes[4][2]=distFactor*distSolTerra*cos(angTerra+((2*PI)/velTerra)*timeFactor);
	raios[4]=raioTerra*scale;

	glTranslatef(distFactor*distSolTerra*sin(angTerra), 0, distFactor*distSolTerra*cos(angTerra));

	//glColor3f(0,0,1);//azul
	//angRotTerra += ((0.25*360)/velRTerra)*timeFactor;
	angRotTerra += (360/velRTerra)*timeFactor;

	rotacao(angRotTerra,axisTiltTerra);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);
	
	if(sphereInFrustum(posicoes[4],raios[4]))
		gluSphere (Q,scale*raioTerra,calcularFatias(4),32);
	
	glDisable(GL_TEXTURE_2D);
	glRotatef(90,1,0,0);
	desenharLua(texture2, Q2);
	glPopMatrix();
	//glColor3f(0,0,1);//azul
	
	if(orbitas)draw_orbita(distFactor*distSolTerra,90,0.0,orbitalTiltTerra);
}

void desenharFobos(GLuint texture, GLUquadric * Q)
{
	glPushMatrix();

	if(orbitas)draw_orbita(scale*distMarteFobos,90,0.0,0.0);
	angFobos += (((2*PI)/velLua)-((360/velRMarte)*(PI/180)))*timeFactor;
	
	posicoes[5][0]=scale*distMarteFobos*sin(angFobos);
	posicoes[5][1]=0.0;
	posicoes[5][2]=scale*distMarteFobos*cos(angFobos);
	raios[5]=raioFobos*scale;

	glTranslatef(scale*distMarteFobos*sin(angFobos), 0, scale*distMarteFobos*cos(angFobos));

	angRotFobos += (360/velRFobos)*timeFactor;
	rotacao(angRotFobos,0.0);
	glRotatef(-90,1,0,0);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

	if(sphereInFrustum(posicoes[5],raios[5]))
		gluSphere (Q,scale*raioFobos,32,32);
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void desenharDeimos(GLuint texture, GLUquadric * Q)
{
	glPushMatrix();
	
	if(orbitas)draw_orbita(scale*distMarteDeimos,90,0.0,0.0);
	angDeimos += (((2*PI)/velLua)-((360/velRMarte)*(PI/180)))*timeFactor;

	posicoes[6][0]=scale*distMarteDeimos*sin(angDeimos);
	posicoes[6][1]=0.0;
	posicoes[6][2]=scale*distMarteDeimos*cos(angDeimos);
	raios[6]=raioDeimos*scale;

	glTranslatef(scale*distMarteDeimos*sin(angDeimos), 0, scale*distMarteDeimos*cos(angDeimos));

	angRotDeimos += (360/velRDeimos)*timeFactor;
	rotacao(angRotDeimos,0.0);

	glRotatef(-90,1,0,0);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

	if(sphereInFrustum(posicoes[6],raios[6]))
		gluSphere (Q,scale*raioDeimos,32,32);
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void desenharMarte(GLuint texture, GLUquadric *  Q, GLuint texture2, GLUquadric *  Q2)
{
	glPushMatrix();
	glRotatef(orbitalTiltMarte,0.0,0.0,1.0);
	angMarte+= ((2*PI)/velMarte)*timeFactor;
	
	posicoes[7][0]=distFactor*distSolMarte*sin(angMarte);
	posicoes[7][1]=0.0;
	posicoes[7][2]=distFactor*distSolMarte*cos(angMarte);
	raios[7]=raioMarte*scale;

	glTranslatef(distFactor*distSolMarte*sin(angMarte), 0, distFactor*distSolMarte*cos(angMarte));

	desenharDeimos(texture2, Q2);
	desenharFobos(texture2, Q2);

	//glColor3f(1,0,0);//vermelho
	angRotMarte += (360/velRMarte)*timeFactor;
	rotacao(angRotMarte,axisTiltMarte);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);
	
	if(sphereInFrustum(posicoes[7],raios[7]))
		gluSphere (Q,scale*raioMarte,calcularFatias(7),32);
	
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolMarte,90,0.0,orbitalTiltMarte);
}

void desenharIO(GLuint texture, GLUquadric * Q)
{
	glPushMatrix();
	//glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distJupiterIo,90,0.0,0.0);
	angIO += (((2*PI)/velLua)-((360/velRJupiter)*(PI/180)))*timeFactor;

	posicoes[8][0]=distFactor*scale*distJupiterIo*sin(angIO);
	posicoes[8][1]=0.0;
	posicoes[8][2]=distFactor*scale*distJupiterIo*cos(angIO);
	raios[8]=raioIo*scale;

	glTranslatef(distFactor*scale*distJupiterIo*sin(angIO), 0, distFactor*scale*distJupiterIo*cos(angIO));

	angRotIO += (360/velRIo)*timeFactor;
	rotacao(angRotIO,0.0);
	glRotatef(-90,1,0,0);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	
	if(sphereInFrustum(posicoes[8],raios[8]))
		gluSphere (Q,scale*raioIo,32,32);
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void desenharEuropa(GLuint texture, GLUquadric * Q)
{
	glPushMatrix();
	//glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distJupiterEuropa,90,0.0,0.0);
	angEuropa += (((2*PI)/velLua)-((360/velRJupiter)*(PI/180)))*timeFactor;
	
	posicoes[9][0]=distFactor*scale*distJupiterEuropa*sin(angEuropa);
	posicoes[9][1]=0.0;
	posicoes[9][2]=distFactor*scale*distJupiterEuropa*cos(angEuropa);
	raios[9]=raioEuropa*scale;

	glTranslatef(distFactor*scale*distJupiterEuropa*sin(angEuropa), 0, distFactor*scale*distJupiterEuropa*cos(angEuropa));

	angRotEuropa += (360/velREuropa)*timeFactor;
	rotacao(angRotEuropa,0.0);
	glRotatef(-90,1,0,0);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	
	if(sphereInFrustum(posicoes[9],raios[9]))
		gluSphere (Q,scale*raioEuropa,32,32);
	
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void desenharGanimedes(GLuint texture, GLUquadric * Q)
{
	glPushMatrix();
	//glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distJupiterGanymede,90,0.0,0.0);
	angGanimedes += (((2*PI)/velLua)-((360/velRJupiter)*(PI/180)))*timeFactor;
	
	posicoes[10][0]=distFactor*scale*distJupiterGanymede*sin(angGanimedes);
	posicoes[10][1]=0.0;
	posicoes[10][2]=distFactor*scale*distJupiterGanymede*cos(angGanimedes);
	raios[10]=raioGanymede*scale;

	glTranslatef(distFactor*scale*distJupiterGanymede*sin(angGanimedes), 0, distFactor*scale*distJupiterGanymede*cos(angGanimedes));

	angRotGanimedes += (360/velRGanimedes)*timeFactor;
	rotacao(angRotGanimedes,0.0);
	glRotatef(-90,1,0,0);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

	if(sphereInFrustum(posicoes[10],raios[10]))
		gluSphere (Q,scale*raioGanymede,32,32);
	
	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}

void desenharCalisto(GLuint texture, GLUquadric * Q)
{
	glPushMatrix();
	//glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distJupiterCalisto,90,0.0,0.0);
	angCalisto += (((2*PI)/velLua)-((360/velRJupiter)*(PI/180)))*timeFactor;
	
	posicoes[11][0]=distFactor*scale*distJupiterCalisto*sin(angCalisto);
	posicoes[11][1]=0.0;
	posicoes[11][2]=distFactor*scale*distJupiterCalisto*cos(angCalisto);
	raios[11]=raioCalisto*scale;
	
	glTranslatef(distFactor*scale*distJupiterCalisto*sin(angCalisto), 0, distFactor*scale*distJupiterCalisto*cos(angCalisto));

	angRotCalisto += (360/velRCalisto)*timeFactor;
	rotacao(angRotCalisto,0.0);
	glRotatef(-90,1,0,0);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

	if(sphereInFrustum(posicoes[11],raios[11]))
		gluSphere (Q,scale*raioCalisto,32,32);
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void desenharJupiter(GLuint texture, GLUquadric *  Q, GLuint texture2, GLUquadric *  Q2)
{
	glPushMatrix();
	glRotatef(orbitalTiltJupiter,0.0,0.0,1.0);
	angJupiter += ((2*PI)/velJupiter)*timeFactor;
	
	posicoes[12][0]=distFactor*distSolJupiter*sin(angJupiter);
	posicoes[12][1]=0.0;
	posicoes[12][2]=distFactor*distSolJupiter*cos(angJupiter);
	raios[12]=raioJupiter*scale;

	glTranslatef(distFactor*distSolJupiter*sin(angJupiter), 0, distFactor*distSolJupiter*cos(angJupiter));
	//glColor3f(1,1,0);//amarelo

	angRotJupiter += (360/velRJupiter)*timeFactor;
	rotacao(angRotJupiter,axisTiltJupiter);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);

	double vec[3];
	vec[0]= posicoes[12][0];
	vec[1]= posicoes[12][1];	
	vec[2]= posicoes[12][2];
	if(sphereInFrustum(posicoes[12],raios[12])){
		gluSphere (Q,scale*raioJupiter,calcularFatias(12),32);
	}
	glDisable(GL_TEXTURE_2D);
	glRotatef(90,1,0,0);
	desenharIO(texture2, Q2);
	desenharEuropa(texture2, Q2);
	desenharGanimedes(texture2, Q2);
	desenharCalisto(texture2, Q2);

	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolJupiter,90,0.0,orbitalTiltJupiter);
}

void desenharRhea(GLuint texture, GLUquadric * Q)
{
	glPushMatrix();
	//glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distSaturnoRhea,90,0.0,0.0);
	
	posicoes[13][0]=distFactor*scale*distSaturnoRhea*sin(velRReia);
	posicoes[13][1]=0.0;
	posicoes[13][2]=distFactor*scale*distSaturnoRhea*cos(velRReia);
	raios[13]=raioRhea*scale;

	glTranslatef(distFactor*scale*distSaturnoRhea*sin(velRReia), 0, distFactor*scale*distSaturnoRhea*cos(velRReia));

	angRotRhea += (360/velRReia)*timeFactor;
	rotacao(angRotRhea,0.0);
	glRotatef(-90,1,0,0);
	glEnable (GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	if(sphereInFrustum(posicoes[13],raios[13]))
		gluSphere (Q,scale*raioRhea,32,32);
	
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
}

void desenharTitan(GLuint texture, GLUquadric * Q)
{
	glPushMatrix();
	//glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distSaturnoTitan,90,0.0,0.0);
	
	posicoes[14][0]=distFactor*scale*distSaturnoTitan*sin(velRTita);
	posicoes[14][1]=0.0;
	posicoes[14][2]=distFactor*scale*distSaturnoTitan*cos(velRTita);
	raios[14]=raioTitan*scale;

	glTranslatef(distFactor*scale*distSaturnoTitan*sin(velRTita), 0, distFactor*scale*distSaturnoTitan*cos(velRTita));

	angRotTitan += (360/velRTita)*timeFactor;
	rotacao(angRotTitan,0.0);
	glRotatef(-90,1,0,0);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

	if(sphereInFrustum(posicoes[14],raios[14]))
		gluSphere (Q,scale*raioTitan,32,32);
	
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
}

void desenharIapetus(GLuint texture, GLUquadric * Q)
{
	glPushMatrix();
	glColor3f(1,1,1);//branco
	if(orbitas)draw_orbita(distFactor*scale*distSaturnoIapetus,90,0.0,0.0);
	
	posicoes[15][0]=distFactor*scale*distSaturnoIapetus*sin(velRJapeto);
	posicoes[15][1]=0.0;
	posicoes[15][2]=distFactor*scale*distSaturnoIapetus*cos(velRJapeto);
	raios[15]=raioIapetus*scale;

	glTranslatef(distFactor*scale*distSaturnoIapetus*sin(velRJapeto), 0, distFactor*scale*distSaturnoIapetus*cos(velRJapeto));

	angRotIapetus += (360/velRJapeto)*timeFactor;
	rotacao(angRotIapetus,0.0);

	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	
	if(sphereInFrustum(posicoes[15],raios[15]))
		gluSphere (Q,scale*raioIapetus,32,32);
	
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
}

void desenharSaturno(GLuint texture, GLUquadric *  Q, GLuint texture2, GLUquadric *  Q2)
{
	glPushMatrix();
	glRotatef(orbitalTiltSaturno,0.0,0.0,1.0);
	angSaturno+= ((2*PI)/velSaturno)*timeFactor;
	
	posicoes[16][0]=distFactor*distSolSaturno*sin(angSaturno);
	posicoes[16][1]=0.0;
	posicoes[16][2]=distFactor*distSolSaturno*cos(angSaturno);
	raios[16]=raioSaturno*scale;

	glTranslatef(distFactor*distSolSaturno*sin(angSaturno), 0, distFactor*distSolSaturno*cos(angSaturno));

	//glColor3f(1,0,1);//rosa
	angRotSaturno += (360/velRSaturno)*timeFactor;
	rotacao(angRotSaturno,axisTiltSaturno);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);
	
	if(sphereInFrustum(posicoes[16],raios[16]))
		gluSphere(Q,scale*raioSaturno,calcularFatias(16),32);
	
	glDisable(GL_TEXTURE_2D);

	glRotatef(90,1,0,0);
	
	desenhaAnel();

	desenharRhea(texture2, Q2);
	desenharTitan(texture2, Q2);
	desenharIapetus(texture2, Q2);

	glPopMatrix();
	//glColor3f(1,0,1);//rosa
	if(orbitas)draw_orbita(distFactor*distSolSaturno,90,0.0,orbitalTiltSaturno);
}
void desenharUrano(GLuint texture, GLUquadric *  Q)
{
	glPushMatrix();
	glRotatef(orbitalTiltUrano,0.0,0.0,1.0);
	angUrano+= ((2*PI)/velUrano)*timeFactor;
	
	posicoes[17][0]=distFactor*distSolUrano*sin(angUrano);
	posicoes[17][1]=0.0;
	posicoes[17][2]=distFactor*distSolUrano*cos(angUrano);
	raios[17]=raioUrano*scale;

	glTranslatef(distFactor*distSolUrano*sin(angUrano), 0, distFactor*distSolUrano*cos(angUrano));

	//glColor3f(0.8,0.1,0.4);//roxo
	angRotUrano += (360/velRUrano)*timeFactor;
	rotacao(angRotUrano,axisTiltUrano);
	glRotatef(90,1,0,0);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	
	if(sphereInFrustum(posicoes[17],raios[17]))
		gluSphere (Q,scale*raioUrano,calcularFatias(17),32);
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	if(orbitas)draw_orbita(distFactor*distSolUrano,90,0.0,orbitalTiltUrano);
}

void desenharNeptuno(GLuint texture, GLUquadric *  Q)
{
	glPushMatrix();
	glRotatef(orbitalTiltNeptuno,0.0,0.0,1.0);
	angNeptuno += ((2*PI)/velNeptuno)*timeFactor;
	
	posicoes[18][0]=distFactor*distSolNeptuno*sin(angNeptuno);
	posicoes[18][1]=0.0;
	posicoes[18][2]=distFactor*distSolNeptuno*cos(angNeptuno);
	raios[18]=raioNeptuno*scale;

	glTranslatef(distFactor*distSolNeptuno*sin(angNeptuno), 0, distFactor*distSolNeptuno*cos(angNeptuno));

	//glColor3f(0.12,0.432,0.123);//verde
	angRotNeptuno += (360/velRNeptuno)*timeFactor;
	rotacao(angRotNeptuno,axisTiltNeptuno);
	glEnable (GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(-90,1,0,0);
	
	if(sphereInFrustum(posicoes[18],raios[18]))
		gluSphere (Q,scale*raioNeptuno,calcularFatias(18),32);
	
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
	for(i=0; i<10000; i++){
		dist = rand();
		ang = rand() / 3.1415;
		x = cos(ang) * (dist + distSolMarte*1.3*distFactor);
		z = sin(ang) * (dist + distSolMarte*1.3*distFactor);
		if(sqrt(x*x+z*z) < distSolJupiter*0.7*distFactor){
			glNormal3f(0,0,0);
			glVertex3f(x, 0, z);
		}
		else i--;
	}
	glEnd();
	glColor3f(1,1,1);

	glEndList();
}
void desenhaAnel(){
	int i=0;
	float x, z;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[10]);
	glDisable(GL_CULL_FACE);
	glBegin(GL_QUAD_STRIP);
		for(i=0; i<=360; i++){
			//os aneis estendem-se desde os 6 630 KM ate 120 700 KM
			x = sin(i*PI/180) * (raioSaturno+6.630)*scale;
			z = cos(i*PI/180) * (raioSaturno+6.630)*scale;
			glNormal3f(0,1,0); glTexCoord2f(0,0); glVertex3f(x, 0, z);
			
			x = sin(i*PI/180) * (raioSaturno+120.700)*scale;
			z = cos(i*PI/180) * (raioSaturno+120.700)*scale;
			glNormal3f(0,1,0); glTexCoord2f(1,0); glVertex3f(x, 0, z);
			
			i++;
			
			x = sin(i*PI/180) * (raioSaturno+6.630)*scale;
			z = cos(i*PI/180) * (raioSaturno+6.630)*scale;
			glNormal3f(0,1,0); glTexCoord2f(0,1); glVertex3f(x, 0, z);
			
			x = sin(i*PI/180) * (raioSaturno+120.700)*scale;
			z = cos(i*PI/180) * (raioSaturno+120.700)*scale;
			glNormal3f(0,1,0); glTexCoord2f(1,1); glVertex3f(x, 0, z);
		}
	glEnd();
	glEnable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);

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

		//definir normal a apontar para o sol (centro)
		glNormal3f(-x,-y,-z);
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
	desenharMarte(texture[4], Qplanetas[4],texture[9], Qplanetas[9]);
	desenharJupiter(texture[5], Qplanetas[5],texture[9], Qplanetas[9]);
	desenharSaturno(texture[6], Qplanetas[6],texture[9], Qplanetas[9]);
	desenharUrano(texture[7], Qplanetas[7]);
	desenharNeptuno(texture[8], Qplanetas[8]);
	glCallList(estrelas);
	glutPostRedisplay();
}
