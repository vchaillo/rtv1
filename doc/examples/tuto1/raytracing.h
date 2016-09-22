/***************************************************************************

                          raytracing.h  -  Raytracing
                          ---------------------------
    Commencé le          : Fri Dec 7 2001
    Copyright            : (C) 2001 by David Fernandes
    Email                : mchepoil@caramail.com
    Site                 : http://www.multimania.com/davvador2416

 ***************************************************************************/


#ifndef __raytracing_h
#define __raytracing_h

#include "infos_compilation.h"
#include "util.h"
#include "3d.h"
#include "import.h"
#include <math.h>
#include <string.h>

#define Max_Alpha 655350


void unitaire(vecteur_3D *v);

float scal(vecteur_3D *v1, vecteur_3D *v2);

float intersection(point_3D pt, vecteur_3D V, unsigned short int *obj);

couleur calcul_rayon(float x, float y);

void no_antialiasing();

couleur lancer_rayon(point_3D pt, vecteur_3D V);

void sauvegarder(char *chemin);

#endif // __raytracing_h

