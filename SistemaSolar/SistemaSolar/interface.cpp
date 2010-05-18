#include "interface.h"
#include "planetas.h"
#include "texturas.h"
#include "colisoes.h"
#include "vfc.h"

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

// 0 = global ; 1 = Nave
int cameraMode = 0;

char s[100];

float navePos[3] = {10000.0, 1000.0, 0.0};


float* unitVector(float a1,float a2,float a3,float b1,float b2,float b3){
	float magnitude = sqrt( pow((a1-b1),2) + pow((a2-b2),2) + pow((a3-b3),2) );
	float vector[3] = { (a1-b1)/magnitude,
						(a2-b2)/magnitude,
						(a3-b3)/magnitude };
	return vector;
}

void processKeysNave(unsigned char tecla, int x, int y){
	float aux;
	float* vec = unitVector(camX,camY,camZ,camlookX,camlookY,camlookZ);
	switch(tecla){
		case 'w' :if(!haColisao(
						(camlookZ-vec[2]*1000),
						(camlookX-vec[0]*1000),
						(camlookY-vec[1]*1000),
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
						(camlookZ+vec[2]*1000),
						(camlookX+vec[0]*1000),
						(camlookY+vec[1]*1000),
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
		case 'a' :
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos((alpha++)*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin((alpha++)*(PI/180)));
			return;
		case 'd' :
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos((alpha--)*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin((alpha--)*(PI/180)));
			return;
		default : return;
	}
}

void processSpecialKeysNave(int key, int xx, int yy) 
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

void processKeysGlobal(unsigned char tecla, int x, int y){
	float aux;
	float* vec = unitVector(camX,camY,camZ,camlookX,camlookY,camlookZ);

	
	switch(tecla){
		case 'w' :  aux = r-1000;
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
	}
}

void processSpecialKeysGlobal(int key, int xx, int yy) 
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


void processKeys(unsigned char tecla, int x, int y){
	//teclas proprias do modo global
	if(cameraMode == 0) processKeysGlobal(tecla, x, y);
	//teclas propias do modo nave
	if(cameraMode == 1) processKeysNave(tecla, x, y);
	//funcionalidades comuns aos modos de navegação
	switch(tecla){
		case '0' : menu(1); break;
		case '1' : menu(2); break;
		case '2' : menu(3); break;
		case '3' : menu(4); break;
		case '4' : menu(5); break;
		case '5' : menu(6); break;
		case '6' : menu(7); break;
		case '7' : menu(8); break;
		case '8' : menu(9); break;
		case '9' : menu(10); break;
		case 27  : exit(0);
		case '+' : if(scale < 200) scale++; desenhaAnel(); glutSetWindow(infotab); glutPostRedisplay(); break;
		case '-' : if(scale > 1) scale--; desenhaAnel(); glutSetWindow(infotab); glutPostRedisplay(); break;

		case ',' : distFactor+=0.01; desenharCintura(); glutSetWindow(infotab); glutPostRedisplay(); break;
		case '.' : if(distFactor > 0.03)distFactor-=0.01; desenharCintura();
			glutSetWindow(infotab); glutPostRedisplay(); break;
		
		case 't' : timeFactor+=0.01; glutSetWindow(infotab); glutPostRedisplay(); break;
		case 'g' : timeFactor-=0.01; glutSetWindow(infotab); glutPostRedisplay(); break;
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
	}
}

void processSpecialKeys(int key, int xx, int yy){
	if(cameraMode == 0) processSpecialKeysGlobal(key, xx, yy);
	if(cameraMode == 1) processSpecialKeysNave(key, xx, yy);
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
			if(r < 1000) r = 1000;
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

	//fazer o rato desaparecer
	glutSetCursor( GLUT_CURSOR_NONE );

}

void menu(int id_op){
	switch (id_op){
		case 1 : {
			if(cameraMode == 0){
				cameraMode = 1;
				camlookX = navePos[0];
				camlookY = navePos[1];
				camlookZ = navePos[2];
				r = 3000;
				camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
				camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
				camY = camlookY +( r * sin(beta*(PI/180)));
			}
			else{
				cameraMode = 0;
				navePos[0] = camlookX;
				navePos[1] = camlookY;
				navePos[2] = camlookZ;
				alpha = 200, beta = 25, r = 30000;
				camlookX = camlookY = camlookZ = 0;
				camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
				camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
				camY = camlookY +( r * sin(beta*(PI/180)));
			}
			glutSetWindow(infotab);
			glutPostRedisplay();
			break;
				 }
		case 2 : {
			alpha = 200, beta = 25, r = 30000;
			camlookX = camlookY = camlookZ = 0;
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		case 3 : {
			camlookX = distFactor*distSolMercurio*sin(angMercurio);
			camlookY = 0;
			camlookZ = distFactor*distSolMercurio*cos(angMercurio);
			r = raioMercurio*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		 case 4 : {
			camlookX = distFactor*distSolVenus*sin(angVenus);
			camlookY = 0;
			camlookZ = distFactor*distSolVenus*cos(angVenus);
			r = raioVenus*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		case 5 : {
			camlookX = distFactor*distSolTerra*sin(angTerra);
			camlookY = 0;
			camlookZ = distFactor*distSolTerra*cos(angTerra);
			r = raioTerra*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		case 6 : {
			camlookX = distFactor*distSolMarte*sin(angMarte);
			camlookY = 0;
			camlookZ = distFactor*distSolMarte*cos(angMarte);
			r = raioMarte*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		case 7 : {
			camlookX = distFactor*distSolJupiter*sin(angJupiter);
			camlookY = 0;
			camlookZ = distFactor*distSolJupiter*cos(angJupiter);
			r = raioJupiter*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		 case 8 : {
			camlookX = distFactor*distSolSaturno*sin(angSaturno);
			camlookY = 0;
			camlookZ = distFactor*distSolSaturno*cos(angSaturno);
			r = raioSaturno*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		case 9 : {
			camlookX = distFactor*distSolUrano*sin(angUrano);
			camlookY = 0;
			camlookZ = distFactor*distSolUrano*cos(angUrano);
			r = raioUrano*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		 case 10 : {
			camlookX = distFactor*distSolNeptuno*sin(angNeptuno);
			camlookY = 0;
			camlookZ = distFactor*distSolNeptuno*cos(angNeptuno);
			r = raioNeptuno*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
	}
}

void gerarMenu(){
	glutCreateMenu(menu);
	glutAddMenuEntry("Trocar Modo de Camera (0)",1);
	glutAddMenuEntry("Vista Geral (1)",2);
	glutAddMenuEntry("Ir Para Mercurio (2)",3);
	glutAddMenuEntry("Ir Para Venus (3)",4);
	glutAddMenuEntry("Ir Para Terra (4)",5);
	glutAddMenuEntry("Ir Para Marte (5)",6);
	glutAddMenuEntry("Ir Para Jupiter (6)",7);
	glutAddMenuEntry("Ir Para Saturno (7)",8);
	glutAddMenuEntry("Ir Para Urano (8)",9);
	glutAddMenuEntry("Ir Para Nepturno (9)",10);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
