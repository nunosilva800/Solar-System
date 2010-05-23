#include "interface.h"
#include "planetas.h"
#include <stdlib.h>

double nh,nw,fh,fw;
double fov[3];

double matriznormais[6][3];
double linhad[6];

void criaVector(float v1,float v2,float v3,double res[3]){
	res[0]=(double)v1;
	res[1]=(double)v2;
	res[2]=(double)v3;
}

void calculaAltLarg(int fov,float ratio,int nearDist,int farDist){
	/*float nhx = 2 * tanf(fov / 2) * nearDist;	
	nw = nh * ratio;	
	fh = 2 * tanf(fov / 2) * farDist;
	fw = fh * ratio;*/

	float tang = (float)tan((PI/180) * fov * 0.5) ;
	nh = nearDist * tang*2;
	nw = nh * ratio; 
	fh = farDist  * tang*2;
	fw = fh * ratio;
}

double innerProduct(double *vec1, double *vec2)
{
	return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}

void prodVect(double vec1[3],double vec2[3],double* res){
	res[0]= vec1[1]*vec2[2] - vec1[2]*vec2[1];
	res[1]= vec1[2]*vec2[0] - vec1[0]*vec2[2];
	res[2]= vec1[0]*vec2[1] - vec1[1]*vec2[0];
}

void normaliza(double *vec){
	double magnitude = sqrt( pow(vec[0],2) + pow(vec[1],2) + pow(vec[2],2) );

	vec[0] = vec[0]/magnitude;
	vec[1] = vec[1]/magnitude;
	vec[2] = vec[2]/magnitude;
}

void somaVectores(double* vec1,double *vec2,double *res){
	res[0]= vec1[0]+vec2[0];
	res[1]= vec1[1]+vec2[1];
	res[2]= vec1[2]+vec2[2];
} 

void subVectores(double* vec1,double *vec2,double *res){
	res[0]= vec1[0]-vec2[0];
	res[1]= vec1[1]-vec2[1];
	res[2]= vec1[2]-vec2[2];
}

void multVecValor(double* vec1,double valor,double *res){
	res[0]= vec1[0]*valor;
	res[1]= vec1[1]*valor;
	res[2]= vec1[2]*valor;
}
	

void geraPlano(double *v1,double* v2,double*v3,int indice)
{
	double *aux1, *aux2;
	double* arrAux;

	aux1 = (double*)(malloc(3*sizeof(double)));
	aux2 = (double*)(malloc(3*sizeof(double)));
	arrAux = (double*)(malloc(3*sizeof(double)));

	subVectores(v1,v2,aux1);
	subVectores(v3,v2,aux2);
	
	prodVect(aux2,aux1,arrAux);

	matriznormais[indice][0]= arrAux[0];
	matriznormais[indice][1]= arrAux[1];
	matriznormais[indice][2]= arrAux[2];

	normaliza(matriznormais[indice]);	

	double * copy = v2;
	
	linhad[indice] = -(innerProduct(matriznormais[indice],copy));
}


