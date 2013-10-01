/*
 * cartografia.c
 *
 *  Created on: 30/09/2013
 *      Author: lulz
 */


#include <stdio.h>
#include <math.h>
#include "GL/glut.h"
#include "cartografia.h"

int maxperfils=0,maxparalels=0,maxmeridians=0,maxpuntets=0;

int meri,carto,para;

GLenum  doubleBuffer, mode;

int FimaX=812;
int FimaY=812;

int MinX, MinY, MinZ, ResX, ResY, ResZ;
float IncX, IncY, IncZ;



void iniValors() {

  MinX=ORIG;  MinY=ORIG;  MinZ=ORIG;
  IncX=INC;  IncY=INC;  IncZ=INC;
  ResX=DIM;  ResY=DIM;  ResZ=DIM;


}


void Init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  mode = GL_FALSE;
  meri=carto=para=1;
}

void CanviTamany(int width, int height) {

   if (width>height) width=height;
   else height=width;

   FimaX=width;
   FimaY=height;
   glViewport(0,0,FimaX,FimaY);
}

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
	//fprintf(stdout,"Leidos %d perfiles\n",k);
	maxperfils=k;
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
	//fprintf(stdout,"Leidos %d paralelos\n",k);
	maxparalels=k;
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
	//fprintf(stdout,"Leidos %d meridianos \n",k);
	maxmeridians=k;
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
	//fprintf(stdout,"Leidos %d puntets",k);
	maxpuntets=k;
}


void pintarEuropaPuntets (float multiplicador) {
	int i=0;
	for ( i=0;i<maxpuntets;i++){
		glBegin(GL_LINE_STRIP);
		glColor3f(1,1,1);
		glVertex3f(((float)puntets[i][0].x)*multiplicador,(float)puntets[i][0].y*multiplicador,0.0);
		glVertex3f((float)puntets[i][1].x*multiplicador,(float)puntets[i][1].y*multiplicador,0.0);
		glEnd();
	}
	glFlush();
}
void pintarEuropaMeridia(float multiplicador){

	int i=0,j=0;
	for ( i=0;i<maxmeridians;i++){
		glBegin(GL_LINE_STRIP);
		glColor3f(0.4,0.4,0.4);
		for( j=0;meridian[i][j+1].x!=0;j++){
			glVertex3f((float)meridian[i][j].x*multiplicador,(float)meridian[i][j].y*multiplicador,0.0);
			glVertex3f((float)meridian[i][j+1].x*multiplicador,(float)meridian[i][j+1].y*multiplicador,0.0);
		}
		glEnd();
	}
	glFlush();
}
void pintarEuropaParalel(float multiplicador){

	int i=0,j=0;
	for ( i=0;i<maxparalels;i++){
		glBegin(GL_LINE_STRIP);
		glColor3f(0.4,0.4,0.4);
		for( j=0;paralel[i][j+1].x!=0;j++){
			glVertex3f((float)paralel[i][j].x*multiplicador,(float)paralel[i][j].y*multiplicador,0.0);
			glVertex3f((float)paralel[i][j+1].x*multiplicador,(float)paralel[i][j+1].y*multiplicador,0.0);
		}
		glEnd();
	}
	glFlush();
}
void pintarEuropaPerfil(float multiplicador){

	int i=0,j=0;
	for ( i=0;i<maxperfils;i++){
		glBegin(GL_LINE_STRIP);
		glColor3f(1,1,1);
		for( j=0;perfil[i][j+1].x!=0;j++){
			glVertex3f((float)perfil[i][j].x*multiplicador,(float)perfil[i][j].y*multiplicador,0.0);
			glVertex3f((float)perfil[i][j+1].x*multiplicador,(float)perfil[i][j+1].y*multiplicador,0.0);
		}
		glEnd();
	}
	glFlush();
}


void PintarCartografia (){
	glViewport(0,0,FimaX,FimaY);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(MinX,ResX,MinY,ResY);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);

	//pintarEuropaPuntets(10);
	if (meri==1)
	pintarEuropaMeridia(10);
	if (para==1)
	pintarEuropaParalel(10);
	if (carto==1)
	pintarEuropaPerfil(8.56);

}

void Tecles( unsigned char tecla, int x, int y) {
  switch(tecla) {
  case 'm':
	  meri = (meri==0) ? 1 : 0;
	  break;
  case 'p':
	  para = (para==0) ? 1 : 0;
	  break;
  case 'c':
	  carto = (carto==0) ? 1 : 0;
  	  break;
    case 'g':

  	  break;
  case 27:
    exit(0);    break;
  }
  glutPostRedisplay();
}
