/***************************************************************************

                          antialiasing.c  -  Raytracing
                          -----------------------------
    Commencé le          : Sat Jan 02 2002
    Copyright            : (C) 2002 by David Fernandes
    Email                : mchepoil@caramail.com
    Site                 : http://www.multimania/davvador2416

 ***************************************************************************/



#include "GL/glut.h"


extern scene_3D             scene;
extern intensite_couleur    *page_tmp;
extern GLenum               ImgFormat;

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

    return lancer_rayon(scene.position, V, scene.iter, -1);
}

void no_antialiasing()
{
    int         xe,ye,
                x,y;
    couleur     pixel;

    // On commence en haut et en bas en même temps
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


