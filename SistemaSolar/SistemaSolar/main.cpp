#include <math.h>
#include<IL\il.h>
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
float alpha = 45, beta = 45, r = 100000;

bool axes = false;
bool fullscreen = false;
int MouseBtnState;
int window;
int winX = 800;
int winY = 600;
int infotab;

int fontTitle = (int) GLUT_BITMAP_HELVETICA_12;
int fontText = (int) GLUT_BITMAP_HELVETICA_10;

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
}


void renderScene(void) {

	glClearColor(0.0f,0.0f,0.0f,0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
			camlookX,camlookY,camlookZ,
			  0.0f,1.0f,0.0f);	

	if(axes) draw_Axes();
	
	/*desenhar ponto para onde a camera olha
	glColor3f(1,0,0);
	glBegin(GL_POINTS);
		glVertex3f(camlookX,camlookY,camlookZ);
	glEnd();	
	*/

	planetas();

	// End of frame
	glutSwapBuffers();
}

void infotabScene(void){
	glClearColor(0.0f,0.0f,0.0f,0.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0,0,10, 0,0,0, 0,1,0);	

	float menuX = -1;
	float menuY = 4;
	char s[25];
	
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
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "f : Ligar/desligar modo ecra inteiro");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "o : Ligar/desligar orbitas");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "c : Ligar/desligar cintura de asteroides");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "(podera causar perdas de desempenho)");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "Use o rato ou setas para rodar a camera");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "CTRL+rato ou w / s para aproximar/afastar");
	writeString(menuX, menuY-=0.2,0, (void *) fontTitle, "ALT+rato para mudar a direcao da camera");

	glutSwapBuffers();
}

void processKeys(unsigned char tecla, int x, int y){
	switch(tecla){
		case 27 : exit(0);
		case '+' : if(scale < 200) scale++; desenhaAnel(); break;
		case '-' : if(scale > 1) scale--; desenhaAnel(); break;

		case ',' : distFactor+=0.01; desenharCintura(); break;
		case '.' : if(distFactor > 0.03)distFactor-=0.01; desenharCintura();  break;
		
		case 't' : timeFactor+=0.01; break;
		case 'g' : timeFactor-=0.01; break;
		case 'a' : axes?axes=false:axes=true; break;
		case 'f' : if(fullscreen){
					fullscreen=false;
					glutPositionWindow(100,100),
					glutReshapeWindow(winX,winY);
					
					glutSetWindow(infotab);
					glutPositionWindow(0.8*winX,0);
					glutReshapeWindow(0.2*winX, winY);
					glutSetWindow(window);
				   }
				   else{
					glutFullScreen();
					fullscreen=true; 

					glutSetWindow(infotab);
					glutPositionWindow(0.8*glutGet(GLUT_SCREEN_WIDTH), 0);
					glutReshapeWindow(0.2*glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
					glutSetWindow(window);
				   }
				   break;

		case 'o' : orbitas?orbitas=false:orbitas=true; break;
		case 'c' : if(drawCintura)drawCintura=false;
				   else{ drawCintura=true; desenharCintura(); desenhaAnel(); }
				   break;
		case 'w' : r-=1000;
				if(r < 2000) r = 2000;
				camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
				camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
				camY = camlookY +( r * sin(beta*(PI/180)));
				return;
		case 's' : r+=1000;
				if(r > 1500000) r = 1500000;
				camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
				camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
				camY = camlookY +( r * sin(beta*(PI/180)));
				return;
		default : return;
	}
	glutPostRedisplay();
	glutSetWindow(infotab);
	glutPostRedisplay();
	glutSetWindow(window);
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
			if(r > 1500000) r = 1500000;
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

	if(x < 0 || x > glutGet(GLUT_WINDOW_WIDTH) || y < 0 || y > glutGet(GLUT_WINDOW_HEIGHT) )
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	else glutSetCursor( GLUT_CURSOR_NONE );

	glutPostRedisplay();
}


void menu(int id_op){
	switch (id_op){
		case 1 : {
			camlookX = distFactor*distSolTerra*sin(angTerra);
			camlookZ = distFactor*distSolTerra*cos(angTerra);
			camX = camlookX - raioTerra*4;
			camY = 10000;
			camZ = camlookZ - raioTerra*4;
			r = raioTerra*2;

				 }

	}

}

void gerarMenu(){
	glutCreateMenu(menu);
	glutAddMenuEntry("Ir Para Terra",1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void main(int argc, char **argv) {
	int i;
// inicialização
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(winX,winY);
	window = glutCreateWindow("SistemaSolar@CG@DI-UM");

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
	desenhaAnel();

// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

//iniciar coordenadas da camera
	camZ = r * cos(beta*(PI/180)) * cos(alpha*(PI/180));
	camX = r * cos(beta*(PI/180)) * sin(alpha*(PI/180));
	camY = r * sin(beta*(PI/180));

	infotab = glutCreateSubWindow(window, 0.8*glutGet(GLUT_WINDOW_WIDTH), 0, 0.2*glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glutDisplayFunc(infotabScene);
	glutReshapeFunc(infotabChangeSize);
	
// entrar no ciclo do GLUT 
	glutMainLoop();
}
