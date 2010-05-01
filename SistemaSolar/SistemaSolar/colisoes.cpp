#include "planetas.h"
#include "interface.h"

double raioCamara=10;
float newCamX=0,newCamY=0,newCamZ=0;

/*
bool haColisao(){
	float distObjs;
	int i = 12;
	for(int i=0;i<19;i++){
		if(i==0)
			distObjs = sqrt( 
				pow(posicoes[i][0]-newCamX,2) + 
				pow(posicoes[i][1]-newCamY,2) +
				pow(posicoes[i][2]-newCamZ,2)) - raios[i]-raioCamara*scale;
		else
			distObjs = sqrt( 
				pow(posicoes[i][0]-newCamX,2) + 
				pow(posicoes[i][1]-newCamY,2) +
				pow(posicoes[i][2]-newCamZ,2)) - (raios[i]*scale)-(raioCamara*scale);
		if(distObjs<=0){printf("colision %d\n",i);return true;}
	}
	return false;
}*/

bool haColisao(float newCamZ,float newCamX,float newCamY){
	float distObjs;
	printf("\n\nraio:%f\n",camlookZ +( r * cos(beta*(PI/180)) * cos(alpha*(PI/180))));
	for(int i=0;i<19;i++){
		if(i==0)
			distObjs = sqrt( 
				pow(posicoes[i][0]-newCamX,2) + 
				pow(posicoes[i][1]-newCamY,2) +
				pow(posicoes[i][2]-newCamZ,2)) - raios[i]-raioCamara*scale;
		else
			distObjs = sqrt( 
				pow(posicoes[i][0]-newCamX,2) + 
				pow(posicoes[i][1]-newCamY,2) +
				pow(posicoes[i][2]-newCamZ,2)) - (raios[i]*scale)-(raioCamara*scale);
		//prints
		if(distObjs<=0)printf("COLISAO:");
		printf(" planeta %d\n",i);
		printf("posicoes camara XX:%f YY:%f ZZ:%f\n",newCamX,newCamY,newCamZ);
		printf("posicoes planeta XX:%f YY:%f ZZ:%f\n",posicoes[i][0],posicoes[i][1],posicoes[i][2]);
		printf("distancia aos centros: %f\n",sqrt( 
				pow(posicoes[i][0]-newCamX,2) + 
				pow(posicoes[i][1]-newCamY,2) +
				pow(posicoes[i][2]-newCamZ,2)) );
		printf("distancia às superficies %f\n",distObjs);


		if(distObjs<=0)return true;
		}
	return false;
}