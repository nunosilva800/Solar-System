#include "planetas.h"
#include "interface.h"

double raioCamara=10;
float newCamX=0,newCamY=0,newCamZ=0;



bool haColisao(float newCamZ,float newCamX,float newCamY,int planeta){
	float distObjs;
	if(planeta>=0){
		if(planeta==0)
			distObjs = sqrt( 
				pow(posicoes[planeta][0]-newCamX,2) + 
				pow(posicoes[planeta][1]-newCamY,2) +
				pow(posicoes[planeta][2]-newCamZ,2)) - raios[planeta]-raioCamara*scale;
		else
			distObjs = sqrt( 
				pow(posicoes[planeta][0]-newCamX,2) + 
				pow(posicoes[planeta][1]-newCamY,2) +
				pow(posicoes[planeta][2]-newCamZ,2)) - (raios[planeta]*scale)-(raioCamara*scale);
		if(distObjs<=0)return true;
	return false;
	
	}
	else{
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
			//printf(" planeta %d\n",i);
			//printf("posicoes camara XX:%f YY:%f ZZ:%f\n",newCamX,newCamY,newCamZ);
			//printf("posicoes planeta XX:%f YY:%f ZZ:%f\n",posicoes[i][0],posicoes[i][1],posicoes[i][2]);
			//printf("distancia aos centros: %f\n",sqrt( 
			//		pow(posicoes[i][0]-newCamX,2) + 
			//		pow(posicoes[i][1]-newCamY,2) +
			//		pow(posicoes[i][2]-newCamZ,2)) );
			//printf("distancia às superficies %f\n",distObjs);


			if(distObjs<=0)return true;
			}
		return false;
	}
}