//cams é o p
//camlooks é o l
//o u é fixo 0.0f,1.0f,0.0f
void setPlanes(double *p, double *l, double *u){
	double dir[3],Z[3];
	double *nc,*fc;
	double *X,*Y,*yAxis;

	X = (double*)malloc(3*sizeof(double));
	yAxis = (double*)malloc(3*sizeof(double));
	Y = (double*)malloc(3*sizeof(double));
	nc = (double*)malloc(3*sizeof(double));
	fc = (double*)malloc(3*sizeof(double));

	double ntr[3],ntl[3],nbr[3],nbl[3];
	double ftr[3],ftl[3],fbr[3],fbl[3];

	int nearDist = 2;
	int farDist = 1000000000;
	// compute the Z axis of camera
	// this axis points in the opposite direction from 
	// the looking direction
	subVectores(l,p,Z);
	normaliza(Z);

	// X axis of camera with given "up" vector and Z axis
	//X[0]= u[1]*Z[2] - u[2]*Z[1];
	//X[1]= u[2]*Z[0] - u[0]*Z[2];
	//X[2]= u[0]*Z[1] - u[1]*Z[0];

	//X = prodVect(u,zAxis);
	prodVect(u,Z,X);
	normaliza(X);
	
	// the real "up" vector is the cross product of Z and X
	//Y[0]= Z[1]*X[2] - Z[2]*X[1];
	//Y[1]= Z[2]*X[0] - Z[0]*X[2];
	//Y[2]= Z[0]*X[1] - Z[1]*X[0];
	prodVect(Z,X,Y);

	// compute the centers of the near and far planes
	double *aux,*aux1,*aux2;
	aux = (double*)(malloc(3*sizeof(double)));
	aux1 = (double*)(malloc(3*sizeof(double)));
	aux2 = (double*)(malloc(3*sizeof(double)));

	multVecValor(Z,nearDist,aux);
	somaVectores(p,aux,nc);
	
	multVecValor(Z,farDist,aux);
	somaVectores(p,aux,fc);

	// compute the 4 corners of the frustum on the near plane
	
	multVecValor(Y,nh/2,aux);
	multVecValor(X,nw/2,aux1);
	somaVectores(aux,aux1,aux2);
	somaVectores(nc,aux2,ntl);
	//ntl = somaVectores(nc,subVectores(multVecValor(X,nh),multVecValor(X,nw)));
	//ntl = nc + yAxis * nh - xAxis * nw;
	multVecValor(Y,nh/2,aux);
	multVecValor(X,nw/2,aux1);
	subVectores(aux,aux1,aux2);
	somaVectores(nc,aux2,ntr);
	//ntr = somaVectores(nc,somaVectores(multVecValor(X,nh),multVecValor(X,nw)));
	//ntr = nc + yAxis * nh + xAxis * nw;
	multVecValor(Y,nh/2,aux);
	multVecValor(X,nw/2,aux1);
	subVectores(aux,aux1,aux2);
	subVectores(nc,aux2,nbl);
	//nbl = subVectores(nc,subVectores(multVecValor(X,nh),multVecValor(X,nw)));
	//nbl = nc - yAxis * nh - xAxis * nw;
	multVecValor(Y,nh/2,aux);
	multVecValor(X,nw/2,aux1);
	somaVectores(aux,aux1,aux2);
	subVectores(nc,aux2,nbr);
	//nbr = subVectores(nc,somaVectores(multVecValor(X,nh),multVecValor(X,nw)));
	//nbr = nc - yAxis * nh + xAxis * nw;

	// compute the 4 corners of the frustum on the far plane
	multVecValor(Y,fh/2,aux);
	multVecValor(X,fw/2,aux1);
	somaVectores(aux,aux1,aux2);
	somaVectores(fc,aux2,ftl);
	
	multVecValor(Y,fh/2,aux);
	multVecValor(X,fw/2,aux1);
	subVectores(aux,aux1,aux2);
	somaVectores(fc,aux2,ftr);
	
	multVecValor(Y,fh/2,aux);
	multVecValor(X,fw/2,aux1);
	subVectores(aux,aux1,aux2);
	subVectores(fc,aux2,fbl);

	multVecValor(Y,fh/2,aux);
	multVecValor(X,fw/2,aux1);
	somaVectores(aux,aux1,aux2);
	subVectores(fc,aux2,fbr);

	//ftl = fc + multVecValor(yAxis,fh) - xAxis * fw;
	//ftl = somaVectores(fc,subVectores(multVecValor(yAxis,fh),multVecValor(X,fw)));
	//ftr = fc + yAxis * fh + xAxis * fw;
	//ftr = somaVectores(fc,somaVectores(multVecValor(yAxis,fh),multVecValor(X,fw)));
	//fbl = fc - yAxis * fh - xAxis * fw;
	//fbl = subVectores(fc,subVectores(multVecValor(yAxis,fh),multVecValor(X,fw)));
	//fbr = fc - yAxis * fh + xAxis * fw;
	//fbr = subVectores(fc,somaVectores(multVecValor(yAxis,fh),multVecValor(X,fw)));

	/*/far plane azul
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_QUADS);
	glVertex3d(fbl[0],fbl[1],fbl[2]);	
	glVertex3d(fbr[0],fbr[1],fbr[2]);
	glVertex3d(ftr[0],ftr[1],ftr[2]);
	glVertex3d(ftl[0],ftl[1],ftl[2]);
	glEnd();
	//near plane vermelho
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);
	glVertex3d(nbl[0],nbl[1],nbl[2]);	
	glVertex3d(nbr[0],nbr[1],nbr[2]);
	glVertex3d(ntr[0],ntr[1],ntr[2]);
	glVertex3d(ntl[0],ntl[1],ntl[2]);
	glEnd();
	//esfera a vermelho
	glPushMatrix();
	glTranslated(nbl[0],nbl[1],nbl[2]/10);
	glutSolidSphere(100,32,32);
	glPopMatrix();
	glPushMatrix();
	glTranslated(20000000,27000000,-999999999);
	glutSolidSphere(2000000000,32,32);
	glPopMatrix();
	//rectangulos dos lados a branco
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3d(nbl[0],nbl[1],nbl[2]/10);	
	glVertex3d(fbl[0],fbl[1],fbl[2]/10);
	glVertex3d(ftl[0],ftl[1],ftl[2]/10);
	glVertex3d(ntl[0],ntl[1],ntl[2]/10);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(nbr[0],nbr[1],nbr[2]/10);	
	glVertex3d(fbr[0],fbr[1],fbr[2]/10);
	glVertex3d(ftr[0],ftr[1],ftr[2]/10);
	glVertex3d(ntr[0],ntr[1],ntr[2]/10);
	glEnd();
*/

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
			{/*printf("OLHA: 0\n");*/return 0;}//OUTSIDE;
		else if (distance < radius)
			result =  2;//INTERSECT;
		
	}
	//printf("OLHA: %d\n",result);
	return(result);
}