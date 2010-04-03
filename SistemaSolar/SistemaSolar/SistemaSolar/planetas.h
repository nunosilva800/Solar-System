#include <GL/glut.h>


//medida em Terras * 10
#define distSolMercurio	58910	 / 127.42
#define distSolVenus	108200	 / 127.42
#define distSolTerra	149597.870 / 127.42
#define distSolMarte	227940	 / 127.42
#define distSolJupiter	778330	 / 127.42
#define distSolSaturno	1426980	 / 127.42
#define distSolUrano	2870990	 / 127.42
#define distSolNeptuno	4497070	 / 127.42
#define distTerraLua	384.403	 / 127.42

//medida em Terras - planetas * 10
#define raioSol			109
#define raioMercurio	0.3829 * 10
#define raioVenus		0.9499 * 10
#define raioTerra		1 * 10
#define raioMarte		0.533 * 10
#define raioJupiter		11.209 * 10
#define raioSaturno		9.4492 * 10
#define raioUrano		4.007 * 10
#define raioNeptuno		3.883 * 10
#define raioLua			0.273 * 10

//km/s
#define velMercurio		47.87
#define velVenus		35.02
#define velTerra		29.783
#define velMarte		24.077
#define velJupiter		13.07
#define velSaturno		9.69
#define velUrano		6.81
#define velNeptuno		5.43
#define velLua			1.022


extern float scale;
extern bool orbitas;

void planetas();
void createcircle (int k, int r, int h);
void draw_Orbita(float raio, float angleX,float angleY,float angleZ);
void rotacao(GLfloat rotacao,float tilt);

#define orbitalTiltJupiter		1.308

#define axisTiltJupiter		3.12