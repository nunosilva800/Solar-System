#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include <GL/glut.h>

//diametro em KM
#define diametroTerra 12742

//medida em Terras		 milhoes
#define distSolMercurio	58000000	/ diametroTerra
#define distSolVenus	108000000	/ diametroTerra
#define distSolTerra	149600000	/ diametroTerra
#define distSolMarte	227940000	/ diametroTerra
#define distSolJupiter	778330000	/ diametroTerra
#define distSolSaturno	1426980000	/ diametroTerra
#define distSolUrano	2870990000	/ diametroTerra
#define distSolNeptuno	4497070000	/ diametroTerra
#define distTerraLua	384403		/ diametroTerra

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
#define orbitalTiltMercurio		7.004
#define orbitalTiltVenus		177.3
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
#define axisTiltVenus			3.394
#define axisTiltTerra			23.5
#define axisTiltLua				1.5424	
#define axisTiltMarte			25.19
#define axisTiltJupiter			3.12
#define axisTiltSaturno			26.73
#define axisTiltUrano			97.86
#define axisTiltNeptuno			29.6

extern float scale;
extern bool orbitas;
extern float distFactor;
extern float timeFactor;

void planetas();
void createcircle (int k, int r, int h);
void draw_Orbita(float raio, float angleX,float angleY,float angleZ);
void rotacao(GLfloat rotacao,float tilt);
void desenharCintura();
