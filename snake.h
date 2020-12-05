#ifndef _K_SNAKE_H_
#define _K_SNAKE_H_

#define MODE_2D_1 1
#define MODE_2D_2 2
#define MODE_3D 3

#define NB_OBSTACLES_P1 10
#define NB_OBSTACLES_P2 10
#define NB_OBSTACLES_P3 10

/* Structure permettant de définir un point */
typedef struct point {
	int x;
  	int y;
  	int z;
}struct_point;

typedef struct_point point;

/* Structure permettant de définir la tête du serpent */
typedef struct tete {
  	point p1;
  	point p2;
}struct_tete;

typedef struct_tete tete;

/* Structure permettant de définir le corps du serpent */
typedef struct corps {
	/* tab[0] --> tête, le reste est le corps du snake */
	tete tab[10000];
	int longueur;
}struct_corps;

typedef struct_corps corps;

/* Structure permettant de définir le serpent */
typedef struct snake {
	corps body;
}struct_snake;

typedef struct_snake snake;

/* Structure permettant de définir le plan */
typedef struct plan {
	point p1;
	point p2;
	point p3;
	point p4;
}struct_plan;

typedef struct_plan plan;

/* Déclaration Snake + Nourriture + Plan + Obstacles */
snake serpent;
tete nourriture1;
tete nourriture2;
tete nourriture3;
tete obs_p1[NB_OBSTACLES_P1];
tete obs_p2[NB_OBSTACLES_P2];
tete obs_p3[NB_OBSTACLES_P3];
plan plan1;
plan plan2;
plan plan3;

/* Caméra */
int camera_x;
int camera_y;
int camera_z;
int hauteur_camera;
int distance_camera_tete;

void dessiner_plan (plan p, int r, int v, int b);
void dessiner_cube (tete cube, int r, int v, int b);
void initialisation_serpent ();
void afficher_texte (const char *text, int length, int x, int y);
void obstacles_plan1 ();
void obstacles_plan2 ();
void obstacles_plan3 ();
void Affichage ();
void nourriture_serpent_plan1 ();
void nourriture_serpent_plan2 ();
void nourriture_serpent_plan3 ();
void avancer ();
void mouvement_gauche_3d ();
void mouvement_droite_3d ();
void mouvement_haut ();
void mouvement_bas ();
void mouvement_gauche ();
void mouvement_droite ();
void SpecialKey(int touche, int x, int y);

#endif