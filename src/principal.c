/*
 * mapa.c
 *
 *  Created on: 29/09/2013
 *      Author: lulz
 */

#include <stdio.h>
#include <math.h>
#include "GL/glut.h"
#include "inicio.h"
#include "cartografia.h"


//extern intFimaX,FimaY;

int main(int argc, char *argv[]) {

  GLenum  type;

 // iniValors();
  llegirEuropaPerfil("./data/euro_perfil.dat");
  llegirEuropaParalel("./data/euro_paral_lels.dat");
  llegirEuropaMeridia("./data/euro_meridians.dat");
  llegirEuropaPuntets("./data/euro_puntets.dat");

  //glutInit(&argc, argv);
  //doubleBuffer=GL_FALSE;
  type = GLUT_RGB;
  type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
 // glutInitDisplayMode(type);
 // glutInitWindowSize(FimaX,FimaY);
//  glutCreateWindow("Model de voxels");
  Init();
  //glutKeyboardFunc( Tecles);
 // glutDisplayFunc( Pintar);
 // glutReshapeFunc(CanviFinestra);

 // glutMainLoop();
  return 0;
}
