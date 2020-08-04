#include "main.h"

//Initialise et lance ce dont allegro à besoins pour fonctionner.
void lancer_allergro(int largeur, int hauteur)
{
    allegro_init();
    install_keyboard();
    install_mouse();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, largeur, hauteur, 0, 0) != 0)
    {
        allegro_message("Probleme mode graphique : %s", allegro_error);
         allegro_exit();
        exit(EXIT_FAILURE);
    }
	show_mouse(screen);

}

//Récupère la progression précédente du joueur à partir d'un fichier binaire.
void recuperer_progression(t_global* VAR)
{
    FILE* fichier = fopen("ressources/progression.dat", "r");
    if (fichier != NULL)
    {
        fread(&(VAR->progression), sizeof(int), 1, fichier);
        fread(&(VAR->deplacement), sizeof(int), 1, fichier);
        fread(&(VAR->scrolling_x), sizeof(int), 1, fichier);
        fclose (fichier);
    }
    else
    {
        VAR->progression = 1;
        VAR->deplacement = 0;
        VAR->scrolling_x = 0;
    }

}

//Sauvegarde la progression du joueur dans un fichier binaire.
void save_progression(t_global* VAR)
{
    FILE* fichier = fopen("ressources/progression.dat", "w");
    if (fichier != NULL)
    {
        fwrite(&(VAR->progression), sizeof(int), 1, fichier);
        fwrite(&(VAR->deplacement), sizeof(int), 1, fichier);
        fwrite(&(VAR->scrolling_x), sizeof(int), 1, fichier);
        fclose (fichier);
    }

}

//Remet à 0 tous les paramètres de la carte de jeu (position des bots, modification potentielle du terrain, etc)
void reset_carte(t_global* VAR)
{
    int i;
    VAR->fin = 1;
    VAR->prgm_lance = 0;
    for(i=0; i<VAR->nbr_perso; i++)
    {
        VAR->perso[i].x = VAR->perso[i].xS;
        VAR->perso[i].y = VAR->perso[i].yS;
        VAR->perso[i].z = VAR->perso[i].zS;
        VAR->perso[i].orientation = VAR->perso[i].orientationS;
        VAR->perso[i].inventaire = 0;
        VAR->perso[i].executer_prgm = 0;
        VAR->perso[i].charge = VAR->perso[i].prgm->last;
    }
    copier_matrice(VAR);
    VAR->MAP->nbr_bouton = VAR->MAP->nbr_boutonS;
}

//Affiche les différentes bitmaps utilisées dans le bon ordre.
void afficher(t_global* VAR)
{
    creer_map(VAR);
    afficher_prgm(VAR);
    afficher_boutons_prgm(VAR);

    stretch_sprite(VAR->buffer, VAR->MAP->terrain, 23 - VAR->MAP->deplacement_x[2] ,32 - VAR->MAP->deplacement_y[2], VAR->MAP->bmp_w/VAR->MAP->grossissement, VAR->MAP->bmp_h/VAR->MAP->grossissement );
    stretch_sprite(VAR->IMG->overlay_hb2, VAR->MAP->terrain_hb, 23 - VAR->MAP->deplacement_x[2] ,32 - VAR->MAP->deplacement_y[2], VAR->MAP->bmp_w/VAR->MAP->grossissement , VAR->MAP->bmp_h/VAR->MAP->grossissement);

    rectfill(VAR->buffer, 608,31, 608+190, 31+190, makecol(0,0,0));
    draw_sprite(VAR->buffer, VAR->bmp_prgm, X_PRGM, Y_PRGM - VAR->perso[VAR->perso_select].defilement_prgm);

    stretch_sprite(VAR->buffer, VAR->IMG->overlay, 0,0, SCREEN_W, SCREEN_H);
    if (VAR->prgm_lance == 0)
        stretch_sprite(VAR->buffer, VAR->bmp_bouton,0,0, SCREEN_W, SCREEN_H);
    blit(VAR->buffer, screen,0,0,0,0,SCREEN_W, SCREEN_H);

}

//Utilisé en fin de jeu, change juste l'aspect de toutes les portes pour les "ouvrir".
void ouvrir_porte(t_global* VAR)
{
    play_sample(VAR->SON->ouverture_porte, 255, 255, 1000, 0);
    int i,j,k;

    for (i=0; i<VAR->MAP->tailleX; i++)
    {
        for (j=0; j<VAR->MAP->tailleY; j++)
        {
            for (k=0; k< VAR->MAP->tailleZ; k++)
            {
                if (VAR->MAP->matrice[i][j][k] == 'p')
                {
                    VAR->MAP->matrice[i][j][k] = 'q';
                }
                else if (VAR->MAP->matrice[i][j][k] == 'P')
                {
                    VAR->MAP->matrice[i][j][k] = 'Q';
                }
            }
        }
    }
}

//Verifie que l'utilisateur a accepte les conditions d'utilisation et de partage des fichiers présents dans le dossier.
void EULA()
{
    char reponse[11];
    char c;
    int i, fin;
    fin = 1;
    FILE* fichier = fopen("EULA.txt", "r");
    if (fichier == NULL)
    {
        fin = 0;
    }
    else
    {
        for (i=0; i<11; i++)
        {
            fscanf(fichier, "%c", &c);
            reponse[i] = c;

            if (reponse[i] == '\n')
            {
                reponse[i] = '\0';
                i = 11;
            }
        }
        fclose(fichier);


        if (reponse[0] != 'E')
        {
            fin = 0;
        }
        if (reponse[1] != 'U')
        {
            fin = 0;
        }
        if (reponse[2] != 'L')
        {
            fin = 0;
        }
        if (reponse[3] != 'A')
        {
            fin = 0;
        }
        if (reponse[4] != '=')
        {
            fin = 0;
        }
        if (reponse[5] != 't' && reponse[5] != 'T')
        {
            fin = 0;
        }
        if (reponse[6] != 'r' && reponse[6] != 'R')
        {
            fin = 0;
        }
        if (reponse[7] != 'u' && reponse[7] != 'U')
        {
            fin = 0;
        }
        if (reponse[8] != 'e' && reponse[8] != 'E')
        {
            fin = 0;
        }
    }

    if (fin == 0)
    {
        allegro_message("EULA non acceptee ou absente. \nMerci de prendre connaissance du fichier 'Eula.txt' present a la racine du dossier pour pouvoir utiliser ce logiciel.");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}






