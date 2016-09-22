/***************************************************************************
                          3d.h  -  Raytracing
                          -------------------
    Commencé le          : Wed Nov 21 2001
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
   // Coordonnées réelles

   float xr;
   float yr;
   float zr;
} point_3D;

typedef struct
{
    // Coordonnées réelles

    float               vxr;
    float               vyr;
    float               vzr;
} vecteur_3D;

typedef struct
{
    char                    methode;        // Méthode de calcul d'appartenance au polygone
    unsigned long int       sommet[3];      // Numéros des sommets
    float                   equation[4];    // Equation du plan défini par le polygone
    vecteur_3D              *normale;       // Tableau des normales à chacun des sommets
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
    vecteur_3D              *normale;       // Tableau des normales à chacun des sommets
    short int               rot_x,          // Angles de rotation de l'objet
                            rot_y,
                            rot_z;
    unsigned long int       materiau;       // L'indice du matériau
    Ombrage                 ombrage;        // Ombrage à utiliser (plat ou Phong) pour un objet polygonal
    double                  anim[3][4];     // Paramètres de l'animation
} objet;

typedef struct
{
    char                    nom[256];           // Nom de la lumière
    unsigned char           type;               // Type de lumière (0:ambiante, 1:ponctuelle, 2:directionnelle)
    point_3D                position;           // Position ou direction
    couleur                 couleur;            // Couleur de la lumière
    float                   far_attenuation[3]; // Atténuation pour ponctuelle ou intensité pour directionnelle
} lumiere;

typedef struct
{
    char                    nom[256];        // Nom du matériau
    couleur                 coul_amb,        // Couleur ambiante
                            coul_dif,        // Couleur diffuse
                            coul_ref,        // Couleur de réflexion
                            coul_spec;       // Couleur spéculaire
    float                   reflexion,       // Coefficient de réflexion
                            ambiance,        // Coefficient d'ambiance
                            diffusion,       // Coefficient de diffusion
                            specularite,     // Coefficient de spécularité
                            opacite,         // Coefficient d'opacité
                            indice_ref;      // Indice de réfraction
    unsigned char           puis_spec;       // Puissance spéculaire
} materiau;

typedef struct
{
    char                            nom[256],               // Nom de la scène
                                    version[256];           // Version du fichier RTD
    point_3D                        position;               // Position de la caméra
    float                           focale,                 // Distance focale de la caméra
                                    pitch_x,                // Largeur d'un pixel en unités
                                    pitch_y;                // Hauteur d'un pixel en unités
    unsigned char                   antialiasing,           // Type d'antialiasing
                                    iter,                   // Nombre d'itérations dans la réflexion
                                    nb_pix;                 // Nombre de pixels par rayon (pour le rendu rapide)
    bool                            rendu;                  // Type de rendu
    vecteur_3D                      Vx,                     // Repère de la caméra
                                    Vy,
                                    Vz;
    objet                           *objet;                 // Tableau d'objets
    lumiere                         *lumiere;               // Tableau de lumières
    materiau                        *materiau;              // Tableau de matériaux
    unsigned short int              nb_objets,              // Nombre d'objets dans la scène
                                    nb_lumieres,            // Nombre de sources de lumière dans la scène
                                    nb_materiaux,           // Nombre de matériaux dans la scène
                                    res_x,                  // Résolution de l'image
                                    res_y,
                                    rot_x,                  // Angles de rotation de la scène
                                    rot_y,
                                    rot_z;
    couleur                         fond;                   // Couleur de fond
    double                          anim_t[2];              // Paramètres de l'animation (Paramètre t)
    double                          anim[3][4];             // Paramètres de l'animation (Position)
    double                          anim_rot[3][2];         // Paramètres de l'animation (Rotation)
} scene_3D;


// Initialisation des tables de cosinus et sinus
void init_cosinus(void);
void init_sinus(void);

// Désallocation de la scène
void desallocation_scene_3D();

// Rotation d'un point autour de chacun des axes du repère
void point_rotation_x(point_3D *p, short int alpha);
void point_rotation_y(point_3D *p, short int alpha);
void point_rotation_z(point_3D *p, short int alpha);

// Rotation d'un vecteur autour de l'axe des Y
void vecteur_rotation_x(vecteur_3D *V, short int *alpha);
void vecteur_rotation_y(vecteur_3D *V, short int *alpha);
void vecteur_rotation_z(vecteur_3D *V, short int *alpha);

// Effacement de la page vidéo
void effacer_ecran(intensite_couleur *page);


#endif  // __3d_h

