#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "GL/freeglut.h"
#include "snake.h"


/* Tableau temporaire permettant de stocker les coordonnées 
   du corps de serpent */
tete tmp[1000];

int mode_affichage = MODE_2D_1;

int test = 0;

int vitesse = 80000;

int menu = 1;

int score = 0;

int score1;

/* Cette fonction permet de dessiner le plan à partir
   de 4 points et une couleur (r, v, b) */
void dessiner_plan (plan p, int r, int v, int b) {
  glBegin(GL_QUADS);
    glColor3ub(r, v, b); 
    glVertex3f(p.p1.x, p.p1.y, p.p1.z);
    glColor3ub(r+30, v+30, b+30); 
    glVertex3f(p.p2.x, p.p2.y, p.p2.z);
    glColor3ub(r+30, v+30, b+30); 
    glVertex3f(p.p3.x, p.p3.y, p.p3.z);
    glColor3ub(r, v, b); 
    glVertex3f(p.p4.x, p.p4.y, p.p4.z); 
  glEnd();
}

/* Cette fonction permet de dessiner un cube */
void dessiner_cube (tete cube, int r, int v, int b) {
  glBegin(GL_QUADS);
    glColor3ub(r, v, b); 
      glVertex3d(cube.p1.x, cube.p1.y, cube.p1.z);
      glVertex3d(cube.p1.x-2, cube.p1.y, cube.p1.z);
      glVertex3d(cube.p1.x-2, cube.p1.y, cube.p1.z+2);
      glVertex3d(cube.p1.x, cube.p1.y, cube.p1.z+2);

    glColor3ub(r, v, b); 
      glVertex3d(cube.p1.x, cube.p1.y, cube.p1.z);
      glVertex3d(cube.p1.x, cube.p1.y, cube.p1.z+2);
      glVertex3d(cube.p1.x, cube.p1.y-2, cube.p1.z+2);
      glVertex3d(cube.p1.x, cube.p1.y-2, cube.p1.z);

    glColor3ub(r, v, b); 
      glVertex3d(cube.p1.x, cube.p1.y, cube.p1.z);
      glVertex3d(cube.p1.x, cube.p1.y-2, cube.p1.z);
      glVertex3d(cube.p1.x-2, cube.p1.y-2, cube.p1.z);
      glVertex3d(cube.p1.x-2, cube.p1.y, cube.p1.z);

    glColor3ub(r, v, b);
      glVertex3d(cube.p2.x, cube.p2.y, cube.p2.z);
      glVertex3d(cube.p2.x+2, cube.p2.y, cube.p2.z);
      glVertex3d(cube.p2.x+2, cube.p2.y+2, cube.p2.z);
      glVertex3d(cube.p2.x, cube.p2.y+2, cube.p2.z);

    glColor3ub(r, v, b); 
      glVertex3d(cube.p2.x, cube.p2.y, cube.p2.z);
      glVertex3d(cube.p2.x, cube.p2.y, cube.p2.z-2);
      glVertex3d(cube.p2.x, cube.p2.y+2, cube.p2.z-2);
      glVertex3d(cube.p2.x, cube.p2.y+2, cube.p2.z);

    glColor3ub(r, v, b); 
      glVertex3d(cube.p2.x, cube.p2.y, cube.p2.z);
      glVertex3d(cube.p2.x+2, cube.p2.y, cube.p2.z);
      glVertex3d(cube.p2.x+2, cube.p2.y, cube.p2.z-2);
      glVertex3d(cube.p2.x, cube.p2.y, cube.p2.z-2);
  glEnd();
}

/* Initialisation du serpent */
void initialisation_serpent () {
  /* Initialisation tête et longueur du serpent */
  serpent.body.longueur = 0;

  serpent.body.tab[0].p1.x = 24;
  serpent.body.tab[0].p1.y = 2;
  serpent.body.tab[0].p1.z = -2;

  serpent.body.tab[0].p2.x = 22;
  serpent.body.tab[0].p2.y = 0;
  serpent.body.tab[0].p2.z = 0;

  serpent.body.longueur++;

  /* Corps : On initialise le serpent avec 3 cubes au début de la partie */
  /* 1er cube */
  serpent.body.tab[1].p1.x = serpent.body.tab[0].p1.x;
  serpent.body.tab[1].p1.y = serpent.body.tab[0].p1.y;
  serpent.body.tab[1].p1.z = serpent.body.tab[0].p1.z + 2;

  serpent.body.tab[1].p2.x = serpent.body.tab[0].p2.x;
  serpent.body.tab[1].p2.y = serpent.body.tab[0].p2.y;
  serpent.body.tab[1].p2.z = serpent.body.tab[0].p2.z + 2;

  serpent.body.longueur++;

  /* 2ème cube */
  serpent.body.tab[2].p1.x = serpent.body.tab[1].p1.x;
  serpent.body.tab[2].p1.y = serpent.body.tab[1].p1.y;
  serpent.body.tab[2].p1.z = serpent.body.tab[1].p1.z + 2;

  serpent.body.tab[2].p2.x = serpent.body.tab[1].p2.x;
  serpent.body.tab[2].p2.y = serpent.body.tab[1].p2.y;
  serpent.body.tab[2].p2.z = serpent.body.tab[1].p2.z + 2;

  serpent.body.longueur++;
}

/* Fonction permettant d'afficher du texte */
void afficher_texte (const char *text, int length, int x, int y) {
  float a;
  float b;
  if (length == 29) {
    a = -0.25;
    b = 0;
  }
  else if (length == 5) {
    a = -0.04; 
    b = 0.5;
  }
  else if (length == 14) {
    a = -0.12; 
    b = -0.5;
  }
  else if (length == 17) {
    a = -0.12;
    b = 0;
  }
  else if (length == 31) {
    a = -0.25;
    b = -0.3;
  }
  else if (length == 9) {
    a = 0.78;
    b = 0.95;
  }
  else if (length == 15) {
    a = 0.69;
    b = 0.95;
  }
  glMatrixMode(GL_PROJECTION);
  double matrix[16];
  glGetDoublev(GL_PROJECTION_MATRIX, matrix);
  glLoadIdentity();
  glOrtho(0, 800, 0, 600, -5, -5);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();
  glLoadIdentity();
  glRasterPos2f(a, b);
  for (int i = 0; i < length; i++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
  }
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixd(matrix);
  glMatrixMode(GL_MODELVIEW);
}

/* Gestion du spawn aléatoire des obstacles sur le plan1 */
void obstacles_plan1 () {
  srand(time(NULL));
  int i;

  for (i = 0; i < NB_OBSTACLES_P1; i++) {
    int test = 0;
    int test1 = 0;
    int test2 = 0;
    while (test != serpent.body.longueur && test1 != i && test2 != 1) {
      /* Calcul d'une position aléatoire pour les obstacles */
      obs_p1[i].p1.x = (rand() % ((plan1.p1.x - 2) - (plan1.p2.x + 2) + 1)) + (plan1.p2.x + 2);
      obs_p1[i].p1.z = (rand() % ((plan1.p3.z - 2) - (plan1.p2.z + 2) + 1)) + (plan1.p2.z + 2);

      /* Test pour que les obstacles ne se placent pas sur le serpent */
      for (int k = 0; k < serpent.body.longueur; k++) {
        if (obs_p1[i].p1.x != serpent.body.tab[k].p1.x ||
            obs_p1[i].p1.z != serpent.body.tab[k].p1.z) {
          test++;
        }
      }

      /* Test pour que les obstacles ne soient pas dans 
         le même emplacement */
      for (int j = 0; j < i; j++) {
        if ((obs_p1[j].p1.x != obs_p1[i].p1.x ||
             obs_p1[j].p1.z != obs_p1[i].p1.z) && 
             j != i) {
          test1++;
        }
      }

      /* Test pour que les obstacles ne soient pas directement
         devant le serpent au début du jeu */
      if (obs_p1[i].p1.x == serpent.body.tab[0].p1.x &&
          obs_p1[i].p1.z == serpent.body.tab[0].p1.z - 2) {
        test2 = 1;
      }
    }

    /* On doit génerer un x et z multiples de 2 pour qu'il n y ait 
       pas de décalage entre la tête du serpent et les obstacles */
    if (obs_p1[i].p1.x % 2 != 0) {
      if (obs_p1[i].p1.x == (plan1.p1.x - 2)) {
        obs_p1[i].p1.x--;
      }
      else if (obs_p1[i].p1.x == (plan1.p2.x + 2)) {
        obs_p1[i].p1.x++;
      }
      else {
        obs_p1[i].p1.x++;
      }
    }

    if (obs_p1[i].p1.z % 2 != 0) {
      if (obs_p1[i].p1.z == (plan1.p3.z - 2)) {
        obs_p1[i].p1.z--;
      }
      else if (obs_p1[i].p1.z == (plan1.p1.z + 2)) {
        obs_p1[i].p1.z++;
      }
      else {
        obs_p1[i].p1.z++;
      }
    }
    obs_p1[i].p1.y = plan1.p1.y + 2;

    /* Les coordonnées du deuxième point p2 sont calculés à partir 
       de celles du premier point p1 */
    obs_p1[i].p2.x = obs_p1[i].p1.x - 2;
    obs_p1[i].p2.y = obs_p1[i].p1.y - 2;
    obs_p1[i].p2.z = obs_p1[i].p1.z + 2;
  }
}

/* Gestion du spawn aléatoire des obstacles sur le plan2 */
void obstacles_plan2 () {
  srand(time(NULL));
  int i;

  for (i = 0; i < NB_OBSTACLES_P2; i++) {
    int test = 0;
    int test1 = 0;
    while (test != serpent.body.longueur && test1 != i) {
      obs_p2[i].p1.y = (rand() % ((plan2.p2.y - 2) - (plan2.p1.y + 2) + 1)) + (plan2.p1.y + 2);
      obs_p2[i].p1.z = (rand() % ((plan2.p3.z - 2) - (plan2.p1.z + 2) + 1)) + (plan2.p1.z + 2);

      for (int k = 0; k < serpent.body.longueur; k++) {
        if (obs_p2[i].p1.y != serpent.body.tab[k].p1.y ||
            obs_p2[i].p1.z != serpent.body.tab[k].p1.z) {
          test++;
        }
      }

      for (int j = 0; j < i; j++) {
        if ((obs_p2[j].p1.y != obs_p2[i].p1.y ||
             obs_p2[j].p1.z != obs_p2[i].p1.z) && 
             j != i) {
          test1++;
        }
      }
    }

    if (obs_p2[i].p1.y % 2 != 0) {
      if (obs_p2[i].p1.y == (plan2.p2.y - 2)) {
        obs_p2[i].p1.y--;
      }
      else if (obs_p2[i].p1.y == (plan2.p2.y + 2)) {
        obs_p2[i].p1.y++;
      }
      else {
        obs_p2[i].p1.y++;
      }
    }

    if (obs_p2[i].p1.z % 2 != 0) {
      if (obs_p2[i].p1.z == (plan2.p3.z - 2)) {
        obs_p2[i].p1.z--;
      }
      else if (obs_p2[i].p1.z == (plan2.p1.z + 2)) {
        obs_p2[i].p1.z++;
      }
      else {
        obs_p2[i].p1.z++;
      }
    }
    obs_p2[i].p1.x = plan2.p1.x + 2;
    if (obs_p2[i].p1.y < 2) {
      obs_p2[i].p1.y += 2;
    }

    obs_p2[i].p2.x = obs_p2[i].p1.x - 2;
    obs_p2[i].p2.y = obs_p2[i].p1.y - 2;
    obs_p2[i].p2.z = obs_p2[i].p1.z + 2;
  }
}

