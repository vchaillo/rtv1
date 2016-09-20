/***************************************************************************
                          import.c  -  Raytracing & Import_3DS
                          ------------------------------------
    Commencé le          : mer nov 21 14:32:59 CET 2001
    Copyright            : (C) 2001 by Dav Vador
    Email                : mchepoil@caramail.com
    Site                 : http://www.multimania.com/davvador2416

 ***************************************************************************/




#include "import.h"

float lire_float_txt(FILE **fichier)
{
    float t;

    fscanf(*fichier,"%f",&t);
    return t;
}

unsigned short int lire_uint32_txt(FILE **fichier)
{
    unsigned long int t;

    fscanf(*fichier,"%lu",&t);
    return t;
}

char lire_char(FILE **fichier)
{
    char tmp;

    fscanf(*fichier,"%c",&tmp);
    return tmp;
}

bool chercher_str_txt(char *str, FILE **fichier)
{
    char ch[256];

    do
        fscanf(*fichier, "%s", ch);
    while ((strcmp(ch, str)) && (!feof(*fichier)));
    if (!feof(*fichier)) return true;
    return false;
}

bool lire_nom_objet_txt(char *nom, FILE **fichier)
{
    unsigned char i;
    lire_char(fichier);
    if ((nom[0]=lire_char(fichier))!='\"') return false;
    i=0;
    do
    {
        i++;
        nom[i]=lire_char(fichier);
    }
    while ((!feof(*fichier)) && (nom[i]!='\"') && (i<255));
    nom[i+1]='\0';
    if ((i<255) && (!feof(*fichier))) return true;
    return false;
}

void sphere_englobante(scene_3D *scene, unsigned long int obj)
{
    float               min_x, max_x,
                        min_y, max_y,
                        min_z, max_z;
    unsigned long int   i;
    point_3D            *som;


    // Initialisation
    min_x = max_x = scene->objet[obj].sommet[0].xr;
    min_y = max_y = scene->objet[obj].sommet[0].yr;
    min_z = max_z = scene->objet[obj].sommet[0].zr;

    som = scene->objet[obj].sommet;

    // Recherche des min et max
    for (i = 1; i < scene->objet[obj].nb_sommets; i++)
    {
        if (som[i].xr < min_x) min_x = som[i].xr;
        else
        {
            if (som[i].xr > max_x) max_x = som[i].xr;
        }
        if (som[i].yr < min_y) min_y = som[i].yr;
        else
        {
            if (som[i].yr > max_y) max_y = som[i].yr;
        }
        if (som[i].zr < min_z) min_z = som[i].zr;
        else
        {
            if (som[i].zr > max_z) max_z = som[i].zr;
        }
    }

    // Calcul de la position de la sphère
    scene->objet[obj].centre.xr = (min_x + max_x) / 2;
    scene->objet[obj].centre.yr = (min_y + max_y) / 2;
    scene->objet[obj].centre.zr = (min_z + max_z) / 2;

    // Calcul du rayon de la sphère
    if ( ((max_x - min_x) >= (max_y - min_y)) && ((max_x - min_x) >= (max_z - min_z)) ) scene->objet[obj].rayon = (max_x - min_x);
    else if ( ((max_y - min_y) >= (max_x - min_x)) && ((max_y - min_y) >= (max_z - min_z)) ) scene->objet[obj].rayon = (max_y - min_y);
        else scene->objet[obj].rayon = (max_z - min_z);
}

void plan(scene_3D *scene, unsigned long int obj)
{
    polygone            *p;
    point_3D            *som;
    unsigned long int   i, j,
                        *somp;
    float               *equation,
                        tmp;


    p = scene->objet[obj].poly;
    som = scene->objet[obj].sommet;

    #ifdef __DEBUG
    printf(" Polygones :\n");
    fflush(stdout);
    #endif

    for (i = 0; i < scene->objet[obj].nb_polys; i++)
    {
        somp = p[i].sommet;
        equation = p[i].equation;
        p[i].methode = -1;

        // Calcul de la méthode
        if (som[somp[1]].xr == som[somp[0]].xr)
        {
            // On échange le point 2 et le point 1
            j = somp[1];
            somp[1] = somp[2];
            somp[2] = j;
        }
        if (som[somp[1]].xr == som[somp[0]].xr)
            p[i].methode = 0;   // L'équation du plan est du type x = cste
        else
        {
            tmp = (som[somp[2]].xr - som[somp[0]].xr) / (som[somp[1]].xr - som[somp[0]].xr);
            if ((som[somp[2]].yr - som[somp[0]].yr - (som[somp[1]].yr - som[somp[0]].yr)*tmp) != 0)
                p[i].methode *= -1;
        }

        // Calcul de l'équation du plan (= aussi la normale pour ombrage plat)
        equation[0] = (som[somp[1]].yr-som[somp[0]].yr)*(som[somp[2]].zr-som[somp[0]].zr)
                    - (som[somp[1]].zr-som[somp[0]].zr)*(som[somp[2]].yr-som[somp[0]].yr);
        equation[1] = (som[somp[1]].zr-som[somp[0]].zr)*(som[somp[2]].xr-som[somp[0]].xr)
                    - (som[somp[1]].xr-som[somp[0]].xr)*(som[somp[2]].zr-som[somp[0]].zr);
        equation[2] = (som[somp[1]].xr-som[somp[0]].xr)*(som[somp[2]].yr-som[somp[0]].yr)
                    - (som[somp[1]].yr-som[somp[0]].yr)*(som[somp[2]].xr-som[somp[0]].xr);
        // On norme le vecteur normal
        equation[3] = sqrt(equation[0]*equation[0] + equation[1]*equation[1] + equation[2]*equation[2]);
        equation[0] /= equation[3];
        equation[1] /= equation[3];
        equation[2] /= equation[3];
        equation[3] = -(equation[0]*som[somp[0]].xr + equation[1]*som[somp[0]].yr + equation[2]*som[somp[0]].zr);

        #ifdef __DEBUG
        printf(" %lu) Méthode : %d\n", i, p[i].methode);
        printf(" %lu) Equation : (%f)X + (%f)Y + (%f)Z + (%f) = 0\n", i, equation[0], equation[1], equation[2], equation[3]);
        fflush(stdout);
        #endif
    }
}

void normales(scene_3D *scene, unsigned long int obj)
{
    polygone            *p;
    point_3D            *som;
    vecteur_3D          N;
    unsigned long int   i, j,
                        nb,
                        *somp;


    // Allocation des normales
    scene->objet[obj].normale = (vecteur_3D *) malloc(scene->objet[obj].nb_sommets*sizeof(vecteur_3D));

    p = scene->objet[obj].poly;
    som = scene->objet[obj].sommet;

    // Normales aux sommets pour ombrage de Phong
    #ifdef __DEBUG
    printf("\n\n");
    fflush(stdout);
    #endif
    for (i = 0; i < scene->objet[obj].nb_sommets; i++)
    {
        // Initialisation de la normale
        N.vxr = 0;
        N.vyr = 0;
        N.vzr = 0;
        nb = 0;

        som = scene->objet[obj].sommet;
        for (j = 0; j < scene->objet[obj].nb_polys; j++)
        {
            somp = scene->objet[obj].poly[j].sommet;
            // Si le sommet appartient au polygone
            if ((somp[0] == i) || (somp[1] == i) || (somp[2] == i))
            {
                N.vxr += scene->objet[obj].poly[j].equation[0];
                N.vyr += scene->objet[obj].poly[j].equation[1];
                N.vzr += scene->objet[obj].poly[j].equation[2];
                nb++;
            }
        }

        // La normale au sommet est égale à la moyenne
        if (nb) scene->objet[obj].normale[i].vxr = N.vxr/nb;
        else scene->objet[obj].normale[i].vxr = 0;
        if (nb) scene->objet[obj].normale[i].vyr = N.vyr/nb;
        else scene->objet[obj].normale[i].vyr = 0;
        if (nb) scene->objet[obj].normale[i].vzr = N.vzr/nb;
        else scene->objet[obj].normale[i].vzr = 0;

        #ifdef __DEBUG
        printf("Normale au sommet %lu : %f %f %f\n", i, scene->objet[obj].normale[i].vxr, scene->objet[obj].normale[i].vyr, scene->objet[obj].normale[i].vzr);
        fflush(stdout);
        #endif
    }
}

char format_fichier(char *chemin)
{
    unsigned short int lg=strlen(chemin);

    if (((chemin[lg-3]=='A') || (chemin[lg-3]=='a')) && ((chemin[lg-2]=='S') || (chemin[lg-2]=='s')) && ((chemin[lg-1]=='E') || (chemin[lg-1]=='e')))
        return 1;

    return -1;
}

