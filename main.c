#include <stdio.h>
#include <stdlib.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "snake.h"

int main(int argc, char *argv[]) {
  /* Plans */
  plan1.p1.x = 80;
  plan1.p1.y = 0;
  plan1.p1.z = -80;

  plan1.p2.x = -80;
  plan1.p2.y = 0;
  plan1.p2.z = -80;

  plan1.p3.x = -80;
  plan1.p3.y = 0;
  plan1.p3.z = 80;

  plan1.p4.x = 80;
  plan1.p4.y = 0;
  plan1.p4.z = 80;

  plan2.p1.x = -80;
  plan2.p1.y = 0;
  plan2.p1.z = -80;

  plan2.p2.x = -80;
  plan2.p2.y = 80;
  plan2.p2.z = -80;

  plan2.p3.x = -80;
  plan2.p3.y = 80;
  plan2.p3.z = 80;

  plan2.p4.x = -80;
  plan2.p4.y = 0;
  plan2.p4.z = 80;

  plan3.p1.x = 80;
  plan3.p1.y = 80;
  plan3.p1.z = -80;

  plan3.p2.x = -80;
  plan3.p2.y = 80;
  plan3.p2.z = -80;

  plan3.p3.x = -80;
  plan3.p3.y = 0;
  plan3.p3.z = -80;

  plan3.p4.x = 80;
  plan3.p4.y = 0;
  plan3.p4.z = -80;

  /* Positionnement caméra */
  hauteur_camera = 10;
  distance_camera_tete = 40;
  camera_x = serpent.body.tab[0].p1.x;
  camera_y = serpent.body.tab[0].p1.y + hauteur_camera;
  camera_z = serpent.body.tab[0].p1.z + distance_camera_tete;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
  glutInitWindowSize (1000,800);
  glutCreateWindow ("Snake - Projet SAI");
  glEnable(GL_DEPTH_TEST);
  glutGetMenu();
  glutDisplayFunc(Affichage);
  glutSpecialFunc(SpecialKey);
  glutMainLoop();

  return 0;
}