/* Gestion du spawn aléatoire des obstacles sur le plan3 */
void obstacles_plan3 () {
  srand(time(NULL));
  int i;

  for (i = 0; i < NB_OBSTACLES_P3; i++) {
    int test = 0;
    int test1 = 0;
    while (test != serpent.body.longueur && test1 != i) {
      obs_p3[i].p1.x = (rand() % ((plan3.p1.x - 2) - (plan3.p2.x + 2) + 1)) + (plan3.p2.x + 2);
      obs_p3[i].p1.y = (rand() % ((plan3.p1.y - 2) - (plan3.p3.y + 2) + 1)) + (plan3.p3.y + 2);

      for (int k = 0; k < serpent.body.longueur; k++) {
        if (obs_p3[i].p1.x != serpent.body.tab[k].p1.x ||
            obs_p3[i].p1.y != serpent.body.tab[k].p1.y) {
          test++;
        }
      }

      for (int j = 0; j < i; j++) {
        if ((obs_p3[j].p1.x != obs_p3[i].p1.x ||
             obs_p3[j].p1.y != obs_p3[i].p1.y) && 
             j != i) {
          test1++;
        }
      }

    }

    if (obs_p3[i].p1.y % 2 != 0) {
      if (obs_p3[i].p1.y == (plan3.p1.y - 2)) {
        obs_p3[i].p1.y--;
      }
      else if (obs_p3[i].p1.y == (plan3.p3.y + 2)) {
        obs_p3[i].p1.y++;
      }
      else {
        obs_p3[i].p1.y++;
      }
    }

    if (obs_p3[i].p1.x % 2 != 0) {
      if (obs_p3[i].p1.x == (plan3.p1.x - 2)) {
        obs_p3[i].p1.x--;
      }
      else if (obs_p3[i].p1.x == (plan3.p2.x + 2)) {
        obs_p3[i].p1.x++;
      }
      else {
        obs_p3[i].p1.x++;
      }
    }
    obs_p3[i].p1.z = plan3.p1.z;
    if (obs_p3[i].p1.y < 2) {
      obs_p3[i].p1.y += 2;
    }

    obs_p3[i].p2.x = obs_p3[i].p1.x - 2;
    obs_p3[i].p2.y = obs_p3[i].p1.y - 2;
    obs_p3[i].p2.z = obs_p3[i].p1.z + 2;
  }
}

/* Gestion du spawn aléatoire de la nourriture sur le plan1 */
void nourriture_serpent_plan1 () {
  srand(time(NULL));
  int test = 0;
  int test1 = 0;

  while (test != serpent.body.longueur && test1 != NB_OBSTACLES_P1) {
    /* Calcul d'une position aléatoire pour la nourriture */
    nourriture1.p1.x = (rand() % ((plan1.p1.x - 2) - (plan1.p2.x + 2) + 1)) + (plan1.p2.x + 2);
    nourriture1.p1.z = (rand() % ((plan1.p3.z - 2) - (plan1.p2.z + 2) + 1)) + (plan1.p2.z + 2);

    /* Test pour que la nourriture ne se place pas sur le serpent */
    for (int i = 0; i < serpent.body.longueur; i++) {
      if (nourriture1.p1.x != serpent.body.tab[i].p1.x ||
          nourriture1.p1.z != serpent.body.tab[i].p1.z) {
        test++;
      }
      else {
        test = 0;
      }
    }

    /* Test pour que la nourriture ne se place pas sur les obstacles */
    for (int i = 0; i < NB_OBSTACLES_P1; i++) {
      if (nourriture1.p1.x != obs_p1[i].p1.x ||
          nourriture1.p1.z != obs_p1[i].p1.z) {
        test1++;
      }
      else {
        test1 = 0;
      }
    }
  }

  /* On doit génerer un x et z multiples de 2 pour qu'il n y ait 
     pas de décalage entre la tête du serpent et la nourriture */
  if (nourriture1.p1.x % 2 != 0) {
    if (nourriture1.p1.x == (plan1.p1.x - 2)) {
      nourriture1.p1.x--;
    }
    else if (nourriture1.p1.x == (plan1.p2.x + 2)) {
      nourriture1.p1.x++;
    }
    else {
      nourriture1.p1.x++;
    }
  }

  if (nourriture1.p1.z % 2 != 0) {
    if (nourriture1.p1.z == (plan1.p3.z - 2)) {
      nourriture1.p1.z--;
    }
    else if (nourriture1.p1.z == (plan1.p1.z + 2)) {
      nourriture1.p1.z++;
    }
    else {
      nourriture1.p1.z++;
    }
  }
  nourriture1.p1.y = plan1.p1.y + 2;

  /* Les coordonnées du deuxième point p2 sont calculés à partir 
     de celles du premier point p1 */
  nourriture1.p2.x = nourriture1.p1.x - 2;
  nourriture1.p2.y = nourriture1.p1.y - 2;
  nourriture1.p2.z = nourriture1.p1.z + 2;
}

/* Gestion du spawn aléatoire de la nourriture sur le plan2 */
void nourriture_serpent_plan2 () {
  srand(time(NULL));
  int test = 0;
  int test1 = 0;

  while (test != serpent.body.longueur && test1 != NB_OBSTACLES_P2) {
    nourriture2.p1.y = (rand() % ((plan2.p2.y - 2) - (plan2.p1.y + 2) + 1)) + (plan2.p1.y + 2);
    nourriture2.p1.z = (rand() % ((plan2.p3.z - 2) - (plan2.p1.z + 2) + 1)) + (plan2.p1.z + 2);

    for (int i = 0; i < serpent.body.longueur; i++) {
      if (nourriture2.p1.y != serpent.body.tab[i].p1.y ||
          nourriture2.p1.z != serpent.body.tab[i].p1.z) {
        test++;
      }
    }

    for (int i = 0; i < NB_OBSTACLES_P2; i++) {
      if (nourriture1.p1.y != obs_p1[i].p1.y ||
          nourriture1.p1.z != obs_p1[i].p1.z) {
        test1++;
      }
      else {
        test1 = 0;
      }
    }
  }

  if (nourriture2.p1.y % 2 != 0) {
    if (nourriture2.p1.y == (plan2.p2.y - 2)) {
      nourriture2.p1.y--;
    }
    else if (nourriture2.p1.y == (plan2.p2.y + 2)) {
      nourriture2.p1.y++;
    }
    else {
      nourriture2.p1.y++;
    }
  }

  if (nourriture2.p1.z % 2 != 0) {
    if (nourriture2.p1.z == (plan2.p3.z - 2)) {
      nourriture2.p1.z--;
    }
    else if (nourriture2.p1.z == (plan2.p1.z + 2)) {
      nourriture2.p1.z++;
    }
    else {
      nourriture2.p1.z++;
    }
  }
  nourriture2.p1.x = plan2.p1.x + 2;

  nourriture2.p2.x = nourriture2.p1.x - 2;
  nourriture2.p2.y = nourriture2.p1.y - 2;
  nourriture2.p2.z = nourriture2.p1.z + 2;
}

/* Gestion du spawn aléatoire de la nourriture sur le plan3 */
void nourriture_serpent_plan3 () {
  srand(time(NULL));
  int test = 0;
  int test1 = 0;

  while (test != serpent.body.longueur && test1 != NB_OBSTACLES_P3) {
    nourriture3.p1.x = (rand() % ((plan3.p1.x - 2) - (plan3.p2.x + 2) + 1)) + (plan3.p2.x + 2);
    nourriture3.p1.y = (rand() % ((plan3.p1.y - 2) - (plan3.p3.y + 2) + 1)) + (plan3.p3.y + 2);

    for (int i = 0; i < serpent.body.longueur; i++) {
      if (nourriture3.p1.x != serpent.body.tab[i].p1.x ||
          nourriture3.p1.y != serpent.body.tab[i].p1.y) {
        test++;
      }
    }

    for (int i = 0; i < NB_OBSTACLES_P3; i++) {
      if (nourriture1.p1.x != obs_p1[i].p1.x ||
          nourriture1.p1.y != obs_p1[i].p1.y) {
        test1++;
      }
      else {
        test1 = 0;
      }
    }
  }

  if (nourriture3.p1.y % 2 != 0) {
    if (nourriture3.p1.y == (plan3.p1.y - 2)) {
      nourriture3.p1.y--;
    }
    else if (nourriture3.p1.y == (plan3.p3.y + 2)) {
      nourriture3.p1.y++;
    }
    else {
      nourriture3.p1.y++;
    }
  }

  if (nourriture3.p1.x % 2 != 0) {
    if (nourriture3.p1.x == (plan3.p1.x - 2)) {
      nourriture3.p1.x--;
    }
    else if (nourriture3.p1.x == (plan3.p2.x + 2)) {
      nourriture3.p1.x++;
    }
    else {
      nourriture3.p1.x++;
    }
  }
  nourriture3.p1.z = plan3.p1.z;

  nourriture3.p2.x = nourriture3.p1.x - 2;
  nourriture3.p2.y = nourriture3.p1.y - 2;
  nourriture3.p2.z = nourriture3.p1.z + 2;
}

/* Cette fonction permet de faire avancer le serpent de manière 
   continue après l'appuie sur une touche de direction */
