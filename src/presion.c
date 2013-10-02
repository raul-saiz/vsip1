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

float micolor[3];

float maxvalor,minvalor;

int geo,geopint;

void llegirEuropaGeo(char* nomFitxer) {
	FILE  *f;
	int i, j,k;
	int fil,col;

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

void transferencia (float propietat){

	/// aqui asigno color per pintar
	/// calcular con max , min    de los valores del geopressio
//float divisor=3;
float pondera;

pondera= (maxvalor-minvalor)/2;

if (propietat < pondera ){
	if(pondera/2 < propietat){
		micolor[0]=0.3;
		micolor[1]=1.0;
		micolor[2]=0.0;
	}else{
		micolor[0]=1.0;
		micolor[1]=0.6;
		micolor[2]=0.0;
	}
}else{
	if(pondera*3/2 < propietat){
		micolor[0]=0.0;
		micolor[1]=1.0;
		micolor[2]=0.3;
	}else{
		micolor[0]=0.0;
		micolor[1]=0.6;
		micolor[2]=1.0;
	}
}

}



void PintarGeoPressio (float multiplicador){

	// calculo el desplazamiento de cada valor * fila * col
	float desplax,desplay;
	// FimaX/maxX incremento
	desplax=FimaX/35;
	desplay=FimaY/25;

	int i=0,j=0;
		for ( i=0;i<35;i++){
			for ( j=0;j<25;j++){
				glBegin(GL_POLYGON);
				transferencia(geopuntos[i][j]);
				glColor3f(micolor[0],micolor[1],micolor[2]);
				glVertex3f(i*desplax,j*desplay,0.0);
				glVertex3f((i+1)*desplax,j*desplay,0.0);
				glVertex3f((i+1)*desplax,(j+1)*desplay,0.0);
				glVertex3f(i*desplax,(j+1)*desplay,0.0);
				glEnd();

			}
		}
}
