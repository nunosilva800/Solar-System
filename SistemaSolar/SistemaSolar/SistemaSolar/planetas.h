#include <GL/glut.h>


/*
#define distSolMercurio = 57910;//milhares de km
#define distSolVenus = 108200;//milhares de km
#define distSolTerra = 149597.870;//milhares de km
#define distSolMarte = 227940;//milhares de km
#define distSolJupiter = 778330;//milhares de km
#define distSolSaturno = 1426980;//milhares de km
#define distSolUrano = 2870990;//milhares de km
#define distSolNeptuno = 4497070;//milhares de km
#define distTerraLua = 384.403;//milhares de km
*/
#define raioSol			696
#define raioMercurio	1.2195
#define raioVenus		3.0259
#define raioTerra		3.1855
#define raioMarte		(6.780/2)
#define raioJupiter		139.822/2
#define raioSaturno		116.464/2
#define raioUrano		50.724/2
#define raioNeptuno		49.244/2
#define raioLua			3.4742/2


extern float scale;

void planetas();
void createcircle (int k, int r, int h);
void draw_Orbita(float raio, float angle);
