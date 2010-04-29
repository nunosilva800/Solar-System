#include "planetas.h"
#include "interface.h"

double raioCamara=20;


bool haColisao(){
	float distObjs;
	int i = 12;
	for(int i=0;i<19;i++){
		if(i==0)
			distObjs = sqrt( 
				pow(posicoes[i][0]-camX,2) + 
				pow(posicoes[i][1]-camY,2) +
				pow(posicoes[i][2]-camZ,2)) - raios[i]-raioCamara*scale;
		else
			distObjs = sqrt( 
				pow(posicoes[i][0]-camX,2) + 
				pow(posicoes[i][1]-camY,2) +
				pow(posicoes[i][2]-camZ,2)) - (raios[i]*scale)-raioCamara*scale;
		if(distObjs<=0){printf("colision %d\n",i);return true;}
	}
	return false;
}
