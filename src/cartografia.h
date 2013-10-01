/*
 * cartografia.h
 *
 *  Created on: 30/09/2013
 *      Author: lulz
 */

#ifndef CARTOGRAFIA_H_
#define CARTOGRAFIA_H_


#define ORIG 0
#define DIM 256
#define INC 1.0

extern GLenum  doubleBuffer, mode;
extern int FimaX,FimaY;
extern int meri,para,carto;

//extern int     PLA;
typedef struct punto{
	int x;
	int y;
}bubu;
typedef struct puntoflo{
	float x;
	float y;
}bubu2;

struct puntoflo perfil [520][620];
struct puntoflo paralel [20][1820];
struct puntoflo meridian [20][1820];
struct puntoflo puntets [4420][2];

void iniValors();
void Init();
void CanviTamany(int width, int height);
void Tecles( unsigned char tecla, int x, int y) ;

void llegirEuropaPerfil(char* nomFitxer);
void llegirEuropaParalel(char* nomFitxer);
void llegirEuropaMeridia(char* nomFitxer);
void llegirEuropaPuntets(char* nomFitxer);

extern int maxperfils,maxparalels,maxmeridians,maxpuntets;

void PintarCartografia ();

void pintarEuropaPerfil(float multiplicador);
void pintarEuropaMeridia(float multiplicador);
void pintarEuropaParalel(float multiplicador);
void pintarEuropaPuntets(float multiplicador);

#endif /* CARTOGRAFIA_H_ */

