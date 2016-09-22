/***************************************************************************

                          infos_compilation.h
                          -------------------
    Commencé le          : Fri Dec 7 2001
    Copyright            : (C) 2001 by David Fernandes
    Email                : mchepoil@caramail.com
    Site                 : http://www.multimania.com/davvador2416

 ***************************************************************************/


	/* Définition des modes de compilation */

#ifndef __infos_compilation
	#define __infos_compilation

	// Définition du mode graphique utilisé
	#define __Open_GL        				// A mettre en commentaire si nécessaire
	//#define __13_h        					// A mettre en commentaire si nécessaire
	//#define __Direct_X  					// A mettre en commentaire si nécessaire


	#ifdef __13_h
	    #define __BORLAND
		#define __DOS

		#define __EXC						// A mettre en commentaire si nécessaire
	    #define __3D_software

		#define __DEBUG						// A mettre en commentaire si nécessaire
		//#define __BETA					// Y'a pas grand chose en plus
		//#define __pas_bon					// Avec ça, ça ne marche pas
	#endif

	#ifdef __Direct_X
	    #define __VISUAL
		#define __WIN32

		#define __EXC
	    #define __3D_software

		#define __DEBUG						// A mettre en commentaire si nécessaire
		//#define __BETA					// Y'a pas grand chose en plus
		//#define __pas_bon					// Avec ça, ça ne marche pas
	#endif

	#ifdef __Open_GL
	    #define __UNIX
	    //#define __WIN32                   // Pas encore implémenté

	    #define __3D_software				// A mettre en commentaire si nécessaire

		//#define __DEBUG						// A mettre en commentaire si nécessaire
		//#define __BETA					// Y'a pas grand chose en plus
		//#define __pas_bon					// Avec ça, ça ne marche pas
	#endif


#define pi 3.1415926

#ifdef __13_h
#define mode_graphique 19               // = Mode graphique à utiliser
#define mode_texte 3                    // = Mode texte à utiliser
#define RES_X 320                       // = Résolution horizontale
#define RES_Y 200                       // = Résolution verticale
#define maxx 319                        // = RES_X-1
#define maxy 199                        // = RES_Y-1
#define RES_X_RES_Y 64000               // = RES_X*RES_Y
#define max_z_buffer 16000              // = RES_X*RES_Y/4
#define max_intensite_couleur 16000     // = RES_X*RES_Y/4
#define div_distance 4                  // = Coefficient pour l'effet distance
typedef unsigned char profondeur_z_buffer;
typedef unsigned char intensite_couleur;
#endif // __13_h

#ifdef __Direct_X
#define RES_X 640                       // = Résolution horizontale
#define RES_Y 480                       // = Résolution verticale
#define maxx 639                        // = RES_X-1
#define maxy 479                        // = RES_Y-1
#define div_distance 2                  // = Coefficient pour l'effet distance
typedef unsigned short int profondeur_z_buffer;
typedef unsigned char intensite_couleur;
#endif // __Direct_X

#ifdef __Open_GL
#define RES_X 640                       // = Résolution horizontale
#define RES_Y 480                       // = Résolution verticale
#define maxx 639                        // = RES_X-1
#define maxy 479                        // = RES_Y-1
#ifdef __3D_software
    #define maxz_visible 512                // = Profondeur maximale visible
    #define RES_X_RES_Y 307200              // = RES_X*RES_Y
    #define max_z_buffer 153600             // = RES_X*RES_Y/2
    #define max_intensite_couleur 230400    // = 3*RES_X*RES_Y/4
    #define div_distance 2                  // = Coefficient pour l'effet distance
    typedef unsigned short int profondeur_z_buffer;
    typedef unsigned char intensite_couleur;
#endif
typedef enum {false,true} bool;
#endif // __Open_GL


#if RES_X == 320
#if RES_Y == 200
#define __320_x_200
#endif
#endif


#endif


