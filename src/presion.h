/*
 * presion.h
 *
 *  Created on: 01/10/2013
 *      Author: lulz
 */

#ifndef PRESION_H_
#define PRESION_H_

extern int geo,geopint,isos,intervalo;

typedef struct puntcont{
	float x;
	float y;
	float val;
}kuku;



void llegirEuropaGeo(char* nomFitxer,int multiplicador);

//void PintarGeoPressio(float multiplicador);

void PintarPressio();

#endif /* PRESION_H_ */
