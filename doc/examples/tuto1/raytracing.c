/***************************************************************************

                          raytracing.c  -  Raytracing
                          ---------------------------
    Commenc� le          : Fri Dec 7 2001
    Copyright            : (C) 2001 by David Fernandes
    Email                : mchepoil@caramail.com
    Site                 : http://www.multimania.com/davvador2416

 ***************************************************************************/


#include "GL/glut.h"
#include "raytracing.h"

extern scene_3D             scene;
extern intensite_couleur    *page_tmp;
extern GLenum               ImgFormat;


void unitaire(vecteur_3D *v)
{
    float norme= sqrt((v->vxr)*(v->vxr)+(v->vyr)*(v->vyr)+(v->vzr)*(v->vzr));

    if (norme)
    {
        v->vxr /= norme;
        v->vyr /= norme;
        v->vzr /= norme;
    }
}

float scal(vecteur_3D *v1, vecteur_3D *v2)
{
    return (v1->vxr)*(v2->vxr) + (v1->vyr)*(v2->vyr) + (v1->vzr)*(v2->vzr);
}

float intersection(point_3D pt, vecteur_3D V, unsigned short int *obj)
{
    const float Eps = 0.02;
    float       delta,
                alpha1 = Max_Alpha,
                alpha2 = Max_Alpha,
                alpha = Max_Alpha;
    double      a,b,c;
    unsigned long int i;

    for (i = 0; i < scene.nb_objets; i++)
    {
        if (scene.objet[i].type == 1)       // Sphere
        {
            a = (V.vxr) * (V.vxr);
            b = 2 * (V.vxr) * (pt.xr-scene.objet[i].centre.xr);
            c = (pt.xr-scene.objet[i].centre.xr) * (pt.xr-scene.objet[i].centre.xr);

            a += (V.vyr) * (V.vyr);
            b += 2 * (V.vyr) * (pt.yr-scene.objet[i].centre.yr);
            c += (pt.yr-scene.objet[i].centre.yr) * (pt.yr-scene.objet[i].centre.yr);

            a += (V.vzr) * (V.vzr);
            b += 2 * (V.vzr) * (pt.zr-scene.objet[i].centre.zr);
            c += (pt.zr-scene.objet[i].centre.zr) * (pt.zr-scene.objet[i].centre.zr);

            c -= scene.objet[i].rayon*scene.objet[i].rayon;

            if (fabs(a) < Eps)
            {
                if (fabs(b) < Eps) alpha1 = Max_Alpha;
                else
                {
                    alpha1 = -c/b;
                    if (alpha1 < Eps) alpha1 = Max_Alpha;
                }
                alpha2 = Max_Alpha;
            }
            else
            {

                delta =  b*b - 4*a*c;

                if (delta<Eps)
                {
                    alpha1 = Max_Alpha;
                    alpha2 = Max_Alpha;
                }
                else
                {
                    if (delta)
                    {
                        alpha1 = (-b -sqrt(delta)) / (2*a);
                        alpha2 = (-b +sqrt(delta)) / (2*a);
                        if (alpha1<Eps) alpha1 = Max_Alpha;
                        if (alpha2<Eps) alpha2 = Max_Alpha;

                    }
                    else
                    {
                        alpha1 = -b / (2*a);
                        if (alpha1<Eps) alpha1 = Max_Alpha;
                        alpha2 = Max_Alpha;
                    }
                }
            }
        }

        else if (scene.objet[i].type == 2)       // Plan
        {
            a = scene.objet[i].centre.xr;
            b = scene.objet[i].centre.yr;
            c = scene.objet[i].centre.zr;
            alpha1 = scene.objet[i].rayon;

            alpha2 = (a*V.vxr + b*V.vyr + c*V.vzr);

            if (!alpha2 && alpha1)      // Rayon parall�le au plan
            {
                alpha1 = Max_Alpha;
                alpha2 = Max_Alpha;
            }
            if (alpha1 < Max_Alpha)
            {
                if (alpha2) alpha2 = -(a*pt.xr + b*pt.yr + c*pt.zr + alpha1) / alpha2;
                else alpha2 = 1;
                if (alpha2 < Eps)
                    alpha2 = Max_Alpha;
                alpha1 = Max_Alpha;
            }
        }

        if (alpha1<alpha)
        {
            alpha = alpha1;
            *obj = i;
        }
        if (alpha2<alpha)
        {
            alpha = alpha2;
            *obj = i;
        }
    }
    if (alpha<Max_Alpha) return alpha;
    return 0;
}

couleur calcul_rayon(float x, float y)
{
    vecteur_3D  V;

    V.vzr = scene.focale;
    V.vxr = x*scene.pitch_x;
    V.vyr = y*scene.pitch_y;
    vecteur_rotation_x(&V,&(scene.rot_x));
    vecteur_rotation_y(&V,&(scene.rot_y));
    vecteur_rotation_z(&V,&(scene.rot_z));
    unitaire(&V);

    return lancer_rayon(scene.position, V);
}

