#include <math.h>
#include<IL/il.h>
#include<IL\ilu.h>
#include<IL\ilut.h>
#include <GL/glut.h>
#include "planetas.h"
#include "texturas.h"

float height = 2.0f;
float x = 0.0f;
float z = 0.0f;
float y = 0.0f;
int mouseBtn = 0;
int mouseMod = 0;

float camX = 0, camY = 0, camZ = 0;
float camlookX = 0.0f, camlookY = 0.0f, camlookZ = 0.0f;
float alpha = 45, beta = 45, r = 50000;

bool axes = false;
int MouseBtnState;

int font=(int)GLUT_BITMAP_8_BY_13;
char s[100];

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
	gluPerspective(45,ratio,10,1000000000);

	// return to the model view matrix mode
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
		glColor3f (1,0,0);  glVertex3f (0,0,0);  glVertex3f (5000,0,0);    // X red.
		glColor3f (0,1,0);  glVertex3f (0,0,0);  glVertex3f (0,5000,0);    // Y green.
		glColor3f (0,0,1);  glVertex3f (0,0,0);  glVertex3f (0,0,5000);    // Z blue.
    glEnd();
}


void renderScene(void) {

	glClearColor(0.0f,0.0f,0.0f,0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
			camlookX,camlookY,camlookZ,
			  0.0f,1.0f,0.0f);	

	if(axes) draw_Axes();
	
	//desenhar ponto para onde a camera olha
	glColor3f(1,1,1);
	glBegin(GL_POINTS);
		glVertex3f(camlookX,camlookY,camlookZ);
	glEnd();	
	
	strcpy(s,"+ - aumenta o tamanho dos planetas e satelites");
    writeString(9999,9999,0, (void *)font, s);

	planetas();

	// End of frame
	glutSwapBuffers();

}

void processKeys(unsigned char tecla, int x, int y){
	switch(tecla){
		case 27 : exit(0);
		case '+' : scale++; break;
		case '-' : scale--; break;

		case '.' : distFactor+=0.01; desenharCintura(); break;
		case ',' : if(distFactor > 0.03)distFactor-=0.01; desenharCintura(); break;
		
		case 't' : timeFactor+=0.01; break;
		case 'g' : timeFactor-=0.01; break;
		case 'a' : axes?axes=false:axes=true; break;
		case 'o' : orbitas?orbitas=false:orbitas=true; break;
		case 'c' : if(drawCintura){
					drawCintura=false;
				   }else{ drawCintura=true; desenharCintura();
				   }
			break;
	}
	glutPostRedisplay();
}
void processSpecialKeys(int key, int xx, int yy) 
{
	switch(key) {
		case GLUT_KEY_UP: 
			if(beta < 89){
				beta++;
				camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
				camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
				camY = camlookY +( r * sin(beta*(PI/180)));
			}
			break;
		case GLUT_KEY_DOWN:
			if(beta > -89){
				beta--;
				camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
				camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
				camY = camlookY +( r * sin(beta*(PI/180)));			}
			break;
		case GLUT_KEY_LEFT:
			alpha--;
				camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
				camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			break;
		case GLUT_KEY_RIGHT:
			alpha++;
				camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
				camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
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
	glutSetCursor   ( GLUT_CURSOR_LEFT_ARROW );
}

void fmotion(int xx, int yy)
{
	if(mouseBtn!=1) return ;
	switch(mouseMod){
		case GLUT_ACTIVE_ALT://muda lookat
			camlookX -= ((x-xx))*100;
			camlookZ -= ((y-yy))*100;
			alpha = atan((camX-camlookX) / (camZ-camlookZ)) * (180/PI);
			beta = atan((camY-camlookY) / (camZ-camlookZ)) * (180/PI);
			r = sqrt(pow((camZ-camlookZ), 2) + pow((camX-camlookX), 2));
			r = sqrt(pow((camY-camlookY), 2) + pow(r, 2));
			break;
		case GLUT_ACTIVE_CTRL://aproxima / afasta
			r-=(y-yy)*100;
			if(r > 2000000) r = 1500000;
			if(r < 2000) r = 2000;
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
		default:
			alpha+=((x-xx)*0.3);
			beta-=((y-yy)*0.3);
			if(beta > 89) beta = 89;
			if(beta < -89) beta = -89;
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
	}
	x=xx;y=yy;

	if(x < 0 || x > 790 || y < 0 || y > 590) glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	else glutSetCursor( GLUT_CURSOR_NONE );

	glutPostRedisplay();
}


void menu(int id_op){}

void gerarMenu(){
	glutCreateMenu(menu);
	glutAddMenuEntry("'Sup?",1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void main(int argc, char **argv) {
	int i;
// inicialização
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("SistemaSolar@CG@DI-UM");
	for(i=0;i<10;i++){Qplanetas[i]=gluNewQuadric(); gluQuadricTexture( Qplanetas[i], GL_TRUE);}
	texture[0]= LoadBitmap("C:/Toolkits/texturas_bmp/sol.bmp");
	texture[1]= LoadBitmap("C:/Toolkits/texturas_bmp/mercurio.bmp");
	texture[2]= LoadBitmap("C:/Toolkits/texturas_bmp/venus.bmp");
	texture[3]= LoadBitmap("C:/Toolkits/texturas_bmp/terra.bmp");
	texture[4]= LoadBitmap("C:/Toolkits/texturas_bmp/marte.bmp");
	texture[5]= LoadBitmap("C:/Toolkits/texturas_bmp/jupiter.bmp");
	texture[6]= LoadBitmap("C:/Toolkits/texturas_bmp/saturno.bmp");
	texture[7]= LoadBitmap("C:/Toolkits/texturas_bmp/urano.bmp");
	texture[8]= LoadBitmap("C:/Toolkits/texturas_bmp/neptuno.bmp");
	texture[9]= LoadBitmap("C:/Toolkits/texturas_bmp/lua.bmp");
	//printf("textura objective not loaded\n"); 	

// registo de funções 
	glutDisplayFunc(renderScene);
	//glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMotionFunc(fmotion);
	glutMouseFunc(fmouse);

	gerarMenu();

//preparação de display lists
	desenharCintura();
	desenharEstrelas();

// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
//iniciar coordenadas da camera
	camZ = r * cos(beta*(PI/180)) * cos(alpha*(PI/180));
	camX = r * cos(beta*(PI/180)) * sin(alpha*(PI/180));
	camY = r * sin(beta*(PI/180));
// entrar no ciclo do GLUT 
	glutMainLoop();
}
