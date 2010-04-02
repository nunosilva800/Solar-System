#include <GL/glut.h>

#include <math.h>

GLfloat rotSol=0.0;
GLfloat rotMercurio=0.0;
GLfloat rotVenus=0.0;
GLfloat rotTerra=0.0;
GLfloat rotLua=0.0;
GLfloat rotMarte=0.0;
GLfloat rotJupiter=0.0;
GLfloat rotSaturno=0.0;
GLfloat rotUrano=0.0;
GLfloat rotNeptuno=0.0;

float PI = 3.14159265f;

float time =0;

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
	   glLineWidth (2.0);

       glBegin (GL_LINES);
          glColor3f (1,0,0);  glVertex3f (0,0,0);  glVertex3f (5000,0,0);    // X red.
          glColor3f (0,1,0);  glVertex3f (0,0,0);  glVertex3f (0,5000,0);    // Y green.
          glColor3f (0,0,1);  glVertex3f (0,0,0);  glVertex3f (0,0,5000);    // Z blue.
       glEnd();

   glPopMatrix ();
}

void draw_Orbita(float raio, float angle){
	glPushMatrix();
	glRotatef(angle,1,0,0);

	float xx=0;
	float yy=0;
	glBegin(GL_LINES);
	for (int i = 0; i < 180; i++)
	{
		xx = raio * cos((float)i) - raio;
		yy = raio * sin((float)i) + raio;
		glVertex3f(xx + raio,yy - raio,0);
		xx = raio * cos(i + 0.1) - raio;
		yy = raio * sin(i + 0.1) + raio;
		glVertex3f(xx + raio,yy - raio,0);
	}
	glEnd();

	glPopMatrix();	
}

void rotacao(GLfloat rotacao)
{
	glRotated(rotacao,0.0,1.0,0.0);
	glutPostRedisplay();
}


void desenharSol()
{
	glPushMatrix();
	glColor3f(1,1,0);
	rotSol+=1;
	rotacao(rotSol);
	glutWireSphere(696,32,32);
	glPopMatrix();
}

void desenharMercurio()
{
	glPushMatrix();
	glTranslatef(1000,0,0);
	glColor3f(0.5,0.5,0.5);
	rotMercurio+=0.2;
	rotacao(rotMercurio);
	glutWireSphere(1.2195,32,32);
	glPopMatrix();
	draw_Orbita(1000,90);
}

void desenharVenus()
{
	glPushMatrix();
	glTranslatef(1100,0,0);
	glColor3f(0.6,0.5,0.1);
	rotVenus+=0.4;
	rotacao(rotVenus);
	glutWireSphere(3.0259,32,32);
	glPopMatrix();
	draw_Orbita(1100,90);
}

void desenharLua()
{
	draw_Orbita(25,90);
	glTranslatef(25,0,0);
	glColor3f(1,1,1);
	rotLua+=0.34;
	rotacao(rotLua);
	glutWireSphere((3.4742/2),32,32);
	
}

void desenharTerra()
{
	glPushMatrix();
	glTranslatef(1200,0,0);
	glColor3f(0,0,1);
	rotTerra+=0.34;
	rotacao(rotTerra);
	glutWireSphere(3.1855,32,32);
	desenharLua();
	glPopMatrix();
	draw_Orbita(1200,90);
}

void desenharMarte()
{
	glPushMatrix();
	glTranslatef(1300,0,0);
	glColor3f(0,0,1);
	rotMarte += 0.6;
	rotacao(rotMarte);
	glutWireSphere((6.780/2),32,32);
	glPopMatrix();
	draw_Orbita(1300,90);
}
void desenharJupiter()
{
	glPushMatrix();
	glTranslatef(2000,0,0);
	glColor3f(0,0,1);
	rotJupiter+=0.87;
	rotacao(rotJupiter);
	glutWireSphere((139.822/2),32,32);
	glPopMatrix();
	draw_Orbita(2000,90);
}
void desenharSaturno()
{
	glPushMatrix();
	glTranslatef(2300,0,0);
	glColor3f(0.48,0.48,0.48);
	rotSaturno+=0.65;
	rotacao(rotSaturno);
	glutWireSphere((116.464/2),32,32);
	glPopMatrix();
	draw_Orbita(2300,90);
}
void desenharUrano()
{
	glPushMatrix();
	glTranslatef(2800,0,0);
	glColor3f(0.8,0.1,0.4);
	rotUrano+=0.543;
	rotacao(rotUrano);
	glutWireSphere((50.724/2),32,32);
	glPopMatrix();
	draw_Orbita(2800,90);
}

void desenharNeptuno()
{
	glPushMatrix();
	glColor3f(0.12,0.432,0.123);
	rotNeptuno+=1.23;
	glRotatef(90,0,0,1);
	glTranslatef(3200*sin(0.0),3200*cos(0.0)*sin(time),3200*cos(0.0)*cos(time));
	rotacao(rotNeptuno);
	glutWireSphere((49.244/2),32,32);
	glPopMatrix();
	draw_Orbita(3200,90);
}

void planetas(){
	time +=0.005;
	//sol
	desenharSol();
	//mercurio
	desenharMercurio();
	//venus
	desenharVenus();
	//terra
	desenharTerra();
	//planeta marte
	desenharMarte();
	//planeta jupiter
	desenharJupiter();
	//planeta saturno
	desenharSaturno();
	//planeta urano
	desenharUrano();
	//planeta spock
	desenharNeptuno();
}

void renderScene(void) {

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX,camY,camZ, 
			camlookX,camlookY,camlookZ,
			  0.0f,1.0f,0.0f);	
	draw_Axes();
	
	glPushMatrix();
	glTranslated(camlookX,camlookY,camlookZ);
	glColor3f(1,1,1);
	glutSolidSphere(1,10,10);
	glPopMatrix();

	glPushMatrix();
	planetas();
	glPopMatrix();

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