void avancer () {
  for (int i = 0; i < serpent.body.longueur; i++) {
    tmp[i] = serpent.body.tab[i];
  }

  /* La variable p permet de savoir dans quel plan on est */
  plan p;
  if (serpent.body.tab[0].p1.y == 2 && serpent.body.tab[0].p2.y == 0) {
    p = plan1;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.x == plan2.p1.x + 2 && serpent.body.tab[0].p2.x == plan2.p1.x) {
    p = plan2;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.z == plan3.p1.z && serpent.body.tab[0].p2.z == plan3.p1.z + 2) {
    p = plan3;
  }

  /* Plan 1 */
  /* Gestion de la tête du serpent */
  /* Le serpent avance selon l'axe z (négatif) */
  /* Test pour savoir dans quel plan on est */
  if (p.p1.x == plan1.p1.x &&
      p.p1.y == plan1.p1.y &&
      p.p1.z == plan1.p1.z &&
      p.p2.x == plan1.p2.x &&
      p.p2.y == plan1.p2.y &&
      p.p2.z == plan1.p2.z &&
      p.p3.x == plan1.p3.x &&
      p.p3.y == plan1.p3.y &&
      p.p3.z == plan1.p3.z) {
    if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
        serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
        serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z + 2 &&
        serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
        serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
        serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z + 2 && 
        serpent.body.tab[0].p1.z > p.p1.z) {
      serpent.body.tab[0].p1.z -= 2;
      serpent.body.tab[0].p2.z -= 2;
    }

    /* Le serpent avance selon l'axe z (positif) */
    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z - 2 &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z - 2 &&
             serpent.body.tab[0].p2.z < p.p3.z) {
      serpent.body.tab[0].p1.z += 2;
      serpent.body.tab[0].p2.z += 2;
    }

    /* Le serpent avance selon l'axe x (négatif) */
    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x + 2 &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x + 2 &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p2.x > p.p2.x) {
      serpent.body.tab[0].p1.x -= 2;
      serpent.body.tab[0].p2.x -= 2;
    }

    /* Le serpent change de plan (plan1 -> plan2) */
    else if (serpent.body.tab[0].p2.x == p.p2.x &&
             serpent.body.tab[0].p1.x < serpent.body.tab[1].p1.x &&
             serpent.body.tab[0].p2.x < serpent.body.tab[1].p2.x) {
      serpent.body.tab[0].p1.y += 2;
      serpent.body.tab[0].p2.y += 2;
      p = plan2;
    }

    /* Le serpent change de plan (plan2 -> plan1) */
    else if (serpent.body.tab[0].p1.y < serpent.body.tab[1].p1.y &&
             serpent.body.tab[0].p2.y < serpent.body.tab[1].p2.y &&
             serpent.body.tab[0].p1.y == 2 &&
             serpent.body.tab[0].p2.y == 0 &&
             serpent.body.tab[1].p1.x == -78 &&
             serpent.body.tab[1].p2.x == -80) {
      serpent.body.tab[0].p1.x += 2;
      serpent.body.tab[0].p2.x += 2;
    }

    /* Le serpent change de plan (plan1 -> plan3) */
    else if (serpent.body.tab[0].p1.z == p.p2.z &&
             serpent.body.tab[0].p1.z < serpent.body.tab[1].p1.z &&
             serpent.body.tab[0].p2.z < serpent.body.tab[1].p2.z) {
      serpent.body.tab[0].p1.y += 2;
      serpent.body.tab[0].p2.y += 2;
      p = plan3;
    }

    /* Le serpent change de plan (plan3 -> plan1) */
    else if (serpent.body.tab[0].p1.y < serpent.body.tab[1].p1.y &&
             serpent.body.tab[0].p2.y < serpent.body.tab[1].p2.y &&
             serpent.body.tab[0].p1.y == 2 &&
             serpent.body.tab[0].p2.y == 0 &&
             serpent.body.tab[1].p1.z == -80 &&
             serpent.body.tab[1].p2.z == -78) {
      serpent.body.tab[0].p1.z += 2;
      serpent.body.tab[0].p2.z += 2;
    }

    /* Le serpent avance selon l'axe x (positif) */
    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x - 2 &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x - 2 &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p1.x < p.p1.x) {
      serpent.body.tab[0].p1.x += 2;
      serpent.body.tab[0].p2.x += 2;
    }
  }

  /* Plan 2 */
  else if (p.p1.x == plan2.p1.x &&
           p.p1.y == plan2.p1.y &&
           p.p1.z == plan2.p1.z &&
           p.p2.x == plan2.p2.x &&
           p.p2.y == plan2.p2.y &&
           p.p2.z == plan2.p2.z &&
           p.p3.x == plan2.p3.x &&
           p.p3.y == plan2.p3.y &&
           p.p3.z == plan2.p3.z) {
    if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
        serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
        serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z + 2 &&
        serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
        serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
        serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z + 2 && 
        serpent.body.tab[0].p1.z > p.p1.z) {
      serpent.body.tab[0].p1.z -= 2;
      serpent.body.tab[0].p2.z -= 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z - 2 &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z - 2 &&
             serpent.body.tab[0].p2.z < p.p3.z) {
      serpent.body.tab[0].p1.z += 2;
      serpent.body.tab[0].p2.z += 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y - 2 &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y - 2 &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p2.y < p.p2.y) {
      serpent.body.tab[0].p1.y += 2;
      serpent.body.tab[0].p2.y += 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y + 2 &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y + 2 &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p1.y > p.p1.y) {
      serpent.body.tab[0].p1.y -= 2;
      serpent.body.tab[0].p2.y -= 2;
    }

    /* Plan2 -> plan1 */
    else if (serpent.body.tab[0].p1.x == p.p2.x &&
             serpent.body.tab[0].p1.y < serpent.body.tab[1].p1.y &&
             serpent.body.tab[0].p2.y < serpent.body.tab[1].p2.y) {
      serpent.body.tab[0].p1.x += 2;
      serpent.body.tab[0].p2.x += 2;
      p = plan1;
    }

    /* Plan2 -> plan3 */
    else if (serpent.body.tab[0].p1.z == p.p1.z &&
             serpent.body.tab[0].p1.z < serpent.body.tab[1].p1.z &&
             serpent.body.tab[0].p2.z < serpent.body.tab[1].p2.z) {
      serpent.body.tab[0].p1.x += 2;
      serpent.body.tab[0].p2.x += 2;
      p = plan3;
    }

    /* Plan3 -> plan2 */
    else if (serpent.body.tab[0].p1.x < serpent.body.tab[1].p1.x &&
             serpent.body.tab[0].p2.x < serpent.body.tab[1].p2.x &&
             serpent.body.tab[0].p1.x == -78 &&
             serpent.body.tab[0].p2.x == -80 &&
             serpent.body.tab[1].p1.z == -80 &&
             serpent.body.tab[1].p2.z == -78) {
      serpent.body.tab[0].p1.z += 2;
      serpent.body.tab[0].p2.z += 2;
    }
  }

  /* Plan 3 */
  else if (p.p1.x == plan3.p1.x &&
           p.p1.y == plan3.p1.y &&
           p.p1.z == plan3.p1.z &&
           p.p2.x == plan3.p2.x &&
           p.p2.y == plan3.p2.y &&
           p.p2.z == plan3.p2.z &&
           p.p3.x == plan3.p3.x &&
           p.p3.y == plan3.p3.y &&
           p.p3.z == plan3.p3.z) {
    if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
        serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y - 2 &&
        serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
        serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
        serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y - 2 &&
        serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z && 
        serpent.body.tab[0].p1.y < p.p1.y) {
      serpent.body.tab[0].p1.y += 2;
      serpent.body.tab[0].p2.y += 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y + 2 &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y + 2 &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p2.y > p.p3.y) {
      serpent.body.tab[0].p1.y -= 2;
      serpent.body.tab[0].p2.y -= 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x + 2 &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x + 2 &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p2.x > p.p2.x) {
      serpent.body.tab[0].p1.x -= 2;
      serpent.body.tab[0].p2.x -= 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x - 2 &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x - 2 &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p1.x < p.p1.x) {
      serpent.body.tab[0].p1.x += 2;
      serpent.body.tab[0].p2.x += 2;
    }

    /* Plan3 -> plan1 */
    else if (serpent.body.tab[0].p2.z == p.p3.z &&
             serpent.body.tab[0].p1.y < serpent.body.tab[1].p1.y &&
             serpent.body.tab[0].p2.y < serpent.body.tab[1].p2.y) {
      serpent.body.tab[0].p1.z += 2;
      serpent.body.tab[0].p2.z += 2;
      p = plan1;
    }

    /* Plan3 -> plan2 */
    else if (serpent.body.tab[0].p2.x == p.p2.x &&
             serpent.body.tab[0].p1.x < serpent.body.tab[1].p1.x &&
             serpent.body.tab[0].p2.x < serpent.body.tab[1].p2.x) {
      serpent.body.tab[0].p1.z += 2;
      serpent.body.tab[0].p2.z += 2;
      p = plan2;
    }

    /* Plan2 -> plan3 */
    else if (serpent.body.tab[0].p1.z < serpent.body.tab[1].p1.z &&
             serpent.body.tab[0].p2.z < serpent.body.tab[1].p2.z &&
             serpent.body.tab[0].p1.z == -78 &&
             serpent.body.tab[0].p2.z == -80 &&
             serpent.body.tab[1].p1.x == -78 &&
             serpent.body.tab[1].p2.x == -80) {
      serpent.body.tab[0].p1.x += 2;
      serpent.body.tab[0].p2.x += 2;
    }
  }

  /* Gestion du corps du serpent */
  for (int i = 1; i < serpent.body.longueur; i++) {
    serpent.body.tab[i] = tmp[i-1];
  }
  glutPostRedisplay();
}

/* Gère le premier mouvement (1 unité) du serpent lors du premier 
   appuie sur une touche de direction */
void mouvement_gauche_3d () {
  for (int i = 0; i < serpent.body.longueur; i++) {
    tmp[i] = serpent.body.tab[i];
  }

  plan p;
  if (serpent.body.tab[0].p1.y == 2 && serpent.body.tab[0].p2.y == 0) {
    p = plan1;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.x == plan2.p1.x + 2 && serpent.body.tab[0].p2.x == plan2.p1.x) {
    p = plan2;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.z == plan3.p1.z && serpent.body.tab[0].p2.z == plan3.p1.z + 2) {
    p = plan3;
  }

  /* Plan 1 */
  if (p.p1.x == plan1.p1.x &&
      p.p1.y == plan1.p1.y &&
      p.p1.z == plan1.p1.z &&
      p.p2.x == plan1.p2.x &&
      p.p2.y == plan1.p2.y &&
      p.p2.z == plan1.p2.z &&
      p.p3.x == plan1.p3.x &&
      p.p3.y == plan1.p3.y &&
      p.p3.z == plan1.p3.z) {
    if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
        serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
        serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z + 2 &&
        serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
        serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
        serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z + 2 &&
        serpent.body.tab[0].p2.x > p.p2.x) {
      serpent.body.tab[0].p1.x -= 2;
      serpent.body.tab[0].p2.x -= 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z - 2 &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z - 2 &&
             serpent.body.tab[0].p1.x < p.p1.x) {
      serpent.body.tab[0].p1.x += 2;
      serpent.body.tab[0].p2.x += 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x - 2 &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x - 2 &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p1.z > p.p1.z) {
      serpent.body.tab[0].p1.z -= 2;
      serpent.body.tab[0].p2.z -= 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x + 2 &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x + 2 &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p2.z < p.p3.z) {
      serpent.body.tab[0].p1.z += 2;
      serpent.body.tab[0].p2.z += 2;
    }
  }

  /* Plan 2 */
  else if (p.p1.x == plan2.p1.x &&
           p.p1.y == plan2.p1.y &&
           p.p1.z == plan2.p1.z &&
           p.p2.x == plan2.p2.x &&
           p.p2.y == plan2.p2.y &&
           p.p2.z == plan2.p2.z &&
           p.p3.x == plan2.p3.x &&
           p.p3.y == plan2.p3.y &&
           p.p3.z == plan2.p3.z) {
    if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
        serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
        serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z + 2 &&
        serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
        serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
        serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z + 2 &&
        serpent.body.tab[0].p2.y < p.p2.y) {
      serpent.body.tab[0].p1.y += 2;
      serpent.body.tab[0].p2.y += 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z - 2 &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z - 2 &&
             serpent.body.tab[0].p1.y > p.p1.y) {
      serpent.body.tab[0].p1.y -= 2;
      serpent.body.tab[0].p2.y -= 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y + 2 &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y + 2 &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p1.z > p.p1.z) {
      serpent.body.tab[0].p1.z -= 2;
      serpent.body.tab[0].p2.z -= 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y - 2 &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y - 2 &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p2.z < p.p3.z) {
      serpent.body.tab[0].p1.z += 2;
      serpent.body.tab[0].p2.z += 2;
    }
  }

  /* Plan 3 */
  else if (p.p1.x == plan3.p1.x &&
           p.p1.y == plan3.p1.y &&
           p.p1.z == plan3.p1.z &&
           p.p2.x == plan3.p2.x &&
           p.p2.y == plan3.p2.y &&
           p.p2.z == plan3.p2.z &&
           p.p3.x == plan3.p3.x &&
           p.p3.y == plan3.p3.y &&
           p.p3.z == plan3.p3.z) {
    if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
        serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y - 2 &&
        serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
        serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
        serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y - 2 &&
        serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
        serpent.body.tab[0].p2.x > p.p2.x) {
      serpent.body.tab[0].p1.x -= 2;
      serpent.body.tab[0].p2.x -= 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y + 2 &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y + 2 &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p1.x < p.p1.x) {
      serpent.body.tab[0].p1.x += 2;
      serpent.body.tab[0].p2.x += 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x - 2 &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x - 2 &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p1.y < p.p1.y) {
      serpent.body.tab[0].p1.y += 2;
      serpent.body.tab[0].p2.y += 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x + 2 &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x + 2 &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p2.y > p.p3.y) {
      serpent.body.tab[0].p1.y -= 2;
      serpent.body.tab[0].p2.y -= 2;
    }
  }

  for (int i = 1; i < serpent.body.longueur; i++) {
    serpent.body.tab[i] = tmp[i-1];
  }
  glutPostRedisplay();
}

