/***************************************************************************
                          import.h  -  Raytracing & Import_3DS
                          ------------------------------------
    Commencé le          : Wed Nov 21 2001
    Copyright            : (C) 2001 by Dav Vador
    Email                : mchepoil@caramail.com
    Site                 : http://www.multimania.com/davvador2416

 ***************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "3d.h"
#include "infos_compilation.h"


float lire_float_txt(FILE **fichier);

unsigned short int lire_uint32_txt(FILE **fichier);

char lire_char(FILE **fichier);

bool chercher_str_txt(char *str, FILE **fichier);

bool lire_nom_objet_txt(char *nom,FILE **fichier);

void sphere_englobante(scene_3D *scene, unsigned long int obj);

void plan(scene_3D *scene, unsigned long int obj);

void normales(scene_3D *scene, unsigned long int obj);

char format_fichier(char *chemin);

unsigned short int import_ASE(char *chemin, scene_3D *scene, unsigned short int *objet_cour, Ombrage omb, float amb, float dif, float ref, point_3D pos, unsigned char r1, short int a1, unsigned char r2, short int a2, unsigned char r3, short int a3, float ech);

bool import(char *chemin, scene_3D *scene, unsigned short int *objet_cour, Ombrage omb, float amb, float dif, float ref, point_3D pos, unsigned char r1, short int a1, unsigned char r2, short int a2, unsigned char r3, short int a3, float ech);

bool charger_rtd(char *chemin, scene_3D *scene);

