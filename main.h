#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>

#define TAILLE 100
#define ECHELLE (1038.0/5447)*TAILLE /// = ((taille du cube/ taille de l'image)*taille)*(3/13) (ratio trouve dans les calculs de M. Fercoq)

#define X_BOUTON 25
#define Y_BOUTON 490
#define ECHELLE_BOUTON 60
#define ECART_BOUTON 12

#define X_PRGM 618
#define X_PRGM 618
#define Y_PRGM 39
#define ECHELLE_PRGM 32
#define ECART_PRGM 8

#define ASSOMBRI 40 ///Facteur d'assombrissement pour l'affichage du menu principal
#define NBR_MENU 4 ///Nombre de choix proposés par le menu principal
#define RETURN_MENU_NIVEAUX_X 10
#define RETURN_MENU_NIVEAUX_Y 10

#define NBR_NIVEAU 6

typedef struct rectangle
{
    int x1;
    int y1;
    int x2;
    int y2;
    int color;
}m_rectangle;


typedef struct PRGM t_prgm;
struct PRGM
{
    char action;
    int param;
};

typedef struct MAILLON t_maillon;
struct MAILLON
{
    t_prgm* objet;
    t_maillon* next;
    t_maillon* prev;
};

typedef struct ANCRE t_ancre;
struct ANCRE
{
    t_maillon* first;
    t_maillon* last;
};


typedef struct PERSO t_perso;
struct PERSO
{
    t_maillon* charge;
    t_ancre* prgm;
    char actions[9];
    BITMAP*** skin;
    BITMAP* skin_hb[4];
    int orientation;
    int x;
    int y;
    int z;
    int orientationS;
    int xS;
    int yS;
    int zS;
    int projX;
    int projY;
    int compteur_prgm;
    int executer_prgm;
    int defilement_prgm;
    int inventaire;
};

typedef struct IMG t_img;
struct IMG
{
    BITMAP* Atlas[4];
    BITMAP* Atlas_cube[4];
    BITMAP* tourelle[4];
    BITMAP* cube_clair;
    BITMAP* cube_sombre;
    BITMAP* compagnion_cube;
    BITMAP* boutton;
    BITMAP* boutton_presse;
    BITMAP* boutton_cube;
    BITMAP** porte;
    BITMAP** porte_ouverte;
    BITMAP* vide;
    BITMAP* action_avancer;
    BITMAP* action_porter;
    BITMAP* action_pousser;
    BITMAP* action_sauter;
    BITMAP* action_tourner_droite;
    BITMAP* action_tourner_gauche;
    BITMAP* action_attendre;
    BITMAP* action_selecteur;
    BITMAP* overlay;
    BITMAP* overlay_hb;
    BITMAP* overlay_hb2;
    BITMAP* fin_reussite;
    BITMAP* fin_echec;
    BITMAP* fin_hb;


    BITMAP *fond_panoramique;///Image du panorama de l'interface du menu principal
    BITMAP *fond_panoramique_assombris;///Image du panorama assombris
    BITMAP *hitbox1;///Image des rectangles de sélection du menu principal
    BITMAP *hitbox2;///Image du texte du menu principal
    BITMAP *hitbox2_assombris;///Image du texte assombris du menu principal
    BITMAP *carte_monde;///Image de fond de l'interface de sélection des niveaux
    BITMAP *personnage_principal[6];///Image du personnage principal (pour sélection des niveaux)
    BITMAP *case_niveaux;///Image des cases de niveaux
    BITMAP *retour_menu_principal;///Image de l'icône de retour vers le menu principal (pour menu de sélection des niveaux)
    BITMAP *regles_du_jeu;///Image contenant les règles du jeu
};

typedef struct SON t_son;
struct SON
{
    SAMPLE* Button_press;
    clock_t c_Button_press;
    SAMPLE* Button_release;
    clock_t c_Button_release;
    SAMPLE* frottement[4];
    clock_t c_frottement;
    SAMPLE* pas[5];
    clock_t c_pas;
    SAMPLE* Buzzer;
    clock_t c_Buzzer;
    SAMPLE* ouverture_porte;
    clock_t c_ouverture_porte;
    SAMPLE* Machine_gun;
    clock_t c_Machine_gun;

    SAMPLE* Music;
    clock_t c_Music;
    SAMPLE* Select;
    clock_t c_Select;
    SAMPLE* Glados_Intro;
    clock_t c_Glados_Intro;
    SAMPLE* Glados_But;
    clock_t c_Glados_But;
};

typedef struct MAP  t_map;
struct MAP
{
    char*** matrice;
    char*** matriceS;
    BITMAP* terrain;
    BITMAP* terrain_hb;
    float grossissement;
    int nbr_bouton;
    int nbr_boutonS;
    int nbr_tourelle;
    int nbr_tourelleS;
    int tailleX;
    int tailleY;
    int tailleZ;
    int bmp_h;
    int bmp_w;
    int deplacement_x[3];
    int deplacement_y[3];
    int deplacement_ok;
};

typedef struct CLIC t_clic; ///Source: Contrôle informatique : Librairie graphique Allegro & Architecture des ordinateurs, DST ING1 de l'ECE Paris, du 22/04/2017
struct CLIC
{
    int prev;
    int now;
};


typedef struct DRAG t_drag;
struct DRAG
{
    int actif;
    char action;
    clock_t delay;
};


typedef struct GLOBAL t_global;
struct GLOBAL
{
    BITMAP* buffer;
    BITMAP* bmp_bouton;
    BITMAP* bmp_prgm;
    t_img* IMG;
    t_son* SON;
    t_map* MAP;
    t_perso* perso;
    int nbr_perso;
    int perso_select;
    int fin;
    int progression;
    int deplacement;
    int scrolling_x;

    int prgm_lance;
    int prgm_fin;

    t_drag drag;
    t_clic clicD;
    t_clic molette;
    m_rectangle *r_menu1;
    int couleur_precedente;
};

#include "charger_map.h"
#include "Divers.h"
#include "Execution_prgrm.h"
#include "Gestion_images.h"

#include "Gestion_personnage.h"
#include "Gestion_son.h"
#include "hitbox.h"
#include "menu.h"
#include "Menu_Selection.h"
#include "regles_du_jeu.h"


#endif // MAIN_H_INCLUDED
