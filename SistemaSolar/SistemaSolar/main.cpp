#include <math.h>
#include<IL\il.h>
#include<IL\ilu.h>
#include<IL\ilut.h>
#include <GL/glut.h>
#include "interface.h"
#include "planetas.h"
#include "texturas.h"
#include "model.h"
#include "vfc.h"

/*#include <AL/alut.h>

ALuint soundBuffer[1];
ALuint soundSource[1];
ALsizei Ssize,Sfreq;
ALenum  Sformat;
ALvoid  *Sdata;*/

int frame=0,time,timebase=0;
char fps[10];

GLfloat ambientLight0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat ambientLight1[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat diffuseLight[] = { 1, 1, 1, 1.0f };
GLfloat specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(-0.1*w, 0, w, h);
	if(!fullscreen){
		winX = w;
		winY = h;
		glutSetWindow(infotab);
		glutPositionWindow(0.8*winX,0);
		glutReshapeWindow(0.2*winX, winY);
		glutSetWindow(window);
	}

	// Set the correct perspective
	gluPerspective(45,ratio,10,1000000000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

}

void infotabChangeSize(int w, int h) {
	if(h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
    glViewport(0, 0, w, h);

	gluPerspective(45,ratio,10,100);

	glMatrixMode(GL_MODELVIEW);
}

void writeString(float x, float y,float z, void *font, char *s)
{
    unsigned int c;
    glRasterPos3f(x,y,z);                // set position to start drawing fonts
    for (c=0; c < strlen(s); c++)
       glutBitmapCharacter(font, s[c] ); // draw the character to the screen
}


void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
			camlookX,camlookY,camlookZ,
			  0.0f,1.0f,0.0f);	

	if(luz){
		glEnable(GL_LIGHTING);
	}else{
		glDisable(GL_LIGHTING);
	}
	
	//desenha a nave
	if(cameraMode == 1){
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(camlookX,camlookY,camlookZ);
		//rodar a nave
		glRotated(-90,1,0,0);
		glRotated(alpha+180,0,0,1);
		drawModel();
		if(luz)glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	planetas();
		if(winY == 0)
	winY = 1;
	float ratio = winX * 1.0 / winY;
	calculaAltLarg(45,ratio,10,1000000000);
	
	
	double vec1[]={camX,camY,camZ};
	double vec2[]={camlookX,camlookY,camlookZ};
	double vec3[]={0,1,0};

	setPlanes(vec1,vec2,vec3);

	// End of frame
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 500) {
		sprintf(fps,"FPS:%4.2f", frame*1000.0/(time-timebase));
		timebase = time;		
		frame = 0;
	}
	glutSetWindowTitle(fps);
	glutSwapBuffers();
}


void SetupLighting(void)
{
	// Enable lighting
	//glEnable(GL_LIGHTING);

	// Setup and enable light0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular1);

	// Setup light1
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	
	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

}

void SetupRC(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	SetupLighting();

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glShadeModel(GL_SMOOTH);
}

void infotabScene(void){
	glClearColor(0.0f,0.0f,0.0f,0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0,0,10, 0,0,0, 0,1,0);	

	float menuX = -1;
	float menuY = 4;

	sprintf(s,"Escala: %g",scale);
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, s);
	writeString(menuX, menuY-=0.2,0, (void *) fontText, "+ / - : Aumenta/diminui escala");
    writeString(menuX, menuY-=0.2,0, (void *) fontText, "----------------------------");

	sprintf(s,"Tempo: %g",timeFactor);
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, s);
	writeString(menuX, menuY-=0.2,0, (void *) fontText, "t / g : Aumenta/diminui tempo");
    writeString(menuX, menuY-=0.2,0, (void *) fontText, "----------------------------");

	sprintf(s,"Distancias: %g",distFactor);
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, s);
	writeString(menuX, menuY-=0.2,0, (void *) fontText, ", / . : Aumenta/diminui distancias");
    writeString(menuX, menuY-=0.2,0, (void *) fontText, "----------------------------");

	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "l : Ligar/desligar efeitos luz");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "f : Ligar/desligar modo ecra inteiro");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "o : Ligar/desligar orbitas");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "c : Ligar/desligar cintura de asteroides");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "(podera causar perdas de desempenho)");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");

	if(cameraMode == 0) writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "Camera Geral");
	if(cameraMode == 1) writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "Camera Nave");
	
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "Use o rato ou setas para rodar a camara");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "CTRL+rato ou w / s para aproximar/afastar");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "ALT+rato para mudar a direcao da camara");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "Botao direito para mais opcoes");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "ESC : terminar aplicacao");

	glutSwapBuffers();
}