void mouvement_droite_3d () {
  for (int i = 0; i < serpent.body.longueur; i++) {
    tmp[i] = serpent.body.tab[i];
  }

  plan p;
  if (serpent.body.tab[0].p1.y == 2 && serpent.body.tab[0].p2.y == 0) {
    p = plan1;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.x == plan2.p1.x + 2 && serpent.body.tab[0].p2.x == plan2.p1.x) {
    p = plan2;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.z == plan3.p1.z && serpent.body.tab[0].p2.z == plan3.p1.z + 2) {
    p = plan3;
  }

  /* Plan 1 */
  if (p.p1.x == plan1.p1.x &&
      p.p1.y == plan1.p1.y &&
      p.p1.z == plan1.p1.z &&
      p.p2.x == plan1.p2.x &&
      p.p2.y == plan1.p2.y &&
      p.p2.z == plan1.p2.z &&
      p.p3.x == plan1.p3.x &&
      p.p3.y == plan1.p3.y &&
      p.p3.z == plan1.p3.z) {
    if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
        serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
        serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z + 2 &&
        serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
        serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
        serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z + 2 &&
        serpent.body.tab[0].p1.x < p.p1.x) {
      serpent.body.tab[0].p1.x += 2;
      serpent.body.tab[0].p2.x += 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z - 2 &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z - 2 &&
             serpent.body.tab[0].p2.x > p.p2.x) {
      serpent.body.tab[0].p1.x -= 2;
      serpent.body.tab[0].p2.x -= 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x - 2 &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x - 2 &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p2.z < p.p3.z) {
      serpent.body.tab[0].p1.z += 2;
      serpent.body.tab[0].p2.z += 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x + 2 &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x + 2 &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p1.z > p.p1.z) {
      serpent.body.tab[0].p1.z -= 2;
      serpent.body.tab[0].p2.z -= 2;
    }
  }

  /* Plan 2 */
  else if (p.p1.x == plan2.p1.x &&
           p.p1.y == plan2.p1.y &&
           p.p1.z == plan2.p1.z &&
           p.p2.x == plan2.p2.x &&
           p.p2.y == plan2.p2.y &&
           p.p2.z == plan2.p2.z &&
           p.p3.x == plan2.p3.x &&
           p.p3.y == plan2.p3.y &&
           p.p3.z == plan2.p3.z) {
    if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
        serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
        serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z + 2 &&
        serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
        serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
        serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z + 2 &&
        serpent.body.tab[0].p1.y > p.p1.y) {
      serpent.body.tab[0].p1.y -= 2;
      serpent.body.tab[0].p2.y -= 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z - 2 &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z - 2 &&
             serpent.body.tab[0].p2.y < p.p2.y) {
      serpent.body.tab[0].p1.y += 2;
      serpent.body.tab[0].p2.y += 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y + 2 &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y + 2 &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p2.z < p.p3.z) {
      serpent.body.tab[0].p1.z += 2;
      serpent.body.tab[0].p2.z += 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y - 2 &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y - 2 &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p1.z > p.p1.z) {
      serpent.body.tab[0].p1.z -= 2;
      serpent.body.tab[0].p2.z -= 2;
    }
  }

  /* Plan 3 */
  else if (p.p1.x == plan3.p1.x &&
           p.p1.y == plan3.p1.y &&
           p.p1.z == plan3.p1.z &&
           p.p2.x == plan3.p2.x &&
           p.p2.y == plan3.p2.y &&
           p.p2.z == plan3.p2.z &&
           p.p3.x == plan3.p3.x &&
           p.p3.y == plan3.p3.y &&
           p.p3.z == plan3.p3.z) {
    if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
        serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y - 2 &&
        serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
        serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
        serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y - 2 &&
        serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
        serpent.body.tab[0].p1.x < p.p1.x) {
      serpent.body.tab[0].p1.x += 2;
      serpent.body.tab[0].p2.x += 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y + 2 &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y + 2 &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p2.x > p.p2.x) {
      serpent.body.tab[0].p1.x -= 2;
      serpent.body.tab[0].p2.x -= 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x - 2 &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x - 2 &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p2.y > p.p3.y) {
      serpent.body.tab[0].p1.y -= 2;
      serpent.body.tab[0].p2.y -= 2;
    }

    else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x + 2 &&
             serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
             serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
             serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x + 2 &&
             serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
             serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z &&
             serpent.body.tab[0].p1.y < p.p1.y) {
      serpent.body.tab[0].p1.y += 2;
      serpent.body.tab[0].p2.y += 2;
    }
  }

  for (int i = 1; i < serpent.body.longueur; i++) {
    serpent.body.tab[i] = tmp[i-1];
  }
  glutPostRedisplay();
}

void mouvement_haut () {
  for (int i = 0; i < serpent.body.longueur; i++) {
    tmp[i] = serpent.body.tab[i];
  }

  plan p;
  if (serpent.body.tab[0].p1.y == 2 && serpent.body.tab[0].p2.y == 0) {
    p = plan1;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.x == plan2.p1.x + 2 && serpent.body.tab[0].p2.x == plan2.p1.x) {
    p = plan2;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.z == plan3.p1.z && serpent.body.tab[0].p2.z == plan3.p1.z + 2) {
    p = plan3;
  }

  /* Plan1 */
  if (p.p1.x == plan1.p1.x &&
      p.p1.y == plan1.p1.y &&
      p.p1.z == plan1.p1.z &&
      p.p2.x == plan1.p2.x &&
      p.p2.y == plan1.p2.y &&
      p.p2.z == plan1.p2.z &&
      p.p3.x == plan1.p3.x &&
      p.p3.y == plan1.p3.y &&
      p.p3.z == plan1.p3.z) {
    if (serpent.body.tab[0].p1.z > plan1.p1.z) {
      serpent.body.tab[0].p1.z -= 2;
      serpent.body.tab[0].p2.z -= 2;
    }
  }

  /* Plan 2 */
  else if (p.p1.x == plan2.p1.x &&
           p.p1.y == plan2.p1.y &&
           p.p1.z == plan2.p1.z &&
           p.p2.x == plan2.p2.x &&
           p.p2.y == plan2.p2.y &&
           p.p2.z == plan2.p2.z &&
           p.p3.x == plan2.p3.x &&
           p.p3.y == plan2.p3.y &&
           p.p3.z == plan2.p3.z) {
    if (serpent.body.tab[0].p1.z > plan2.p1.z) {
      serpent.body.tab[0].p1.z -= 2;
      serpent.body.tab[0].p2.z -= 2;
    }
  }

  /* Plan 3 */
  else if (p.p1.x == plan3.p1.x &&
           p.p1.y == plan3.p1.y &&
           p.p1.z == plan3.p1.z &&
           p.p2.x == plan3.p2.x &&
           p.p2.y == plan3.p2.y &&
           p.p2.z == plan3.p2.z &&
           p.p3.x == plan3.p3.x &&
           p.p3.y == plan3.p3.y &&
           p.p3.z == plan3.p3.z) {
    if (serpent.body.tab[0].p1.y < plan3.p1.y) {
      serpent.body.tab[0].p1.y += 2;
      serpent.body.tab[0].p2.y += 2;
    }
  }

  for (int i = 1; i < serpent.body.longueur; i++) {
    serpent.body.tab[i] = tmp[i-1];
  }
  glutPostRedisplay();
}

void mouvement_bas () {
  for (int i = 0; i < serpent.body.longueur; i++) {
    tmp[i] = serpent.body.tab[i];
  }

  plan p;
  if (serpent.body.tab[0].p1.y == 2 && serpent.body.tab[0].p2.y == 0) {
    p = plan1;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.x == plan2.p1.x + 2 && serpent.body.tab[0].p2.x == plan2.p1.x) {
    p = plan2;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.z == plan3.p1.z && serpent.body.tab[0].p2.z == plan3.p1.z + 2) {
    p = plan3;
  }

  /* Plan1 */
  if (p.p1.x == plan1.p1.x &&
      p.p1.y == plan1.p1.y &&
      p.p1.z == plan1.p1.z &&
      p.p2.x == plan1.p2.x &&
      p.p2.y == plan1.p2.y &&
      p.p2.z == plan1.p2.z &&
      p.p3.x == plan1.p3.x &&
      p.p3.y == plan1.p3.y &&
      p.p3.z == plan1.p3.z) {
    if (serpent.body.tab[0].p1.z < plan1.p3.z) {
      serpent.body.tab[0].p1.z += 2;
      serpent.body.tab[0].p2.z += 2;
    }
  }

  /* Plan 2 */
  else if (p.p1.x == plan2.p1.x &&
           p.p1.y == plan2.p1.y &&
           p.p1.z == plan2.p1.z &&
           p.p2.x == plan2.p2.x &&
           p.p2.y == plan2.p2.y &&
           p.p2.z == plan2.p2.z &&
           p.p3.x == plan2.p3.x &&
           p.p3.y == plan2.p3.y &&
           p.p3.z == plan2.p3.z) {
    if (serpent.body.tab[0].p1.z < plan2.p3.z) {
      serpent.body.tab[0].p1.z += 2;
      serpent.body.tab[0].p2.z += 2;
    }
  }

  /* Plan 3 */
  else if (p.p1.x == plan3.p1.x &&
           p.p1.y == plan3.p1.y &&
           p.p1.z == plan3.p1.z &&
           p.p2.x == plan3.p2.x &&
           p.p2.y == plan3.p2.y &&
           p.p2.z == plan3.p2.z &&
           p.p3.x == plan3.p3.x &&
           p.p3.y == plan3.p3.y &&
           p.p3.z == plan3.p3.z) {
    if (serpent.body.tab[0].p1.y > plan3.p3.y) {
      serpent.body.tab[0].p1.y -= 2;
      serpent.body.tab[0].p2.y -= 2;
    }
  }

  for (int i = 1; i < serpent.body.longueur; i++) {
    serpent.body.tab[i] = tmp[i-1];
  }
  glutPostRedisplay();
}

