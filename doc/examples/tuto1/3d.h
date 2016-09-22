/***************************************************************************
                          3d.h  -  Raytracing
                          -------------------
    Commenc� le          : Wed Nov 21 2001
    Copyright            : (C) 2001 by Dav Vador
    Email                : mchepoil@caramail.com
    Site                 : http://www.multimania/davvador2416

 ***************************************************************************/


#ifndef __3d_h
#define __3d_h

#include "infos_compilation.h"
#include <stdlib.h>
#include <math.h>


typedef struct
{
    intensite_couleur r,v,b;
} couleur;

typedef enum {Plat, Phong} Ombrage;

typedef struct
{
   // Coordonn�es r�elles

   float xr;
   float yr;
   float zr;
} point_3D;

typedef struct
{
    // Coordonn�es r�elles

    float               vxr;
    float               vyr;
    float               vzr;
} vecteur_3D;

typedef struct
{
    char                    methode;        // M�thode de calcul d'appartenance au polygone
    unsigned long int       sommet[3];      // Num�ros des sommets
    float                   equation[4];    // Equation du plan d�fini par le polygone
    vecteur_3D              *normale;       // Tableau des normales � chacun des sommets
} polygone;

typedef struct
{
    char                    nom[256];       // Nom de l'objet
    unsigned char           type;           // Type de l'objet
    point_3D                centre;         // Centre de la sphere ou coeffs a, b, c
    float                   rayon;          // Rayon de la sphere ou coeff d
    unsigned long int       nb_sommets,     // Nombre de sommets
                            nb_polys;       // Nombre de polygones
    point_3D                *sommet;        // Tableau de sommets
    polygone                *poly;          // Tableau de polygones
    vecteur_3D              *normale;       // Tableau des normales � chacun des sommets
    short int               rot_x,          // Angles de rotation de l'objet
                            rot_y,
                            rot_z;
    unsigned long int       materiau;       // L'indice du mat�riau
    Ombrage                 ombrage;        // Ombrage � utiliser (plat ou Phong) pour un objet polygonal
    double                  anim[3][4];     // Param�tres de l'animation
} objet;

typedef struct
{
    char                    nom[256];           // Nom de la lumi�re
    unsigned char           type;               // Type de lumi�re (0:ambiante, 1:ponctuelle, 2:directionnelle)
    point_3D                position;           // Position ou direction
    couleur                 couleur;            // Couleur de la lumi�re
    float                   far_attenuation[3]; // Att�nuation pour ponctuelle ou intensit� pour directionnelle
} lumiere;

typedef struct
{
    char                    nom[256];        // Nom du mat�riau
    couleur                 coul_amb,        // Couleur ambiante
                            coul_dif,        // Couleur diffuse
                            coul_ref,        // Couleur de r�flexion
                            coul_spec;       // Couleur sp�culaire
    float                   reflexion,       // Coefficient de r�flexion
                            ambiance,        // Coefficient d'ambiance
                            diffusion,       // Coefficient de diffusion
                            specularite,     // Coefficient de sp�cularit�
                            opacite,         // Coefficient d'opacit�
                            indice_ref;      // Indice de r�fraction
    unsigned char           puis_spec;       // Puissance sp�culaire
} materiau;

typedef struct
{
    char                            nom[256],               // Nom de la sc�ne
                                    version[256];           // Version du fichier RTD
    point_3D                        position;               // Position de la cam�ra
    float                           focale,                 // Distance focale de la cam�ra
                                    pitch_x,                // Largeur d'un pixel en unit�s
                                    pitch_y;                // Hauteur d'un pixel en unit�s
    unsigned char                   antialiasing,           // Type d'antialiasing
                                    iter,                   // Nombre d'it�rations dans la r�flexion
                                    nb_pix;                 // Nombre de pixels par rayon (pour le rendu rapide)
    bool                            rendu;                  // Type de rendu
    vecteur_3D                      Vx,                     // Rep�re de la cam�ra
                                    Vy,
                                    Vz;
    objet                           *objet;                 // Tableau d'objets
    lumiere                         *lumiere;               // Tableau de lumi�res
    materiau                        *materiau;              // Tableau de mat�riaux
    unsigned short int              nb_objets,              // Nombre d'objets dans la sc�ne
                                    nb_lumieres,            // Nombre de sources de lumi�re dans la sc�ne
                                    nb_materiaux,           // Nombre de mat�riaux dans la sc�ne
                                    res_x,                  // R�solution de l'image
                                    res_y,
                                    rot_x,                  // Angles de rotation de la sc�ne
                                    rot_y,
                                    rot_z;
    couleur                         fond;                   // Couleur de fond
    double                          anim_t[2];              // Param�tres de l'animation (Param�tre t)
    double                          anim[3][4];             // Param�tres de l'animation (Position)
    double                          anim_rot[3][2];         // Param�tres de l'animation (Rotation)
} scene_3D;


// Initialisation des tables de cosinus et sinus
void init_cosinus(void);
void init_sinus(void);

// D�sallocation de la sc�ne
void desallocation_scene_3D();

// Rotation d'un point autour de chacun des axes du rep�re
void point_rotation_x(point_3D *p, short int alpha);
void point_rotation_y(point_3D *p, short int alpha);
void point_rotation_z(point_3D *p, short int alpha);

// Rotation d'un vecteur autour de l'axe des Y
void vecteur_rotation_x(vecteur_3D *V, short int *alpha);
void vecteur_rotation_y(vecteur_3D *V, short int *alpha);
void vecteur_rotation_z(vecteur_3D *V, short int *alpha);

// Effacement de la page vid�o
void effacer_ecran(intensite_couleur *page);


#endif  // __3d_h

