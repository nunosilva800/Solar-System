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

bool axes = false;
bool fullscreen = false;
bool luz = false;

int winX = 800;
int winY = 600;

int fontTitle = (int) GLUT_BITMAP_HELVETICA_12;
int fontText = (int) GLUT_BITMAP_HELVETICA_10;

GLfloat lamb[] = {.2, .2, .2, 1};
GLfloat ldiff[] = {1, 1, 1, 1};
GLfloat lpos[] = {0.0, 0.0 ,0.0, 1.0};
GLfloat specular[] = {.5, .5, .5, 1.0f};

int infotab;
int window;

char s[100];

void processKeys(unsigned char tecla, int x, int y){
	float aux;
	switch(tecla){
		case 27 : exit(0);
		case '+' : if(scale < 200) scale++; desenhaAnel(); break;
		case '-' : if(scale > 1) scale--; desenhaAnel(); break;

		case ',' : distFactor+=0.01; desenharCintura(); break;
		case '.' : if(distFactor > 0.03)distFactor-=0.01; desenharCintura();  break;
		
		case 't' : timeFactor+=0.01; break;
		case 'g' : timeFactor-=0.01; break;
		case 'l' : luz?luz=false:luz=true; break;
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
		case 'w' :	aux = r-1000;
					if(aux<2000)aux=2000;
					if(!haColisao(
						(camlookZ +( aux * cos(beta*(PI/180)) * cos(alpha*(PI/180)))),
						(camlookX +( aux * cos(beta*(PI/180)) * sin(alpha*(PI/180)))),
						(camlookY +( aux * sin(beta*(PI/180)))),
						-1
						)){
						r-=1000;
						if(r < 2000) r = 2000;
						camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
						camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
						camY = camlookY +( r * sin(beta*(PI/180)));
					}
					return;
		case 's' :	aux = r+1000;
					if(aux>1500000) aux = 1500000;
					if(!haColisao(
						(camlookZ +( aux * cos(beta*(PI/180)) * cos(alpha*(PI/180)))),
						(camlookX +( aux * cos(beta*(PI/180)) * sin(alpha*(PI/180)))),
						(camlookY +( aux * sin(beta*(PI/180)))),
						-1
						)){
					r+=1000;
					if(r > 1500000) r = 1500000;
					camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
					camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
					camY = camlookY +( r * sin(beta*(PI/180)));
				}
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
			if(r > 1500000) r = 1500000;
			if(r < 2000) r = 2000;
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
		default:/*auxAlpha=alpha+((x-xx)*0.3);
				  auxBeta=beta-((y-yy)*0.3);
				  if(auxBeta > 89) beta = 89;
				  if(auxBeta < -89) beta = -89;

				if(!haColisao(camlookZ +( r * cos(auxBeta*(PI/180)) * cos(auxAlpha*(PI/180))),
					camlookX +( r * cos(auxBeta*(PI/180)) * sin(auxAlpha*(PI/180))),
					camlookY +( r * sin(auxBeta*(PI/180))),-1
					)){*/
					alpha+=((x-xx)*0.3);
					beta-=((y-yy)*0.3);
					if(beta > 89) beta = 89;
					if(beta < -89) beta = -89;
					camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
					camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
					camY = camlookY +( r * sin(beta*(PI/180)));
				//}
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
	camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
	camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
	camY = camlookY +( r * sin(beta*(PI/180)));

}

void gerarMenu(){
	glutCreateMenu(menu);
	glutAddMenuEntry("Vista Geral",1);
	glutAddMenuEntry("Ir Para Terra",2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
