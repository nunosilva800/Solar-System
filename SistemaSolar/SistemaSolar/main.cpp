#include <math.h>
#include<IL\il.h>
#include<IL\ilu.h>
#include<IL\ilut.h>
#include <GL/glut.h>
#include "interface.h"
#include "planetas.h"
#include "texturas.h"

int frame=0,time,timebase=0;
char fps[10];

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

void draw_Axes (void)
{ 
	glBegin (GL_LINES);
		glColor3f (1,0,0);  glVertex3f (0,0,0);  glVertex3f (50000,0,0);    // X red.
		glColor3f (0,1,0);  glVertex3f (0,0,0);  glVertex3f (0,50000,0);    // Y green.
		glColor3f (0,0,1);  glVertex3f (0,0,0);  glVertex3f (0,0,50000);    // Z blue.
    glEnd();
	glColor3f(1,1,1);
}

void renderScene(void) {

	glClearColor(0.0f,0.0f,0.0f,0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
			camlookX,camlookY,camlookZ,
			  0.0f,1.0f,0.0f);	

	if(luz){
		glLightfv(GL_LIGHT0, GL_POSITION, lpos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lamb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, ldiff);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}else{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}

	if(axes) draw_Axes();
	
	planetas();

	// End of frame
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(fps,"FPS:%4.2f", frame*1000.0/(time-timebase));
		timebase = time;		
		frame = 0;
	}
	glutSetWindowTitle(fps);
	glutSwapBuffers();
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

	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "a : Ligar/desligar eixos");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "l : Ligar/desligar efeitos luz");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "f : Ligar/desligar modo ecra inteiro");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "o : Ligar/desligar orbitas");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "c : Ligar/desligar cintura de asteroides");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "(podera causar perdas de desempenho)");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "Use o rato ou setas para rodar a camara");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "CTRL+rato ou w / s para aproximar/afastar");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "ALT+rato para mudar a direcao da camara");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "Botao direito para mais opcoes");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "ESC : terminar aplicacao");

	glutSwapBuffers();
}

void main(int argc, char **argv) {
// inicialização
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(winX,winY);
	window = glutCreateWindow("SistemaSolar@CG@DI-UM");

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
	//printf("textura objective not loaded\n"); 	

	//preparação de display lists
	desenharCintura();
	desenharEstrelas();
	desenhaAnel();

	// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);

	//iniciar coordenadas da camera
	camZ = r * cos(beta*(PI/180)) * cos(alpha*(PI/180));
	camX = r * cos(beta*(PI/180)) * sin(alpha*(PI/180));
	camY = r * sin(beta*(PI/180));

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
	
// entrar no ciclo do GLUT 
	glutMainLoop();
}
