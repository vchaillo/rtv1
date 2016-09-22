/***************************************************************************

                          antialiasing.h  -  Raytracing
                          -----------------------------
    Commencé le          : Sat Jan 02 2002
    Copyright            : (C) 2002 by David Fernandes
    Email                : mchepoil@caramail.com
    Site                 : http://www.multimania/davvador2416

 ***************************************************************************/


#ifndef __antialiasing_h
#define __antialiasing_h

#include "infos_compilation.h"
#include "3d.h"
#include "raytracing.h"


// Calcul la couleur d'un rayon en rendu normal
couleur calcul_rayon(float x, float y);

// Calcul la couleur d'un rayon en rendu rapide
couleur calcul_rayon_rapide(float x, float y);

// Affichage de l'image sans antialiasing
void no_antialiasing();

// Affichage de l'image en rendu rapide ligne par ligne
void aliasing_ligne();

// Affichage de l'image en rendu rapide écran par écran
void aliasing_ecran();

// Calcul de la couleur d'un rayon avec antialiasing de type flou
couleur point_xy_aa_flou(float x, float y);

// Remplissage de la matrice pour un point avec antialiasing de type flou
void point_aa_flou(short int x, short int y);

// Remplissage d'une ligne dans la matrice avec antialiasing de type flou
void ligne_aa_flou(short int x1, short int x2, short int y);
void ligne_vert_aa_flou(short int y1, short int y2, short int x);

// Affichage de la ligne avec antialiasing de type flou
void calcul_ligne_aa_flou(short int x1, short int x2, short int y);

// Affichage de l'image avec antialiasing de type flou
void antialiasing_flou();

// Affichage de la ligne avec antialiasing (5 rayons par pixels)
void calcul_ligne_aa_5(short int x1, short int x2, short int y);

// Affichage de la ligne avec antialiasing (9 rayons par pixels)
void calcul_ligne_aa_9(short int x1, short int x2, short int y);

// Affichage de l'image avec antialiasing
void antialiasing();

#endif

