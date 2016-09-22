/*==============================================================================\
*                                                                               *
*                       /===========================\                           *
*                       * Raytracing - Tutorial n°1 *                           *
*                       \===========================/                           *
*                                                                               *
*                                                                               *
*        Auteur :   Dav Vador                                                   *
*                 __                                                            *
*               _~\/~_                                                          *
*              |(o)(o)|              Email  :   mchepoil@caramail.com           *
*               \ \/ /                          ~~~~~~~~~~~~~~~~~~~~~           *
*                (^^)                                                           *
*                                                                               *
*            *       .       .     +        .    .  *      .   +             .  *
*             .    .    *      .-------°°°°°°°°-------.           .   .   +     *
*               +       .:::~~°:::O::::(::oo::)::::O:::°~~:::.      *           *
*  <Site>  :        <{{ http://www.multimania.com/davvador2416 }}>      °   *   *
*                .     '<-(||}-----{#}~~~[##]~~~{#}-----{||)->'      .      .   *
*             *     .     _/           _/ ## \_           \_     .  *     .     *
\==============================================================================*/


/*==============================================================================\
*                                                                               *
*  Fichier       : main.c                                                       *
*                                                                               *
*  Auteur        : Dav Vador                                                    *
*  Commencé le   : 13 Mars 2k+2                                                 *
*  Modifications : (si vous modifiez le code, mettez votre nom ici)             *
\==============================================================================*/


#include "GL/glut.h"
#include "infos_compilation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "3d.h"
#include "import.h"
#include "raytracing.h"

GLenum                      ImgFormat=GL_RGB;
intensite_couleur           *page_tmp;
scene_3D                    scene;
char                        chemin_sav[256];
bool                        sauve = true,
                            draw = true;
extern float                sinus[360];
extern float                cosinus[360];



/* Implémentation des fonctions utilisées */


// Affichage en rendu normal
void Calculer_Scene()
{
	draw = false;
    no_antialiasing();
}

// Affichage de la scène
void DrawScene()
{
    if (draw)   // Recalcul de l'image
    {
        effacer_ecran(page_tmp);    // Ca permet de voir où on en est pendant le rendu

        Calculer_Scene();
        if (!sauve) sauvegarder(chemin_sav);
        sauve = true;
    }
    else        // Affichage du tampon
    {
        glDrawPixels(scene.res_x, scene.res_y, ImgFormat, GL_UNSIGNED_BYTE, page_tmp);
        glutSwapBuffers();
    }
}

// Affichage
void display()
{
    DrawScene();
}

// Fonction de test de touche du clavier
static void key( unsigned char key, int x, int y )
{
    switch (key)
    {
        case ' ' :  // Réaffichage du tampon vidéo
            printf("\nRéaffichage du tampon vidéo\n");
            display();
        break;

        case 27:               /* sortie si ESC */
            exit(0);
    }
}

/* Fonction de reaffichage */
static void reshape(GLsizei w, GLsizei h)
{
}

// Programme principal
int main(int argc, char** argv)
{
    // A éxecuter en fin de programme
    atexit(desallocation_scene_3D);

    // Initialisation des sinus et cosinus
    init_cosinus();
    init_sinus();

    // Chargement de la scène
    if ( argc > 1)
    {
        if (!charger_rtd(argv[1], &scene)) return -1;
    }
    else return -1;

    if ( argc > 2)
    {
    	// Sauvegarde dans fichier
        strcpy(chemin_sav,argv[2]);
        sauve = false;
    }
    else sauve = true;

    // Allocation de la page Vidéo temporaire
    page_tmp = (intensite_couleur*) malloc( 3 * scene.res_x * scene.res_y * sizeof(intensite_couleur));

    // Initialisation de glut
    glutInit(&argc, argv);

    // Initialisation du mode graphique
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    // Initialisation de la fenêtre
    glutInitWindowSize(scene.res_x, scene.res_y);
    glutCreateWindow ("RayTracing - Dav Vador");
    glClearColor (0.0, 0.0, 0.0, 0.0);

    // Initialisation des périphériques d'entrée
    glutKeyboardFunc(key);

    // Initialisation de l'affichage
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Boucle principale
    glutMainLoop();

    return 0;
}

