#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include <GL/glut.h>


//Distancia ao sol		KM(x1000)
#define distSolMercurio	58000
#define distSolVenus	108000
#define distSolTerra	149600
#define distSolMarte	227940
#define distSolJupiter	778330
#define distSolSaturno	1426980
#define distSolUrano	2870990
#define distSolNeptuno	4497070
#define distTerraLua	384.403


//Raios Planetas		KM(x1000)
#define raioSol			695.5
#define raioMercurio	2.4395
#define raioVenus		6.052
#define raioTerra		6.371
#define raioMarte		3.396
#define raioJupiter		71.492
#define raioSaturno		60.268
#define raioUrano		25.559 
#define raioNeptuno		24.764

//Distancia planeta<->luas		KM(x1000)
#define distTerraLua			384.403
	//Marte
#define distMarteFobos			9.337
#define distMarteDeimos			23.460
	//Jupiter
#define distJupiterIo			422.000
#define distJupiterEuropa		670.000
#define distJupiterGanymede		1070
#define distJupiterCalisto		1880
	//Saturno
#define distSaturnoRhea			527
#define distSaturnoTitan		1222
#define distSaturnoIapetus		3560

//Raios Luas			KM(x1000)
#define raioLua			1.73710
	//Marte
#define raioFobos		0.0111
#define raioDeimos		0.0062
	//Jupiter
#define raioIo			1.8213
#define raioEuropa		1.569
#define raioGanymede	2.6341
#define raioCalisto		2.4103
	//Saturno
#define raioRhea		0.764
#define raioTitan		2.5762
#define raioIapetus		0.7356

//velocidade translação - dias
#define velMercurio		87.969
#define velVenus		224.701
#define velTerra		365.5
#define velMarte		687
#define velJupiter		4333
#define velSaturno		10759
#define velUrano		30685
#define velNeptuno		60190
#define velLua			27.321582

/*
//velocidade translação 1 / ( velPlaneta / velTerra )
#define velMercurio		4.1549
#define velVenus		1.6266
//#define velTerra		1
#define velTerra		365.5
#define velMarte		0.532
//#define velJupiter		0.08425
#define velJupiter		4333
#define velSaturno		0.03397
#define velUrano		0.01191
#define velNeptuno		0.00607
#define velLua			13.537*/

//velocidade rotação - dias
#define velRSol			25.38
#define velRMercurio	58.646
#define velRVenus		243.0185
#define velRTerra		1
#define velRMarte		1.025957
#define velRJupiter		0.413541667
#define velRSaturno		0.440416667
#define velRUrano		-0.71833
#define velRNeptuno		0.6713

//velocidade rotação Luas - dias
#define velRLua			27.321582
	//Marte
#define velRFobos		1.90
#define velRDeimos		2.20
	//Júpiter
#define velRIo			1.77
#define velREuropa		3.55
#define velRGanimedes	7.16
#define velRCalisto		16.69
	//Saturno
#define velRMimas		0.94
#define velREncelado	1.37
#define velRTetis		1.89
#define velRDione		2.73
#define velRReia		4.52
#define velRTita		15.95
#define velRJapeto		79.32
	//Urano
#define velRMiranda		1.41
#define velRAriel		2.52
#define velRUmbriel		4.41
#define velRTitania		8.71
#define velROberon		13.46
	//Neptuno
#define velRProteu		1.12
#define velRTritao		5.88


//inclinaçao das orbitas
#define orbitalTiltMercurio		7.004
#define orbitalTiltVenus		3.394
#define orbitalTiltTerra		0
#define orbitalTiltLua			23.25 //NOT SURE
#define orbitalTiltMarte		1.850
#define orbitalTiltJupiter		1.308
#define orbitalTiltSaturno		2.488
#define orbitalTiltUrano		0.774
#define orbitalTiltNeptuno		1.774

//inclinaçao dos eixos
#define axisTiltSol				7.25
#define axisTiltMercurio		-0.1
#define axisTiltVenus			177.3
#define axisTiltTerra			23.5
#define axisTiltLua				1.5424	
#define axisTiltMarte			25.19
#define axisTiltJupiter			3.12
#define axisTiltSaturno			26.73
#define axisTiltUrano			97.86
#define axisTiltNeptuno			29.6

#define PI 3.1415926535897

#define MAX_STARS 			10000
#define STAR_RADIUS 		2000000


extern GLfloat rotDemios;

extern GLfloat angMercurio;
extern GLfloat angVenus;
extern GLfloat angTerra;
extern GLfloat angMarte;
extern GLfloat angJupiter;
extern GLfloat angSaturno;
extern GLfloat angUrano;
extern GLfloat angNeptuno;
extern GLfloat angLua;

extern GLfloat angFobos;
extern GLfloat angDeimos;
extern GLfloat angIO;
extern GLfloat angEuropa;
extern GLfloat angGanimedes;
extern GLfloat angCalisto;

extern GLfloat angRotSol;
extern GLfloat angRotMercurio;
extern GLfloat angRotVenus;
extern GLfloat angRotTerra;
extern GLfloat angRotMarte;
extern GLfloat angRotJupiter;
extern GLfloat angRotSaturno;
extern GLfloat angRotUrano;
extern GLfloat angRotNeptuno;
extern GLfloat angRotLua;

extern GLfloat angRotFobos;
extern GLfloat angRotDeimos;
extern GLfloat angRotIO;
extern GLfloat angRotEuropa;
extern GLfloat angRotGanimedes;
extern GLfloat angRotCalisto;
extern GLfloat angRotRhea;
extern GLfloat angRotTitan;
extern GLfloat angRotIapetus;

extern float scale;
extern bool orbitas;
extern bool drawCintura;
extern float distFactor;
extern float timeFactor;

//vectores com a posiçao dos planetas
extern double posicoes[19][3];
extern double raios[19];

void planetas();
void createcircle (int k, int r, int h);
void draw_orbita(float raio, float angleX,float angleY,float angleZ);
void rotacao(GLfloat rotacao,float tilt);
void desenharCintura();
void desenharEstrelas();
void desenhaAnel();
