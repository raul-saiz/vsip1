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
#include "presion.h"

float geopuntos[35][25];

struct puntcont puntsini[35][25];

struct puntcont puntscontorn[1000];

float interx;
float intery;

int indicpunt=0;

float micolor[3];
int fil,col;
float maxvalor,minvalor;
struct puntoflo punttemporalX;
struct puntoflo punttemporalY;
int geo,geopint,isos;

void llegirEuropaGeo(char* nomFitxer,int multiplicador) {
	FILE  *f;
	int i, j;

	struct puntcont puntco;

	//int punts;
	char s[4]="    ";


	f=fopen(nomFitxer,"r");
	if (!f)    {
		printf("no puc obrir el fitxer %s\n", nomFitxer);
		exit(1);
	}

	i=0;
	fscanf(f,"%s",s); // leo el DSAA
	fscanf(f,"%d %d",&fil,&col); // leo filas y columnas
	fscanf(f,"%f %f",&punttemporalX.x,&punttemporalX.y);  // inicio del muestreo
	fscanf(f,"%f %f",&punttemporalY.x,&punttemporalY.y);  // final del muestreo
	fscanf(f,"%f %f",&minvalor,&maxvalor);  // valores MAX i MIN

	interx=punttemporalX.y/fil;
	intery=punttemporalY.y/col;

	for (i=0; i<fil; i++) {
		for (j=0; j<col; j++) {

			fscanf(f,"%f",&(geopuntos[i][j]));// leo los valores de geopresion

			/// guardo estructura para pintar contornos
			puntco.x=interx*i*multiplicador;
			puntco.y=intery*j*multiplicador;
			puntco.val=geopuntos[i][j];

			puntsini[i][j]=puntco;
			//k++;
		}
	}

	fclose(f);
	//fprintf(stdout,"Leidas %d geopresiones del fichero:%s \n",k, nomFitxer);
	//maxmeridians=k;
}

void transferencia (float propietat){

	micolor[2]=(propietat-minvalor)/(maxvalor-minvalor);

	micolor[0]=1-micolor[2];

	if ( (propietat-minvalor) <= (maxvalor-minvalor)/2 ){
		micolor[1]=(propietat-minvalor)/((maxvalor-minvalor)/2);
	}else{
		micolor[1]=2-((propietat-minvalor)/((maxvalor-minvalor)/2));//
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

void buscaPuntos (struct puntcont punt1,struct puntcont punt2,struct puntcont punt3,struct puntcont punt4, float valor,float increm ){

	int indictot=0,indic1=0,indic2=0,indic3=0,indic4=0;

	 if (punt1.val > valor-increm && punt1.val <= valor+increm)
	 {
		 indictot++;
		 indic1=1;
	 }

	 if (punt2.val > valor-increm && punt2.val <= valor+increm)
	 {
	 		 indictot++;
	 		 indic2=1;
	 	 }
	 if (punt3.val > valor-increm && punt3.val <= valor+increm)
	 {
	 		 indictot++;
	 		 indic3=1;
	 	 }
	 if (punt4.val > valor-increm && punt4.val <= valor+increm)
	 {
	 		 indictot++;
	 		 indic4=1;
	 	 }

	 switch(indictot){
					case 0:  // nada que hacer ....
						//fprintf(stdout,"caso 0\n");
						break;
					case 1: // añado el punto como si pasase por el
						fprintf(stdout,"caso 1\n");

						if (indic1>0)
							puntscontorn[indicpunt]=punt1;
						if (indic2>0)
							puntscontorn[indicpunt]=punt2;
						if (indic3>0)
							puntscontorn[indicpunt]=punt3;
						if (indic4>0)
							puntscontorn[indicpunt]=punt4;
						indicpunt++;
						break;
					case 2: // añado el  punto medio
						fprintf(stdout,"caso 2\n");

//						if (indic1 && indic2) // punto medio del lado
//							puntscontorn[i][j]=punt1;
//						if (indic2 && indic3)// punto medio del lado
//							puntscontorn[i][j]=punt1;
//						if (indic3 && indic4)// punto medio del lado
//							puntscontorn[i][j]=punt1;
//						if (indic1 && indic4)// punto medio del lado
//							puntscontorn[i][j]=punt1;
//						if (indic1 && indic3) // miro diagonal, punto medio
//							puntscontorn[i][j]=punt1;
//						if (indic2 && indic4) // miro diagonal, punto medio
//							puntscontorn[i][j]=punt1;
						indicpunt++;
						break;
					case 3:  // añado los dos puntos medios
						fprintf(stdout,"caso 3\n");

//						if (indic1 && indic2 && indic3)
//						{
//							puntscontorn[i][j]=punt1;// punto medio del lado
//							puntscontorn[i][j]=punt1;
//						}
//
//						if (indic4 && indic2 && indic3) // punto medio del lado
//						{
//							puntscontorn[i][j]=punt1;// punto medio del lado
//							puntscontorn[i][j]=punt1;
//						}
//						if (indic1 && indic4 && indic3) // punto medio del lado
//						{
//							puntscontorn[i][j]=punt1;// punto medio del lado
//							puntscontorn[i][j]=punt1;
//						}
//						if (indic1 && indic4 && indic2) // punto medio del lado
//						{
//							puntscontorn[i][j]=punt1;// punto medio del lado
//							puntscontorn[i][j]=punt1;
//						}
						indicpunt++;
						break;
					case 4:  // subdivido en 4 partes y vulevo a relizar este case
						fprintf(stdout,"caso 4\n");

						//buscapuntos();
						break;
	 }

}

void PintarIsoPressio (int miintervalo){

	// definir las presiones que hay que buscar para hacer un for de ellas en los valores
	// para cada valor recorrer las estructuras pintando al final

	// for ( diferentes valores a buscar )     ENGLOBA LOS DOS FORS , BUSQUEDA Y PINTAR.

		int i=0,j=0;
		for ( i=0;i<fil;i++){
			for ( j=0;j<col;j++){
				buscaPuntos (puntsini[i][j],puntsini[i][j+1],puntsini[i+1][j+1],puntsini[i+1][j],310,miintervalo);

			}
		}

		// for para pintar lo hallado en los for anteriores



		// limpio estructura de puntos pintados
		indicpunt=0;

}

void PintarPressio(){

	if (geopint==1)
	PintarGeoPressio(10);
	if (isos==1)
	PintarIsoPressio(5);

	glFlush();

}
