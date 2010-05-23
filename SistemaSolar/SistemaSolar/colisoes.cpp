#include "planetas.h"
#include "interface.h"
#include "vfc.h"

double raioCamara=10;
float newCamX=0,newCamY=0,newCamZ=0;
//detecçao colisoes planeta -> nave/camara
double dir[3];
double cam[3];


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
				pow(posicoes[planeta][2]-newCamZ,2)) - (raios[planeta])-(raioCamara*scale);
		if(distObjs<=0){
			double vec1[]={(double)camX,(double)camY,(double)camZ};
			double vec2[]={(double)camlookX,(double)camlookY,(double)camlookZ};
			double vec3[]={0.0,1.0,0.0};
			setPlanes(vec1,vec2,vec3);
			return true;
		}
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
					pow(posicoes[i][2]-newCamZ,2)) - (raios[i])-(raioCamara*scale);
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

bool haColisaoNave(float newCamZ,float newCamX,float newCamY,int planeta){
	float distObjs;
	if(planeta>=0){
		if(planeta==0)
			distObjs = sqrt( 
				pow(posicoes[planeta][0]-newCamX,2) + 
				pow(posicoes[planeta][1]-newCamY,2) +
				pow(posicoes[planeta][2]-newCamZ,2)) - raios[planeta]-r;
		else
			distObjs = sqrt( 
				pow(posicoes[planeta][0]-newCamX,2) + 
				pow(posicoes[planeta][1]-newCamY,2) +
				pow(posicoes[planeta][2]-newCamZ,2)) - (raios[planeta])-r;
		if(distObjs<=0){
			double vec1[]={(double)camX,(double)camY,(double)camZ};
			double vec2[]={(double)camlookX,(double)camlookY,(double)camlookZ};
			double vec3[]={0.0,1.0,0.0};
			setPlanes(vec1,vec2,vec3);
			return true;
		}
	return false;
	
	}
	else{
		for(int i=0;i<19;i++){
			if(i==0)
				distObjs = sqrt( 
					pow(posicoes[i][0]-newCamX,2) + 
					pow(posicoes[i][1]-newCamY,2) +
					pow(posicoes[i][2]-newCamZ,2)) - raios[i]-r;
			else
				distObjs = sqrt( 
					pow(posicoes[i][0]-newCamX,2) + 
					pow(posicoes[i][1]-newCamY,2) +
					pow(posicoes[i][2]-newCamZ,2)) - (raios[i])-r;
			//prints
			if(distObjs<=0)printf("COLISAO:    raio %f    planeta %d\n",r,i);
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

void afastaCamara(int planeta){
	if(cameraMode==0){
		criaVector(camX,camY,camZ,cam);
		normaliza(cam);
		normaliza(posicoes[planeta]);
		subVectores(cam,posicoes[planeta],dir);

		camX = camX+dir[0]*500*scale;
		camY = camY+dir[1]*500*scale;
		camZ = camZ+dir[2]*500*scale;	
	}else{
		criaVector(camlookX,camlookY,camlookZ,cam);
		normaliza(cam);
		normaliza(posicoes[planeta]);
		subVectores(cam,posicoes[planeta],dir);

		camlookX = camlookX+dir[0]*500*scale;
		camlookY = camlookY+dir[1]*500*scale;
		camlookZ = camlookZ+dir[2]*500*scale;
		camX = camX+dir[0]*500*scale;
		camY = camY+dir[1]*500*scale;
		camZ = camZ+dir[2]*500*scale;
	}
	double vec1[]={(double)camX,(double)camY,(double)camZ};
	double vec2[]={(double)camlookX,(double)camlookY,(double)camlookZ};
	double vec3[]={0.0,1.0,0.0};

	setPlanes(vec1,vec2,vec3);
}


bool haColisaoNave2(float camZ,float camX,float camY,float lookZ,float lookX,float lookY,int planeta){
	if(haColisao(camZ,camX,camY,planeta)){
		printf("colidou a camara\n");
		return true;}
	if(haColisao(lookZ,lookX,lookY,planeta))
	printf("colidou a nave\n");
	return haColisao(lookZ,lookX,lookY,planeta);
}