void no_antialiasing()
{
    int         xe,ye,
                x,y;
    couleur     pixel;

    // On commence en haut et en bas en m�me temps
    for (y = -scene.res_y/2; y < 0; y++)
    {
        for (x = -scene.res_x/2; x < scene.res_x/2; x++)
        {
            pixel = calcul_rayon((float)(x)+0.5, (float)(y)+0.5);

            xe = x+scene.res_x/2;
            ye = y+scene.res_y/2;
            page_tmp[ye*scene.res_x*3+xe*3]   = pixel.r;
            page_tmp[ye*scene.res_x*3+xe*3+1] = pixel.v;
            page_tmp[ye*scene.res_x*3+xe*3+2] = pixel.b;
        }
        y = -y-1;
        for (x = -scene.res_x/2; x < scene.res_x/2; x++)
        {
            pixel = calcul_rayon((float)(x)+0.5, (float)(y)+0.5);

            xe = x+scene.res_x/2;
            ye = y+scene.res_y/2;
            page_tmp[ye*scene.res_x*3+xe*3]   = pixel.r;
            page_tmp[ye*scene.res_x*3+xe*3+1] = pixel.v;
            page_tmp[ye*scene.res_x*3+xe*3+2] = pixel.b;
        }
        y = -y-1;
        glDrawPixels(scene.res_x, scene.res_y, ImgFormat, GL_UNSIGNED_BYTE, page_tmp);
        glutSwapBuffers();
    }

    // La ligne du milieu
    for (x = -scene.res_x/2; x < scene.res_x/2; x++)
    {
        pixel = calcul_rayon((float)(x)+0.5, (float)(y)+0.5);

        xe = x+scene.res_x/2;
        ye = scene.res_y/2;
        page_tmp[ye*scene.res_x*3+xe*3]   = pixel.r;
        page_tmp[ye*scene.res_x*3+xe*3+1] = pixel.v;
        page_tmp[ye*scene.res_x*3+xe*3+2] = pixel.b;
    }
    glDrawPixels(scene.res_x, scene.res_y, ImgFormat, GL_UNSIGNED_BYTE, page_tmp);
    glutSwapBuffers();
}

// On lance le rayon � partir du point pt de direction V
couleur lancer_rayon(point_3D pt, vecteur_3D V)
{
    unsigned short int  obj,
                        mater;
    float               alpha,
                        tmp;
    couleur             amb;
    point_3D            inter;
    int                 i;

    amb.r = 0;
    amb.v = 0;
    amb.b = 0;

    if ((alpha = intersection(pt, V, &obj)))
    {
        mater = scene.objet[obj].materiau;

        inter.xr = pt.xr+alpha*V.vxr;
        inter.yr = pt.yr+alpha*V.vyr;
        inter.zr = pt.zr+alpha*V.vzr;

        for (i = 0; i < scene.nb_lumieres; i++)
        {
            // Lumi�re ambiante
            if (scene.lumiere[i].type == 0)
            {
                tmp = 1;//scene.materiau[mater].ambiance;
                if ((unsigned short int) (amb.r+tmp*scene.lumiere[i].couleur.r*scene.materiau[mater].coul_amb.r/255) > scene.materiau[mater].coul_amb.r) amb.r = scene.materiau[mater].coul_amb.r;
                else amb.r += tmp*scene.lumiere[i].couleur.r*scene.materiau[mater].coul_amb.r/255;

                if ((unsigned short int) (amb.v+tmp*scene.lumiere[i].couleur.v*scene.materiau[mater].coul_amb.v/255) > scene.materiau[mater].coul_amb.v) amb.v = scene.materiau[mater].coul_amb.v;
                else amb.v += tmp*scene.lumiere[i].couleur.v*scene.materiau[mater].coul_amb.v/255;

                if ((unsigned short int) (amb.b+tmp*scene.lumiere[i].couleur.b*scene.materiau[mater].coul_amb.b/255) > scene.materiau[mater].coul_amb.b) amb.b = scene.materiau[mater].coul_amb.b;
                else amb.b += tmp*scene.lumiere[i].couleur.b*scene.materiau[mater].coul_amb.b/255;
            }
            // Lumi�re ponctuelle ou directionnelle
            else if (scene.lumiere[i].type == 1 || scene.lumiere[i].type == 2)
            {
            }
        }
    }
    else return scene.fond;

    return amb;
}

// Sauvegarde de l'image au format PPM
void sauvegarder(char *chemin)
{
    register short int i, j;
    FILE* fichier;

    // Ouverture
    printf("\nCr�ation du fichier...");
    fflush(stdout);
    if ((fichier = fopen(chemin, "w")))
    {
        printf(" Ok\n");
        printf("Ecriture du fichier...");
        fflush(stdout);

        // Ecriture
            // Ent�te
        fprintf(fichier, "P6\n");
        fprintf(fichier, "%d %d \n", scene.res_x, scene.res_y);
        fprintf(fichier,"%d\n",255);
            // Corps
        for(j=scene.res_y-1; j > -1 ; j--)
            for(i=0; i < scene.res_x ; i++)
        fprintf(fichier, "%c%c%c", page_tmp[j * scene.res_x*3 + i*3], page_tmp[j * scene.res_x*3 + i*3+1], page_tmp[j * scene.res_x*3 + i*3+2]);
        printf(" Ok\n");
        fflush(stdout);

    // Fermeture
    fclose(fichier);
    printf("\n... Le fichier %s a �t� cr�e avec succ�s.\n", chemin);
    fflush(stdout);
    }
    else printf("\n!!! Le fichier %s n'a pas pu �tre cr�e.\n", chemin);
    fflush(stdout);
}
