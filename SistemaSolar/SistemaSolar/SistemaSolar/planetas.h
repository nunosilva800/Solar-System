#include <GL/glut.h>



#define distSolMercurio = 57910;//milhares de km
#define distSolVenus = 108200;//milhares de km
#define distSolTerra = 149597.870;//milhares de km
#define distSolMarte = 227940;//milhares de km
#define distSolJupiter = 778330;//milhares de km
#define distSolSaturno = 1426980;//milhares de km
#define distSolUrano = 2870990;//milhares de km
#define distSolNeptuno = 4497070;//milhares de km
#define distTerraLua = 384.403;//milhares de km

/*
double raioSol=
double raioMercurio=
double raioVenus=
double raioTerra=
double raioMarte=
double raioJupiter=
double raioSaturno=
double raioUrano=
double raioNeptuno=
double raioPlutao=
double raioLua=
*/

void planetas();
void createcircle (int k, int r, int h);
void draw_Orbita(float raio, float angle);