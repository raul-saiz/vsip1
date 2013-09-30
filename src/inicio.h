#ifndef PINTARTOMATO_H_
#define PINTARTOMATO_H_


#define ORIG 0
#define DIM 256
#define INC 1.0


/* variables per al viewport de la imatge */


typedef unsigned char MonVoxels[DIM][DIM][64];

extern MonVoxels MonActual;
extern GLenum  doubleBuffer, mode;
extern int     PLA;
typedef struct punto{
	int x;
	int y;
}bubu;
typedef struct puntoflo{
	float x;
	float y;
}bubu2;

struct puntoflo perfil [520][620];
struct puntoflo paralel [20][420];
struct puntoflo meridian [20][420];
struct puntoflo puntets [4420][2];

int  FimaX;
int FimaY;

int MinX, MinY, MinZ, ResX, ResY, ResZ;
float IncX, IncY, IncZ;

void iniValors() ;
void llegirMonVoxels(char* nomFitxer);
void Init();
void Pintar( void);
void Tecles( unsigned char tecla, int x, int y) ;
void CanviFinestra(int width, int height);

#endif /* PINTARTOMATO_H_ */
