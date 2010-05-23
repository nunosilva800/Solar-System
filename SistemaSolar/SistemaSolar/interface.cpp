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
float alpha = -150, beta = 30, r = 30000;

bool fullscreen = false;
bool luz = true;

int winX = 800;
int oldwinX = 800;
int winY = 600;
int oldwinY = 600;

int fontTitle = (int) GLUT_BITMAP_HELVETICA_12;
int fontText = (int) GLUT_BITMAP_HELVETICA_10;

int infotab;
int window;

// 0 = global ; 1 = Nave
int cameraMode = 0;

char s[100];

float navePos[3] = {10000.0, 1000.0, 0.0};


void unitVector(float a1,float a2,float a3,float b1,float b2,float b3,float* vec){
	float magnitude = sqrt( pow((a1-b1),2) + pow((a2-b2),2) + pow((a3-b3),2) );
	vec[0] = (a1-b1)/magnitude;
	vec[1] = (a2-b2)/magnitude;
	vec[2] = (a3-b3)/magnitude;
}

void processKeysNave(unsigned char tecla, int x, int y){
	float vec[3];
	unitVector(camX,camY,camZ,camlookX,camlookY,camlookZ,vec);
	float up[3] = { 0, 1, 0};
	float res[3];
	switch(tecla){
		case 'w' :if(!haColisaoNave2(
						(camZ-vec[2]*1000*distFactor*scale),	
						(camX-vec[0]*1000*distFactor*scale),
						(camY-vec[1]*1000*distFactor*scale),
						(camlookZ-vec[2]*1000*distFactor*scale),
						(camlookX-vec[0]*1000*distFactor*scale),
						(camlookY-vec[1]*1000*distFactor*scale),
						-1
						)){
						camlookX = camlookX-vec[0]*1000*distFactor*scale;
						camlookY = camlookY-vec[1]*1000*distFactor*scale;
						camlookZ = camlookZ-vec[2]*1000*distFactor*scale;
						camX = camX-vec[0]*1000*distFactor*scale;
						camY = camY-vec[1]*1000*distFactor*scale;
						camZ = camZ-vec[2]*1000*distFactor*scale;
						}
					return;
		case 's' : if(!haColisaoNave2(
						(camZ+vec[2]*1000*distFactor*scale),
						(camX+vec[0]*1000*distFactor*scale),
						(camY+vec[1]*1000*distFactor*scale),
						(camlookZ+vec[2]*1000*distFactor*scale),
						(camlookX+vec[0]*1000*distFactor*scale),
						(camlookY+vec[1]*1000*distFactor*scale),
						-1
						)){
						camlookX = camlookX+vec[0]*1000*distFactor*scale;
						camlookY = camlookY+vec[1]*1000*distFactor*scale;
						camlookZ = camlookZ+vec[2]*1000*distFactor*scale;
						camX = camX+vec[0]*1000*distFactor*scale;
						camY = camY+vec[1]*1000*distFactor*scale;
						camZ = camZ+vec[2]*1000*distFactor*scale;
				}
				return;
		case 'a' :
			if(!haColisaoNave2(
						(camlookZ +( r * cos(beta*(PI/180)) * cos((alpha++)*(PI/180)))),
						(camlookX +( r * cos(beta*(PI/180)) * sin((alpha++)*(PI/180)))),
						camY,
						camlookZ,
						camlookX,
						camlookY,
						-1
						)){
				camZ = camlookZ +( r * cos(beta*(PI/180)) * cos((alpha++)*(PI/180)));
				camX = camlookX +( r * cos(beta*(PI/180)) * sin((alpha++)*(PI/180)));
			}
			return;
		case 'd' :
			if(!haColisaoNave2(
						(camlookZ +( r * cos(beta*(PI/180)) * cos((alpha--)*(PI/180)))),
						(camlookX +( r * cos(beta*(PI/180)) * sin((alpha--)*(PI/180)))),
						camY,
						camlookZ,
						camlookX,
						camlookY,
						-1
						)){
				camZ = camlookZ +( r * cos(beta*(PI/180)) * cos((alpha--)*(PI/180)));
				camX = camlookX +( r * cos(beta*(PI/180)) * sin((alpha--)*(PI/180)));
			}
			return;
		case 'e' :
			res[0] = up[1] * vec[2] - up[2] * vec[1];
			res[1] = up[2] * vec[0] - up[0] * vec[2];
			res[2] = up[0] * vec[1] - up[1] * vec[0];
			if(!haColisaoNave2(
					(camZ + res[2]*1000*distFactor*scale),
					(camX + res[0]*1000*distFactor*scale),
					(camY + res[1]*1000*distFactor*scale),
					(camlookZ + res[2]*1000*distFactor*scale),
					(camlookX + res[0]*1000*distFactor*scale),
					(camlookY + res[1]*1000*distFactor*scale),
					-1
					)){
				camlookX = camlookX + res[0]*1000*distFactor*scale;
				camlookY = camlookY + res[1]*1000*distFactor*scale;
				camlookZ = camlookZ + res[2]*1000*distFactor*scale;
				camX = camX + res[0]*1000*distFactor*scale;
				camY = camY + res[1]*1000*distFactor*scale;
				camZ = camZ + res[2]*1000*distFactor*scale;
				}
			return;
		case 'q' :
			res[0] = up[1] * vec[2] - up[2] * vec[1];
			res[1] = up[2] * vec[0] - up[0] * vec[2];
			res[2] = up[0] * vec[1] - up[1] * vec[0];
			if(!haColisaoNave2(
					(camZ - res[2]*1000*distFactor*scale),
					(camX - res[0]*1000*distFactor*scale),
					(camY - res[1]*1000*distFactor*scale),
					(camlookZ - res[2]*1000*distFactor*scale),
					(camlookX - res[0]*1000*distFactor*scale),
					(camlookY - res[1]*1000*distFactor*scale),
					-1
					)){
				camlookX = camlookX - res[0]*1000*distFactor*scale;
				camlookY = camlookY - res[1]*1000*distFactor*scale;
				camlookZ = camlookZ - res[2]*1000*distFactor*scale;
				camX = camX - res[0]*1000*distFactor*scale;
				camY = camY - res[1]*1000*distFactor*scale;
				camZ = camZ - res[2]*1000*distFactor*scale;
				}
			return;
		default : return;
	}
}
void processKeysGlobal(unsigned char tecla, int x, int y){
	float aux;
	float vec[3];
	unitVector(camX,camY,camZ,camlookX,camlookY,camlookZ,vec);
	
	switch(tecla){
		case 'w' :  aux = r-500*distFactor*scale;
					if(aux<2000)aux=2000;
					if(!haColisao(
						(camlookZ +( aux * cos(beta*(PI/180)) * cos(alpha*(PI/180)))),
						(camlookX +( aux * cos(beta*(PI/180)) * sin(alpha*(PI/180)))),
						(camlookY +( aux * sin(beta*(PI/180)))),
						-1
						)){
							r -= 500*distFactor*scale;
						if(r < 1000*distFactor*scale) r = 1000*distFactor*scale;
							
						camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
						camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
						camY = camlookY +( r * sin(beta*(PI/180)));
					}
					return;
		case 's' :	aux = r+500*distFactor*scale;
					if(aux>1500000) aux = 1500000;
					if(!haColisao(
						(camlookZ +( aux * cos(beta*(PI/180)) * cos(alpha*(PI/180)))),
						(camlookX +( aux * cos(beta*(PI/180)) * sin(alpha*(PI/180)))),
						(camlookY +( aux * sin(beta*(PI/180)))),
						-1
						)){
					r+=500*distFactor*scale;
					if(r > 1500000) r = 1500000;
					camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
					camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
					camY = camlookY +( r * sin(beta*(PI/180)));
					}
					return;
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
			alpha++;
				camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
				camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			break;
		case GLUT_KEY_RIGHT:
			alpha--;
				camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
				camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			break;
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
	double vec1[]={(double)camX,(double)camY,(double)camZ};
	double vec2[]={(double)camlookX,(double)camlookY,(double)camlookZ};
	double vec3[]={0.0,1.0,0.0};

	setPlanes(vec1,vec2,vec3);
}


void processKeys(unsigned char tecla, int x, int y){
	//teclas proprias do modo global
	if(cameraMode == 0) processKeysGlobal(tecla, x, y);
	//teclas propias do modo nave
	if(cameraMode == 1) processKeysNave(tecla, x, y);
	//funcionalidades comuns aos modos de navegação
	switch(tecla){
		case '0' : menu(1); break;
		//diferenciar modos de camara
		case '1' : cameraMode ? menu(22) : menu(2); break;
		case '2' : cameraMode ? menu(33) : menu(3); break;
		case '3' : cameraMode ? menu(44) : menu(4); break;
		case '4' : cameraMode ? menu(55) : menu(5); break;
		case '5' : cameraMode ? menu(66) : menu(6); break;
		case '6' : cameraMode ? menu(77) : menu(7); break;
		case '7' : cameraMode ? menu(88) : menu(8); break;
		case '8' : cameraMode ? menu(99) : menu(9); break;
		case '9' : cameraMode ? menu(1010) : menu(10); break;
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
				winX = oldwinX;
				winY = oldwinY;
				fullscreen=false;
				glutPositionWindow(100,100);
				glutReshapeWindow(winX,winY);
				//ao sair de fullscreen, colocar a infotab no sitio correcto
				glutSetWindow(infotab);
				glutPositionWindow(0.8*winX,0);
				glutReshapeWindow(0.2*winX, winY);
		   }
		   else{
				glutFullScreen();
				oldwinX = winX;
				oldwinY = winY;
				winX = glutGet(GLUT_SCREEN_WIDTH);
				winY = glutGet(GLUT_SCREEN_HEIGHT);
				fullscreen=true; 
				//ao entrar em fullscreen, colocar a infotab no sitio correcto
				glutSetWindow(infotab);
				glutPositionWindow(0.8*winX, 0);
				glutReshapeWindow(0.2*winX, winY);
		   }
		   break;
		case 'o' : orbitas?orbitas=false:orbitas=true; break;
		case 'c' : if(drawCintura)drawCintura=false;
				   else{ drawCintura=true; desenharCintura(); desenhaAnel(); }
				   break;
	}
	//update view frustum
	double vec1[]={(double)camX,(double)camY,(double)camZ};
	double vec2[]={(double)camlookX,(double)camlookY,(double)camlookZ};
	double vec3[]={0.0,1.0,0.0};

	setPlanes(vec1,vec2,vec3);
}

