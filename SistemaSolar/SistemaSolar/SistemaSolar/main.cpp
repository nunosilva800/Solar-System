#include <GL/glut.h>

#include <math.h>
#include "planetas.h"

float PI = 3.14159265f;

float height = 2.0f;
float x = 0.0f;
float z = 0.0f;
float y = 0.0f;
int mouseBtn = 0;
int mouseMod = 0;

float camX = 900.0f, camY = 0.0f, camZ = 900;
float camlookX = 900.0f, camlookY = 0.0f, camlookZ = 0.0f;
float alpha = 45, beta = 0, r = 1200;

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
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,10,100000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void draw_Axes (void)
{ 
    glPushMatrix ();
	glBegin (GL_LINES);
		glColor3f (1,0,0);  glVertex3f (0,0,0);  glVertex3f (5000,0,0);    // X red.
		glColor3f (0,1,0);  glVertex3f (0,0,0);  glVertex3f (0,5000,0);    // Y green.
		glColor3f (0,0,1);  glVertex3f (0,0,0);  glVertex3f (0,0,5000);    // Z blue.
    glEnd();
	glPopMatrix ();
}

void renderScene(void) {

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
			camlookX,camlookY,camlookZ,
			  0.0f,1.0f,0.0f);	
	
	draw_Axes();
	
	//desenhar ponto para onde a camera olha
	glPushMatrix();
	glTranslated(camlookX,camlookY,camlookZ);
	glColor3f(1,1,1);
	glutSolidSphere(1,10,10);
	glPopMatrix();

	planetas();

	// End of frame
	glutSwapBuffers();

}

void processKeys(unsigned char tecla, int x, int y){
	switch(tecla){
		case 27 : exit(0);
	}
	glutPostRedisplay();
}
void processSpecialKeys(int key, int xx, int yy) 
{
	switch(key) {
		case GLUT_KEY_UP: 
			if(beta < (89*PI/180)){
				beta+=0.03;
				camZ = r * cos(beta) * cos(alpha);
				camX = r * cos(beta) * sin(alpha);
				camY = r * sin(beta);
			}
			break;
		case GLUT_KEY_DOWN:
			if(beta > -(89*PI/180)){
				beta-=0.03;
				camZ = r * cos(beta) * cos(alpha);
				camX = r * cos(beta) * sin(alpha);
				camY = r * sin(beta);
			}
			break;
		case GLUT_KEY_LEFT:
			alpha-=0.03;
			camZ = r * cos(beta) * cos(alpha);
			camX = r * cos(beta) * sin(alpha);
			break;
		case GLUT_KEY_RIGHT:
			alpha+=0.03;
			camZ = r * cos(beta) * cos(alpha);
			camX = r * cos(beta) * sin(alpha);
			break;
	}
	glutPostRedisplay();
}

void fmouse(int button, int state, int xx, int yy) 
{
	switch(button){
		case GLUT_LEFT_BUTTON:
			mouseBtn=1;
			mouseMod=glutGetModifiers();
			x=xx; y=yy;
			break;
		default :
			mouseBtn = 0;
	}	
}

//TODO: prender o rato ao ecra e nao o mexer.
void fmotion(int xx, int yy)
{
	if(mouseBtn!=1) return ;
	switch(mouseMod){
		case GLUT_ACTIVE_ALT://muda lookat
			camlookX -= ((x-xx))*10;
			camlookZ -= ((y-yy))*10;
			break;
		case GLUT_ACTIVE_CTRL://aproxima / afasta
			r+=(y-yy)*10;
			camZ = camlookZ +( r * cos(beta) * cos(alpha));
			camX = camlookX +( r * cos(beta) * sin(alpha));
			camY = camlookY +( r * sin(beta));
			break;
		default:
			alpha+=((x-xx)/100);
			beta-=((y-yy)/100);
			camZ = r * cos(beta) * cos(alpha);
			camX = r * cos(beta) * sin(alpha);
			camY = r * sin(beta);
	}
	x=xx;y=yy;
	glutPostRedisplay();
}

void menu(int id_op){}

void gerarMenu(){
	glutCreateMenu(menu);
	glutAddMenuEntry("'Sup?",1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void main(int argc, char **argv) {

// inicialização
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,640);
	glutCreateWindow("SistemaSolar@CG@DI-UM");
		
// registo de funções 
	glutDisplayFunc(renderScene);
	//glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMotionFunc(fmotion);
	glutMouseFunc(fmouse);

	gerarMenu();

// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// entrar no ciclo do GLUT 
	glutMainLoop();
}