void mouvement_gauche () {
  for (int i = 0; i < serpent.body.longueur; i++) {
    tmp[i] = serpent.body.tab[i];
  }

  plan p;
  if (serpent.body.tab[0].p1.y == 2 && serpent.body.tab[0].p2.y == 0) {
    p = plan1;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.x == plan2.p1.x + 2 && serpent.body.tab[0].p2.x == plan2.p1.x) {
    p = plan2;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.z == plan3.p1.z && serpent.body.tab[0].p2.z == plan3.p1.z + 2) {
    p = plan3;
  }

  /* Plan1 */
  if (p.p1.x == plan1.p1.x &&
      p.p1.y == plan1.p1.y &&
      p.p1.z == plan1.p1.z &&
      p.p2.x == plan1.p2.x &&
      p.p2.y == plan1.p2.y &&
      p.p2.z == plan1.p2.z &&
      p.p3.x == plan1.p3.x &&
      p.p3.y == plan1.p3.y &&
      p.p3.z == plan1.p3.z) {
    if (serpent.body.tab[0].p1.x > plan1.p2.x) {
      serpent.body.tab[0].p1.x -= 2;
      serpent.body.tab[0].p2.x -= 2;
    }
  }

  /* Plan 2 */
  else if (p.p1.x == plan2.p1.x &&
           p.p1.y == plan2.p1.y &&
           p.p1.z == plan2.p1.z &&
           p.p2.x == plan2.p2.x &&
           p.p2.y == plan2.p2.y &&
           p.p2.z == plan2.p2.z &&
           p.p3.x == plan2.p3.x &&
           p.p3.y == plan2.p3.y &&
           p.p3.z == plan2.p3.z) {
    if (serpent.body.tab[0].p1.y < plan2.p2.y) {
      serpent.body.tab[0].p1.y += 2;
      serpent.body.tab[0].p2.y += 2;
    }
  }

  /* Plan 3 */
  else if (p.p1.x == plan3.p1.x &&
           p.p1.y == plan3.p1.y &&
           p.p1.z == plan3.p1.z &&
           p.p2.x == plan3.p2.x &&
           p.p2.y == plan3.p2.y &&
           p.p2.z == plan3.p2.z &&
           p.p3.x == plan3.p3.x &&
           p.p3.y == plan3.p3.y &&
           p.p3.z == plan3.p3.z) {
    if (serpent.body.tab[0].p1.x > plan3.p2.x) {
      serpent.body.tab[0].p1.x -= 2;
      serpent.body.tab[0].p2.x -= 2;
    }
  }

  for (int i = 1; i < serpent.body.longueur; i++) {
    serpent.body.tab[i] = tmp[i-1];
  }
  glutPostRedisplay();
}

void mouvement_droite () {
  for (int i = 0; i < serpent.body.longueur; i++) {
    tmp[i] = serpent.body.tab[i];
  }

  plan p;
  if (serpent.body.tab[0].p1.y == 2 && serpent.body.tab[0].p2.y == 0) {
    p = plan1;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.x == plan2.p1.x + 2 && serpent.body.tab[0].p2.x == plan2.p1.x) {
    p = plan2;
  }
  else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
           serpent.body.tab[0].p1.z == plan3.p1.z && serpent.body.tab[0].p2.z == plan3.p1.z + 2) {
    p = plan3;
  }

  /* Plan1 */
  if (p.p1.x == plan1.p1.x &&
      p.p1.y == plan1.p1.y &&
      p.p1.z == plan1.p1.z &&
      p.p2.x == plan1.p2.x &&
      p.p2.y == plan1.p2.y &&
      p.p2.z == plan1.p2.z &&
      p.p3.x == plan1.p3.x &&
      p.p3.y == plan1.p3.y &&
      p.p3.z == plan1.p3.z) {
    if (serpent.body.tab[0].p1.x < plan1.p1.x) {
      serpent.body.tab[0].p1.x += 2;
      serpent.body.tab[0].p2.x += 2;
    }
  }

  /* Plan 2 */
  else if (p.p1.x == plan2.p1.x &&
           p.p1.y == plan2.p1.y &&
           p.p1.z == plan2.p1.z &&
           p.p2.x == plan2.p2.x &&
           p.p2.y == plan2.p2.y &&
           p.p2.z == plan2.p2.z &&
           p.p3.x == plan2.p3.x &&
           p.p3.y == plan2.p3.y &&
           p.p3.z == plan2.p3.z) {
    if (serpent.body.tab[0].p1.y > plan2.p1.y) {
      serpent.body.tab[0].p1.y -= 2;
      serpent.body.tab[0].p2.y -= 2;
    }
  }

  /* Plan 3 */
  else if (p.p1.x == plan3.p1.x &&
           p.p1.y == plan3.p1.y &&
           p.p1.z == plan3.p1.z &&
           p.p2.x == plan3.p2.x &&
           p.p2.y == plan3.p2.y &&
           p.p2.z == plan3.p2.z &&
           p.p3.x == plan3.p3.x &&
           p.p3.y == plan3.p3.y &&
           p.p3.z == plan3.p3.z) {
    if (serpent.body.tab[0].p1.x < plan3.p1.x) {
      serpent.body.tab[0].p1.x += 2;
      serpent.body.tab[0].p2.x += 2;
    }
  }

  for (int i = 1; i < serpent.body.longueur; i++) {
    serpent.body.tab[i] = tmp[i-1];
  }
  glutPostRedisplay();
}