void processSpecialKeys(int key, int xx, int yy){
	if(cameraMode == 0) processSpecialKeysGlobal(key, xx, yy);
	if(cameraMode == 1) processSpecialKeysNave(key, xx, yy);
	//update view frustum
	double vec1[]={(double)camX,(double)camY,(double)camZ};
	double vec2[]={(double)camlookX,(double)camlookY,(double)camlookZ};
	double vec3[]={0.0,1.0,0.0};

	setPlanes(vec1,vec2,vec3);
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
	
	//update view frustum	
	double vec1[]={(double)camX,(double)camY,(double)camZ};
	double vec2[]={(double)camlookX,(double)camlookY,(double)camlookZ};
	double vec3[]={0.0,1.0,0.0};

	setPlanes(vec1,vec2,vec3);
}

void fmotion(int xx, int yy)
{
	if(mouseBtn!=1) return ;
	float aux;
	switch(mouseMod){
		case GLUT_ACTIVE_ALT://muda lookat
			if(cameraMode == 0){
				camlookX -= (x-xx)*500*distFactor;
				camlookZ -= (y-yy)*500*distFactor;
				alpha = atan((camX-camlookX) / (camZ-camlookZ)) * (180/PI);
				beta = atan((camY-camlookY) / (camZ-camlookZ)) * (180/PI);
				r = sqrt(pow((camZ-camlookZ), 2) + pow((camX-camlookX), 2));
				r = sqrt(pow((camY-camlookY), 2) + pow(r, 2));
			}
			break;
		case GLUT_ACTIVE_CTRL://aproxima / afasta
			if(cameraMode == 0){
				aux = r;
				aux-=(y-yy)*3*scale;
				if(aux > 1500000) aux = 1500000;
				if(aux < 50*scale) aux = 50*scale;
				if(!haColisao(
					(camlookZ +( aux * cos(beta*(PI/180)) * cos(alpha*(PI/180)))),
					(camlookX +( aux * cos(beta*(PI/180)) * sin(alpha*(PI/180)))),
					(camlookY +( aux * sin(beta*(PI/180)))),
					-1))
				{
					r-=(y-yy)*3*scale;
					if(r > 1500000) r = 1500000;
					if(r < 50*scale) r = 50*scale;
					camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
					camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
					camY = camlookY +( r * sin(beta*(PI/180)));
				}
			}
			break;
		default:
			if(!haColisao(
				(camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)))),
				(camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)))),
				(camlookY +( r * sin(beta*(PI/180)))),
				-1)){
					alpha+=((x-xx)*0.3);
					beta-=((y-yy)*0.3);
					if(beta > 89) beta = 89;
					if(beta < -89) beta = -89;
					camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
					camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
					camY = camlookY +( r * sin(beta*(PI/180)));
			}
	}
	x=xx;y=yy;
	//update view frustum
	double vec1[]={(double)camX,(double)camY,(double)camZ};
	double vec2[]={(double)camlookX,(double)camlookY,(double)camlookZ};
	double vec3[]={0.0,1.0,0.0};

	setPlanes(vec1,vec2,vec3);
}

