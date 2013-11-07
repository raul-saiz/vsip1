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

float geopuntos[25][35];

struct puntcont puntsini[25][35];

struct puntcont puntscontorn[150000];

float interx;
float intery;


int max_profundidad = 4 ;

int indicpunt=0;

float micolor[3];
int fily,colx;
float maxvalor,minvalor;
struct puntoflo punttemporalX;
struct puntoflo punttemporalY;
int geo,geopint,isos,intervalo;

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
	fscanf(f,"%d %d",&colx,&fily); // leo filas y columnas
	fscanf(f,"%f %f",&punttemporalX.x,&punttemporalX.y);  // inicio del muestreo
	fscanf(f,"%f %f",&punttemporalY.x,&punttemporalY.y);  // final del muestreo
	fscanf(f,"%f %f",&minvalor,&maxvalor);  // valores MAX i MIN

	interx=(punttemporalX.y-punttemporalX.x)/colx*multiplicador;
	intery=(punttemporalY.y-punttemporalY.x)/fily*multiplicador;

	for (i=0; i<fily; i++) {
		for (j=0; j<colx; j++) {

			fscanf(f,"%f ",&(geopuntos[j][i]));// leo los valores de geopresion
			//printf("%f \n",geopuntos[i][j]);
			/// guardo estructura para pintar contornos
			puntco.x=interx*j;
			puntco.y=intery*i;
			puntco.val=geopuntos[j][i];

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
		micolor[1]=(2-((propietat-minvalor)/((maxvalor-minvalor)/2)));//
	}
//printf("transf: %f, %f, %f : % f %f --- %f \n",micolor[0],micolor[1],micolor[2],minvalor,maxvalor ,propietat);
}

void PintarGeoPressio (float multiplicador){

	// calculo el desplazamiento de cada valor * fila * col
	// FimaX/maxX incremento

	float desplax,desplay;

	desplax=((punttemporalX.y-punttemporalX.x)/colx)*multiplicador;
	desplay=((punttemporalY.y-punttemporalY.x)/fily)*multiplicador;
	fprintf(stdout,"intervalo isobaras : %i\n",intervalo);
	int i=0,j=0;
	for ( i=0;i<fily;i++){
		for ( j=0;j<colx;j++){

			//fprintf(stdout,"%.2f -- %.2f %.2f %.2f | ",geopuntos[i][j],micolor[0],micolor[1],micolor[2]);

			glBegin(GL_POLYGON);

			transferencia(geopuntos[j][i]);
			glColor3f(micolor[0],micolor[1],micolor[2]);
			glVertex3f(j*desplax,i*desplay,0.0);

			transferencia(geopuntos[j][i+1]);
			glColor3f(micolor[0],micolor[1],micolor[2]);
			glVertex3f((j)*desplax,(i+1)*desplay,0.0);

			transferencia(geopuntos[j+1][i+1]);
			glColor3f(micolor[0],micolor[1],micolor[2]);
			glVertex3f((j+1)*desplax,(i+1)*desplay,0.0);

			transferencia(geopuntos[j+1][i]);
			glColor3f(micolor[0],micolor[1],micolor[2]);
			glVertex3f((j+1)*desplax,(i)*desplay,0.0);

			glEnd();

		}
		//fprintf(stdout,"\n");

	}

	glFlush();
}