unsigned short int import_ASE(char *chemin, scene_3D *scene, unsigned short int *objet_cour, Ombrage omb, float amb, float dif, float ref, point_3D pos, unsigned char r1, short int a1, unsigned char r2, short int a2, unsigned char r3, short int a3, float ech)
{
    FILE                *fichier_ASE;
    char                tmp[256];
    unsigned short int  ancien_nb = scene->nb_objets;
    unsigned long int   i, j, k,
                        ancien_nb_mater = scene->nb_materiaux,
                        mater_std = scene->objet[*objet_cour].materiau,
                        ici,
                        num,
                        *somp;
    float               *equation,
                        min_x = 0, max_x = 0,
                        min_y = 0, max_y = 0,
                        min_z = 0, max_z = 0,
                        fl;
    polygone            *p;
    point_3D            *som,

                        pt;
    bool                Normales_Ok = true,
                        Lissage_Ok = true,
                        MTLID_Ok = true,
                        Materiau_Ok = true;

    fichier_ASE = fopen(chemin,"rt");
    printf("Verification de l'entete du fichier ...");
    fflush(stdout);
    if (!chercher_str_txt("*3DSMAX_ASCIIEXPORT", &fichier_ASE))
    {
        fclose(fichier_ASE);
        printf(" Erreur\nL'entete du fichier n'est pas valide...\n");
        fflush(stdout);
        return 0;
    }
    printf(" Ok\n");


    printf("Calcul du nombre d'objets dans la scene ASE");
    fflush(stdout);
    while (chercher_str_txt("*GEOMOBJECT", &fichier_ASE))
    {
        printf(".");
        fflush(stdout);
        scene->nb_objets++;
    }
    scene->nb_objets--;     // On enlève l'objet ASE
    fclose(fichier_ASE);
    printf(" %hu\n\n",scene->nb_objets - ancien_nb +1);
    fflush(stdout);

    scene->objet=(objet *) realloc(scene->objet, scene->nb_objets*sizeof(objet));
    ancien_nb = scene->nb_objets - ancien_nb + *objet_cour + 1;
    for (i = *objet_cour; i < ancien_nb; i++)
    {
        // Initialisation
        scene->objet[i].type     = 4;
        scene->objet[i].materiau = mater_std;
        scene->objet[i].sommet   = 0;
        scene->objet[i].poly     = 0;
        scene->objet[i].ombrage  = omb;
    }

    fichier_ASE=fopen(chemin,"rt");

    printf("\nRecherche de la liste des matériaux ...");
    fflush(stdout);
    ici = ftell(fichier_ASE);
    if (!chercher_str_txt("*MATERIAL_LIST", &fichier_ASE))
    {
            Materiau_Ok = false;
            printf(" Absente\n");
            fflush(stdout);
            fseek(fichier_ASE, ici, SEEK_SET);
    }
    else
    {
        if (!chercher_str_txt("*MATERIAL_COUNT", &fichier_ASE))
        {
            Materiau_Ok = false;
            printf(" Erreur\nLa liste des matériaux est incomplète...\n");
            fflush(stdout);
            fseek(fichier_ASE, ici, SEEK_SET);
        }
        else
        {
            // Lecture du nombre de matériaux
            scene->nb_materiaux += lire_uint32_txt(&fichier_ASE);
            scene->materiau=(materiau *) realloc(scene->materiau, scene->nb_materiaux*sizeof(materiau));
            // Initialisation des matériaux
            for (i = ancien_nb_mater; Materiau_Ok && (i < scene->nb_materiaux); i++)
            {
                strcpy(scene->materiau[i].nom, "Materiau");
                scene->materiau[i].ambiance    =   1;
                scene->materiau[i].coul_amb.r   = 255;
                scene->materiau[i].coul_amb.v   = 255;
                scene->materiau[i].coul_amb.b   = 255;
                scene->materiau[i].diffusion   =   0;
                scene->materiau[i].coul_dif.r   = 255;
                scene->materiau[i].coul_dif.v   = 255;
                scene->materiau[i].coul_dif.b   = 255;
                scene->materiau[i].reflexion   =   0;
                scene->materiau[i].coul_ref.r  = 255;
                scene->materiau[i].coul_ref.v  = 255;
                scene->materiau[i].coul_ref.b  =  55;
                scene->materiau[i].specularite =   0;
                scene->materiau[i].coul_spec.r = 255;
                scene->materiau[i].coul_spec.v = 255;
                scene->materiau[i].coul_spec.b = 255;
                scene->materiau[i].puis_spec   =   5;
                scene->materiau[i].opacite     =   1;
                scene->materiau[i].indice_ref  =   1;
            }

            printf(" Ok\n");
        }

        #ifndef __DEBUG
        printf("Lecture de la liste des materiaux ...");
        fflush(stdout);
        #endif
        for (i = ancien_nb_mater; Materiau_Ok && (i < scene->nb_materiaux); i++)
        {
            #ifdef __DEBUG
            printf("Lecture du materiau");
            fflush(stdout);
            #endif
            if (!chercher_str_txt("*MATERIAL", &fichier_ASE))
            {
                printf(" Erreur\nLe materiau n°%lu est introuvable...\n",i);
                fflush(stdout);
                Materiau_Ok = false;
                fseek(fichier_ASE, ici, SEEK_SET);
            }
            else
            {
                // Lecture du numéro du matériau
                num = lire_uint32_txt(&fichier_ASE);
                #ifdef __DEBUG
                printf(" %lu ...\n",num);
                fflush(stdout);
                #endif

                if (!chercher_str_txt("*MATERIAL_NAME", &fichier_ASE))

                {
                    printf(" Erreur\nLe materiau n°%lu est incomplet...\n",num);
                    fflush(stdout);
                    Materiau_Ok = false;
                    fseek(fichier_ASE, ici, SEEK_SET);
                }
                else
                {
                    // Lecture du nom du matériau
                    lire_nom_objet_txt(scene->materiau[ancien_nb_mater+num].nom, &fichier_ASE);
                    #ifdef __DEBUG
                    printf(" Nom : %s\n", scene->materiau[ancien_nb_mater+num].nom);
                    fflush(stdout);
                    #endif

                    if (!chercher_str_txt("*MATERIAL_AMBIENT", &fichier_ASE))
                    {
                        printf(" Erreur\nLe materiau n°%lu est incomplet...\n",num);
                        fflush(stdout);
                        Materiau_Ok = false;
                        fseek(fichier_ASE, ici, SEEK_SET);
                    }
                    else
                    {
                        // On lit l'ambiance
                        scene->materiau[ancien_nb_mater+num].coul_amb.r = lire_float_txt(&fichier_ASE)*255;
                        scene->materiau[ancien_nb_mater+num].coul_amb.v = lire_float_txt(&fichier_ASE)*255;
                        scene->materiau[ancien_nb_mater+num].coul_amb.b = lire_float_txt(&fichier_ASE)*255;

                        if (!chercher_str_txt("*MATERIAL_DIFFUSE", &fichier_ASE))
                        {
                            printf(" Erreur\nLe materiau n°%lu est incomplet...\n",num);
                            fflush(stdout);
                            Materiau_Ok = false;
                            fseek(fichier_ASE, ici, SEEK_SET);
                        }
                        else
                        {
                            // On lit la diffusion
                            scene->materiau[ancien_nb_mater+num].coul_dif.r = lire_float_txt(&fichier_ASE)*255;
                            scene->materiau[ancien_nb_mater+num].coul_dif.v = lire_float_txt(&fichier_ASE)*255;
                            scene->materiau[ancien_nb_mater+num].coul_dif.b = lire_float_txt(&fichier_ASE)*255;

                            if (!chercher_str_txt("*MATERIAL_SPECULAR", &fichier_ASE))
                            {
                                printf(" Erreur\nLe materiau n°%lu est incomplet...\n",num);
                                fflush(stdout);
                                Materiau_Ok = false;
                                fseek(fichier_ASE, ici, SEEK_SET);
                            }
                            else
                            {
                                // On lit la spécularité et la réfexion
                                fl = lire_float_txt(&fichier_ASE);
                                scene->materiau[ancien_nb_mater+num].coul_spec.r = fl*255;
                                scene->materiau[ancien_nb_mater+num].coul_ref.r = fl*255;
                                fl = lire_float_txt(&fichier_ASE);
                                scene->materiau[ancien_nb_mater+num].coul_spec.v = fl*255;
                                scene->materiau[ancien_nb_mater+num].coul_ref.v = fl*255;
                                fl = lire_float_txt(&fichier_ASE);
                                scene->materiau[ancien_nb_mater+num].coul_spec.b = fl*255;
                                scene->materiau[ancien_nb_mater+num].coul_ref.b = fl*255;
                                if (!chercher_str_txt("*MATERIAL_SHINE", &fichier_ASE))
                                {
                                    printf(" Erreur\nLe materiau n°%lu est incomplet...\n",num);
                                    fflush(stdout);
                                    Materiau_Ok = false;
                                    fseek(fichier_ASE, ici, SEEK_SET);
                                }
                                else
                                {
                                    fl = lire_float_txt(&fichier_ASE);
                                    scene->materiau[ancien_nb_mater+num].specularite = fl;
                                    scene->materiau[ancien_nb_mater+num].reflexion = fl*ref;
                                    scene->materiau[ancien_nb_mater+num].ambiance = amb*(1-fl);
                                    scene->materiau[ancien_nb_mater+num].diffusion = dif*(1-fl);
                                    if (!chercher_str_txt("*MATERIAL_SHINESTRENGTH", &fichier_ASE))
                                    {
                                        printf(" Erreur\nLe materiau n°%lu est incomplet...\n",num);
                                        fflush(stdout);
                                        Materiau_Ok = false;
                                        fseek(fichier_ASE, ici, SEEK_SET);
                                    }
                                    else
                                    {
                                        fl = lire_float_txt(&fichier_ASE);
                                        scene->materiau[ancien_nb_mater+num].puis_spec = (unsigned char) (fl*100);
                                        #ifdef __DEBUG
                                        printf(" Ambiance : %d%% %d %d %d\n", (int)(100*scene->materiau[ancien_nb_mater+num].ambiance), scene->materiau[ancien_nb_mater+num].coul_amb.r, scene->materiau[ancien_nb_mater+num].coul_amb.v, scene->materiau[ancien_nb_mater+num].coul_amb.b);
                                        printf(" Diffusion : %d%% %d %d %d\n", (int)(100*scene->materiau[ancien_nb_mater+num].diffusion), scene->materiau[ancien_nb_mater+num].coul_dif.r, scene->materiau[ancien_nb_mater+num].coul_dif.v, scene->materiau[ancien_nb_mater+num].coul_dif.b);
                                        printf(" Spécularité : %d%% °%d %d %d %d\n", (int)(100*scene->materiau[ancien_nb_mater+num].specularite), (int)(scene->materiau[ancien_nb_mater+num].puis_spec), scene->materiau[ancien_nb_mater+num].coul_spec.r, scene->materiau[ancien_nb_mater+num].coul_spec.v,scene->materiau[ancien_nb_mater+num].coul_spec.b);
                                        printf(" Réflexion : %d%% %d %d %d\n", (int)(100*scene->materiau[ancien_nb_mater+num].reflexion), scene->materiau[ancien_nb_mater+num].coul_ref.r, scene->materiau[ancien_nb_mater+num].coul_ref.v, scene->materiau[ancien_nb_mater+num].coul_ref.b);
                                        fflush(stdout);
                                        #endif

                                        if (!chercher_str_txt("*MATERIAL_TRANSPARENCY", &fichier_ASE))
                                        {
                                            printf(" Erreur\nLe materiau n°%lu est incomplet...\n",num);
                                            fflush(stdout);
                                            Materiau_Ok = false;
                                            fseek(fichier_ASE, ici, SEEK_SET);
                                        }
                                        else
                                        {
                                            // On lit l'opacite
                                            fl = lire_float_txt(&fichier_ASE);
                                            scene->materiau[ancien_nb_mater+num].opacite = 1-fl;
                                            #ifdef __DEBUG
                                            printf(" Opacite : %d%%\n", (int)(100*scene->materiau[ancien_nb_mater+num].opacite));
                                            fflush(stdout);
                                            #endif
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        #ifndef __DEBUG
        printf(" Ok\n");
        fflush(stdout);
        #endif
    }


    for (i = *objet_cour; i < ancien_nb; i++)
    {
        printf("\nRecherche de l'objet n°%lu ...",i);
        fflush(stdout);
        if (!chercher_str_txt("*GEOMOBJECT", &fichier_ASE))
        {
            printf(" Erreur\nL'objet n°%lu est introuvable...\n",i);
            fflush(stdout);
            return i;
        }
        printf(" Ok\n");

        printf("Nom de l'objet ...");
        fflush(stdout);
        if (!(chercher_str_txt("*NODE_NAME", &fichier_ASE) && lire_nom_objet_txt(scene->objet[i].nom,&fichier_ASE)))
        {
            printf(" Erreur\nLe nom de l'objet est introuvable...\n");
            fflush(stdout);
            return i;
        }
        printf(" %s\n", scene->objet[i].nom);

        printf("Recherche du maillage ...");
        fflush(stdout);
        if (!chercher_str_txt("*MESH", &fichier_ASE))
        {
            printf(" Erreur\nLe maillage est introuvable...\n");
            fflush(stdout);
            return i;
        }
        printf(" Ok\n");

        printf("Recherche du nombre de sommets ...");
        fflush(stdout);
        if (!chercher_str_txt("*MESH_NUMVERTEX", &fichier_ASE))
        {
            printf(" Erreur\nLe nombre de sommets est introuvable...\n");
            fflush(stdout);
            return i;
        }
        scene->objet[i].nb_sommets=lire_uint32_txt(&fichier_ASE);
        printf(" %lu\n",scene->objet[i].nb_sommets);
        // Allocation des sommets
        scene->objet[i].sommet=(point_3D *) malloc(scene->objet[i].nb_sommets*sizeof(point_3D));

        printf("Recherche du nombre de polygones ...");
        fflush(stdout);
        if (!chercher_str_txt("*MESH_NUMFACES", &fichier_ASE))
        {
            printf(" Erreur\nLe nombre de polygones est introuvable...\n");
            fflush(stdout);
            return i;
        }
        scene->objet[i].nb_polys=lire_uint32_txt(&fichier_ASE);
        printf(" %lu\n",scene->objet[i].nb_polys);
        // Allocation des polygones
        scene->objet[i].poly=(polygone *) malloc(scene->objet[i].nb_polys*sizeof(polygone));

        printf("Recherche de la liste de sommets ...");
        fflush(stdout);
        if (!chercher_str_txt("*MESH_VERTEX_LIST", &fichier_ASE))
        {
            printf(" Erreur\nLa liste de sommets est introuvable...\n");
            fflush(stdout);
            return i;
        }
        printf(" Ok\n");

        #ifndef __DEBUG
        printf("Lecture de la liste de sommets ...");
        fflush(stdout);
        #endif
        for (j=0;j<scene->objet[i].nb_sommets;j++)
        {
            #ifdef __DEBUG
            printf("Lecture du sommet");
            fflush(stdout);
            #endif
            if (!chercher_str_txt("*MESH_VERTEX", &fichier_ASE))
            {
                printf(" Erreur\nLe sommet n°%lu est introuvable...\n",j);
                fflush(stdout);
                return i;
            }
            num=lire_uint32_txt(&fichier_ASE);
            #ifdef __DEBUG
            printf(" %lu ...",num);
            fflush(stdout);
            #endif

            scene->objet[i].sommet[num].xr = lire_float_txt(&fichier_ASE);
            scene->objet[i].sommet[num].yr = lire_float_txt(&fichier_ASE);
            scene->objet[i].sommet[num].zr = lire_float_txt(&fichier_ASE);

            if ((i!=*objet_cour) || j)
            {
                if (scene->objet[i].sommet[num].xr < min_x) min_x = scene->objet[i].sommet[num].xr;
                else if (scene->objet[i].sommet[num].xr > max_x) max_x = scene->objet[i].sommet[num].xr;

                if (scene->objet[i].sommet[num].yr < min_y) min_y = scene->objet[i].sommet[num].yr;
                else if (scene->objet[i].sommet[num].yr > max_y) max_y = scene->objet[i].sommet[num].yr;
                if (scene->objet[i].sommet[num].zr < min_z) min_z = scene->objet[i].sommet[num].zr;
                else if (scene->objet[i].sommet[num].zr > max_z) max_z = scene->objet[i].sommet[num].zr;
            }
            else
            {
                max_x = min_x = scene->objet[i].sommet[num].xr;
                max_y = min_y = scene->objet[i].sommet[num].yr;
                max_z = min_z = scene->objet[i].sommet[num].zr;
            }

            #ifdef __DEBUG
            printf(" X:%f",scene->objet[i].sommet[num].xr);
            printf(" Y:%f",scene->objet[i].sommet[num].yr);
            printf(" Z:%f",scene->objet[i].sommet[num].zr);
            printf(" Ok\n");
            fflush(stdout);
            #endif
        }
        #ifndef __DEBUG
        printf(" Ok\n");
        #endif

        printf("Recherche de la liste de polygones ...");
        fflush(stdout);
        if (!chercher_str_txt("*MESH_FACE_LIST", &fichier_ASE))
        {
            printf(" Erreur\nLa liste de polygones est introuvable...\n");
            fflush(stdout);
            return i;
        }
        printf(" Ok\n");

        #ifndef __DEBUG
        printf("Lecture de la liste de polygones ...");
        fflush(stdout);
        #endif
        p = scene->objet[i].poly;
        som = scene->objet[i].sommet;
        for (j=0;j<scene->objet[i].nb_polys;j++)
        {
            // Allocation du tableau de normales
            p[j].normale = (vecteur_3D *) malloc(3*sizeof(vecteur_3D));

            somp = p[j].sommet;
            equation = p[j].equation;
            #ifdef __DEBUG
            printf("Lecture du polygone");
            fflush(stdout);
            #endif
            if (!chercher_str_txt("*MESH_FACE", &fichier_ASE))
            {
                printf(" Erreur\nLe polygone n°%lu est introuvable...\n",j);
                fflush(stdout);
                return i;
            }
            num=lire_uint32_txt(&fichier_ASE);
            #ifdef __DEBUG
            printf(" %lu ...",num);
            fflush(stdout);
            #endif
            lire_char(&fichier_ASE);
            for (k=0;k<3;k++)
            {
                fscanf(fichier_ASE,"%s",tmp),
                somp[k]=lire_uint32_txt(&fichier_ASE);
                #ifdef __DEBUG

                printf(" A:%lu",somp[k]);
                fflush(stdout);
                #endif
            }

            for (k=0;k<3;k++)
            {
                fscanf(fichier_ASE,"%s",tmp),
                lire_uint32_txt(&fichier_ASE);
            }

            ici = ftell(fichier_ASE);
            if ((!Lissage_Ok) || (!chercher_str_txt("*MESH_SMOOTHING", &fichier_ASE)))
            {
                Lissage_Ok = false;
                fseek(fichier_ASE, ici, SEEK_SET);
            }
            ici = ftell(fichier_ASE);
            if ((!MTLID_Ok) || (!chercher_str_txt("*MESH_MTLID", &fichier_ASE)))
            {
                MTLID_Ok = false;
                fseek(fichier_ASE, ici, SEEK_SET);
            }

            #ifdef __DEBUG
            printf(" Ok\n");
            fflush(stdout);
            #endif
        }
        #ifndef __DEBUG
        printf(" Ok\n");
        #endif

        printf("Recherche de la liste des normales ...");
        fflush(stdout);
        ici = ftell(fichier_ASE);
        if ((!Normales_Ok) || (!chercher_str_txt("*MESH_NORMALS", &fichier_ASE)))
        {
            fseek(fichier_ASE, ici, SEEK_SET);
            Normales_Ok = false;
            printf(" Absente\n");
            fflush(stdout);
        }
        else
        {
            printf(" Ok\n");

            #ifndef __DEBUG
            printf("Lecture de la liste des normales ...");
            fflush(stdout);
            #endif
            p = scene->objet[i].poly;
            for (j = 0; j < scene->objet[i].nb_polys; j++)
            {
                equation = p[j].equation;
                #ifdef __DEBUG
                printf("Lecture de la normale");
                fflush(stdout);
                #endif
                if (!chercher_str_txt("*MESH_FACENORMAL", &fichier_ASE))
                {
                    printf(" Erreur\nLa normale n°%lu est introuvable...\n",j);
                    fflush(stdout);
                    return i;
                }
                num=lire_uint32_txt(&fichier_ASE);
                #ifdef __DEBUG
                printf(" %lu ...",num);
                fflush(stdout);
                #endif

                // On passe la normale à la face
                /*p[j].equation[0] = */lire_float_txt(&fichier_ASE);
                /*p[j].equation[1] = */lire_float_txt(&fichier_ASE);
                /*p[j].equation[2] = */lire_float_txt(&fichier_ASE);

                for (k=0;k<3;k++)
                {
                    if (!chercher_str_txt("*MESH_VERTEXNORMAL", &fichier_ASE))
                    {
                        printf(" Erreur\nUne des normales au sommet est introuvable...\n");
                        fflush(stdout);
                        return i;
                    }
                    // Le numéro du sommet
                    num=lire_uint32_txt(&fichier_ASE);
                    // Les coordonnées de la normale au sommet
                    p[j].normale[k].vxr = lire_float_txt(&fichier_ASE);
                    p[j].normale[k].vyr = lire_float_txt(&fichier_ASE);
                    p[j].normale[k].vzr = lire_float_txt(&fichier_ASE);
                }

                #ifdef __DEBUG
                printf(" Ok\n");
                fflush(stdout);
                #endif
            }
            #ifndef __DEBUG
            printf(" Ok\n");
            #endif
        }

        printf("Recherche du matériau ...");
        fflush(stdout);
        ici = ftell(fichier_ASE);
        if ((!Materiau_Ok) || (!chercher_str_txt("*MATERIAL_REF", &fichier_ASE)))
        {
            fseek(fichier_ASE, ici, SEEK_SET);
            Materiau_Ok = false;
            printf(" Absent\n");
            fflush(stdout);
        }
        else
        {
            scene->objet[i].materiau = ancien_nb_mater + lire_uint32_txt(&fichier_ASE);
            printf(" %lu\n", scene->objet[i].materiau);
        }

    }

    fclose(fichier_ASE);

    // Centrage des objets
    for (i = *objet_cour; i < ancien_nb; i++)
    {
        for (j = 0; j < scene->objet[i].nb_sommets; j++)
        {
            // Centre à peu près en 0,0,0
            scene->objet[i].sommet[j].xr -= (max_x - min_x);
            scene->objet[i].sommet[j].yr -= (max_y - min_y);
            scene->objet[i].sommet[j].zr -= (max_z - min_z);

            // On effectue les rotoations si nécessaires
            if (r1 == 1) point_rotation_x(&(scene->objet[i].sommet[j]), a1);
            else if (r1 == 2) point_rotation_y(&(scene->objet[i].sommet[j]), a1);
                else if (r1 == 3) point_rotation_z(&(scene->objet[i].sommet[j]), a1);

            if (r2 == 1) point_rotation_x(&(scene->objet[i].sommet[j]), a2);
            else if (r2 == 2) point_rotation_y(&(scene->objet[i].sommet[j]), a2);
                else if (r2 == 3) point_rotation_z(&(scene->objet[i].sommet[j]), a2);

            pt.xr = scene->objet[i].sommet[j].xr;
            pt.yr = scene->objet[i].sommet[j].yr;
            pt.zr = scene->objet[i].sommet[j].zr;
            if (r3 == 1) point_rotation_x(&(scene->objet[i].sommet[j]), a3);
            else if (r3 == 2) point_rotation_y(&(scene->objet[i].sommet[j]), a3);
                else if (r3 == 3) point_rotation_z(&(scene->objet[i].sommet[j]), a3);

            // Et le déplacement si nécessaire
            scene->objet[i].sommet[j].xr += pos.xr;
            scene->objet[i].sommet[j].yr += pos.yr;
            scene->objet[i].sommet[j].zr += pos.zr;

            // Mise à l'échelle
            scene->objet[i].sommet[j].xr *= ech;
            scene->objet[i].sommet[j].yr *= ech;
            scene->objet[i].sommet[j].zr *= ech;
        }
        sphere_englobante(scene, i);
        #ifdef __DEBUG
        printf(" Sphère englobante : Position (%f, %f, %f), Rayon %f\n", scene->objet[i].centre.xr, scene->objet[i].centre.yr, scene->objet[i].centre.zr, scene->objet[i].rayon);
        #endif

        plan(scene, i);
        if (!Normales_Ok)

        {
            // On désalloue les normales
            for (j = 0; j < scene->objet[i].nb_polys; j++)
                free(scene->objet[i].poly[j].normale);
            // On modifie le type de l'objet
            scene->objet[i].type = 3;
            // Et on recalcule
            normales(scene, i);
        }
    }

    (*objet_cour) = ancien_nb-1;

    return scene->nb_objets;
}

bool import(char *chemin, scene_3D *scene, unsigned short int *objet_cour, Ombrage omb, float amb, float dif, float ref, point_3D pos, unsigned char r1, short int a1, unsigned char r2, short int a2, unsigned char r3, short int a3, float ech)
{
    FILE            *fichier;

    printf("Recherche du fichier %s ...",chemin);
    fflush(stdout);
    if (!(fichier=fopen(chemin,"rt")))
    {
    	printf(" Erreur\nLe fichier %s est introuvable...\n",chemin);
        fflush(stdout);
        fclose(fichier);
        return false;
    }
    fclose(fichier);
    printf(" Ok\n");

    printf("Determination du format de fichier ...");
    fflush(stdout);
    switch(format_fichier(chemin))
    {
        case 1:
            printf(" ASE\n");
            fflush(stdout);
            return import_ASE(chemin, scene, objet_cour, omb, amb, dif, ref, pos, r1, a1, r2, a2, r3, a3, ech);
        break;
        default:
            printf(" Erreur\nFormat du fichier non pris en charge...\n");
            fflush(stdout);
            return false;
        break;
    }
    return false;
}

bool charger_rtd(char *chemin, scene_3D *scene)
{
    FILE*               fichier;
    char                tmp[256],
                        version[256],
                        ch;
    unsigned char       etat = 0,
                        touche;
    short int           objet_cour = -1,
                        lum_cour = -1,
                        materiau_cour = -1,
                        r1 = 0,
                        r2 = 0,
                        r3 =0,
                        usi;
    unsigned long int   i,
                        *somp;
    polygone            *p = 0;
    point_3D            *som;
    bool                fin = false,
                        erreur = false;
    float               amb = 0.2,
                        dif = 0.8,
                        ref = 1.0,
                        ech = 1.0,
                        ftmp,
                        taille_ecran_x = 0.0, taille_ecran_y;
    short int           a1 = 0,
                        a2 = 0,
                        a3 =0;



    // On commence par donner une valeur par défaut aux paramètres de la scène
    strcpy(scene->nom,"Scene");
    scene->res_x = RES_X;
    scene->res_y = RES_Y;
    scene->pitch_x = 1.0;
    scene->pitch_y = 1.0;
    scene->focale = 300.0;
    scene->antialiasing = 0;
    scene->iter = 6;
    scene->nb_pix = 16;
    scene->rendu = 0;
    scene->fond.r = 0;
    scene->fond.v = 0;
    scene->fond.b = 0;
    scene->position.xr = 0.0;
    scene->position.yr = 0.0;
    scene->position.zr = -300.0;
    scene->rot_x = 0.0;
    scene->rot_y = 0.0;
    scene->rot_z = 0.0;
    scene->Vx.vxr = 1.0;
    scene->Vx.vyr = 0.0;
    scene->Vx.vzr = 0.0;
    scene->Vy.vxr = 0.0;
    scene->Vy.vyr = 1.0;
    scene->Vy.vzr = 0.0;
    scene->Vz.vxr = 0.0;
    scene->Vz.vyr = 0.0;
    scene->Vz.vzr = 1.0;
    scene->anim_t[0]      = 0.0;
    scene->anim_t[1]      = 2.0;
    scene->anim[0][0]     = 0.0;
    scene->anim[0][1]     = 0.0;
    scene->anim[0][2]     = 0.0;
    scene->anim[0][3]     = 1.0;
    scene->anim[1][0]     = 0.0;
    scene->anim[1][1]     = 0.0;
    scene->anim[1][2]     = 0.0;
    scene->anim[1][3]     = 1.0;
    scene->anim[2][0]     = 0.0;
    scene->anim[2][1]     = 0.0;
    scene->anim[2][2]     = 0.0;
    scene->anim[2][3]     = 1.0;
    scene->anim_rot[0][0] = 0.0;
    scene->anim_rot[0][1] = 0.0;
    scene->anim_rot[1][0] = 0.0;
    scene->anim_rot[1][1] = 0.0;
    scene->anim_rot[2][0] = 0.0;
    scene->anim_rot[2][1] = 0.0;

    // Ouverture
    printf("Ouverture du fichier %s...", chemin);
    fflush(stdout);
    if ((fichier = fopen(chemin, "r")))
    {
        printf(" Ok\n");
        printf("Lecture du fichier...\n\n");

        printf("Verification du format...");
        fflush(stdout);
        fscanf(fichier, "%s", tmp);
        if (strcmp(tmp, "RTD")) return false;
        printf(" RTD\n");
        printf("Verification de la version...");
        fflush(stdout);
        fscanf(fichier, "%s", version);

        // Si la version est prise en charge
        if ((!strcmp(version,"0.1")) || (!strcmp(version,"0.2")) || (!strcmp(version,"0.3")) || (!strcmp(version,"0.4")))
        {
            strcpy(scene->version, version);
            printf(" %s\n\n", scene->version);

            while (!feof(fichier) && !fin && !erreur)
            {
                    // Lecture de la commande
                    fscanf(fichier, "%s", tmp);

                    // Commentaire
                    if (!strcmp(tmp,"/*"))
                    {
                        while ((!feof(fichier)) && (strcmp(tmp,"*/")))
                            fscanf(fichier, "%s", tmp);
                    }

                    // Résolution
                    else if (!strcmp(tmp,"Resolution"))
                    {
                        fscanf(fichier, "%hu", &scene->res_x);
                        if (scene->res_x%8) scene->res_x+=scene->res_x%8;
                        fscanf(fichier, "%hu", &scene->res_y);
                        if (scene->res_y%8) scene->res_y+=scene->res_y%8;
                        printf("\nRésolution : %hux%hu\n", scene->res_x, scene->res_y);
                        fflush(stdout);
                    }

                    // Nombre d'itérations dans la réflexion
                    else if (!strcmp(tmp,"Iteration_ref"))
                    {
                        fscanf(fichier, "%hu", &usi);
                        scene->iter = (unsigned char) (usi);
                        printf("\nNombre d'itérations dans la réflexion : %hd\n", scene->iter);
                        fflush(stdout);
                    }

                    // Nombre de pixels par rayon
                    else if (!strcmp(tmp,"Nb_pix"))
                    {
                        fscanf(fichier, "%hu", &usi);
                        scene->nb_pix = (unsigned char) (usi);
                        printf("\nNombre de pixels par rayon (rendu rapide) : %hu pixels\n", scene->nb_pix);
                        fflush(stdout);
                    }

                    // Type du rendu
                    else if (!strcmp(tmp,"Rendu"))
                    {
                        fscanf(fichier, "%hu", &usi);
                        if (usi>1)
                        {
                            printf("\n!!! Type de rendu : Inconnu\n... Passage en rendu rapide\n");
                            scene->rendu = false;
                        }
                        else
                        {
                            scene->rendu = (bool) (usi);
                            if (scene->rendu) printf("\nType de rendu : Normal\n");
                            else printf("\nType de rendu : Rapide\n");
                        }
                        fflush(stdout);
                    }

                    // Antialiasing
                    else if (!strcmp(tmp,"Antialiasing"))
                    {
                        fscanf(fichier, "%hu", &usi);
                        scene->antialiasing = (unsigned char) (usi);
                        switch (scene->antialiasing)
                        {
                            case 0 :
                                printf("\nAntialiasing : Aucun\n");
                            break;
                            case 1 :
                                printf("\nAntialiasing : Flou 16 rayons par pixel\n");
                            break;
                            case 2 :
                                printf("\nAntialiasing : Flou 32 rayons par pixel\n");
                            break;
                            case 3 :
                                printf("\nAntialiasing : 5 rayons par pixel\n");
                            break;
                            case 4 :
                                printf("\nAntialiasing : 9 rayons par pixel\n");
                            break;
                            default :
                                scene->antialiasing = 0;
                                printf("\n!!! Antialiasing : Inconnu\n... Antialiasing non activé\n");
                        }
                        fflush(stdout);
                    }

                    // Nombre d'objets
                    else if (!strcmp(tmp,"Nb_objets"))
                    {
                        fscanf(fichier, "%hu", &scene->nb_objets);
                        scene->objet = (objet *) malloc(scene->nb_objets*sizeof(objet));
                        if (!strcmp(scene->version,"0.1"))
                        {
                            scene->nb_materiaux = scene->nb_objets;
                            scene->materiau = (materiau *) malloc(scene->nb_materiaux*sizeof(materiau));
                        }
                        printf("\nNombre d'objets : %hu\n", scene->nb_objets);
                        fflush(stdout);
                    }

                    // Nombre de lumières
                    else if (!strcmp(tmp,"Nb_lumieres"))
                    {
                        fscanf(fichier, "%hu", &scene->nb_lumieres);
                        scene->lumiere = (lumiere *) malloc(scene->nb_lumieres*sizeof(lumiere));
                        printf("\nNombre de lumières : %hu\n", scene->nb_lumieres);
                        fflush(stdout);
                    }

                    // Nombre de matériaux
                    else if (!strcmp(tmp,"Nb_materiaux"))
                    {
                        fscanf(fichier, "%hu", &scene->nb_materiaux);
                        scene->materiau = (materiau *) malloc(scene->nb_materiaux*sizeof(materiau));
                        printf("\nNombre de matériaux : %hu\n", scene->nb_materiaux);
                        fflush(stdout);
                    }

                    // Couleur de fond
                    else if (!strcmp(tmp,"Fond"))
                    {
                        fscanf(fichier, "%hu", &usi);
                        scene->fond.r = (unsigned char) (usi);
                        fscanf(fichier, "%hu", &usi);
                        scene->fond.v = (unsigned char) (usi);
                        fscanf(fichier, "%hu", &usi);
                        scene->fond.b = (unsigned char) (usi);
                        printf("\nFond : %d %d %d\n", scene->fond.r, scene->fond.v, scene->fond.b);
                        fflush(stdout);
                    }

                    // Entête de la caméra
                    else if (!strcmp(tmp,"Camera"))
                    {
                        printf("\nCamera\n");
                        fflush(stdout);
                        etat = 1;   /* Pour dire qu'on lit les caractéristiques de la caméra */
                    }

                    // Nom
                    else if (!strcmp(tmp,"Nom"))
                    {
                        fscanf(fichier, "%c", &ch);
                        fscanf(fichier, "%c", &ch);
                        i = 0;
                        if (ch == '\"')
                        {
                            fscanf(fichier, "%c", &ch);
                            while (ch != '\"')
                            {
                                tmp[i++] = ch;
                                fscanf(fichier, "%c", &ch);
                            }
                            tmp[i] = '\0';
                        }
                        switch (etat)
                        {
                            case 0:
                            case 1: /* Caméra */
                                strcpy(scene->nom, tmp);
                                printf(" Nom : %s\n", scene->nom);
                                fflush(stdout);
                            break;
                            case 2: /* Objet */
                                strcpy(scene->objet[objet_cour].nom, tmp);
                                printf(" Nom : %s\n", scene->objet[objet_cour].nom);
                                fflush(stdout);
                            break;
                            case 3: /* Lumière */
                                strcpy(scene->lumiere[lum_cour].nom, tmp);
                                printf(" Nom : %s\n", scene->lumiere[lum_cour].nom);
                                fflush(stdout);
                            break;
                            case 4: /* Matériau */
                                strcpy(scene->materiau[materiau_cour].nom, tmp);
                                printf(" Nom : %s\n", scene->materiau[materiau_cour].nom);
                                fflush(stdout);
                            break;
                        }
                    }

                    // Position
                    else if (!strcmp(tmp,"Position"))
                    {
                        switch (etat)
                        {
                            case 0:
                            case 1: /* Caméra */
                                fscanf(fichier, "%f", &(scene->position.xr));
                                fscanf(fichier, "%f", &(scene->position.yr));
                                fscanf(fichier, "%f", &(scene->position.zr));
                                printf(" Position : %f %f %f\n", scene->position.xr, scene->position.yr, scene->position.zr);
                                fflush(stdout);
                            break;
                            case 2: /* Objet de type ASE */
                                fscanf(fichier, "%f", &(scene->objet[objet_cour].centre.xr));
                                fscanf(fichier, "%f", &(scene->objet[objet_cour].centre.yr));
                                fscanf(fichier, "%f", &(scene->objet[objet_cour].centre.zr));
                                printf(" Position : %f %f %f\n", scene->objet[objet_cour].centre.xr, scene->objet[objet_cour].centre.yr, scene->objet[objet_cour].centre.zr);
                                fflush(stdout);
                            break;
                            case 3: /* Lumière */
                                fscanf(fichier, "%f", &(scene->lumiere[lum_cour].position.xr));
                                fscanf(fichier, "%f", &(scene->lumiere[lum_cour].position.yr));
                                fscanf(fichier, "%f", &(scene->lumiere[lum_cour].position.zr));
                                printf(" Position : %f %f %f\n", scene->lumiere[lum_cour].position.xr, scene->lumiere[lum_cour].position.yr, scene->lumiere[lum_cour].position.zr);
                                fflush(stdout);
                            break;
                        }
                    }

                    // Pitch
                    else if (!strcmp(tmp,"Pitch"))
                    {
                        fscanf(fichier, "%f", &scene->pitch_x);
                        fscanf(fichier, "%f", &scene->pitch_y);
                        printf(" Pitch : %f %f\n", scene->pitch_x, scene->pitch_y);
                        fflush(stdout);
                        taille_ecran_x = 0.0;
                    }

                    // Taille de l'écran
                    else if (!strcmp(tmp,"Taille"))
                    {
                        fscanf(fichier, "%f", &taille_ecran_x);
                        fscanf(fichier, "%f", &taille_ecran_y);
                        if (!taille_ecran_x || !taille_ecran_y)
                        {
                            printf("!!! La taille de l'écran est incorrecte !!!\n??? Voulez-vous mettre une valeur par défaut (taper 'O') ou arrêter (taper 'N') ??? ");
                            scanf("%c", &touche);
                            if ((touche == 'O') || (touche =='o'))
                            {
                                taille_ecran_x = 0.0;
                                scene->pitch_x = 1.0;
                                scene->pitch_y = 1.0;
                            }
                            else erreur = true;
                        }
                        printf(" Taille de l'écran : %f unités par %f unités\n", taille_ecran_x, taille_ecran_y);
                        fflush(stdout);
                    }

                    // Focale de la caméra
                    else if (!strcmp(tmp,"Focale"))
                    {
                        fscanf(fichier, "%f", &scene->focale);
                        if (scene->focale <= 0)
                        {
                            printf("!!! La distancce focale est incorrecte !!!\n??? Voulez-vous mettre une valeur par défaut (taper 'O') ou arrêter (taper 'N') ??? ");
                            scanf("%c", &touche);
                            if ((touche == 'O') || (touche =='o'))
                                scene->focale = 300.0;
                            else erreur = true;
                        }
                        printf(" Focale : %f\n", scene->focale);
                        fflush(stdout);
                    }

                    // Paramètre t pour l'animation
                    else if (!strcmp(tmp,"Anim_t"))
                    {
                        fscanf(fichier, "%lf\n", &(scene->anim_t[0]));
                        fscanf(fichier, "%lf\n", &(scene->anim_t[1]));
                        printf(" Animation : Paramètre t : t = t + Tps*%f + %f\n", scene->anim_t[0], scene->anim_t[1]);
                        fflush(stdout);
                    }

                    // Entête de l'objet
                    else if (!strcmp(tmp,"Objet"))
                    {
                        printf("\nObjet\n");
                        fflush(stdout);
                        etat = 2;   /* Pour dire qu'on lit les caractéristiques de l'objet */
                        // Valeurs par défaut pour les caractéristiques de l'objet
                        strcpy(scene->objet[++objet_cour].nom, "Objet");
                        scene->objet[objet_cour].type       =    1;
                        scene->objet[objet_cour].centre.xr  =   0.0;
                        scene->objet[objet_cour].centre.yr  =   1.0;
                        scene->objet[objet_cour].centre.zr  =   0.0;
                        scene->objet[objet_cour].rayon      = 100.0;
                        scene->objet[objet_cour].sommet     =     0;
                        scene->objet[objet_cour].poly       =     0;
                        scene->objet[objet_cour].normale    =     0;
                        scene->objet[objet_cour].nb_sommets =     0;
                        scene->objet[objet_cour].nb_polys   =     0;
                        scene->objet[objet_cour].ombrage    =     0;
                        scene->objet[objet_cour].anim[0][0] =     0.0;
                        scene->objet[objet_cour].anim[0][1] =     0.0;
                        scene->objet[objet_cour].anim[0][2] =     0.0;
                        scene->objet[objet_cour].anim[0][3] =     1.0;
                        scene->objet[objet_cour].anim[1][0] =     0.0;
                        scene->objet[objet_cour].anim[1][1] =     0.0;
                        scene->objet[objet_cour].anim[1][2] =     0.0;
                        scene->objet[objet_cour].anim[1][3] =     1.0;
                        scene->objet[objet_cour].anim[2][0] =     0.0;
                        scene->objet[objet_cour].anim[2][1] =     0.0;
                        scene->objet[objet_cour].anim[2][2] =     0.0;
                        scene->objet[objet_cour].anim[2][3] =     1.0;
                        scene->objet[objet_cour].materiau   =     0;

                        if (!strcmp(scene->version,"0.1"))
                        {
                            materiau_cour = objet_cour;
                            scene->objet[objet_cour].materiau  =   materiau_cour;
                            strcpy(scene->materiau[materiau_cour].nom, "Materiau");
                            scene->materiau[materiau_cour].ambiance    = 1.0;
                            scene->materiau[materiau_cour].coul_amb.r  = 255;
                            scene->materiau[materiau_cour].coul_amb.v  = 255;
                            scene->materiau[materiau_cour].coul_amb.b  = 255;
                            scene->materiau[materiau_cour].diffusion   = 0.0;
                            scene->materiau[materiau_cour].coul_dif.r  = 255;
                            scene->materiau[materiau_cour].coul_dif.v  = 255;
                            scene->materiau[materiau_cour].coul_dif.b  = 255;
                            scene->materiau[materiau_cour].reflexion   = 0.0;
                            scene->materiau[materiau_cour].coul_ref.r  = 255;
                            scene->materiau[materiau_cour].coul_ref.v  = 255;
                            scene->materiau[materiau_cour].coul_ref.b  = 255;
                            scene->materiau[materiau_cour].specularite = 0.0;
                            scene->materiau[materiau_cour].coul_spec.r = 255;
                            scene->materiau[materiau_cour].coul_spec.v = 255;
                            scene->materiau[materiau_cour].coul_spec.b = 255;
                            scene->materiau[materiau_cour].puis_spec   =   5;
                            scene->materiau[materiau_cour].opacite     = 1.0;
                            scene->materiau[materiau_cour].indice_ref  = 1.0;
                        }
                    }

                    // Type d'objet
                    else if (!strcmp(tmp,"Type"))
                    {
                        switch (etat)
                        {
                            case 2: /* Objet */
                                fscanf(fichier, "%hu", &usi);
                                scene->objet[objet_cour].type = (unsigned char) (usi);
                                switch (scene->objet[objet_cour].type)
                                {
                                    case 1 :
                                        printf(" Type : Sphère\n");
                                    break;
                                    case 2 :
                                        printf(" Type : Plan\n");
                                    break;
                                    case 3 :
                                        printf(" Type : Polygones\n");
                                    break;
                                    case 4 :
                                        printf(" Type : ASE\n");
                                    break;
                                    default :
                                        printf("!!! Type : Inconnu\n");
                                        erreur = true;
                                }
                                fflush(stdout);
                            break;

                            case 3: /* Lumière */
                                fscanf(fichier, "%hu", &usi);
                                scene->lumiere[lum_cour].type = (unsigned char) (usi);
                                switch (scene->lumiere[lum_cour].type)
                                {
                                    case 0 :
                                        printf(" Type : Ambiante\n");
                                    break;
                                    case 1 :
                                        printf(" Type : Ponctuelle\n");
                                    break;
                                    case 2 :
                                        printf(" Type : Directionnelle\n");
                                    break;
                                    default :
                                        printf("!!! Type : Inconnu\n");
                                        erreur = true;
                                }
                                fflush(stdout);
                            break;

                            default : /* Erreur */
                                printf("!!! Commande <Type>  mal placée\n");
                                erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Taux d'ambiance ASE
                    else if (!strcmp(tmp,"Taux_Amb"))
                    {
                        fscanf(fichier, "%f", &amb);
                        printf(" Taux d'ambiance : %d\n", (int)(100*amb));
                        fflush(stdout);
                    }

                    // Taux de diffusion ASE
                    else if (!strcmp(tmp,"Taux_Dif"))
                    {
                        fscanf(fichier, "%f", &dif);
                        printf(" Taux de diffusion : %d\n", (int)(100*dif));
                        fflush(stdout);
                    }

                    // Taux de réflexion ASE
                    else if (!strcmp(tmp,"Taux_Ref"))
                    {
                        fscanf(fichier, "%f", &ref);
                        printf(" Taux de réflexion : %d\n", (int)(100*ref));
                        fflush(stdout);
                    }

                    // Echelle ASE
                    else if (!strcmp(tmp,"Echelle"))
                    {
                        fscanf(fichier, "%f", &ech);
                        printf(" Echelle : %d%%\n", (int)(100*ech));
                        fflush(stdout);
                    }

                    // Rotation autour de l'axe des X ASE
                    else if (!strcmp(tmp,"Rot_x"))
                    {
                        if (!r1)
                        {
                            r1 = 1;
                            fscanf(fichier, "%hu", &a1);
                            printf(" Rotation en X : %hu degrés\n", a1);
                        }
                        else if (!r2)
                        {
                            r2 = 1;
                            fscanf(fichier, "%hu", &a2);
                            printf(" Rotation en X : %hu degrés\n", a2);
                        }
                        else
                        {
                            r3 = 1;
                            fscanf(fichier, "%hu", &a3);
                            printf(" Rotation en X : %hu degrés\n", a3);
                        }
                        fflush(stdout);
                    }

                    // Rotation autour de l'axe des Y ASE
                    else if (!strcmp(tmp,"Rot_y"))
                    {
                        if (!r1)
                        {
                            r1 = 2;
                            fscanf(fichier, "%hu", &a1);
                            printf(" Rotation en Y : %hu degrés\n", a1);
                        }
                        else if (!r2)
                        {
                            r2 = 2;
                            fscanf(fichier, "%hu", &a2);
                            printf(" Rotation en Y : %hu degrés\n", a2);
                        }
                        else
                        {
                            r3 = 2;
                            fscanf(fichier, "%hu", &a3);
                            printf(" Rotation en Y : %hu degrés\n", a3);
                        }
                        fflush(stdout);
                    }

                    // Rotation autour de l'axe des Z ASE
                    else if (!strcmp(tmp,"Rot_z"))
                    {
                        if (!r1)
                        {
                            r1 = 3;
                            fscanf(fichier, "%hu", &a1);
                            printf(" Rotation en Z : %hu degrés\n", a1);
                        }
                        else if (!r2)
                        {
                            r2 = 3;
                            fscanf(fichier, "%hu", &a2);
                            printf(" Rotation en Z : %hu degrés\n", a2);
                        }
                        else
                        {
                            r3 = 3;
                            fscanf(fichier, "%hu", &a3);
                            printf(" Rotation en Z : %hu degrés\n", a3);
                        }
                        fflush(stdout);
                    }

                    // Chemin du fichier ASE
                    else if (!strcmp(tmp,"Chemin"))
                    {
                        fscanf(fichier, "%s", tmp);
                        if (etat == 2 && scene->objet[objet_cour].type == 4)
                        {
                            if (!import(tmp, scene, &objet_cour, scene->objet[objet_cour].ombrage, amb, dif, ref, scene->objet[objet_cour].centre, r1, a1, r2, a2, r3, a3, ech)) erreur = true;
                        }
                        else
                        {
                            printf("!!! Commande <Chemin> mal placée\n");
                            fflush(stdout);
                            erreur = true;
                        }
                    }

                    // Centre de la spère
                    else if (!strcmp(tmp,"Centre"))
                    {
                        if (etat == 2)
                        {
                            fscanf(fichier, "%f", &(scene->objet[objet_cour].centre.xr));
                            fscanf(fichier, "%f", &(scene->objet[objet_cour].centre.yr));
                            fscanf(fichier, "%f", &(scene->objet[objet_cour].centre.zr));
                            printf(" Centre : %f %f %f\n", scene->objet[objet_cour].centre.xr, scene->objet[objet_cour].centre.yr, scene->objet[objet_cour].centre.zr);
                        }
                        else
                        {
                            printf("!!! Commande <Centre> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Rayon de la sphère
                    else if (!strcmp(tmp,"Rayon"))
                    {
                        if (etat == 2)
                        {
                            fscanf(fichier, "%f", &(scene->objet[objet_cour].rayon));
                            printf(" Rayon : %f\n", scene->objet[objet_cour].rayon);
                        }
                        else
                        {
                            printf("!!! Commande <Rayon> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Equation du plan
                    else if (!strcmp(tmp,"Equation"))
                    {
                        if (etat == 2)
                        {
                            fscanf(fichier, "%f", &(scene->objet[objet_cour].centre.xr));
                            fscanf(fichier, "%f", &(scene->objet[objet_cour].centre.yr));
                            fscanf(fichier, "%f", &(scene->objet[objet_cour].centre.zr));
                            fscanf(fichier, "%f", &(scene->objet[objet_cour].rayon));
                            printf(" Equation : (%f)X + (%f)Y + (%f)Z + (%f) = 0\n", scene->objet[objet_cour].centre.xr, scene->objet[objet_cour].centre.yr, scene->objet[objet_cour].centre.zr, scene->objet[objet_cour].rayon);
                        }
                        else
                        {
                            printf("!!! Commande <Equation> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Nombre de sommets
                    else if (!strcmp(tmp,"Nb_sommets"))
                    {
                        if (etat == 2 && scene->objet[objet_cour].type == 3)
                        {
                            fscanf(fichier, "%lu", &(scene->objet[objet_cour].nb_sommets));
                            if (scene->objet[objet_cour].nb_sommets > 2)
                            {
                                // Allocation
                                scene->objet[objet_cour].sommet = (point_3D *) malloc(scene->objet[objet_cour].nb_sommets*sizeof(point_3D));

                                som = scene->objet[objet_cour].sommet;
                                for (i = 0; i < scene->objet[objet_cour].nb_sommets; i++)
                                {
                                    som[i].xr = 0;
                                    som[i].yr = 0;
                                    som[i].zr = 0;
                                }
                                printf(" Nombre de sommets : %lu\n", scene->objet[objet_cour].nb_sommets);
                            }
                            else
                            {
                                printf("!!! Nombre de sommets insuffisants (3 au minimum)\n");
                                erreur = true;
                            }
                        }
                        else
                        {
                            printf("!!! Commande <Nb_sommets> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Liste des sommets
                    else if (!strcmp(tmp,"Sommets"))
                    {
                        if (etat == 2 && scene->objet[objet_cour].type == 3)
                        {
                            printf(" Sommets :\n");
                            som = scene->objet[objet_cour].sommet;
                            // Lecture du premier sommet
                            fscanf(fichier, "%f", &(som[0].xr));
                            fscanf(fichier, "%f", &(som[0].yr));
                            fscanf(fichier, "%f", &(som[0].zr));
                            printf("  %f %f %f\n", som[0].xr, som[0].yr, som[0].zr);
                            fflush(stdout);

                            // Lecture des autres
                            for (i = 1; i < scene->objet[objet_cour].nb_sommets; i++)
                            {
                                fscanf(fichier, "%f", &(som[i].xr));
                                fscanf(fichier, "%f", &(som[i].yr));
                                fscanf(fichier, "%f", &(som[i].zr));
                                printf("  %f %f %f\n", som[i].xr, som[i].yr, som[i].zr);
                                fflush(stdout);
                            }

                            // Calcul de la sphère englobante
                            sphere_englobante(scene, objet_cour);
                            #ifdef __DEBUG
                            printf(" Sphère englobante : Position (%f, %f, %f), Rayon %f\n", scene->objet[objet_cour].centre.xr, scene->objet[objet_cour].centre.yr, scene->objet[objet_cour].centre.zr, scene->objet[objet_cour].rayon);
                            #endif
                        }
                        else
                        {
                            printf("!!! Commande <Sommets> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Nombre de polygones
                    else if (!strcmp(tmp,"Nb_polygones"))
                    {
                        if (etat == 2 && scene->objet[objet_cour].type == 3)
                        {
                            // Lecture
                            fscanf(fichier, "%lu", &(scene->objet[objet_cour].nb_polys));

                            if (scene->objet[objet_cour].nb_polys > 0)
                            {
                                // Allocation
                                scene->objet[objet_cour].poly = (polygone *) malloc(scene->objet[objet_cour].nb_polys*sizeof(polygone));

                                // Valeurs par défaut
                                p = scene->objet[objet_cour].poly;
                                for (i = 0; i < scene->objet[objet_cour].nb_polys; i++)
                                {
                                    p[i].sommet[0] = 0;
                                    p[i].sommet[1] = 0;
                                    p[i].sommet[2] = 0;
                                    p[i].normale   = 0;
                                }

                                // Affichage
                                printf(" Nombre de polygones : %lu\n", scene->objet[objet_cour].nb_polys);
                            }
                            else
                            {
                                printf("!!! Nombre de polygones insuffisant (1 minimum)\n");
                                erreur = true;
                            }
                        }
                        else
                        {
                            printf("!!! Commande <Nb_polygones> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }
                    else if (!strcmp(tmp,"Polygones"))
                    {
                        if (etat == 2 && scene->objet[objet_cour].type == 3)
                        {
                            printf(" Polygones :\n");
                            som = scene->objet[objet_cour].sommet;
                            for (i = 0; i < scene->objet[objet_cour].nb_polys; i++)
                            {
                                somp = p[i].sommet;
                                fscanf(fichier, "%lu", &(somp[0]));
                                fscanf(fichier, "%lu", &(somp[1]));
                                fscanf(fichier, "%lu", &(somp[2]));
                                printf("  %lu %lu %lu\n", somp[0], somp[1], somp[2]);
                                fflush(stdout);
                            }

                            // Calcul de léquation du plan et des normales
                            plan(scene, objet_cour);
                            normales(scene, objet_cour);
                        }
                        else
                        {
                            printf("!!! Commande <Polygones> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Ombrage
                    else if (!strcmp(tmp,"Ombrage"))
                    {
                        if (etat == 2 && (scene->objet[objet_cour].type == 3 || scene->objet[objet_cour].type == 4))
                        {
                            fscanf(fichier, "%hu\n", &usi);
                            scene->objet[objet_cour].ombrage = (bool) (usi);
                            switch (scene->objet[objet_cour].ombrage)
                            {
                                case 0:
                                    printf(" Ombrage : Plat\n");
                                break;
                                case 1:
                                    printf(" Ombrage : Phong\n");
                                break;
                                default :
                                    printf("!!! Ombrage : Inconnu\n... Ombrage Plat activé\n");
                                    scene->objet[objet_cour].ombrage = 0;
                            }
                        }
                        else
                        {
                            printf("!!! Commande <Ombrage> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Animation de l'objet et de la scène
                    else if (!strcmp(tmp,"Anim_X"))
                    {
                        if (etat == 1)
                        {
                            fscanf(fichier, "%lf\n", &(scene->anim[0][0]));
                            fscanf(fichier, "%lf\n", &(scene->anim[0][1]));
                            fscanf(fichier, "%lf\n", &(scene->anim[0][2]));
                            fscanf(fichier, "%lf\n", &(scene->anim[0][3]));
                            printf(" Animation sur X : %f*cos(%f*t + %f) + %f\n", scene->anim[0][0], scene->anim[0][1],
                                        scene->anim[0][2], scene->anim[0][3]);
                        }
                        else if (etat == 2)
                        {
                            fscanf(fichier, "%lf\n", &(scene->objet[objet_cour].anim[0][0]));
                            fscanf(fichier, "%lf\n", &(scene->objet[objet_cour].anim[0][1]));
                            fscanf(fichier, "%lf\n", &(scene->objet[objet_cour].anim[0][2]));
                            fscanf(fichier, "%lf\n", &(scene->objet[objet_cour].anim[0][3]));
                            printf(" Animation sur X : %f*cos(%f*t + %f) + %f\n", scene->objet[objet_cour].anim[0][0], scene->objet[objet_cour].anim[0][1],
                                        scene->objet[objet_cour].anim[0][2], scene->objet[objet_cour].anim[0][3]);
                        }
                        else
                        {
                            printf("!!! Commande <Anim_X> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }
                    else if (!strcmp(tmp,"Anim_Y"))
                    {
                        if (etat == 1)
                        {
                            fscanf(fichier, "%lf\n", &(scene->anim[1][0]));
                            fscanf(fichier, "%lf\n", &(scene->anim[1][1]));
                            fscanf(fichier, "%lf\n", &(scene->anim[1][2]));
                            fscanf(fichier, "%lf\n", &(scene->anim[1][3]));
                            printf(" Animation sur X : %f*cos(%f*t + %f) + %f\n", scene->anim[1][0], scene->anim[1][1],
                                        scene->anim[1][2], scene->anim[1][3]);
                        }
                        else if (etat == 2)
                        {
                            fscanf(fichier, "%lf\n", &(scene->objet[objet_cour].anim[1][0]));
                            fscanf(fichier, "%lf\n", &(scene->objet[objet_cour].anim[1][1]));
                            fscanf(fichier, "%lf\n", &(scene->objet[objet_cour].anim[1][2]));
                            fscanf(fichier, "%lf\n", &(scene->objet[objet_cour].anim[1][3]));
                            printf(" Animation sur Y : %f*cos(%f*t + %f) + %f\n", scene->objet[objet_cour].anim[1][0], scene->objet[objet_cour].anim[1][1],
                                        scene->objet[objet_cour].anim[1][2], scene->objet[objet_cour].anim[1][3]);
                        }
                        else
                        {
                            printf("!!! Commande <Anim_Y> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }
                    else if (!strcmp(tmp,"Anim_Z"))
                    {
                        if (etat == 1)
                        {
                            fscanf(fichier, "%lf\n", &(scene->anim[2][0]));
                            fscanf(fichier, "%lf\n", &(scene->anim[2][1]));
                            fscanf(fichier, "%lf\n", &(scene->anim[2][2]));
                            fscanf(fichier, "%lf\n", &(scene->anim[2][3]));
                            printf(" Animation sur X : %f*cos(%f*t + %f) + %f\n", scene->anim[2][0], scene->anim[2][1],
                                        scene->anim[2][2], scene->anim[2][3]);
                        }
                        else if (etat == 2)
                        {
                            fscanf(fichier, "%lf\n", &(scene->objet[objet_cour].anim[2][0]));
                            fscanf(fichier, "%lf\n", &(scene->objet[objet_cour].anim[2][1]));
                            fscanf(fichier, "%lf\n", &(scene->objet[objet_cour].anim[2][2]));
                            fscanf(fichier, "%lf\n", &(scene->objet[objet_cour].anim[2][3]));
                            printf(" Animation sur Z : %f*cos(%f*t + %f) + %f\n", scene->objet[objet_cour].anim[2][0], scene->objet[objet_cour].anim[2][1],
                                        scene->objet[objet_cour].anim[2][2], scene->objet[objet_cour].anim[2][3]);
                        }
                        else
                        {
                            printf("!!! Commande <Anim_Z> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    else if (!strcmp(tmp,"Anim_Rot_X"))
                    {
                        if (etat == 1)
                        {
                            fscanf(fichier, "%lf\n", &(scene->anim_rot[0][0]));
                            fscanf(fichier, "%lf\n", &(scene->anim_rot[0][1]));
                            printf(" Animation sur Rot_X : %f*t + %f\n", scene->anim_rot[0][0], scene->anim_rot[0][1]);
                        }
                        else
                        {
                            printf("!!! Commande <Anim_X> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }
                    else if (!strcmp(tmp,"Anim_Rot_Y"))
                    {
                        if (etat == 1)
                        {
                            fscanf(fichier, "%lf\n", &(scene->anim_rot[1][0]));
                            fscanf(fichier, "%lf\n", &(scene->anim_rot[1][1]));
                            printf(" Animation sur Rot_Y : %f*t + %f\n", scene->anim_rot[1][0], scene->anim_rot[1][1]);
                        }
                        else
                        {
                            printf("!!! Commande <Anim_Y> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }
                    else if (!strcmp(tmp,"Anim_Rot_Z"))
                    {
                        if (etat == 1)
                        {
                            fscanf(fichier, "%lf\n", &(scene->anim_rot[2][0]));
                            fscanf(fichier, "%lf\n", &(scene->anim_rot[2][1]));
                            printf(" Animation sur Rot_Y : %f*t + %f\n", scene->anim_rot[2][0], scene->anim_rot[2][1]);
                        }
                        else
                        {
                            printf("!!! Commande <Anim_Z> mal placée\n");

                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Matériau de l'objet
                    else if (!strcmp(tmp,"Matiere"))
                    {
                        if (etat == 2)
                        {
                            fscanf(fichier, "%lu\n", &(scene->objet[objet_cour].materiau));
                            if (scene->objet[objet_cour].materiau >= scene->nb_materiaux)
                            {
                                printf("!!! Matière d'indice supérieur au nombre de matériaux total\n");
                                erreur = true;
                            }
                            else printf(" Matière : %lu\n", scene->objet[objet_cour].materiau);
                        }
                        else
                        {
                            printf("!!! Commande <Matiere> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Entête de la lumière
                    else if (!strcmp(tmp,"Lumiere"))
                    {
                        printf("\nLumière\n");
                        etat = 3;   /* Pour dire qu'on lit les caractéristiques de la lumière */

                        // Valeurs par défaut pour les caractéristiques de la lumière
                        scene->lumiere[++lum_cour].type=0;

                        strcpy(scene->lumiere[lum_cour].nom, "Lumière");
                        scene->lumiere[lum_cour].position.xr=0;
                        scene->lumiere[lum_cour].position.yr=100;
                        scene->lumiere[lum_cour].position.zr=0;
                        scene->lumiere[lum_cour].couleur.r=255;
                        scene->lumiere[lum_cour].couleur.v=255;
                        scene->lumiere[lum_cour].couleur.b=255;
                        scene->lumiere[lum_cour].far_attenuation[0]=0.1;
                        scene->lumiere[lum_cour].far_attenuation[1]=0.3;
                        scene->lumiere[lum_cour].far_attenuation[2]=0.3;
                    }

                    // Far attenuation
                    else if (!strcmp(tmp,"Attenuation"))
                    {
                        if (etat == 3)
                        {
                            if (!strcmp(scene->version,"0.1") || !strcmp(scene->version,"0.2") || !strcmp(scene->version,"0.3"))
                            {
                                fscanf(fichier, "%f", &(scene->lumiere[lum_cour].far_attenuation[0]));
                                if (scene->lumiere[lum_cour].far_attenuation[0] < 0)
                                {
                                    printf("!!! Le coefficient de far attenuation est inférieur à 0\n");
                                    erreur = true;
                                }
                                else printf(" Attenuation : %f\n", scene->lumiere[lum_cour].far_attenuation[0]);
                            }
                            else
                            {
                                fscanf(fichier, "%f", &(scene->lumiere[lum_cour].far_attenuation[0]));
                                fscanf(fichier, "%f", &(scene->lumiere[lum_cour].far_attenuation[1]));
                                fscanf(fichier, "%f", &(scene->lumiere[lum_cour].far_attenuation[2]));
                                if (scene->lumiere[lum_cour].far_attenuation[0] < 0
                                 || scene->lumiere[lum_cour].far_attenuation[1] < 0
                                 || scene->lumiere[lum_cour].far_attenuation[2] < 0
                                 || (scene->lumiere[lum_cour].far_attenuation[0]
                                   + scene->lumiere[lum_cour].far_attenuation[1]
                                   + scene->lumiere[lum_cour].far_attenuation[2]) == 0 )
                                {
                                    printf("!!! Au moins un des coefficients de far attenuation est inférieur à 0\n");
                                    erreur = true;
                                }
                                else printf(" Attenuation : %f %f %f\n",
                                        scene->lumiere[lum_cour].far_attenuation[0],
                                        scene->lumiere[lum_cour].far_attenuation[1],
                                        scene->lumiere[lum_cour].far_attenuation[2]);
                            }
                        }
                        else
                        {
                            printf("!!! Commande <Attenuation> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Intensité
                    else if (!strcmp(tmp,"Intensite"))
                    {
                        if (etat == 3)
                        {
                            if (scene->lumiere[lum_cour].type == 2)
                            {
                                fscanf(fichier, "%f", &(scene->lumiere[lum_cour].far_attenuation[0]));
                                printf(" Intensité : %f\n", scene->lumiere[lum_cour].far_attenuation[0]);
                            }
                            else
                            {
                                fscanf(fichier, "%f", &ftmp);
                                printf("!!! Commande <Intensite> incorrect pour une lumière de ce type !!!\n");
                                printf("??? Voulez-vous ne pas tenir compte du paramètre (taper 'O') ou arrêter (taper 'N') ??? ");
                                scanf("%c", &touche);
                                if ((touche == 'N') || (touche =='n'))
                                    erreur = true;
                            }
                        }
                        else
                        {

                            printf("!!! Commande <Intensite> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Direction
                    else if (!strcmp(tmp,"Direction"))
                    {
                        if (etat == 3)
                        {
                            fscanf(fichier, "%f", &(scene->lumiere[lum_cour].position.xr));
                            fscanf(fichier, "%f", &(scene->lumiere[lum_cour].position.yr));
                            fscanf(fichier, "%f", &(scene->lumiere[lum_cour].position.zr));
                            printf(" Direction : %f %f %f\n", scene->lumiere[lum_cour].position.xr, scene->lumiere[lum_cour].position.yr, scene->lumiere[lum_cour].position.zr);
                        }
                        else
                        {
                            printf("!!! Commande <Direction> mal placée\n");
                            erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Couleur
                    else if (!strcmp(tmp,"Couleur"))
                    {
                        if ((!strcmp(scene->version,"0.1")) && (etat == 2))
                            etat = 4;
                        switch (etat)
                        {
                            case 3: /* Lumière */
                                fscanf(fichier, "%hu", &usi);
                                scene->lumiere[lum_cour].couleur.r = (unsigned char) (usi);
                                fscanf(fichier, "%hu", &usi);
                                scene->lumiere[lum_cour].couleur.v = (unsigned char) (usi);
                                fscanf(fichier, "%hu", &usi);
                                scene->lumiere[lum_cour].couleur.b = (unsigned char) (usi);
                                printf(" Couleur : %d %d %d\n", scene->lumiere[lum_cour].couleur.r, scene->lumiere[lum_cour].couleur.v, scene->lumiere[lum_cour].couleur.b);
                            break;

                            case 4: /* Matériau */
                                // Ambiante et diffuse
                                fscanf(fichier, "%hu", &usi);
                                scene->materiau[materiau_cour].coul_amb.r = (unsigned char) (usi);
                                scene->materiau[materiau_cour].coul_dif.r = (unsigned char) (usi);
                                fscanf(fichier, "%hu", &usi);
                                scene->materiau[materiau_cour].coul_amb.v = (unsigned char) (usi);
                                scene->materiau[materiau_cour].coul_dif.v = (unsigned char) (usi);
                                fscanf(fichier, "%hu", &usi);
                                scene->materiau[materiau_cour].coul_amb.b = (unsigned char) (usi);
                                scene->materiau[materiau_cour].coul_dif.b = (unsigned char) (usi);
                                printf(" Couleur : %d %d %d\n", scene->materiau[materiau_cour].coul_amb.r, scene->materiau[materiau_cour].coul_amb.v, scene->materiau[materiau_cour].coul_amb.b);
                                if (!strcmp(scene->version,"0.1")) etat = 2;
                            break;

                            default:
                                printf("!!! Commande <Couleur> mal placée\n");
                                erreur = true;
                        }
                        fflush(stdout);
                    }

                    // Entête du matériau
                    else if (!strcmp(tmp,"Materiau"))
                    {
                        printf("\nMateriau\n");
                        fflush(stdout);
                        etat = 4;   /* Pour dire qu'on lit les caractéristiques du matériau */

                        // Valeurs par défaut pour les caractéristiques du matériau
                        strcpy(scene->materiau[++materiau_cour].nom, "Matériau");
                        scene->materiau[materiau_cour].ambiance    = 1.0;
                        scene->materiau[materiau_cour].coul_amb.r  = 255;
                        scene->materiau[materiau_cour].coul_amb.v  = 255;
                        scene->materiau[materiau_cour].coul_amb.b  = 255;
                        scene->materiau[materiau_cour].diffusion   = 0.0;
                        scene->materiau[materiau_cour].coul_dif.r  = 255;
                        scene->materiau[materiau_cour].coul_dif.v  = 255;
                        scene->materiau[materiau_cour].coul_dif.b  = 255;
                        scene->materiau[materiau_cour].reflexion   = 0.0;
                        scene->materiau[materiau_cour].coul_ref.r  = 255;
                        scene->materiau[materiau_cour].coul_ref.v  = 255;
                        scene->materiau[materiau_cour].coul_ref.b  =  55;
                        scene->materiau[materiau_cour].specularite = 0.0;
                        scene->materiau[materiau_cour].coul_spec.r = 255;
                        scene->materiau[materiau_cour].coul_spec.v = 255;
                        scene->materiau[materiau_cour].coul_spec.b = 255;
                        scene->materiau[materiau_cour].puis_spec   =   5;
                        scene->materiau[materiau_cour].opacite     = 1.0;
                        scene->materiau[materiau_cour].indice_ref  = 1.0;
                    }

                    // Opacité
                    else if (!strcmp(tmp,"Opacite"))
                    {
                        fscanf(fichier, "%f", &(scene->materiau[materiau_cour].opacite));
                        printf(" Opacité : %f\n", scene->materiau[materiau_cour].opacite);
                        fflush(stdout);
                    }

                    //Réfraction
                    else if (!strcmp(tmp,"Refraction"))
                    {
                        fscanf(fichier, "%f", &(scene->materiau[materiau_cour].indice_ref));
                        printf(" Indice de réfraction : %f\n", scene->materiau[materiau_cour].indice_ref);
                        fflush(stdout);
                    }

                    // Ambiance
                    else if (!strcmp(tmp,"Ambiance"))
                    {
                        if ((!strcmp(scene->version,"0.1")) || (!strcmp(scene->version,"0.2")))
                        {
                            fscanf(fichier, "%f", &(scene->materiau[materiau_cour].ambiance));
                            printf(" Ambiance : %f\n", scene->materiau[materiau_cour].ambiance);
                        }
                        else
                        {
                            fscanf(fichier, "%f", &(scene->materiau[materiau_cour].ambiance));
                            fscanf(fichier, "%hu", &usi);
                            scene->materiau[materiau_cour].coul_amb.r = (unsigned char) (usi);
                            fscanf(fichier, "%hu", &usi);
                            scene->materiau[materiau_cour].coul_amb.v = (unsigned char) (usi);
                            fscanf(fichier, "%hu", &usi);
                            scene->materiau[materiau_cour].coul_amb.b = (unsigned char) (usi);
                            printf(" Ambiance : %d%% %d %d %d\n", (int)(100*scene->materiau[materiau_cour].ambiance), scene->materiau[materiau_cour].coul_amb.r, scene->materiau[materiau_cour].coul_amb.v, scene->materiau[materiau_cour].coul_amb.b);
                        }
                        fflush(stdout);
                    }

                    // Réflexion
                    else if (!strcmp(tmp,"Reflexion"))
                    {
                        fscanf(fichier, "%f", &(scene->materiau[materiau_cour].reflexion));
                        fscanf(fichier, "%hu", &usi);
                        scene->materiau[materiau_cour].coul_ref.r = (unsigned char) (usi);
                        fscanf(fichier, "%hu", &usi);
                        scene->materiau[materiau_cour].coul_ref.v = (unsigned char) (usi);
                        fscanf(fichier, "%hu", &usi);
                        scene->materiau[materiau_cour].coul_ref.b = (unsigned char) (usi);
                        printf(" Réflexion : %d%% %d %d %d\n", (int)(100*scene->materiau[materiau_cour].reflexion), scene->materiau[materiau_cour].coul_ref.r, scene->materiau[materiau_cour].coul_ref.v, scene->materiau[materiau_cour].coul_ref.b);
                        fflush(stdout);
                    }

                    // Diffusion
                    else if (!strcmp(tmp,"Diffusion"))
                    {
                        if ((!strcmp(scene->version,"0.1")) || (!strcmp(scene->version,"0.2")))
                        {
                            fscanf(fichier, "%f", &(scene->materiau[materiau_cour].diffusion));
                            printf(" Diffusion : %f\n", scene->materiau[materiau_cour].diffusion);
                        }
                        else
                        {
                            fscanf(fichier, "%f", &(scene->materiau[materiau_cour].diffusion));
                            fscanf(fichier, "%hu", &usi);
                            scene->materiau[materiau_cour].coul_dif.r = (unsigned char) (usi);
                            fscanf(fichier, "%hu", &usi);
                            scene->materiau[materiau_cour].coul_dif.v = (unsigned char) (usi);
                            fscanf(fichier, "%hu", &usi);
                            scene->materiau[materiau_cour].coul_dif.b = (unsigned char) (usi);
                            printf(" Diffusion : %d%% %d %d %d\n", (int)(100*scene->materiau[materiau_cour].diffusion), scene->materiau[materiau_cour].coul_dif.r, scene->materiau[materiau_cour].coul_dif.v, scene->materiau[materiau_cour].coul_dif.b);
                        }
                        fflush(stdout);
                    }

                    // Spécularité
                    else if (!strcmp(tmp,"Specularite"))
                    {
                        fscanf(fichier, "%f", &(scene->materiau[materiau_cour].specularite));
                        fscanf(fichier, "%hu", &usi);
                        scene->materiau[materiau_cour].puis_spec = (unsigned char) (usi);
                        fscanf(fichier, "%hu", &usi);
                        scene->materiau[materiau_cour].coul_spec.r = (unsigned char) (usi);
                        fscanf(fichier, "%hu", &usi);
                        scene->materiau[materiau_cour].coul_spec.v = (unsigned char) (usi);
                        fscanf(fichier, "%hu", &usi);
                        scene->materiau[materiau_cour].coul_spec.b = (unsigned char) (usi);
                        printf(" Spécularité : %d%% °%hu %d %d %d\n", (int)(100*scene->materiau[materiau_cour].specularite), scene->materiau[materiau_cour].puis_spec, scene->materiau[materiau_cour].coul_spec.r, scene->materiau[materiau_cour].coul_spec.v, scene->materiau[materiau_cour].coul_spec.b);
                        fflush(stdout);
                    }

                    // EOF
                    else if (!strcmp(tmp,"Eof"))
                    {
                        fin = true;
                    }

                    // Erreur
                    else
                    {
                        printf("\n!!! Commande <%s> non prise en charge par le programme...\n\n", tmp);
                        erreur = true;
                    }
                }
        }
    }
    else
    {
    	printf("\nLe fichier %s n'existe pas.\n", chemin);
      return false;
    }
    // Fermeture
    fclose(fichier);

    if (taille_ecran_x)
    {
        scene->pitch_x = taille_ecran_x/scene->res_x;
        scene->pitch_y = taille_ecran_y/scene->res_y;
    }

    if (!strcmp(scene->version,"0.1"))
        for (usi = 0; usi < scene->nb_materiaux; usi++)
        {
            scene->materiau[usi].ambiance*=scene->materiau[usi].opacite;
            scene->materiau[usi].diffusion*=scene->materiau[usi].opacite;
        }

    if (!erreur)
    {
        printf("\n... Lecture du fichier %s terminée avec succès.\n\n", chemin);
        fflush(stdout);
        return true;
    }

    printf("\n!!! Lecture du fichier %s terminée, mais il y a des erreurs de syntaxe.\n\n", chemin);
    fflush(stdout);
    return false;
}

