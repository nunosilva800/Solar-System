#include "interface.h"
#include "planetas.h"
#include "texturas.h"
#include "colisoes.h"

float height = 2.0f;
float x = 0.0f;
float z = 0.0f;
float y = 0.0f;
int mouseBtn = 0;
int mouseMod = 0;

float camX = 0, camY = 0, camZ = 0;
float camlookX = 0.0f, camlookY = 0.0f, camlookZ = 0.0f;
float alpha = 200, beta = 25, r = 30000;

bool fullscreen = false;
bool luz = true;

int winX = 800;
int winY = 600;

int fontTitle = (int) GLUT_BITMAP_HELVETICA_12;
int fontText = (int) GLUT_BITMAP_HELVETICA_10;

int infotab;
int window;

char s[100];

int rotNaveX = -90;
int rotNaveY = 0;
int rotNaveZ = 180;

float* unitVector(float a1,float a2,float a3,float b1,float b2,float b3){
	float magnitude = sqrt( pow((a1-b1),2) + pow((a2-b2),2) + pow((a3-b3),2) );
	float vector[3] = { (a1-b1)/magnitude,
						(a2-b2)/magnitude,
						(a3-b3)/magnitude };
	return vector;
}

void processKeys(unsigned char tecla, int x, int y){
	float aux;
	float* vec = unitVector(camX,camY,camZ,camlookX,camlookY,camlookZ);
	switch(tecla){
		case 27  : exit(0);
		case '+' : if(scale < 200) scale++; desenhaAnel(); break;
		case '-' : if(scale > 1) scale--; desenhaAnel(); break;

		case ',' : distFactor+=0.01; desenharCintura(); break;
		case '.' : if(distFactor > 0.03)distFactor-=0.01; desenharCintura();  break;
		
		case 't' : timeFactor+=0.01; break;
		case 'g' : timeFactor-=0.01; break;
		case 'l' : luz?luz=false:luz=true; break;
		case 'f' : glutSetWindow(window);
			if(fullscreen){
				fullscreen=false;
				glutPositionWindow(100,100),
				glutReshapeWindow(winX,winY);
				//ao sair de fullscreen, colocar a infotab no sitio correcto
				glutSetWindow(infotab);
				glutPositionWindow(0.8*winX,0);
				glutReshapeWindow(0.2*winX, winY);
		   }
		   else{
				glutFullScreen();
				fullscreen=true; 
				//ao entrar em fullscreen, colocar a infotab no sitio correcto
				glutSetWindow(infotab);
				glutPositionWindow(0.8*glutGet(GLUT_SCREEN_WIDTH), 0);
				glutReshapeWindow(0.2*glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
		   }
		   break;

		case 'o' : orbitas?orbitas=false:orbitas=true; break;
		case 'c' : if(drawCintura)drawCintura=false;
				   else{ drawCintura=true; desenharCintura(); desenhaAnel(); }
				   break;
		case 'w' :if(!haColisao(
						(camlookZ +( aux * cos(beta*(PI/180)) * cos(alpha*(PI/180)))),
						(camlookX +( aux * cos(beta*(PI/180)) * sin(alpha*(PI/180)))),
						(camlookY +( aux * sin(beta*(PI/180)))),
						-1
						)){
						camlookX = camlookX-vec[0]*1000;
						camlookY = camlookY-vec[1]*1000;
						camlookZ = camlookZ-vec[2]*1000;
						camX = camX-vec[0]*1000;
						camY = camY-vec[1]*1000;
						camZ = camZ-vec[2]*1000;
						}
					return;
		case 's' : if(!haColisao(
						(camlookZ +( aux * cos(beta*(PI/180)) * cos(alpha*(PI/180)))),
						(camlookX +( aux * cos(beta*(PI/180)) * sin(alpha*(PI/180)))),
						(camlookY +( aux * sin(beta*(PI/180)))),
						-1
						)){
						camlookX = camlookX+vec[0]*1000;
						camlookY = camlookY+vec[1]*1000;
						camlookZ = camlookZ+vec[2]*1000;
						camX = camX+vec[0]*1000;
						camY = camY+vec[1]*1000;
						camZ = camZ+vec[2]*1000;
				}
				return;
		case 'a' :if(!haColisao(
						(camlookZ +( aux * cos(beta*(PI/180)) * cos(alpha*(PI/180)))),
						(camlookX +( aux * cos(beta*(PI/180)) * sin(alpha*(PI/180)))),
						(camlookY +( aux * sin(beta*(PI/180)))),
						-1
						)){
						camlookX = camlookX-vec[0]*1000;
						camlookY = camlookY-vec[1]*1000;
						camlookZ = camlookZ-vec[2]*1000;
						camX = camX-vec[0]*1000;
						camY = camY-vec[1]*1000;
						camZ = camZ-vec[2]*1000;
						}
					return;
		default : return;
	}
	glutSetWindow(infotab);
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
	float auxAlpha,auxBeta;
	if(mouseBtn!=1) return ;
	switch(mouseMod){
		case GLUT_ACTIVE_ALT://muda lookat
			camlookX -= (x-xx)*100;
			camlookZ -= (y-yy)*100;
			alpha = atan((camX-camlookX) / (camZ-camlookZ)) * (180/PI);
			beta = atan((camY-camlookY) / (camZ-camlookZ)) * (180/PI);
			r = sqrt(pow((camZ-camlookZ), 2) + pow((camX-camlookX), 2));
			r = sqrt(pow((camY-camlookY), 2) + pow(r, 2));
			break;
		case GLUT_ACTIVE_CTRL://aproxima / afasta
			r-=(y-yy)*100;
			if(r > 150000) r = 150000;
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

}

void menu(int id_op){
	switch (id_op){
		case 1 : {
			alpha = 200, beta = 25, r = 30000;
			camlookX = camlookY = camlookZ = 0;
			break;
				 }
		case 2 : {
			camlookX = distFactor*distSolTerra*sin(angTerra);
			camlookZ = distFactor*distSolTerra*cos(angTerra);
			r = raioTerra*scale*10;
			beta = 45; alpha = 45;
			break;
				 }
	}
}

void gerarMenu(){
	glutCreateMenu(menu);
	glutAddMenuEntry("Vista Geral",1);
	glutAddMenuEntry("Ir Para Terra",2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