void menu(int id_op){
	double vec [3];
	double vec1 [3];
	double camAux[3];
	double planetaAux[3]={0,0,0};
	switch (id_op){
		case 1 : {
			if(cameraMode == 0){
				cameraMode = 1;
				camlookX = navePos[0];
				camlookY = navePos[1];
				camlookZ = navePos[2];
				r = 2000;
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
		 //settings para modo de camara geral
		case 2 : {
			alpha = 200, beta = 25, r = 30000;
			camlookX = camlookY = camlookZ = 0;
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		case 3 : {//mercurio
			camlookX = posicoes[1][0];
			camlookY = posicoes[1][1];
			camlookZ = posicoes[1][2];
			r = raioMercurio*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		 case 4 : {//venus
			camlookX = posicoes[2][0];
			camlookY = posicoes[2][1];
			camlookZ = posicoes[2][2];
			r = raioVenus*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		case 5 : {//terra
			camlookX = posicoes[4][0];
			camlookY = posicoes[4][1];
			camlookZ = posicoes[4][2];
			r = raioTerra*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		case 6 : {//marte
			camlookX = posicoes[7][0];
			camlookY = posicoes[7][1];
			camlookZ = posicoes[7][2];
			r = raioMarte*scale*10;
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		case 7 : {//jupiter
			camlookX = posicoes[12][0];
			camlookY = posicoes[12][1];
			camlookZ = posicoes[12][2];
			r = raioJupiter*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		 case 8 : {//saturno
			camlookX = posicoes[16][0];
			camlookY = posicoes[16][1];
			camlookZ = posicoes[16][2];
			r = raioSaturno*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		case 9 : {//urano
			camlookX = posicoes[17][0];
			camlookY = posicoes[17][1];
			camlookZ = posicoes[17][2];
			r = raioUrano*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		 case 10 : {//nepturno
			camlookX = posicoes[18][0];
			camlookY = posicoes[18][1];
			camlookZ = posicoes[18][2];
			r = raioNeptuno*scale*10;
			
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
	   //settings para a nave
		case 22 : {
			camlookX = 10000;
			camlookY = 1000;
			camlookZ = 1000;
			r = 2000;
			camZ = camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180)));
			camX = camlookX +( r * cos(beta*(PI/180)) * sin(alpha*(PI/180)));
			camY = camlookY +( r * sin(beta*(PI/180)));
			break;
				 }
		case 33 : {
			normaliza(camAux);
			vec1[0] = posicoes[1][0];
			vec1[1] = posicoes[1][1];
			vec1[2] = posicoes[1][2];

			normaliza(vec1);
			subVectores(planetaAux,vec1,vec);

			camlookX = posicoes[1][0] - vec[0]*(300+raioMercurio*scale*2);
			camlookY = posicoes[1][1] - vec[1]*(300+raioMercurio*scale*2);
			camlookZ = posicoes[1][2] - vec[2]*(300+raioMercurio*scale*2);

			r = 2000;
			camZ = camlookZ - r*vec[2];
			camX = camlookX - r*vec[0];
			camY = camlookY - r*vec[1];
			break;
				 }
		 case 44 : {
			normaliza(camAux);
			vec1[0] = posicoes[2][0];
			vec1[1] = posicoes[2][1];
			vec1[2] = posicoes[2][2];

			normaliza(vec1);
			subVectores(planetaAux,vec1,vec);

			camlookX = posicoes[2][0] - vec[0]*(300+raioMercurio*scale*2);
			camlookY = posicoes[2][1] - vec[1]*(300+raioMercurio*scale*2);
			camlookZ = posicoes[2][2] - vec[2]*(300+raioMercurio*scale*2);

			r = 2000;
			camZ = camlookZ - r*vec[2];
			camX = camlookX - r*vec[0];
			camY = camlookY - r*vec[1];
			break;
				 }
		case 55 : {
			normaliza(camAux);
			vec1[0] = posicoes[4][0];
			vec1[1] = posicoes[4][1];
			vec1[2] = posicoes[4][2];

			normaliza(vec1);
			subVectores(planetaAux,vec1,vec);

			camlookX = posicoes[4][0] - vec[0]*(300+raioMercurio*scale*2);
			camlookY = posicoes[4][1] - vec[1]*(300+raioMercurio*scale*2);
			camlookZ = posicoes[4][2] - vec[2]*(300+raioMercurio*scale*2);

			r = 2000;
			camZ = camlookZ - r*vec[2];
			camX = camlookX - r*vec[0];
			camY = camlookY - r*vec[1];
			break;
				 }
		case 66 : {
			normaliza(camAux);
			vec1[0] = posicoes[7][0];
			vec1[1] = posicoes[7][1];
			vec1[2] = posicoes[7][2];

			normaliza(vec1);
			subVectores(planetaAux,vec1,vec);

			camlookX = posicoes[7][0] - vec[0]*(300+raioMercurio*scale*2);
			camlookY = posicoes[7][1] - vec[1]*(300+raioMercurio*scale*2);
			camlookZ = posicoes[7][2] - vec[2]*(300+raioMercurio*scale*2);

			r = 2000;
			camZ = camlookZ - r*vec[2];
			camX = camlookX - r*vec[0];
			camY = camlookY - r*vec[1];
			break;
				 }
		case 77 : {
			normaliza(camAux);
			vec1[0] = posicoes[12][0];
			vec1[1] = posicoes[12][1];
			vec1[2] = posicoes[12][2];

			normaliza(vec1);
			subVectores(planetaAux,vec1,vec);

			camlookX = posicoes[12][0] - vec[0]*(300+raioMercurio*scale*2);
			camlookY = posicoes[12][1] - vec[1]*(300+raioMercurio*scale*2);
			camlookZ = posicoes[12][2] - vec[2]*(300+raioMercurio*scale*2);

			r = 2000;
			camZ = camlookZ - r*vec[2];
			camX = camlookX - r*vec[0];
			camY = camlookY - r*vec[1];
			break;
				 }
		 case 88 : {
			normaliza(camAux);
			vec1[0] = posicoes[16][0];
			vec1[1] = posicoes[16][1];
			vec1[2] = posicoes[16][2];

			normaliza(vec1);
			subVectores(planetaAux,vec1,vec);

			camlookX = posicoes[16][0] - vec[0]*(300+raioMercurio*scale*2);
			camlookY = posicoes[16][1] - vec[1]*(300+raioMercurio*scale*2);
			camlookZ = posicoes[16][2] - vec[2]*(300+raioMercurio*scale*2);

			r = 2000;
			camZ = camlookZ - r*vec[2];
			camX = camlookX - r*vec[0];
			camY = camlookY - r*vec[1];
			break;
				 }
		case 99 : {
			normaliza(camAux);
			vec1[0] = posicoes[17][0];
			vec1[1] = posicoes[17][1];
			vec1[2] = posicoes[17][2];

			normaliza(vec1);
			subVectores(planetaAux,vec1,vec);

			camlookX = posicoes[17][0] - vec[0]*(300+raioMercurio*scale*2);
			camlookY = posicoes[17][1] - vec[1]*(300+raioMercurio*scale*2);
			camlookZ = posicoes[17][2] - vec[2]*(300+raioMercurio*scale*2);

			r = 2000;
			camZ = camlookZ - r*vec[2];
			camX = camlookX - r*vec[0];
			camY = camlookY - r*vec[1];
			break;
				 }
		 case 1010 : {
			normaliza(camAux);
			vec1[0] = posicoes[18][0];
			vec1[1] = posicoes[18][1];
			vec1[2] = posicoes[2][2];

			normaliza(vec1);
			subVectores(planetaAux,vec1,vec);

			camlookX = posicoes[2][0] - vec[0]*(300+raioMercurio*scale*2);
			camlookY = posicoes[2][1] - vec[1]*(300+raioMercurio*scale*2);
			camlookZ = posicoes[2][2] - vec[2]*(300+raioMercurio*scale*2);

			r = 2000;
			camZ = camlookZ - r*vec[2];
			camX = camlookX - r*vec[0];
			camY = camlookY - r*vec[1];
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