/* Fonction d'affichage */
void Affichage () {

  /* Menu principal */
  if (menu == 1) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    char texte1[5] = {'S', 'N', 'A', 'K', 'E'};
    glColor3f(1, 0, 0);
    afficher_texte(texte1, 5, 0, 0);

    char texte2[29] = {'A', 'p', 'p', 'u', 'y', 'e', 'r', ' ',
                       's', 'u', 'r', ' ', 'F', '4', ' ', 'p',
                       'o', 'u', 'r', ' ', 'c', 'o', 'm', 'm',
                       'e', 'n', 'c', 'e', 'r'};
    glColor3f(0, 1, 0);
    afficher_texte(texte2, 29, 0, 0);

    char texte3[14] = {'W', 'a', 'l', 'i', 'd', ' ', 'O', 'U',
                       'C', 'H', 'T', 'I', 'T', 'I'};
    glColor3f(0, 0, 1);
    afficher_texte(texte3, 14, 0, 0);

    /* Initialisation serpent */
    initialisation_serpent();

    /* Initialisation bstacles */
    obstacles_plan1();
    obstacles_plan2();
    obstacles_plan3();

    /* Initialisation nourriture */
    nourriture_serpent_plan1();
    nourriture_serpent_plan2();
    nourriture_serpent_plan3();

    score = 0;

    glutPostRedisplay();
  }

  /* Si le joueur perd la partie */
  else if (menu == 2) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    char texte1[17] = {'V', 'o', 'u', 's', ' ', 'a', 'v', 'e',
                       'z', ' ', 'p', 'e', 'r', 'd', 'u', ' ',
                       '!'};
    glColor3f(0, 1, 0);
    afficher_texte(texte1, 17, 0, 0);

    char texte2[15] = {'V', 'o', 't', 'r', 'e', ' ', 's', 'c',
                       'o', 'r', 'e', ' ', ':', ' '};
    texte2[14] = score1 + '0';
    glColor3f(0, 1, 1);
    afficher_texte(texte2, 15, 0, 0);

    /* Initialisation serpent */
    initialisation_serpent();

    /* Initialisation bstacles */
    obstacles_plan1();
    obstacles_plan2();
    obstacles_plan3();

    /* Initialisation nourriture */
    nourriture_serpent_plan1();
    nourriture_serpent_plan2();
    nourriture_serpent_plan3();

    score = 0;

    glutPostRedisplay();
  }

  else {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* Configuration caméra */
    gluPerspective(40, 1, 1, 1000);

    plan p;
    if (serpent.body.tab[0].p1.y == 2 && serpent.body.tab[0].p2.y == 0) {
      p = plan1;
    }
    else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
             serpent.body.tab[0].p1.x == plan2.p1.x + 2 && serpent.body.tab[0].p2.x == plan2.p1.x) {
      p = plan2;
    }
    else if (serpent.body.tab[0].p1.y > 2 && serpent.body.tab[0].p2.y > 0 &&
             serpent.body.tab[0].p1.z == plan3.p1.z && serpent.body.tab[0].p2.z == plan3.p1.z + 2) {
      p = plan3;
    }

    if (mode_affichage == MODE_2D_1) {
      gluLookAt(-10, 290, 170, -10, 0, 0, 0, 1, 0);
    }

    else if (mode_affichage == MODE_2D_2) {
      if (p.p1.x == plan1.p1.x &&
          p.p1.y == plan1.p1.y &&
          p.p1.z == plan1.p1.z &&
          p.p2.x == plan1.p2.x &&
          p.p2.y == plan1.p2.y &&
          p.p2.z == plan1.p2.z &&
          p.p3.x == plan1.p3.x &&
          p.p3.y == plan1.p3.y &&
          p.p3.z == plan1.p3.z) {
        gluLookAt(0, 235, 0, 0, 0, 0, 0, 0, -1);
      }
      else if (p.p1.x == plan2.p1.x &&
               p.p1.y == plan2.p1.y &&
               p.p1.z == plan2.p1.z &&
               p.p2.x == plan2.p2.x &&
               p.p2.y == plan2.p2.y &&
               p.p2.z == plan2.p2.z &&
               p.p3.x == plan2.p3.x &&
               p.p3.y == plan2.p3.y &&
               p.p3.z == plan2.p3.z) {
        gluLookAt(200, 40, 0, 0, 40, 0, 0, 0, -1);
      }
      else if (p.p1.x == plan3.p1.x &&
               p.p1.y == plan3.p1.y &&
               p.p1.z == plan3.p1.z &&
               p.p2.x == plan3.p2.x &&
               p.p2.y == plan3.p2.y &&
               p.p2.z == plan3.p2.z &&
               p.p3.x == plan3.p3.x &&
               p.p3.y == plan3.p3.y &&
               p.p3.z == plan3.p3.z) {
        gluLookAt(0, 0, 225, 0, 40, 0, 0, 1, 0);
      }
    }

    else if (mode_affichage == MODE_3D) {
      int vitesse_camera = 2;

      /* Caméra plan 1 */
      if (p.p1.x == plan1.p1.x &&
          p.p1.y == plan1.p1.y &&
          p.p1.z == plan1.p1.z &&
          p.p2.x == plan1.p2.x &&
          p.p2.y == plan1.p2.y &&
          p.p2.z == plan1.p2.z &&
          p.p3.x == plan1.p3.x &&
          p.p3.y == plan1.p3.y &&
          p.p3.z == plan1.p3.z) {
        if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
            serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
            serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z + 2 &&
            serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
            serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
            serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z + 2) {

          if (camera_x < serpent.body.tab[0].p1.x) {
            camera_x += vitesse_camera;
          }
          else if (camera_x > serpent.body.tab[0].p1.x) {
            camera_x -= vitesse_camera;
          }

          if (camera_y < serpent.body.tab[0].p1.y + hauteur_camera) {
            camera_y += vitesse_camera;
          }
          else if (camera_y > serpent.body.tab[0].p1.y + hauteur_camera) {
            camera_y -= vitesse_camera;
          }

          if (camera_z < serpent.body.tab[0].p1.z + distance_camera_tete) {
            camera_z += vitesse_camera;
          }
          else if (camera_z > serpent.body.tab[0].p1.z + distance_camera_tete) {
            camera_z -= vitesse_camera;
          }

          gluLookAt(camera_x, camera_y, camera_z, 
                  serpent.body.tab[0].p1.x, serpent.body.tab[0].p1.y, serpent.body.tab[0].p1.z,
                  0, 1, 0);
        }

        else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x &&
                 serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
                 serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z - 2 &&
                 serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x &&
                 serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
                 serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z - 2) {

          if (camera_x < serpent.body.tab[0].p1.x) {
            camera_x += vitesse_camera;
          }
          else if (camera_x > serpent.body.tab[0].p1.x) {
            camera_x -= vitesse_camera;
          }

          if (camera_y < serpent.body.tab[0].p1.y + hauteur_camera) {
            camera_y += vitesse_camera;
          }
          else if (camera_y > serpent.body.tab[0].p1.y + hauteur_camera) {
            camera_y -= vitesse_camera;
          }

          if (camera_z < serpent.body.tab[0].p1.z - distance_camera_tete) {
            camera_z += vitesse_camera;
          }
          else if (camera_z > serpent.body.tab[0].p1.z - distance_camera_tete) {
            camera_z -= vitesse_camera;
          }

          gluLookAt(camera_x, camera_y, camera_z, 
                  serpent.body.tab[0].p1.x, serpent.body.tab[0].p1.y, serpent.body.tab[0].p1.z,
                  0, 1, 0);
        }

        else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x - 2 &&
                 serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
                 serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
                 serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x - 2 &&
                 serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
                 serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z) {

          if (camera_x < serpent.body.tab[0].p1.x - distance_camera_tete) {
            camera_x += vitesse_camera;
          }
          else if (camera_x > serpent.body.tab[0].p1.x - distance_camera_tete) {
            camera_x -= vitesse_camera;
          }

          if (camera_y < serpent.body.tab[0].p1.y + hauteur_camera) {
            camera_y += vitesse_camera;
          }
          else if (camera_y > serpent.body.tab[0].p1.y + hauteur_camera) {
            camera_y -= vitesse_camera;
          }

          if (camera_z < serpent.body.tab[0].p1.z) {
            camera_z += vitesse_camera;
          }
          else if (camera_z > serpent.body.tab[0].p1.z) {
            camera_z -= vitesse_camera;
          }

          gluLookAt(camera_x, camera_y, camera_z, 
                  serpent.body.tab[0].p1.x, serpent.body.tab[0].p1.y, serpent.body.tab[0].p1.z,
                  0, 1, 0);
        }

        else if (serpent.body.tab[1].p1.x == serpent.body.tab[0].p1.x + 2 &&
                 serpent.body.tab[1].p1.y == serpent.body.tab[0].p1.y &&
                 serpent.body.tab[1].p1.z == serpent.body.tab[0].p1.z &&
                 serpent.body.tab[1].p2.x == serpent.body.tab[0].p2.x + 2 &&
                 serpent.body.tab[1].p2.y == serpent.body.tab[0].p2.y &&
                 serpent.body.tab[1].p2.z == serpent.body.tab[0].p2.z) {

          if (camera_x < serpent.body.tab[0].p1.x + distance_camera_tete) {
            camera_x += vitesse_camera;
          }
          else if (camera_x > serpent.body.tab[0].p1.x + distance_camera_tete) {
            camera_x -= vitesse_camera;
          }

          if (camera_y < serpent.body.tab[0].p1.y + hauteur_camera) {
            camera_y += vitesse_camera;
          }
          else if (camera_y > serpent.body.tab[0].p1.y + hauteur_camera) {
            camera_y -= vitesse_camera;
          }

          if (camera_z < serpent.body.tab[0].p1.z) {
            camera_z += vitesse_camera;
          }
          else if (camera_z > serpent.body.tab[0].p1.z) {
            camera_z -= vitesse_camera;
          }

          gluLookAt(camera_x, camera_y, camera_z, 
                  serpent.body.tab[0].p1.x, serpent.body.tab[0].p1.y, serpent.body.tab[0].p1.z,
                  0, 1, 0);
        }
      }

      /* Caméra plan 2 */
      else if (p.p1.x == plan2.p1.x &&
               p.p1.y == plan2.p1.y &&
               p.p1.z == plan2.p1.z &&
               p.p2.x == plan2.p2.x &&
               p.p2.y == plan2.p2.y &&
               p.p2.z == plan2.p2.z &&
               p.p3.x == plan2.p3.x &&
               p.p3.y == plan2.p3.y &&
               p.p3.z == plan2.p3.z) {
        if (serpent.body.tab[0].p1.y == serpent.body.tab[1].p1.y &&
            serpent.body.tab[0].p1.z < serpent.body.tab[1].p1.z) {

          if (camera_x < serpent.body.tab[0].p1.x + hauteur_camera) {
            camera_x += vitesse_camera;
          }
          else if (camera_x > serpent.body.tab[0].p1.x + hauteur_camera) {
            camera_x -= vitesse_camera;
          }

          if (camera_y < serpent.body.tab[0].p1.y) {
            camera_y += vitesse_camera;
          }
          else if (camera_y > serpent.body.tab[0].p1.y) {
            camera_y -= vitesse_camera;
          }

          if (camera_z < serpent.body.tab[0].p1.z + distance_camera_tete) {
            camera_z += vitesse_camera;
          }
          else if (camera_z > serpent.body.tab[0].p1.z + distance_camera_tete) {
            camera_z -= vitesse_camera;
          }

          gluLookAt(camera_x, camera_y, camera_z,
                  serpent.body.tab[0].p1.x, serpent.body.tab[0].p1.y, serpent.body.tab[0].p1.z,
                  1, 0, 0);
        }
        else if (serpent.body.tab[0].p1.y == serpent.body.tab[1].p1.y &&
                 serpent.body.tab[0].p1.z > serpent.body.tab[1].p1.z) {

          if (camera_x < serpent.body.tab[0].p1.x + hauteur_camera) {
            camera_x += vitesse_camera;
          }
          else if (camera_x > serpent.body.tab[0].p1.x + hauteur_camera) {
            camera_x -= vitesse_camera;
          }

          if (camera_y < serpent.body.tab[0].p1.y) {
            camera_y += vitesse_camera;
          }
          else if (camera_y > serpent.body.tab[0].p1.y) {
            camera_y -= vitesse_camera;
          }

          if (camera_z < serpent.body.tab[0].p1.z - distance_camera_tete) {
            camera_z += vitesse_camera;
          }
          else if (camera_z > serpent.body.tab[0].p1.z - distance_camera_tete) {
            camera_z -= vitesse_camera;
          }

          gluLookAt(camera_x, camera_y, camera_z,
                  serpent.body.tab[0].p1.x, serpent.body.tab[0].p1.y, serpent.body.tab[0].p1.z,
                  1, 0, 0);
        }
        else if (serpent.body.tab[0].p1.y < serpent.body.tab[1].p1.y &&
                 serpent.body.tab[0].p1.z == serpent.body.tab[0].p1.z) {

          if (camera_x < serpent.body.tab[0].p1.x + hauteur_camera) {
            camera_x += vitesse_camera;
          }
          else if (camera_x > serpent.body.tab[0].p1.x + hauteur_camera) {
            camera_x -= vitesse_camera;
          }

          if (camera_y < serpent.body.tab[0].p1.y + distance_camera_tete) {
            camera_y += vitesse_camera;
          }
          else if (camera_y > serpent.body.tab[0].p1.y + distance_camera_tete) {
            camera_y -= vitesse_camera;
          }

          if (camera_z < serpent.body.tab[0].p1.z) {
            camera_z += vitesse_camera;
          }
          else if (camera_z > serpent.body.tab[0].p1.z) {
            camera_z -= vitesse_camera;
          }

          gluLookAt(camera_x, camera_y, camera_z,
                  serpent.body.tab[0].p1.x, serpent.body.tab[0].p1.y, serpent.body.tab[0].p1.z,
                  1, 0, 0);
        }
        else if (serpent.body.tab[0].p1.y > serpent.body.tab[1].p1.y &&
                 serpent.body.tab[0].p1.z == serpent.body.tab[0].p1.z) {

          if (camera_x < serpent.body.tab[0].p1.x + hauteur_camera) {
            camera_x += vitesse_camera;
          }
          else if (camera_x > serpent.body.tab[0].p1.x + hauteur_camera) {
            camera_x -= vitesse_camera;
          }

          if (camera_y < serpent.body.tab[0].p1.y - distance_camera_tete) {
            camera_y += vitesse_camera;
          }
          else if (camera_y > serpent.body.tab[0].p1.y - distance_camera_tete) {
            camera_y -= vitesse_camera;
          }

          if (camera_z < serpent.body.tab[0].p1.z) {
            camera_z += vitesse_camera;
          }
          else if (camera_z > serpent.body.tab[0].p1.z) {
            camera_z -= vitesse_camera;
          }

          gluLookAt(camera_x, camera_y, camera_z,
                  serpent.body.tab[0].p1.x, serpent.body.tab[0].p1.y, serpent.body.tab[0].p1.z,
                  1, 0, 0);
        }
      }

      /* Caméra plan 3 */
      else if (p.p1.x == plan3.p1.x &&
               p.p1.y == plan3.p1.y &&
               p.p1.z == plan3.p1.z &&
               p.p2.x == plan3.p2.x &&
               p.p2.y == plan3.p2.y &&
               p.p2.z == plan3.p2.z &&
               p.p3.x == plan3.p3.x &&
               p.p3.y == plan3.p3.y &&
               p.p3.z == plan3.p3.z) {
        if (serpent.body.tab[0].p1.x == serpent.body.tab[1].p1.x &&
            serpent.body.tab[0].p1.y > serpent.body.tab[1].p1.y) {

          if (camera_x < serpent.body.tab[0].p1.x) {
            camera_x += vitesse_camera;
          }
          else if (camera_x > serpent.body.tab[0].p1.x) {
            camera_x -= vitesse_camera;
          }

          if (camera_y < serpent.body.tab[0].p1.y - distance_camera_tete) {
            camera_y += vitesse_camera;
          }
          else if (camera_y > serpent.body.tab[0].p1.y - distance_camera_tete) {
            camera_y -= vitesse_camera;
          }

          if (camera_z < serpent.body.tab[0].p1.z + hauteur_camera) {
            camera_z += vitesse_camera;
          }
          else if (camera_z > serpent.body.tab[0].p1.z + hauteur_camera) {
            camera_z -= vitesse_camera;
          }

          gluLookAt(camera_x, camera_y, camera_z,
                  serpent.body.tab[0].p1.x, serpent.body.tab[0].p1.y, serpent.body.tab[0].p1.z,
                  0, 0, 1);
        }
        else if (serpent.body.tab[0].p1.x == serpent.body.tab[1].p1.x &&
                 serpent.body.tab[0].p1.y < serpent.body.tab[1].p1.y) {

          if (camera_x < serpent.body.tab[0].p1.x) {
            camera_x += vitesse_camera;
          }
          else if (camera_x > serpent.body.tab[0].p1.x) {
            camera_x -= vitesse_camera;
          }

          if (camera_y < serpent.body.tab[0].p1.y + distance_camera_tete) {
            camera_y += vitesse_camera;
          }
          else if (camera_y > serpent.body.tab[0].p1.y + distance_camera_tete) {
            camera_y -= vitesse_camera;
          }

          if (camera_z < serpent.body.tab[0].p1.z + hauteur_camera) {
            camera_z += vitesse_camera;
          }
          else if (camera_z > serpent.body.tab[0].p1.z + hauteur_camera) {
            camera_z -= vitesse_camera;
          }

          gluLookAt(camera_x, camera_y, camera_z,
                  serpent.body.tab[0].p1.x, serpent.body.tab[0].p1.y, serpent.body.tab[0].p1.z,
                  0, 0, 1);
        }
        else if (serpent.body.tab[0].p1.x < serpent.body.tab[1].p1.x &&
                 serpent.body.tab[0].p1.y == serpent.body.tab[0].p1.y) {

          if (camera_x < serpent.body.tab[0].p1.x + distance_camera_tete) {
            camera_x += vitesse_camera;
          }
          else if (camera_x > serpent.body.tab[0].p1.x + distance_camera_tete) {
            camera_x -= vitesse_camera;
          }

          if (camera_y < serpent.body.tab[0].p1.y) {
            camera_y += vitesse_camera;
          }
          else if (camera_y > serpent.body.tab[0].p1.y) {
            camera_y -= vitesse_camera;
          }

          if (camera_z < serpent.body.tab[0].p1.z + hauteur_camera) {
            camera_z += vitesse_camera;
          }
          else if (camera_z > serpent.body.tab[0].p1.z + hauteur_camera) {
            camera_z -= vitesse_camera;
          }

          gluLookAt(camera_x, camera_y, camera_z,
                  serpent.body.tab[0].p1.x, serpent.body.tab[0].p1.y, serpent.body.tab[0].p1.z,
                  0, 0, 1);
        }
        else if (serpent.body.tab[0].p1.x > serpent.body.tab[1].p1.x &&
                 serpent.body.tab[0].p1.y == serpent.body.tab[0].p1.y) {

          if (camera_x < serpent.body.tab[0].p1.x - distance_camera_tete) {
            camera_x += vitesse_camera;
          }
          else if (camera_x > serpent.body.tab[0].p1.x - distance_camera_tete) {
            camera_x -= vitesse_camera;
          }

          if (camera_y < serpent.body.tab[0].p1.y) {
            camera_y += vitesse_camera;
          }
          else if (camera_y > serpent.body.tab[0].p1.y) {
            camera_y -= vitesse_camera;
          }

          if (camera_z < serpent.body.tab[0].p1.z + hauteur_camera) {
            camera_z += vitesse_camera;
          }
          else if (camera_z > serpent.body.tab[0].p1.z + hauteur_camera) {
            camera_z -= vitesse_camera;
          }

          gluLookAt(camera_x, camera_y, camera_z,
                  serpent.body.tab[0].p1.x, serpent.body.tab[0].p1.y, serpent.body.tab[0].p1.z,
                  0, 0, 1);
        }
      }
    }

    /* Dessiner plans */
    /* On affiche que le plan actif dans le mode 3D */
    if (mode_affichage == MODE_3D) {
      if (p.p1.x == plan1.p1.x &&
          p.p1.y == plan1.p1.y &&
          p.p1.z == plan1.p1.z &&
          p.p2.x == plan1.p2.x &&
          p.p2.y == plan1.p2.y &&
          p.p2.z == plan1.p2.z &&
          p.p3.x == plan1.p3.x &&
          p.p3.y == plan1.p3.y &&
          p.p3.z == plan1.p3.z) {
        dessiner_plan(plan1, 9, 106, 9);
      }
      
      else if (p.p1.x == plan2.p1.x &&
               p.p1.y == plan2.p1.y &&
               p.p1.z == plan2.p1.z &&
               p.p2.x == plan2.p2.x &&
               p.p2.y == plan2.p2.y &&
               p.p2.z == plan2.p2.z &&
               p.p3.x == plan2.p3.x &&
               p.p3.y == plan2.p3.y &&
               p.p3.z == plan2.p3.z) {
        dessiner_plan(plan2, 148, 129, 43);
      }
      else if (p.p1.x == plan3.p1.x &&
               p.p1.y == plan3.p1.y &&
               p.p1.z == plan3.p1.z &&
               p.p2.x == plan3.p2.x &&
               p.p2.y == plan3.p2.y &&
               p.p2.z == plan3.p2.z &&
               p.p3.x == plan3.p3.x &&
               p.p3.y == plan3.p3.y &&
               p.p3.z == plan3.p3.z) {
        dessiner_plan(plan3, 86, 130, 3);
      }
    }

    /* On affiche tous les plans dans les autres modes d'affichage */
    else {
      dessiner_plan(plan1, 9, 106, 9);
      dessiner_plan(plan2, 148, 129, 43);
      dessiner_plan(plan3, 86, 130, 3);
    }

    /* Dessiner serpent */
    for (int i = 0; i < serpent.body.longueur; i++) {
      /* Dessiner la tête en utilisant une couleur différente */
      if (i % 2 == 0) {
        dessiner_cube(serpent.body.tab[i], 44, 3, 11);
      }
      else {
        dessiner_cube(serpent.body.tab[i], 63, 34, 4);
      }
    }

    /* Test permettant de vérifier que la nourriture ne soit pas 
       au dessus des obstacles */
    if (test == 0) {
      /* Plan1 */
      for (int i = 0; i < NB_OBSTACLES_P1; i++) {
        if (nourriture1.p1.x == obs_p1[i].p1.x &&
            nourriture1.p1.y == obs_p1[i].p1.y &&
            nourriture1.p1.z == obs_p1[i].p1.z) {
          if (nourriture1.p1.x > (plan1.p1.x + plan1.p2.x) / 2) {
            obs_p1[i].p1.x -= 4;
            obs_p1[i].p2.x -= 4;
          }
          else {
            obs_p1[i].p1.x += 4;
            obs_p1[i].p2.x += 4;
          }
        }
      }

      /* Plan2 */
      for (int i = 0; i < NB_OBSTACLES_P2; i++) {
        if (nourriture2.p1.x == obs_p2[i].p1.x &&
            nourriture2.p1.y == obs_p2[i].p1.y &&
            nourriture2.p1.z == obs_p2[i].p1.z) {
          if (nourriture2.p1.y > (plan2.p1.y + plan2.p2.y) / 2) {
            obs_p2[i].p1.y -= 4;
            obs_p2[i].p2.y -= 4;
          }
          else {
            obs_p2[i].p1.y += 4;
            obs_p2[i].p2.y += 4;
          }
        }
      }

      /* Plan3 */
      for (int i = 0; i < NB_OBSTACLES_P3; i++) {
        if (nourriture3.p1.x == obs_p3[i].p1.x &&
            nourriture3.p1.y == obs_p3[i].p1.y &&
            nourriture3.p1.z == obs_p3[i].p1.z) {
          if (nourriture3.p1.y > (plan3.p1.y + plan3.p3.y) / 2) {
            obs_p3[i].p1.y -= 4;
            obs_p3[i].p2.y -= 4;
          }
          else {
            obs_p3[i].p1.y += 4;
            obs_p3[i].p2.y += 4;
          }
        }
      }
      test = 1;
    }

    /* Dessiner nourriture */
    if (mode_affichage == MODE_2D_2) {
      if (p.p1.x == plan1.p1.x &&
          p.p1.y == plan1.p1.y &&
          p.p1.z == plan1.p1.z &&
          p.p2.x == plan1.p2.x &&
          p.p2.y == plan1.p2.y &&
          p.p2.z == plan1.p2.z &&
          p.p3.x == plan1.p3.x &&
          p.p3.y == plan1.p3.y &&
          p.p3.z == plan1.p3.z) {
        dessiner_cube(nourriture1, 3, 34, 76);
      }
      
      else if (p.p1.x == plan2.p1.x &&
               p.p1.y == plan2.p1.y &&
               p.p1.z == plan2.p1.z &&
               p.p2.x == plan2.p2.x &&
               p.p2.y == plan2.p2.y &&
               p.p2.z == plan2.p2.z &&
               p.p3.x == plan2.p3.x &&
               p.p3.y == plan2.p3.y &&
               p.p3.z == plan2.p3.z) {
        dessiner_cube(nourriture2, 6, 119, 144);
      }
      else if (p.p1.x == plan3.p1.x &&
               p.p1.y == plan3.p1.y &&
               p.p1.z == plan3.p1.z &&
               p.p2.x == plan3.p2.x &&
               p.p2.y == plan3.p2.y &&
               p.p2.z == plan3.p2.z &&
               p.p3.x == plan3.p3.x &&
               p.p3.y == plan3.p3.y &&
               p.p3.z == plan3.p3.z) {
        dessiner_cube(nourriture3, 150, 131, 236);
      }
    }

    else {
      dessiner_cube(nourriture1, 3, 34, 76);
      dessiner_cube(nourriture2, 6, 119, 144);
      dessiner_cube(nourriture3, 150, 131, 236);
    }

    /* Dessiner obstacles */
    if (mode_affichage == MODE_2D_2) {
      if (p.p1.x == plan1.p1.x &&
          p.p1.y == plan1.p1.y &&
          p.p1.z == plan1.p1.z &&
          p.p2.x == plan1.p2.x &&
          p.p2.y == plan1.p2.y &&
          p.p2.z == plan1.p2.z &&
          p.p3.x == plan1.p3.x &&
          p.p3.y == plan1.p3.y &&
          p.p3.z == plan1.p3.z) {
        for (int i = 0; i < NB_OBSTACLES_P1; i++) {
        dessiner_cube(obs_p1[i], 243, 214, 23);
        }
      }
      
      else if (p.p1.x == plan2.p1.x &&
               p.p1.y == plan2.p1.y &&
               p.p1.z == plan2.p1.z &&
               p.p2.x == plan2.p2.x &&
               p.p2.y == plan2.p2.y &&
               p.p2.z == plan2.p2.z &&
               p.p3.x == plan2.p3.x &&
               p.p3.y == plan2.p3.y &&
               p.p3.z == plan2.p3.z) {
        for (int i = 0; i < NB_OBSTACLES_P2; i++) {
        dessiner_cube(obs_p2[i], 243, 214, 23);
        }
      }
      else if (p.p1.x == plan3.p1.x &&
               p.p1.y == plan3.p1.y &&
               p.p1.z == plan3.p1.z &&
               p.p2.x == plan3.p2.x &&
               p.p2.y == plan3.p2.y &&
               p.p2.z == plan3.p2.z &&
               p.p3.x == plan3.p3.x &&
               p.p3.y == plan3.p3.y &&
               p.p3.z == plan3.p3.z) {
        for (int i = 0; i < NB_OBSTACLES_P3; i++) {
        dessiner_cube(obs_p3[i], 243, 214, 23);
        }
      }
    }

    else {
      for (int i = 0; i < NB_OBSTACLES_P1; i++) {
        dessiner_cube(obs_p1[i], 243, 214, 23);
      }
      for (int i = 0; i < NB_OBSTACLES_P2; i++) {
        dessiner_cube(obs_p2[i], 243, 214, 23);
      }
      for (int i = 0; i < NB_OBSTACLES_P3; i++) {
        dessiner_cube(obs_p3[i], 243, 214, 23);
      }
    }

    /* On teste si la tête du serpent a touché un obstacle du plan 1 */
    if (p.p1.x == plan1.p1.x &&
        p.p1.y == plan1.p1.y &&
        p.p1.z == plan1.p1.z &&
        p.p2.x == plan1.p2.x &&
        p.p2.y == plan1.p2.y &&
        p.p2.z == plan1.p2.z &&
        p.p3.x == plan1.p3.x &&
        p.p3.y == plan1.p3.y &&
        p.p3.z == plan1.p3.z) {
      for (int i = 0; i < NB_OBSTACLES_P1; i++) {
        if (serpent.body.tab[0].p1.x == obs_p1[i].p1.x &&
            serpent.body.tab[0].p1.y == obs_p1[i].p1.y &&
            serpent.body.tab[0].p1.z == obs_p1[i].p1.z &&
            serpent.body.tab[0].p2.x == obs_p1[i].p2.x &&
            serpent.body.tab[0].p2.y == obs_p1[i].p2.y &&
            serpent.body.tab[0].p2.z == obs_p1[i].p2.z) {
          menu = 2;
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
      }
    }

    /* On teste si la tête du serpent a touché un obstacle du plan 2 */
    else if (p.p1.x == plan2.p1.x &&
             p.p1.y == plan2.p1.y &&
             p.p1.z == plan2.p1.z &&
             p.p2.x == plan2.p2.x &&
             p.p2.y == plan2.p2.y &&
             p.p2.z == plan2.p2.z &&
             p.p3.x == plan2.p3.x &&
             p.p3.y == plan2.p3.y &&
             p.p3.z == plan2.p3.z) {
      for (int i = 0; i < NB_OBSTACLES_P2; i++) {
        if (serpent.body.tab[0].p1.x == obs_p2[i].p1.x &&
            serpent.body.tab[0].p1.y == obs_p2[i].p1.y &&
            serpent.body.tab[0].p1.z == obs_p2[i].p1.z &&
            serpent.body.tab[0].p2.x == obs_p2[i].p2.x &&
            serpent.body.tab[0].p2.y == obs_p2[i].p2.y &&
            serpent.body.tab[0].p2.z == obs_p2[i].p2.z) {
          menu = 2;
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
      }
    }

    /* On teste si la tête du serpent a touché un obstacle du plan 3 */
    else if (p.p1.x == plan3.p1.x &&
             p.p1.y == plan3.p1.y &&
             p.p1.z == plan3.p1.z &&
             p.p2.x == plan3.p2.x &&
             p.p2.y == plan3.p2.y &&
             p.p2.z == plan3.p2.z &&
             p.p3.x == plan3.p3.x &&
             p.p3.y == plan3.p3.y &&
             p.p3.z == plan3.p3.z) {
      for (int i = 0; i < NB_OBSTACLES_P3; i++) {
        if (serpent.body.tab[0].p1.x == obs_p3[i].p1.x &&
            serpent.body.tab[0].p1.y == obs_p3[i].p1.y &&
            serpent.body.tab[0].p1.z == obs_p3[i].p1.z &&
            serpent.body.tab[0].p2.x == obs_p3[i].p2.x &&
            serpent.body.tab[0].p2.y == obs_p3[i].p2.y &&
            serpent.body.tab[0].p2.z == obs_p3[i].p2.z) {
          menu = 2;
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
      }
    }

    /* On teste si la tête du serpent a touché la nourriture plan 1 */
    if (p.p1.x == plan1.p1.x &&
        p.p1.y == plan1.p1.y &&
        p.p1.z == plan1.p1.z &&
        p.p2.x == plan1.p2.x &&
        p.p2.y == plan1.p2.y &&
        p.p2.z == plan1.p2.z &&
        p.p3.x == plan1.p3.x &&
        p.p3.y == plan1.p3.y &&
        p.p3.z == plan1.p3.z) {
      if (serpent.body.tab[0].p1.x == nourriture1.p1.x &&
          serpent.body.tab[0].p1.y == nourriture1.p1.y &&
          serpent.body.tab[0].p1.z == nourriture1.p1.z &&
          serpent.body.tab[0].p2.x == nourriture1.p2.x &&
          serpent.body.tab[0].p2.y == nourriture1.p2.y &&
          serpent.body.tab[0].p2.z == nourriture1.p2.z) {
        serpent.body.longueur++;

        /* On donne une nouvelle position à la nourriture */
        nourriture_serpent_plan1();
        score++;
      }
    }

    /* On teste si la tête du serpent a touché la nourriture plan 2 */
    else if (p.p1.x == plan2.p1.x &&
             p.p1.y == plan2.p1.y &&
             p.p1.z == plan2.p1.z &&
             p.p2.x == plan2.p2.x &&
             p.p2.y == plan2.p2.y &&
             p.p2.z == plan2.p2.z &&
             p.p3.x == plan2.p3.x &&
             p.p3.y == plan2.p3.y &&
             p.p3.z == plan2.p3.z) {
      if (serpent.body.tab[0].p1.x == nourriture2.p1.x &&
          serpent.body.tab[0].p1.y == nourriture2.p1.y &&
          serpent.body.tab[0].p1.z == nourriture2.p1.z &&
          serpent.body.tab[0].p2.x == nourriture2.p2.x &&
          serpent.body.tab[0].p2.y == nourriture2.p2.y &&
          serpent.body.tab[0].p2.z == nourriture2.p2.z) {
        serpent.body.longueur++;

        nourriture_serpent_plan2();
        score++;
      }
    }

    /* On teste si la tête du serpent a touché la nourriture plan 3 */
    else if (p.p1.x == plan3.p1.x &&
             p.p1.y == plan3.p1.y &&
             p.p1.z == plan3.p1.z &&
             p.p2.x == plan3.p2.x &&
             p.p2.y == plan3.p2.y &&
             p.p2.z == plan3.p2.z &&
             p.p3.x == plan3.p3.x &&
             p.p3.y == plan3.p3.y &&
             p.p3.z == plan3.p3.z) {
      if (serpent.body.tab[0].p1.x == nourriture3.p1.x &&
          serpent.body.tab[0].p1.y == nourriture3.p1.y &&
          serpent.body.tab[0].p1.z == nourriture3.p1.z &&
          serpent.body.tab[0].p2.x == nourriture3.p2.x &&
          serpent.body.tab[0].p2.y == nourriture3.p2.y &&
          serpent.body.tab[0].p2.z == nourriture3.p2.z) {
        serpent.body.longueur++;

        nourriture_serpent_plan3();
        score++;
      }
    }

    /* Affichage score */
    score1 = score;
    char texte1[9] = {'S', 'c', 'o', 'r', 'e', ' ', ':', ' '};
    texte1[8] = score + '0';
    glColor3f(0, 1, 0);
    afficher_texte(texte1, 9, 0, 0);

    /* On teste s'il y a une collision */
    for (int i = 1; i < serpent.body.longueur; i++) {
      if (serpent.body.tab[0].p1.x == serpent.body.tab[i].p1.x &&
          serpent.body.tab[0].p1.y == serpent.body.tab[i].p1.y &&
          serpent.body.tab[0].p1.z == serpent.body.tab[i].p1.z &&
          serpent.body.tab[0].p2.x == serpent.body.tab[i].p2.x &&
          serpent.body.tab[0].p2.y == serpent.body.tab[i].p2.y &&
          serpent.body.tab[0].p2.z == serpent.body.tab[i].p2.z) {
        menu = 2;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      }
    }

    /* Permettre l'avancé continue du serpent */
    avancer();
    usleep(vitesse);
  }

  glutSwapBuffers();
}

/* Fonction permettant de gérer les évenements d'appuie 
   sur l'un des touches de direction du clavier */
void SpecialKey(int touche, int x, int y) {
  switch(touche) {
    case GLUT_KEY_UP:
      if (menu == -1) {
        if (mode_affichage == MODE_2D_1 || mode_affichage == MODE_2D_2) {
          mouvement_haut();
        }
      }
      break;

    case GLUT_KEY_DOWN:
      if (menu == -1) {
        if (mode_affichage == MODE_2D_1 || mode_affichage == MODE_2D_2) {
          mouvement_bas();
        }
      }
      break;

    case GLUT_KEY_LEFT:
      if (menu == -1) {
        if (mode_affichage == MODE_3D) {
          mouvement_gauche_3d();
        }
        else if (mode_affichage == MODE_2D_1 || mode_affichage == MODE_2D_2) {
          mouvement_gauche();
        }
      }
      break;

    case GLUT_KEY_RIGHT:
      if (menu == -1) {
        if (mode_affichage == MODE_3D) {
          mouvement_droite_3d();
        }
        else if (mode_affichage == MODE_2D_1 || mode_affichage == MODE_2D_2) {
          mouvement_droite();
        }
      }
      break;

    case GLUT_KEY_PAGE_UP:
      if (menu == -1) {
        if (vitesse > 40000) {
          vitesse -= 10000;
        }
      }
      break;

    case GLUT_KEY_PAGE_DOWN:
      if (menu == -1) {
        if (vitesse < 120000) {
          vitesse += 10000;
        }
      }
      break;

    case GLUT_KEY_F1:
      if (menu == -1) {
        mode_affichage = MODE_2D_1;
      }
      break;

    case GLUT_KEY_F2:
      if (menu == -1) {
        mode_affichage = MODE_2D_2;
      }
      break;

    case GLUT_KEY_F3:
      if (menu == -1) {
        mode_affichage = MODE_3D;
      }
      break;

    case GLUT_KEY_F4:
      if (menu == 1) {
        menu = -1;
      }
      break;
  }
}