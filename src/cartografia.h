/*
 * cartografia.h
 *
 *  Created on: 30/09/2013
 *      Author: lulz
 */

#ifndef CARTOGRAFIA_H_
#define CARTOGRAFIA_H_

extern GLenum  doubleBuffer, mode;
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


void Init();
void CanviTamany(int width, int height);

void llegirEuropaPerfil(char* nomFitxer);
void llegirEuropaParalel(char* nomFitxer);
void llegirEuropaMeridia(char* nomFitxer);
void llegirEuropaPuntets(char* nomFitxer);

extern int maxperfils,maxparalels,maxmeridians,maxpuntets;

void PintarCartografia ();

void pintarEuropaPerfil(int multiplicador);
void pintarEuropaMeridia(int multiplicador);
void pintarEuropaParalel(int multiplicador);
void pintarEuropaPuntets(int multiplicador);

#endif /* CARTOGRAFIA_H_ */

