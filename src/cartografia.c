/*
 * cartografia.c
 *
 *  Created on: 30/09/2013
 *      Author: lulz
 */
#include <stdio.h>
#include <math.h>
#include "GL/glut.h"
#include "inicio.h"

void llegirEuropaPerfil(char* nomFitxer) {
	FILE  *f;
	int i,k;

	int punts;
	struct puntoflo punttemp;

	f=fopen(nomFitxer,"r");
	if (!f)    {
		printf("no puc obrir el fitxer %s\n", nomFitxer);
		exit(1);
	}
	i=0;k=0;
	while (! feof(f)){

		fscanf(f,"%d ",&punts);

		for (i=0; i<punts; i++) {

			fscanf(f,"%f %f",&(punttemp.x),&(punttemp.y));
			//fprintf(stdout,"%f",punttemp.x);
			perfil[k][i]=punttemp;

		}
		i=0;
		k++;
	}
	fclose(f);
	fprintf(stdout,"Leidos %d perfiles\n",k);

}

void llegirEuropaParalel(char* nomFitxer) {
	FILE  *f;
	int i, k;

	int punts;
	struct puntoflo punttemp;

	f=fopen(nomFitxer,"r");
	if (!f)    {
		printf("no puc obrir el fitxer %s\n", nomFitxer);
		exit(1);
	}
	i=0;k=0;
	while (! feof(f)){
		fscanf(f,"%d ",&punts);

				for (i=0; i<punts; i++) {

					fscanf(f,"%f %f",&(punttemp.x),&(punttemp.y));
					//fprintf(stdout,"%f",punttemp.x);
					paralel[k][i]=punttemp;

				}
				i=0;
				k++;
	}
	fclose(f);
	fprintf(stdout,"Leidos %d paralelos\n",k);
}

void llegirEuropaMeridia(char* nomFitxer) {
	FILE  *f;
	int i, k;
	int punts;
	struct puntoflo punttemp;
	f=fopen(nomFitxer,"r");
	if (!f)    {
		printf("no puc obrir el fitxer %s\n", nomFitxer);
		exit(1);
	}
	i=0;k=0;
	while (! feof(f)){
		fscanf(f,"%d ",&punts);

				for (i=0; i<punts; i++) {

					fscanf(f,"%f %f",&(punttemp.x),&(punttemp.y));
					//fprintf(stdout,"%f",punttemp.x);
					meridian[k][i]=punttemp;

				}
				i=0;
				k++;
	}
	fclose(f);
	fprintf(stdout,"Leidos %d meridianos \n",k);
}

void llegirEuropaPuntets (char* nomFitxer) {
	FILE  *f;
	int i, k;
	int punts;
	struct puntoflo punttemp;

	f=fopen(nomFitxer,"r");
	if (!f)    {
		printf("no puc obrir el fitxer %s\n", nomFitxer);
		exit(1);
	}
	i=0;k=0;
	while (! feof(f)){
		fscanf(f,"%d ",&punts);

				for (i=0; i<punts; i++) {

					fscanf(f,"%f %f",&(punttemp.x),&(punttemp.y));
					//fprintf(stdout,"%f",punttemp.x);
					puntets[k][i]=punttemp;

				}
				i=0;
				k++;
	}
	fclose(f);
	fprintf(stdout,"Leidos %d puntets",k);
}