void initSound(){
	/*
	alutInit(NULL,NULL);
	alListener3f(AL_POSITION, 0,0,0);
	alListener3f(AL_VELOCITY, 0,0,0);
    alListener3f(AL_ORIENTATION, 0,1,0);

	alGenBuffers(1,soundBuffer);
	//alutLoadWAVFile("C:\Users\Nuno\Documents\trolololoclpi.wav",&Sformat,&Sdata,&Ssize,&Sfreq,(ALboolean *)true);
	Sdata = alutLoadMemoryFromFile("C:\Users\Nuno\Documents\trolololoclpi.wav",NULL,NULL,NULL);

	alBufferData(soundBuffer[0], Sformat, Sdata, Ssize, Sfreq);
	//alutUnloadWAV(Sformat,Sdata,Ssize,Sfreq);

	alGenSources(1,soundSource);

	alSourcef(soundSource[0], AL_PITCH, 1.0f);
	alSourcef(soundSource[0], AL_GAIN, 1.0f);
	alSource3f(soundSource[0], AL_POSITION,camX,camY,camZ);
	alSource3f(soundSource[0], AL_VELOCITY,0,1,0);
	alSourcei(soundSource[0], AL_BUFFER,*soundBuffer);
	alSourcei(soundSource[0], AL_LOOPING, AL_TRUE);
	*/
}

void main(int argc, char **argv) {
// inicialização
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(winX,winY);
	window = glutCreateWindow("SistemaSolar@CG@DI-UM");

	//inicia o modelo da nave
	initModels();

// registo de funções 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMotionFunc(fmotion);
	glutMouseFunc(fmouse);

	gerarMenu();

	//carregar imagens
	for(int i=0;i<10;i++){Qplanetas[i]=gluNewQuadric(); gluQuadricTexture( Qplanetas[i], GL_TRUE);}
	texture[0]= LoadBitmap("Resource/sol.bmp");
	texture[1]= LoadBitmap("Resource/mercurio.bmp");
	texture[2]= LoadBitmap("Resource/venus.bmp");
	texture[3]= LoadBitmap("Resource/terra.bmp");
	texture[4]= LoadBitmap("Resource/marte.bmp");
	texture[5]= LoadBitmap("Resource/jupiter.bmp");
	texture[6]= LoadBitmap("Resource/saturno.bmp");
	texture[7]= LoadBitmap("Resource/urano.bmp");
	texture[8]= LoadBitmap("Resource/neptuno.bmp");
	texture[9]= LoadBitmap("Resource/lua.bmp");
	texture[10]= LoadBitmap("Resource/saturnringcolor.bmp");
	//printf("textura objective not loaded\n"); 	

	//preparação de display lists
	desenharCintura();
	desenharEstrelas();
	desenhaAnel();

// alguns settings para OpenGL
	SetupRC();

	//iniciar coordenadas da camera
	camZ = r * cos(beta*(PI/180)) * cos(alpha*(PI/180));
	camX = r * cos(beta*(PI/180)) * sin(alpha*(PI/180));
	camY = r * sin(beta*(PI/180));

	if(winY == 0)
	winY = 1;
	//inicializa a piramide do view f culling
	float ratio = winX * 1.0 / winY;
	calculaAltLarg(45,ratio,10,1000000000);

	//criar janela secundaria
	infotab = glutCreateSubWindow(window, 
		0.8*glutGet(GLUT_WINDOW_WIDTH), 0,
		0.2*glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glutDisplayFunc(infotabScene);
	glutReshapeFunc(infotabChangeSize);
	//esta janela trata do teclado da mesma forma
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMotionFunc(fmotion);
	glutMouseFunc(fmouse);

	//initSound();

// entrar no ciclo do GLUT 
	glutMainLoop();
}
