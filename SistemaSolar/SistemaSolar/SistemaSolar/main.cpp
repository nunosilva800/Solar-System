#include <GL/glut.h>

#include <math.h>

float cameraxx = 1000.0;
float camerayy = 0.0;
float camerazz = 200.0;
float rotate = 0.0;

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

void renderScene(void) {

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(cameraxx,camerayy,camerazz, 
		      1000.0,0.0,0.0,
			  0.0f,1.0f,0.0f);	

	//sol
	glColor3f(1,1,0);
	glutSolidSphere(696,32,32);
	//mercurio
	glTranslatef(1000,0,0);
	glColor3f(0.5,0.5,0.5);
	glutSolidSphere(1.2195,32,32);
	//venus
	glTranslatef(10,0,0);
	glColor3f(0.6,0.5,0.1);
	glutSolidSphere(3.0259,32,32);
	//terra
	glTranslatef(10,0,0);
	glColor3f(0,0,1);
	glutSolidSphere(3.1855,32,32);
	// End of frame
	glutSwapBuffers();

}

void keys(unsigned char tecla, int x, int y){
	switch(tecla){
		case 'w': camerayy+=100;
			break;
		case 's': camerayy-=100;
			break;
		case 'a': cameraxx-=100;
			break;
		case 'd': cameraxx+=100;
			break;
		case 27 : exit(0);
	}
}

void skeys(int tecla, int x, int y){
	switch(tecla){
		case GLUT_KEY_UP: camerazz-=100; break;
		case GLUT_KEY_DOWN: camerazz+=100; break;
	}
}

void mouse(int botão, int estado, int x, int y){}


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
	glutIdleFunc(renderScene);
	
	glutReshapeFunc(changeSize);

	glutKeyboardFunc(keys);
	glutSpecialFunc(skeys);
	glutMouseFunc(mouse);

	gerarMenu();

// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// entrar no ciclo do GLUT 
	glutMainLoop();
}

