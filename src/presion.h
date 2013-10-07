/*
 * presion.h
 *
 *  Created on: 01/10/2013
 *      Author: lulz
 */

#ifndef PRESION_H_
#define PRESION_H_

extern int geo,geopint,isos;

typedef struct puntcont{
	int x;
	int y;
	float val;
};



void llegirEuropaGeo(char* nomFitxer);

//void PintarGeoPressio(float multiplicador);

void PintarPressio();

#endif /* PRESION_H_ */