void buscaPuntos (struct puntcont punt1,struct puntcont punt2,struct puntcont punt3,struct puntcont punt4, float valor ,int profundidad ){

	int indictot=0,indic1=0,indic2=0,indic3=0,indic4=0;
	struct puntcont temp1;
	struct puntcont temp2;
	struct puntcont temp3;
	float discri=0.00;


	indictot=0;indic1=0;indic2=0;indic3=0;indic4=0;

	//if (punt1.val >= valor-discri+intervalo && punt1.val <= valor+discri+intervalo )  //punt1.val > valor-increm && punt1.val <= valor+increm
	if (punt1.val <= valor+discri+intervalo && punt1.val > 1)
	{

		indictot++;
		indic1=1;
	}

	//if (punt2.val >= valor-discri+intervalo && punt2.val <= valor+discri+intervalo )
	if (punt2.val <= valor+discri+intervalo && punt2.val > 1)
	{
		indictot++;
		indic2=1;
	}
	//if (punt3.val >= valor-discri+intervalo && punt3.val <= valor+discri+intervalo )
	if (punt3.val <= valor+discri+intervalo && punt3.val > 1)
	{
		indictot++;
		indic3=1;
	}
	//if (punt4.val >= valor-discri+intervalo && punt4.val <= valor+discri+intervalo )
	if (punt4.val <= valor+discri+intervalo && punt4.val > 1)
	{
		indictot++;
		indic4=1;
	}

	switch(indictot){
	case 0:  // nada que hacer ....
		//fprintf(stdout,"caso 0\n");
		break;
	case 1: // añado el punto como si pasase por el
		//fprintf(stdout,"caso 1\n");
		if ( profundidad < max_profundidad){
											// SENTIDO ANTIHORARIO , EMPIEZO DEL (0,0)
											temp1.x=(punt1.x+punt2.x)/2;
											temp1.y=punt1.y;//(punt1.y+punt2.y)/2;    // medio entre 1 y 2    --- A
											temp1.val=(punt1.val+punt2.val)/2;

											temp2.x=(punt1.x+punt2.x)/2;
											temp2.y=(punt1.y+punt4.y)/2;		//  medio diagonal   ---  B
											temp2.val=(punt1.val+punt3.val)/2;

											temp3.x=punt1.x;//(punt1.x+punt2.x)/2;
											temp3.y=(punt1.y+punt4.y)/2; 			//  medio entre 1 y 4   --- C
											temp3.val=(punt1.val+punt4.val)/2;

											buscaPuntos (punt1,temp1,temp2,temp3,valor,profundidad+1);

											////  SEGUNDO CUADRADO
											temp1.x=(punt1.x+punt2.x)/2;
											temp1.y=punt1.y;//(punt1.y+punt2.y)/2;		// ***  A  1y2
											temp1.val=(punt1.val+punt2.val)/2;

											temp2.x=(punt1.x+punt2.x)/2;
											temp2.y=(punt1.y+punt4.y)/2;				//  *** B  diag
											temp2.val=(punt1.val+punt3.val)/2;

											temp3.x=punt2.x;//(punt1.x+punt2.x)/2;
											temp3.y=(punt2.y+punt3.y)/2;				// medio entre 2 y 3   --- D
											temp3.val=(punt2.val+punt3.val)/2;

											buscaPuntos (temp1,punt2,temp3,temp2,valor,profundidad+1);

											////  TERCER CUADRADO
											temp1.x=(punt4.x+punt3.x)/2;
											temp1.y=punt3.y;//(punt1.y+punt2.y)/2;    //  medio entre 3y 4  --  E
											temp1.val=(punt4.val+punt3.val)/2;

											temp2.x=(punt1.x+punt2.x)/2;
											temp2.y=(punt1.y+punt4.y)/2;				//  *** B  diag
											temp2.val=(punt1.val+punt3.val)/2;

											temp3.x=punt2.x;//(punt1.x+punt2.x)/2;
											temp3.y=(punt2.y+punt3.y)/2;					//   *** D   2y3
											temp3.val=(punt2.val+punt3.val)/2;

											buscaPuntos (temp2,temp3,punt3,temp1,valor,profundidad+1);


											/// CUARTO CUADRADO
											temp1.x=(punt4.x+punt3.x)/2;
											temp1.y=punt3.y;//(punt1.y+punt2.y)/2;			// E
											temp1.val=(punt4.val+punt3.val)/2;

											temp2.x=(punt1.x+punt2.x)/2;
											temp2.y=(punt1.y+punt4.y)/2;				//  diag
											temp2.val=(punt1.val+punt3.val)/2;

											temp3.x=punt1.x;//(punt1.x+punt2.x)/2;
											temp3.y=(punt1.y+punt4.y)/2;					//  1y4
											temp3.val=(punt1.val+punt4.val)/2;

											buscaPuntos (temp3,temp2,temp1,punt4,valor,profundidad+1);
		}else{


		if (indic1>0){
			//							puntscontorn[indicpunt]=punt1;
			//							indicpunt++;
			temp1.x=(punt1.x+punt2.x)/2;
			temp1.y=(punt1.y+punt2.y)/2;
			temp1.val=(punt1.val+punt2.val)/2;
			puntscontorn[indicpunt]=temp1;
			indicpunt++;
			temp1.x=(punt1.x+punt4.x)/2;
			temp1.y=(punt1.y+punt4.y)/2;
			temp1.val=(punt1.val+punt4.val)/2;
			puntscontorn[indicpunt]=temp1;
			indicpunt++;

		}
		//puntscontorn[indicpunt]=punt1;
		if (indic2>0){
			//							puntscontorn[indicpunt]=punt2;
			//							indicpunt++;
			temp1.x=(punt1.x+punt2.x)/2;
			temp1.y=(punt1.y+punt2.y)/2;
			temp1.val=(punt1.val+punt2.val)/2;
			puntscontorn[indicpunt]=temp1;
			indicpunt++;
			temp1.x=(punt3.x+punt2.x)/2;
			temp1.y=(punt3.y+punt2.y)/2;
			temp1.val=(punt3.val+punt2.val)/2;
			puntscontorn[indicpunt]=temp1;
			indicpunt++;

		}
		if (indic3>0){
			//							puntscontorn[indicpunt]=punt3;
			//							indicpunt++;
			temp1.x=(punt3.x+punt2.x)/2;
			temp1.y=(punt3.y+punt2.y)/2;
			temp1.val=(punt3.val+punt2.val)/2;
			puntscontorn[indicpunt]=temp1;
			indicpunt++;
			temp1.x=(punt3.x+punt4.x)/2;
			temp1.y=(punt3.y+punt4.y)/2;
			temp1.val=(punt3.val+punt4.val)/2;
			puntscontorn[indicpunt]=temp1;
			indicpunt++;

		}
		if (indic4>0){
			//							puntscontorn[indicpunt]=punt4;
			//							indicpunt++;
			temp1.x=(punt3.x+punt4.x)/2;
			temp1.y=(punt3.y+punt4.y)/2;
			temp1.val=(punt3.val+punt4.val)/2;
			puntscontorn[indicpunt]=temp1;
			indicpunt++;
			temp1.x=(punt1.x+punt4.x)/2;
			temp1.y=(punt1.y+punt4.y)/2;
			temp1.val=(punt1.val+punt4.val)/2;
			puntscontorn[indicpunt]=temp1;
			indicpunt++;

		}
		}
		break;
	case 2: // añado el  punto medio
		//fprintf(stdout,"caso 2\n");


		if ( profundidad < max_profundidad){
//			// SENTIDO ANTIHORARIO , EMPIEZO DEL (0,0)
//			temp1.x=(punt1.x+punt2.x)/2;
//			temp1.y=punt1.y;//(punt1.y+punt2.y)/2;    // medio entre 1 y 2    --- A
//			temp1.val=(punt1.val+punt2.val)/2;
//
//			temp2.x=(punt1.x+punt2.x)/2;
//			temp2.y=(punt1.y+punt4.y)/2;		//  medio diagonal   ---  B
//			temp2.val=(punt1.val+punt3.val)/2;
//
//			temp3.x=punt1.x;//(punt1.x+punt2.x)/2;
//			temp3.y=(punt1.y+punt4.y)/2; 			//  medio entre 1 y 4   --- C
//			temp3.val=(punt1.val+punt4.val)/2;
//
//			buscaPuntos (punt1,temp1,temp2,temp3,valor,profundidad+1);
//
//			////  SEGUNDO CUADRADO
//			temp1.x=(punt1.x+punt2.x)/2;
//			temp1.y=punt1.y;//(punt1.y+punt2.y)/2;		// ***  A  1y2
//			temp1.val=(punt1.val+punt2.val)/2;
//
//			temp2.x=(punt1.x+punt2.x)/2;
//			temp2.y=(punt1.y+punt4.y)/2;				//  *** B  diag
//			temp2.val=(punt1.val+punt3.val)/2;
//
//			temp3.x=punt2.x;//(punt1.x+punt2.x)/2;
//			temp3.y=(punt2.y+punt3.y)/2;				// medio entre 2 y 3   --- D
//			temp3.val=(punt2.val+punt3.val)/2;
//
//			buscaPuntos (temp1,punt2,temp3,temp2,valor,profundidad+1);
//
//			/// CUARTO CUADRADO
//			temp1.x=(punt4.x+punt3.x)/2;
//			temp1.y=punt3.y;//(punt1.y+punt2.y)/2;			// E
//			temp1.val=(punt4.val+punt3.val)/2;
//
//			temp2.x=(punt1.x+punt2.x)/2;
//			temp2.y=(punt1.y+punt4.y)/2;				//  diag
//			temp2.val=(punt1.val+punt3.val)/2;
//
//			temp3.x=punt1.x;//(punt1.x+punt2.x)/2;
//			temp3.y=(punt1.y+punt4.y)/2;					//  1y4
//			temp3.val=(punt1.val+punt4.val)/2;
//
//			buscaPuntos (temp3,temp2,temp1,punt4,valor,profundidad+1);
//
//			////  TERCER CUADRADO
//			temp1.x=(punt4.x+punt3.x)/2;
//			temp1.y=punt3.y;//(punt1.y+punt2.y)/2;    //  medio entre 3y 4  --  E
//			temp1.val=(punt4.val+punt3.val)/2;
//
//			temp2.x=(punt1.x+punt2.x)/2;
//			temp2.y=(punt1.y+punt4.y)/2;				//  *** B  diag
//			temp2.val=(punt1.val+punt3.val)/2;
//
//			temp3.x=punt2.x;//(punt1.x+punt2.x)/2;
//			temp3.y=(punt2.y+punt3.y)/2;					//   *** D   2y3
//			temp3.val=(punt2.val+punt3.val)/2;
//
//			buscaPuntos (temp2,temp3,punt3,temp1,valor,profundidad+1);
//
//
											// SENTIDO ANTIHORARIO , EMPIEZO DEL (0,0)
											temp1.x=(punt1.x+punt2.x)/2;
											temp1.y=punt1.y;//(punt1.y+punt2.y)/2;    // medio entre 1 y 2    --- A
											temp1.val=(punt1.val+punt2.val)/2;

											temp2.x=(punt1.x+punt2.x)/2;
											temp2.y=(punt1.y+punt4.y)/2;		//  medio diagonal   ---  B
											temp2.val=(punt1.val+punt3.val)/2;

											temp3.x=punt1.x;//(punt1.x+punt2.x)/2;
											temp3.y=(punt1.y+punt4.y)/2; 			//  medio entre 1 y 4   --- C
											temp3.val=(punt1.val+punt4.val)/2;

											buscaPuntos (punt1,temp1,temp2,temp3,valor,profundidad+1);

											////  SEGUNDO CUADRADO
											temp1.x=(punt1.x+punt2.x)/2;
											temp1.y=punt1.y;//(punt1.y+punt2.y)/2;		// ***  A  1y2
											temp1.val=(punt1.val+punt2.val)/2;

											temp2.x=(punt1.x+punt2.x)/2;
											temp2.y=(punt1.y+punt4.y)/2;				//  *** B  diag
											temp2.val=(punt1.val+punt3.val)/2;

											temp3.x=punt2.x;//(punt1.x+punt2.x)/2;
											temp3.y=(punt2.y+punt3.y)/2;				// medio entre 2 y 3   --- D
											temp3.val=(punt2.val+punt3.val)/2;

											buscaPuntos (temp1,punt2,temp3,temp2,valor,profundidad+1);

											////  TERCER CUADRADO
											temp1.x=(punt4.x+punt3.x)/2;
											temp1.y=punt3.y;//(punt1.y+punt2.y)/2;    //  medio entre 3y 4  --  E
											temp1.val=(punt4.val+punt3.val)/2;

											temp2.x=(punt1.x+punt2.x)/2;
											temp2.y=(punt1.y+punt4.y)/2;				//  *** B  diag
											temp2.val=(punt1.val+punt3.val)/2;

											temp3.x=punt2.x;//(punt1.x+punt2.x)/2;
											temp3.y=(punt2.y+punt3.y)/2;					//   *** D   2y3
											temp3.val=(punt2.val+punt3.val)/2;

											buscaPuntos (temp2,temp3,punt3,temp1,valor,profundidad+1);


											/// CUARTO CUADRADO
											temp1.x=(punt4.x+punt3.x)/2;
											temp1.y=punt3.y;//(punt1.y+punt2.y)/2;			// E
											temp1.val=(punt4.val+punt3.val)/2;

											temp2.x=(punt1.x+punt2.x)/2;
											temp2.y=(punt1.y+punt4.y)/2;				//  diag
											temp2.val=(punt1.val+punt3.val)/2;

											temp3.x=punt1.x;//(punt1.x+punt2.x)/2;
											temp3.y=(punt1.y+punt4.y)/2;					//  1y4
											temp3.val=(punt1.val+punt4.val)/2;

											buscaPuntos (temp3,temp2,temp1,punt4,valor,profundidad+1);
		}else{
			//creo el punto medio temporal

			if (indic1 && indic2){
				//							temp1.x=(punt1.x+punt2.x)/2;
				//							temp1.y=(punt1.y+punt2.y)/2;
				//							temp1.val=(punt1.val+punt2.val)/2;
				//							puntscontorn[indicpunt]=temp1;
				//							indicpunt++;
				// punto medio del lado
				temp1.x=(punt1.x+punt4.x)/2;
				temp1.y=(punt1.y+punt4.y)/2;
				temp1.val=(punt1.val+punt4.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
				temp1.x=(punt3.x+punt2.x)/2;
				temp1.y=(punt3.y+punt2.y)/2;
				temp1.val=(punt3.val+punt2.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;

			}

			if (indic2 && indic3){
				//							temp1.x=(punt3.x+punt2.x)/2;
				//							temp1.y=(punt3.y+punt2.y)/2;
				//							temp1.val=(punt3.val+punt2.val)/2;
				//							puntscontorn[indicpunt]=temp1;
				//							indicpunt++;
				// punto medio del lado
				temp1.x=(punt1.x+punt2.x)/2;
				temp1.y=(punt1.y+punt2.y)/2;
				temp1.val=(punt1.val+punt2.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
				temp1.x=(punt3.x+punt4.x)/2;
				temp1.y=(punt3.y+punt4.y)/2;
				temp1.val=(punt3.val+punt4.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;

			}// punto medio del lado

			if (indic3 && indic4){
				//							temp1.x=(punt3.x+punt4.x)/2;
				//							temp1.y=(punt3.y+punt4.y)/2;
				//							temp1.val=(punt3.val+punt4.val)/2;
				//							puntscontorn[indicpunt]=temp1;
				//							indicpunt++;
				// punto medio del lado

				temp1.x=(punt3.x+punt2.x)/2;
				temp1.y=(punt3.y+punt2.y)/2;
				temp1.val=(punt3.val+punt2.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
				temp1.x=(punt1.x+punt4.x)/2;
				temp1.y=(punt1.y+punt4.y)/2;
				temp1.val=(punt1.val+punt4.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
			}// punto medio del lado

			if (indic1 && indic4){
				//							temp1.x=(punt1.x+punt4.x)/2;
				//							temp1.y=(punt1.y+punt4.y)/2;
				//							temp1.val=(punt1.val+punt4.val)/2;
				//							puntscontorn[indicpunt]=temp1;
				//							indicpunt++;
				// punto medio del lado
				temp1.x=(punt1.x+punt2.x)/2;
				temp1.y=(punt1.y+punt2.y)/2;
				temp1.val=(punt1.val+punt2.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
				temp1.x=(punt3.x+punt4.x)/2;
				temp1.y=(punt3.y+punt4.y)/2;
				temp1.val=(punt3.val+punt4.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;

			}// punto medio del lado

			if (indic1 && indic3){
				//						temp1.x=(punt1.x+punt3.x)/2;
				//						temp1.y=(punt1.y+punt3.y)/2;
				//						temp1.val=(punt1.val+punt3.val)/2;
				//						puntscontorn[indicpunt]=temp1;
				//						indicpunt++;
				// punto medio del lado
				puntscontorn[indicpunt]=punt1;
								indicpunt++;
				puntscontorn[indicpunt]=punt1;
				indicpunt++;
				puntscontorn[indicpunt]=punt3;
				indicpunt++;
				puntscontorn[indicpunt]=punt3;
								indicpunt++;

			} // miro diagonal, punto medio

			if (indic2 && indic4){
				//						temp1.x=(punt4.x+punt2.x)/2;
				//						temp1.y=(punt4.y+punt2.y)/2;
				//						temp1.val=(punt4.val+punt2.val)/2;
				//						puntscontorn[indicpunt]=temp1;
				//						indicpunt++;
				// punto medio del lado

				puntscontorn[indicpunt]=punt2;
				indicpunt++;
				puntscontorn[indicpunt]=punt2;
								indicpunt++;
				puntscontorn[indicpunt]=punt4;
				indicpunt++;
				puntscontorn[indicpunt]=punt4;
								indicpunt++;
			} // miro diagonal, punto medio

		}

		break;
	case 3:  // añado los dos puntos medios
		//fprintf(stdout,"caso 3\n");

		if ( profundidad < max_profundidad){
			// SENTIDO ANTIHORARIO , EMPIEZO DEL (0,0)
			temp1.x=(punt1.x+punt2.x)/2;
			temp1.y=punt1.y;//(punt1.y+punt2.y)/2;    // medio entre 1 y 2    --- A
			temp1.val=(punt1.val+punt2.val)/2;

			temp2.x=(punt1.x+punt2.x)/2;
			temp2.y=(punt1.y+punt4.y)/2;		//  medio diagonal   ---  B
			temp2.val=(punt1.val+punt3.val)/2;

			temp3.x=punt1.x;//(punt1.x+punt2.x)/2;
			temp3.y=(punt1.y+punt4.y)/2; 			//  medio entre 1 y 4   --- C
			temp3.val=(punt1.val+punt4.val)/2;

			buscaPuntos (punt1,temp1,temp2,temp3,valor,profundidad+1);

			////  SEGUNDO CUADRADO
			temp1.x=(punt1.x+punt2.x)/2;
			temp1.y=punt1.y;//(punt1.y+punt2.y)/2;		// ***  A  1y2
			temp1.val=(punt1.val+punt2.val)/2;

			temp2.x=(punt1.x+punt2.x)/2;
			temp2.y=(punt1.y+punt4.y)/2;				//  *** B  diag
			temp2.val=(punt1.val+punt3.val)/2;

			temp3.x=punt2.x;//(punt1.x+punt2.x)/2;
			temp3.y=(punt2.y+punt3.y)/2;				// medio entre 2 y 3   --- D
			temp3.val=(punt2.val+punt3.val)/2;

			buscaPuntos (temp1,punt2,temp3,temp2,valor,profundidad+1);




			/// CUARTO CUADRADO
			temp1.x=(punt4.x+punt3.x)/2;
			temp1.y=punt3.y;//(punt1.y+punt2.y)/2;			// E
			temp1.val=(punt4.val+punt3.val)/2;

			temp2.x=(punt1.x+punt2.x)/2;
			temp2.y=(punt1.y+punt4.y)/2;				//  diag
			temp2.val=(punt1.val+punt3.val)/2;

			temp3.x=punt1.x;//(punt1.x+punt2.x)/2;
			temp3.y=(punt1.y+punt4.y)/2;					//  1y4
			temp3.val=(punt1.val+punt4.val)/2;

			buscaPuntos (temp3,temp2,temp1,punt4,valor,profundidad+1);

			////  TERCER CUADRADO
			temp1.x=(punt4.x+punt3.x)/2;
			temp1.y=punt3.y;//(punt1.y+punt2.y)/2;    //  medio entre 3y 4  --  E
			temp1.val=(punt4.val+punt3.val)/2;

			temp2.x=(punt1.x+punt2.x)/2;
			temp2.y=(punt1.y+punt4.y)/2;				//  *** B  diag
			temp2.val=(punt1.val+punt3.val)/2;

			temp3.x=punt2.x;//(punt1.x+punt2.x)/2;
			temp3.y=(punt2.y+punt3.y)/2;					//   *** D   2y3
			temp3.val=(punt2.val+punt3.val)/2;

			buscaPuntos (temp2,temp3,punt3,temp1,valor,profundidad+1);
		}else{

			if (indic1 && indic2 && indic3)
			{
				temp1.x=(punt1.x+punt2.x)/2;
				temp1.y=(punt1.y+punt2.y)/2;
				temp1.val=(punt1.val+punt2.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
				temp1.x=(punt3.x+punt2.x)/2;
				temp1.y=(punt3.y+punt2.y)/2;
				temp1.val=(punt3.val+punt2.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
			}

			if (indic4 && indic2 && indic3) // punto medio del lado
					{
				temp1.x=(punt3.x+punt2.x)/2;
				temp1.y=(punt3.y+punt2.y)/2;
				temp1.val=(punt3.val+punt2.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
				temp1.x=(punt3.x+punt4.x)/2;
				temp1.y=(punt3.y+punt4.y)/2;
				temp1.val=(punt3.val+punt4.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
					}
			if (indic1 && indic4 && indic3) // punto medio del lado
			{
				temp1.x=(punt3.x+punt4.x)/2;
				temp1.y=(punt3.y+punt4.y)/2;
				temp1.val=(punt3.val+punt4.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
				temp1.x=(punt1.x+punt4.x)/2;
				temp1.y=(punt1.y+punt4.y)/2;
				temp1.val=(punt1.val+punt4.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
			}
			if (indic1 && indic4 && indic2) // punto medio del lado
			{
				temp1.x=(punt1.x+punt2.x)/2;
				temp1.y=(punt1.y+punt2.y)/2;
				temp1.val=(punt1.val+punt2.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
				temp1.x=(punt1.x+punt4.x)/2;
				temp1.y=(punt1.y+punt4.y)/2;
				temp1.val=(punt1.val+punt4.val)/2;
				puntscontorn[indicpunt]=temp1;
				indicpunt++;
			}

		}

		break;
	case 4:  // subdivido en 4 partes y vulevo a relizar este case
		//fprintf(stdout,"caso 4\n");
		if ( profundidad < max_profundidad){
//
								// SENTIDO ANTIHORARIO , EMPIEZO DEL (0,0)
								temp1.x=(punt1.x+punt2.x)/2;
								temp1.y=punt1.y;//(punt1.y+punt2.y)/2;    // medio entre 1 y 2    --- A
								temp1.val=(punt1.val+punt2.val)/2;

								temp2.x=(punt1.x+punt2.x)/2;
								temp2.y=(punt1.y+punt4.y)/2;		//  medio diagonal   ---  B
								temp2.val=(punt1.val+punt3.val)/2;

								temp3.x=punt1.x;//(punt1.x+punt2.x)/2;
								temp3.y=(punt1.y+punt4.y)/2; 			//  medio entre 1 y 4   --- C
								temp3.val=(punt1.val+punt4.val)/2;

								buscaPuntos (punt1,temp1,temp2,temp3,valor,profundidad+1);

								////  SEGUNDO CUADRADO
								temp1.x=(punt1.x+punt2.x)/2;
								temp1.y=punt1.y;//(punt1.y+punt2.y)/2;		// ***  A  1y2
								temp1.val=(punt1.val+punt2.val)/2;

								temp2.x=(punt1.x+punt2.x)/2;
								temp2.y=(punt1.y+punt4.y)/2;				//  *** B  diag
								temp2.val=(punt1.val+punt3.val)/2;

								temp3.x=punt2.x;//(punt1.x+punt2.x)/2;
								temp3.y=(punt2.y+punt3.y)/2;				// medio entre 2 y 3   --- D
								temp3.val=(punt2.val+punt3.val)/2;

								buscaPuntos (temp1,punt2,temp3,temp2,valor,profundidad+1);

								////  TERCER CUADRADO
								temp1.x=(punt4.x+punt3.x)/2;
								temp1.y=punt3.y;//(punt1.y+punt2.y)/2;    //  medio entre 3y 4  --  E
								temp1.val=(punt4.val+punt3.val)/2;

								temp2.x=(punt1.x+punt2.x)/2;
								temp2.y=(punt1.y+punt4.y)/2;				//  *** B  diag
								temp2.val=(punt1.val+punt3.val)/2;

								temp3.x=punt2.x;//(punt1.x+punt2.x)/2;
								temp3.y=(punt2.y+punt3.y)/2;					//   *** D   2y3
								temp3.val=(punt2.val+punt3.val)/2;

								buscaPuntos (temp2,temp3,punt3,temp1,valor,profundidad+1);


								/// CUARTO CUADRADO
								temp1.x=(punt4.x+punt3.x)/2;
								temp1.y=punt3.y;//(punt1.y+punt2.y)/2;			// E
								temp1.val=(punt4.val+punt3.val)/2;

								temp2.x=(punt1.x+punt2.x)/2;
								temp2.y=(punt1.y+punt4.y)/2;				//  diag
								temp2.val=(punt1.val+punt3.val)/2;

								temp3.x=punt1.x;//(punt1.x+punt2.x)/2;
								temp3.y=(punt1.y+punt4.y)/2;					//  1y4
								temp3.val=(punt1.val+punt4.val)/2;

								buscaPuntos (temp3,temp2,temp1,punt4,valor,profundidad+1);

		//						//glFlush();
		}else{



		}

		break;
	}
	glFlush();
}

void PintarIsoPressio (int miintervalo){

	int i=0,j=0,m=0;
	float k;
	// definir las presiones que hay que buscar para hacer un for de ellas en los valores
	// para cada valor recorrer las estructuras pintando al final
	k=minvalor;
	// for ( diferentes valores a buscar )     ENGLOBA LOS DOS FORS , BUSQUEDA Y PINTAR.
	while (k<=maxvalor){

	for ( i=0;i<fily-1;i++){
		for ( j=0;j<colx-1;j++){
			buscaPuntos (puntsini[i][j],puntsini[i][j+1],puntsini[i+1][j+1],puntsini[i+1][j],k,0);

		}
	}

	// for para pintar lo hallado en los for anteriores
	//glPolygonMode(GL_FRONT_AND_BACK,GL_PO);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glBegin(GL_POLYGON);
	//
	//	//eligeColor(k,intervalo);
	//	glColor3f(1,1,k);
	//	glVertex3f((float)puntscontorn[0].x,(float)puntscontorn[0].y,0.0);
	//	for ( m=1; m<indicpunt;m++)
	//	{
	//		// COMPROBACION QUE LOS PUNTOS ESTAN SUFICIENTEMENTE CERCA
	//		if( ( ((float)puntscontorn[m].x - (float)puntscontorn[m-1].x )> intervalo ) &&
	//				(((float)puntscontorn[m].y - (float)puntscontorn[m-1].y )> intervalo ) && m > 1 ){
	//			glEnd();
	//			glBegin(GL_POLYGON);
	//		}
	//
	//		// pinto lineas
	//		glVertex3f((float)puntscontorn[m].x,(float)puntscontorn[m].y,0.0);
	//	}
	//	glEnd();


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glBegin(GL_POLYGON);


	for ( m=0; m<indicpunt;m++)
	{
		glBegin(GL_LINES);
		glColor3f(1,1,1);
		glVertex3f((float)puntscontorn[m].x,(float)puntscontorn[m].y,0.0);
		m++;
		glVertex3f((float)puntscontorn[m].x,(float)puntscontorn[m].y,0.0);
		glEnd();
	}

//	for ( m=0; m<indicpunt;m++)
//		{
//			glBegin(GL_LINES);
//			glColor3f(1,1,0);
//			glVertex3f((float)puntscontorn[m].x,(float)puntscontorn[m].y,0.0);
//			m++;
//			glVertex3f((float)puntscontorn[m].x,(float)puntscontorn[m].y,0.0);
//			glEnd();
//		}


	fprintf(stdout,"valor %f , %i puntos a pintar\n",k,indicpunt);
	// limpio estructura de puntos pintados
	//glFlush();
	indicpunt=0;
	k += miintervalo;
	}
	glFlush();
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void PintarPressio(){

	if (geopint==1)
		PintarGeoPressio(10);
	if (isos==1)
		PintarIsoPressio(intervalo);

	glFlush();

}
