/*
 * presion.c
 *
 *  Created on: 01/10/2013
 *      Author: lulz
 */

#include <stdio.h>
#include <math.h>
#include "GL/glut.h"
#include "cartografia.h"

float geopuntos[35][25];

int geo,geopint;

void llegirEuropaGeo(char* nomFitxer) {
	FILE  *f;
	int i, j,k;
	int fil,col;
	float maxvalor,minvalor;
	//int punts;
	char s[4]="    ";
	struct puntoflo punttemporalX;
	struct puntoflo punttemporalY;

	f=fopen(nomFitxer,"r");
	if (!f)    {
		printf("no puc obrir el fitxer %s\n", nomFitxer);
		exit(1);
	}

	i=0;k=0;
	fscanf(f,"%s",s); // leo el DSAA
	fscanf(f,"%d %d",&fil,&col); // leo filas y columnas
	fscanf(f,"%f %f",&punttemporalX.x,&punttemporalX.y);  // inicio del muestreo
	fscanf(f,"%f %f",&punttemporalY.x,&punttemporalY.y);  // final del muestreo
	fscanf(f,"%f %f",&minvalor,&maxvalor);  // valores MAX i MIN
	for (i=0; i<fil; i++) {
		for (j=0; j<col; j++) {
			fscanf(f,"%f",&(geopuntos[i][j])); // leo los valores de geopresion
			k++;
		}
	}

	fclose(f);
	fprintf(stdout,"Leidas %d geopresiones del fichero:%s \n",k, nomFitxer);
	//maxmeridians=k;
}

void PintarGeoPressio (float multiplicador){

	// calculo el desplazamiento de cada valor * fila * col
	float desplax,desplay;
	// FimaX/maxX incremento
	desplax=0.0;
	desplay=0.0;

	int i=0,j=0;
		for ( i=0;i<maxmeridians;i++){
		//	glBegin(GL_LINE_STRIP);
		//	glColor3f(0.4,0.4,0.4);
			for( j=0;meridian[i][j+1].x!=0;j++){
			//	glVertex3f((float)meridian[i][j].x*multiplicador,(float)meridian[i][j].y*multiplicador,0.0);
		//		glVertex3f((float)meridian[i][j+1].x*multiplicador,(float)meridian[i][j+1].y*multiplicador,0.0);
			}
		//	glEnd();
		}
	//	glFlush();
}
