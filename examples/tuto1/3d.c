/***************************************************************************
                             3d.c  -  Raytracing
                             -------------------
    Commencé le          : mer nov 21 14:32:59 CET 2001
    Copyright            : (C) 2001 by Dav Vador
    Email                : mchepoil@caramail.com
    Site                 : http://www.multimania/davvador2416

 ***************************************************************************/



#include "3d.h"

// Page vidéo et d'antialiasing
extern intensite_couleur        *page_tmp,
                                *anti_aliasing;

// La scène à afficher
extern scene_3D                 scene;

// Tables des sinus et cosinus
float sinus[360];
float cosinus[360];


/* Implémentation des fonctions utilisées */

void init_cosinus(void)
{
    register int i;

    for (i=0;i<360;i++)
    cosinus[i]=cos((float)(pi*i)/(float)(180));
}

void init_sinus(void)
{
    register int i;

    for (i=0;i<360;i++)
    sinus[i]=sin((float)(pi*i)/(float)(180));
}

void point_rotation_x(point_3D *p, short int alpha)
{
    float tmp = p->yr;

    alpha %= 360;
    if (alpha < 0) alpha += 360;
    p->yr = tmp*cosinus[alpha] - p->zr*sinus[alpha];
    p->zr = tmp*sinus[alpha] + p->zr*cosinus[alpha];
}

void point_rotation_y(point_3D *p, short int alpha)
{
    float tmp = p->xr;

    alpha %= 360;
    if (alpha < 0) alpha += 360;
    p->xr = tmp*cosinus[alpha] - p->zr*sinus[alpha];
    p->zr = tmp*sinus[alpha] + p->zr*cosinus[alpha];
}

void point_rotation_z(point_3D *p, short int alpha)
{
    float tmp = p->xr;

    alpha %= 360;
    if (alpha < 0) alpha += 360;
    p->xr = tmp*cosinus[alpha] - p->yr*sinus[alpha];
    p->yr = tmp*sinus[alpha] + p->yr*cosinus[alpha];
}


void vecteur_rotation_x(vecteur_3D *V, short int *alpha)
{
    float tmp = V->vyr;

    *alpha %= 360;
    if (*alpha < 0) *alpha += 360;
    V->vyr = tmp*cosinus[*alpha] - V->vzr*sinus[*alpha];
    V->vzr = tmp*sinus[*alpha] + V->vzr*cosinus[*alpha];
}

void vecteur_rotation_y(vecteur_3D *V, short int *alpha)
{
    float tmp = V->vxr;

    *alpha %= 360;
    if (*alpha < 0) *alpha += 360;
    V->vxr = tmp*cosinus[*alpha] - V->vzr*sinus[*alpha];
    V->vzr = tmp*sinus[*alpha] + V->vzr*cosinus[*alpha];
}

void vecteur_rotation_z(vecteur_3D *V, short int *alpha)
{
    float tmp = V->vxr;

    *alpha %= 360;
    if (*alpha < 0) *alpha += 360;
    V->vxr = tmp*cosinus[*alpha] - V->vyr*sinus[*alpha];
    V->vyr = tmp*sinus[*alpha] + V->vyr*cosinus[*alpha];
}

void effacer_ecran(intensite_couleur *page)
{
    long int i;

    for (i=0;i<3*scene.res_x*scene.res_y;i++) page[i]=0;
}

void desallocation_scene_3D()
{       /* Désallocation de la scène */
    unsigned long int i, j;


    // Pour chaque objet
    for (i = 0; i< scene.nb_objets; i++)
    {
        for (j = 0; j< scene.objet[i].nb_polys; j++)
            free(scene.objet[i].poly[j].normale);
        free(scene.objet[i].sommet);
        free(scene.objet[i].poly);
        free(scene.objet[i].normale);
    }

    // On désalloue les objets
    if (scene.objet)
        free(scene.objet);

    // On désalloue les lumières
    if (scene.lumiere)
        free(scene.lumiere);

    // On désalloue les matériaux
    if (scene.materiau)
        free(scene.materiau);

    // On désalloue la page vidéo
    if (page_tmp)
        free(page_tmp);
}


