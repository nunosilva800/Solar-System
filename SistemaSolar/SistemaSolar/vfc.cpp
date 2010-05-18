#include "interface.h"
#include <stdlib.h>

double nh,nw,fh,fw;
double fov[3];

double matriznormais[6][3];
double linhad[6];

void calculaAltLarg(int fov,int ratio,int nearDist,int farDist){
	nh = 2 * tanf(fov / 2) * nearDist;	
	nw = nh * ratio;	
	fh = 2 * tanf(fov / 2) * farDist;
	fw = fh * ratio;
}

double innerProduct(double * vec1, double *vec2)
{
	return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}

double* prodVect(double vec1[3],double vec2[3]){
	double res[3];
	res[0]= vec1[1]*vec2[2] - vec1[2]*vec2[1];
	res[1]= vec1[2]*vec2[0] - vec1[0]*vec2[2];
	res[2]= vec1[0]*vec2[1] - vec1[1]*vec2[0];

	return res;
}

double* normaliza(double *vec){
	double magnitude = sqrt( pow(vec[0],2) + pow(vec[1],2) + pow(vec[2],2) );
	double vector[3] = { vec[0]/magnitude,
						vec[1]/magnitude,
						vec[2]/magnitude };
	return vector;
}

double* somaVectores(double vec1[3],double vec2[3]){
	double res[3];
	res[0]= vec1[0]+vec2[0];
	res[1]= vec1[1]+vec2[1];
	res[2]= vec1[2]+vec2[2];
	return res;
} 

double* subVectores(double vec1[3],double vec2[3]){
	double res[3];
	res[0]= vec1[0]-vec2[0];
	res[1]= vec1[1]-vec2[1];
	res[2]= vec1[2]-vec2[2];
	return res;
}

double* multVecValor(double vec1[3],double valor){
	double res[3];
	res[0]= vec1[0]*valor;
	res[1]= vec1[1]*valor;
	res[2]= vec1[2]*valor;
	return res;
}
	

void geraPlano(double *v1,double* v2,double*v3,int indice)
{
	double* aux1, *aux2;

	aux1 = subVectores(v1,v2);
	aux2 = subVectores(v3,v2);
	
	double* arrAux=prodVect(aux2,aux1);

	matriznormais[indice][0]= arrAux[0];
	matriznormais[indice][1]= arrAux[1];
	matriznormais[indice][2]= arrAux[2];

	arrAux = normaliza(matriznormais[indice]);
	matriznormais[indice][0]=arrAux[0];	
	matriznormais[indice][1]=arrAux[1];	
	matriznormais[indice][2]=arrAux[2];

	double * copy = v2;
	
	linhad[indice] = -(innerProduct(matriznormais[indice],copy));
}


//cams é o p
//camlooks é o l
//o u é fixo 0.0f,1.0f,0.0f
void setPlanes(double *p, double *l, double *u){
	double dir[3],Z[3];
	double *nc,*fc;
	double *X,*Y,*zAxis,*xAxis,*yAxis;

	double *ntr,*ntl,*nbr,*nbl;
	double *ftr,*ftl,*fbr,*fbl;
	int nearDist = 10;
	int farDist = 1000000000;
	// compute the Z axis of camera
	// this axis points in the opposite direction from 
	// the looking direction
	Z[0]=p[0]-l[0];
	Z[1]=p[1]-l[1];
	Z[2]=p[2]-l[2];
	zAxis = normaliza(Z);

	// X axis of camera with given "up" vector and Z axis
	X = prodVect(u,zAxis);
	xAxis = normaliza(X);

	// the real "up" vector is the cross product of Z and X
	Y = prodVect(zAxis,xAxis);

	// compute the centers of the near and far planes
	nc = subVectores(p,multVecValor(zAxis,nearDist));
	fc = subVectores(p,multVecValor(zAxis,farDist));

	// compute the 4 corners of the frustum on the near plane
	yAxis = (double*)malloc(3*sizeof(double));
	
	ntl = somaVectores(nc,subVectores(multVecValor(yAxis,nh),multVecValor(xAxis,nw)));
	//ntl = nc + yAxis * nh - xAxis * nw;
	ntr = somaVectores(nc,somaVectores(multVecValor(yAxis,nh),multVecValor(xAxis,nw)));
	//ntr = nc + yAxis * nh + xAxis * nw;
	nbl = subVectores(nc,subVectores(multVecValor(yAxis,nh),multVecValor(xAxis,nw)));
	//nbl = nc - yAxis * nh - xAxis * nw;
	nbr = subVectores(nc,somaVectores(multVecValor(yAxis,nh),multVecValor(xAxis,nw)));
	//nbr = nc - yAxis * nh + xAxis * nw;

	// compute the 4 corners of the frustum on the far plane
	//ftl = fc + multVecValor(yAxis,fh) - xAxis * fw;
	ftl = somaVectores(fc,subVectores(multVecValor(yAxis,fh),multVecValor(xAxis,fw)));
	//ftr = fc + yAxis * fh + xAxis * fw;
	ftr = somaVectores(fc,somaVectores(multVecValor(yAxis,fh),multVecValor(xAxis,fw)));
	//fbl = fc - yAxis * fh - xAxis * fw;
	fbl = subVectores(fc,subVectores(multVecValor(yAxis,fh),multVecValor(xAxis,fw)));
	//fbr = fc - yAxis * fh + xAxis * fw;
	fbr = subVectores(fc,somaVectores(multVecValor(yAxis,fh),multVecValor(xAxis,fw)));

	printf("nBR : %f %f %f",nbr[0],nbr[1],nbr[2]);
	glBegin(GL_QUADS);
	glVertex3dv(ntl);
	glVertex3dv(nbl);
	glVertex3dv(nbr);
	glVertex3dv(ntr);
	glEnd();

	// compute the six planes
	// the function set3Points assumes that the points
	// are given in counter clockwise order
	geraPlano(ntr,ntl,ftl,0);
	//pl[TOP].set3Points(ntr,ntl,ftl);
	geraPlano(nbl,nbr,fbr,1);
	//pl[BOTTOM].set3Points(nbl,nbr,fbr);
	geraPlano(ntl,nbl,fbl,2);
	//pl[LEFT].set3Points(ntl,nbl,fbl);
	geraPlano(nbr,ntr,fbr,3);
	//pl[RIGHT].set3Points(nbr,ntr,fbr);
	geraPlano(ntl,ntr,nbr,4);
	//pl[NEARP].set3Points(ntl,ntr,nbr);
	geraPlano(ftr,ftl,fbl,5);
	//pl[FARP].set3Points(ftr,ftl,fbl);
}	
	
double distancia(double *p,int indice){

	return (linhad[indice] + innerProduct(matriznormais[indice],p));	
}
int sphereInFrustum(double *point, double radius) {

	double distance;
	int result = 1;//INSIDE;

	double* p = (double*)malloc(3*sizeof(double));
	p[0]=point[0];
	p[1]=point[1];
	p[2]=point[2];
	
	for(int i=0; i < 6; i++) {
		distance = distancia(p,i);
		if (distance < -radius)
			result = 0;//OUTSIDE;
		else if (distance < radius)
			result =  2;//INTERSECT;
		
	}
	printf("OLHA: %d\n",result);
	return(result);
}