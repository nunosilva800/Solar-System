#include "planetas.h"
#include "interface.h"

double raioCamara=30;

bool haColisaoTerra(){
	printf("\nposX:%f posY:%f posz:%f",posTerra[0],posTerra[1],posTerra[2]);
	printf("\nCamX:%f CamY:%f Camz:%f",camX,camY,camY);
	float distObjs= sqrt(abs((posTerra[0]-camX)+(posTerra[1]-camY)+(posTerra[2]-camZ)))-raioTerra-raioCamara;
	printf("\n distancia: %f \n\n",distObjs);
	if (distObjs>0){
		return false;		
	}
	else return true;
}

bool haColisao(){
	return haColisaoTerra();
	
}
