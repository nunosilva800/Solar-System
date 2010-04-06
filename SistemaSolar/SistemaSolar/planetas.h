#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include <GL/glut.h>


//medida em Terras
#define distSolMercurio	58910	 / 127.42
#define distSolVenus	108200	 / 127.42
#define distSolTerra	149597.870 / 127.42
#define distSolMarte	227940	 / 127.42 
#define distSolJupiter	778330	 / 127.42
#define distSolSaturno	1426980	 / 127.42
#define distSolUrano	2870990	 / 127.42
#define distSolNeptuno	4497070	 / 127.42
#define distTerraLua	384.403	 / 127.42

//medida em Terras (raio da terra)
#define raioSol			109
#define raioMercurio	0.3829
#define raioVenus		0.9499
#define raioTerra		1 
#define raioMarte		0.533
#define raioJupiter		11.209
#define raioSaturno		9.4492
#define raioUrano		4.007 
#define raioNeptuno		3.883 
#define raioLua			0.273 

//velocidade translação - km/s
#define velMercurio		47.87
#define velVenus		35.02
#define velTerra		29.783
#define velMarte		24.077
#define velJupiter		13.07
#define velSaturno		9.69
#define velUrano		6.81
#define velNeptuno		5.43
#define velLua			1.022

//velocidade rotação - dias
#define velRSol			25.38
#define velRMercurio	58.646
#define velRVenus		-243.0185
#define velRTerra		1
#define velRMarte		1.025957
#define velRJupiter		0.413541667
#define velRSaturno		0.440416667
#define velRUrano		-0.71833
#define velRNeptuno		0.6713
#define velRLua			27.321582

//inclinaçao das orbitas
#define orbitalTiltMercurio		20
#define orbitalTiltVenus		20
#define orbitalTiltTerra		20
#define orbitalTiltLua			20
#define orbitalTiltMarte		20
#define orbitalTiltJupiter		1.308
#define orbitalTiltSaturno		20
#define orbitalTiltUrano		20
#define orbitalTiltNeptuno		20

//inclinaçao dos eixos
#define axisTiltMercurio		20
#define axisTiltVenus		20
#define axisTiltTerra		20
#define axisTiltLua			20	
#define axisTiltMarte		20
#define axisTiltJupiter		3.12
#define axisTiltSaturno		20
#define axisTiltUrano		20
#define axisTiltNeptuno		20





extern float scale;
extern bool orbitas;
extern float distFactor;
extern float timeFactor;

void planetas();
void createcircle (int k, int r, int h);
void draw_Orbita(float raio, float angleX,float angleY,float angleZ);
void rotacao(GLfloat rotacao,float tilt);
void desenharCintura();
