/*
 * mapa.c
 *
 *  Created on: 29/09/2013
 *      Author: lulz
 */

#include <stdio.h>
#include <math.h>
#include "GL/glut.h"
#include "cartografia.h"
#include "presion.h"

void iniValors() {

  MinX=ORIG;  MinY=ORIG;  MinZ=ORIG;
  IncX=INC;  IncY=INC;  IncZ=INC;
  ResX=DIM;  ResY=DIM;  ResZ=DIM;

}

void Init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  mode = GL_FALSE;
  meri=carto=para=geopint=punt=1;
  geo=0;
  isos=1;
  intervalo=15;
}


void Tecles( unsigned char tecla, int x, int y) {
  switch(tecla) {
//  case 'l':
//
//  	  break;
  case 'm':
	  punt = (punt==0) ? 1 : 0;
	  meri = (meri==0) ? 1 : 0;
	  para = (para==0) ? 1 : 0;
	  break;
//  case 'p':
//
//	  break;
  case 'c':
	  carto = (carto==0) ? 1 : 0;
  	  break;
    case 'g':
    	geo++;
    	if (geo==9)
    		geo=0;
    	if ( geo == 8 )
    		llegirEuropaGeo("./data/geo48.grd",10);
    	if ( geo == 7 )
    		llegirEuropaGeo("./data/geo42.grd",10);
    	if ( geo == 6 )
    		llegirEuropaGeo("./data/geo36.grd",10);
    	if ( geo == 5 )
    		llegirEuropaGeo("./data/geo30.grd",10);
    	if ( geo == 4 )
    		llegirEuropaGeo("./data/geo24.grd",10);
    	if ( geo == 3 )
    		llegirEuropaGeo("./data/geo18.grd",10);
    	if ( geo == 2 )
    		llegirEuropaGeo("./data/geo12.grd",10);
    	if ( geo == 1 )
    		llegirEuropaGeo("./data/geo06.grd",10);
    	if ( geo == 0 )
    		llegirEuropaGeo("./data/geo00.grd",10);
    	break;
    case 'h':
    	geopint = (geopint==0) ? 1 : 0;
    	// pintar o no geopressions
    	break;
    case 'i':
       	isos = (isos==0) ? 1 : 0;
       	// pintar o no geopressions
       	break;
    case 'a':
          // intervalos de las presiones
    	intervalo++;
    	if ( intervalo > 25)
    	    intervalo=25;
          	break;
    case 'z':
            intervalo-- ;
        	if ( intervalo < 5)
        		intervalo=5;
        	break;
  case 27:
    exit(0);    break;
  }
  glutPostRedisplay();
}
//extern intFimaX,FimaY;

void Pintar(){

	glViewport(0,0,FimaX,FimaY);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(MinX,ResX,MinY,ResY);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);


	PintarPressio();
	PintarCartografia();


}


int main(int argc, char *argv[]) {

  GLenum  type;

  iniValors();
  llegirEuropaPerfil("./data/euro_perfil.dat");
  llegirEuropaParalel("./data/euro_paral_lels.dat");
  llegirEuropaMeridia("./data/euro_meridians.dat");
  llegirEuropaPuntets("./data/euro_puntets.dat");

  llegirEuropaGeo("./data/geo30.grd",10);

  glutInit(&argc, argv);
  doubleBuffer=GL_FALSE;
  type = GLUT_RGB;
  type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
  glutInitDisplayMode(type);
  glutInitWindowSize(FimaX,FimaY);
  glutCreateWindow("VSI Prac 1");
  Init();
  glutKeyboardFunc( Tecles);
  glutDisplayFunc( Pintar);
  glutReshapeFunc(CanviTamany);

  glutMainLoop();
  return 0;
}
