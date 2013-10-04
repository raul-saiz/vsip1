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
int fil,col;
float maxvalor,minvalor;
struct puntoflo punttemporalX;
struct puntoflo punttemporalY;
int geo,geopint;

void llegirEuropaGeo(char* nomFitxer) {
	FILE  *f;
	int i, j,k;


	//int punts;
	char s[4]="    ";


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

// color rojo funcion y=x
	//micolor[0]=sin(propietat);
micolor[0]=((maxvalor-minvalor)-(propietat-minvalor))/maxvalor;
// color green funcion y=1-x
micolor[1]=1-micolor[0];
// color blue funcion y=x^2  ---
if ( (((maxvalor-minvalor)-(propietat-minvalor))/maxvalor) <= 0.5 ){
	micolor[2]=(1-micolor[0])*2;//
}else{
	micolor[2]=micolor[0]/2;//
}


}



void PintarGeoPressio (float multiplicador){

	// calculo el desplazamiento de cada valor * fila * col
	// FimaX/maxX incremento

	float desplax,desplay;

	desplax=punttemporalX.y/fil*multiplicador;
	desplay=punttemporalY.y/col*multiplicador;

	int i=0,j=0;
		for ( i=0;i<fil;i++){
			for ( j=0;j<col;j++){


				//fprintf(stdout,"%.2f -- %.2f %.2f %.2f | ",geopuntos[i][j],micolor[0],micolor[1],micolor[2]);

				glBegin(GL_POLYGON);

				transferencia(geopuntos[i][j]);
				glColor3f(micolor[0],micolor[1],micolor[2]);
				glVertex3f(i*desplax,j*desplay,0.0);

				transferencia(geopuntos[i+1][j]);
				glColor3f(micolor[0],micolor[1],micolor[2]);
				glVertex3f((i+1)*desplax,j*desplay,0.0);

				transferencia(geopuntos[i+1][j+1]);
				glColor3f(micolor[0],micolor[1],micolor[2]);
				glVertex3f((i+1)*desplax,(j+1)*desplay,0.0);

				transferencia(geopuntos[i][j+1]);
				glColor3f(micolor[0],micolor[1],micolor[2]);
				glVertex3f(i*desplax,(j+1)*desplay,0.0);

				glEnd();

			}
			//fprintf(stdout,"\n");

		}
}
