#include "main.h"
/**
  * Il y a des instabilitées dans le programme, dont on ignore l'origine.
  * Le programme plante, de manière aléatoire, et sans raison apparente.
  * Le débugger de CodeBlocks nous indique un problème avec alleg42.dll (ou alleg44.dll, en fonction des versions)
  * Donc on en a déduit que le problème venait probablement d'Allegro même, et non pas de nous.
  * (A savoir que toutes les bitmaps ne sont chargée qu'UNE SEULE fois en début de main,
  *  et que toutes les bitmaps créées sont systématiquement détruites, donc c'est peut probable que ce soit
  *  un problème de mémoire).
 */

int main(int argc, char* argv[])
{
    lancer_allergro(800,600);
    srand(time(NULL));

    EULA();

    int i;
    int choix_menu = 0;


    t_global* VAR = malloc(sizeof(t_global));
    VAR->buffer = create_bitmap(SCREEN_W, SCREEN_H);
    VAR->bmp_bouton = create_bitmap(SCREEN_W, SCREEN_H);
    VAR->bmp_prgm = create_bitmap(4*(ECHELLE_PRGM + ECART_PRGM), (ECHELLE_PRGM + ECART_PRGM));
    clear_to_color(VAR->bmp_prgm, makecol(255,0,255));
    VAR->IMG = malloc(sizeof(t_img));
    VAR->SON = malloc(sizeof(t_son));
    VAR->MAP = malloc(sizeof(t_map));
    VAR->MAP->bmp_h = 0;
    VAR->MAP->nbr_bouton = 0;
    VAR->MAP->nbr_boutonS = 0;
    VAR->MAP->nbr_tourelle = 0;
    VAR->MAP->nbr_tourelleS = 0;
    VAR->MAP->deplacement_x[2] = 0;
    VAR->MAP->deplacement_y[2] = 0;
    BITMAP* buffer2 = create_bitmap(SCREEN_W, SCREEN_H);

    VAR->perso_select = 0;
    VAR->drag.actif = 0;
    VAR->drag.action = 0;
    VAR->fin = 1;
    VAR->couleur_precedente = 0;

    recuperer_progression(VAR);

    VAR->IMG->porte = malloc(2*sizeof(BITMAP*));
    VAR->IMG->porte_ouverte = malloc(2*sizeof(BITMAP*));

    charger_tout_img(VAR);
    charger_tout_son(VAR);


    VAR->prgm_lance = 0;
    VAR->prgm_fin = 0;
    int jeu_lance = 0;
    clock_t delai_perso = clock();

    blit(VAR->IMG->overlay_hb, VAR->IMG->overlay_hb2, 0,0,0,0, SCREEN_W, SCREEN_H);

    play_sample(VAR->SON->Music, 50, 50, 1000, 1);
    while(VAR->fin != 0)
    {
        ///Source: Contrôle informatique : Librairie graphique Allegro & Architecture des ordinateurs, DST ING1 de l'ECE Paris, du 22/04/2017
        VAR->clicD.prev = VAR->clicD.now;
        VAR->clicD.now = mouse_b&1;
        VAR->molette.prev = VAR->molette.now - mouse_z;
        VAR->molette.now= mouse_z;


        if (key[KEY_ESC])
        {
            if (choix_menu == 3)
            {
                choix_menu = 0;
            }
            else if (VAR->prgm_lance == 1)
            {
                VAR->prgm_fin = -1;
            }
            else if (jeu_lance == 1)
            {
                choix_menu = 0;
                play_sample(VAR->SON->Music, 50, 50, 1000, 1);
            }
            else
            {
                VAR->fin = 0;
            }
        }
        if (choix_menu == 0)
        {
            choix_menu = menu_principal(VAR, VAR->r_menu1);
            //scanf("%d", &choix_menu);
        }

        switch(choix_menu)
        {
        case 1:
            {
                switch(menu_selection_niveaux(VAR))
                /*char d;
                scanf("%d", &d);
                switch(d)*/
                {
                case -1:
                    {
                        choix_menu = 0;
                        break;
                    }
                case 1:
                    {
                        VAR->fin = 1;
                        stop_sample(VAR->SON->Music);
                        rest(100);
                        play_sample(VAR->SON->Glados_Intro, 100, 100, 1000, 0);
                        VAR->SON->c_Glados_Intro = clock() + (43 * CLOCKS_PER_SEC);
                        while(clock() < VAR->SON->c_Glados_Intro && !key[KEY_ENTER])
                        {
                            clear_bitmap(VAR->buffer);
                            textprintf_ex(VAR->buffer, font, SCREEN_W/2-100, SCREEN_H-100, makecol(255,255,255), -1, "APPUYEZ SUR ENTRER POUR PASSER");
                            blit(VAR->buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
                        }
                        stop_sample(VAR->SON->Glados_Intro);

                        load_matrice(VAR, "ressources/lvl1.txt");
                        copier_matrice(VAR);
                        jeu_lance = 1;
                        choix_menu = -1;
                        break;
                    }
                case 2:
                    {
                        VAR->fin = 1;
                        stop_sample(VAR->SON->Music);
                        load_matrice(VAR, "ressources/lvl2.txt");
                        copier_matrice(VAR);
                        jeu_lance = 1;
                        choix_menu = -1;
                        break;
                    }
                case 3:
                    {
                        VAR->fin = 1;
                        stop_sample(VAR->SON->Music);
                        load_matrice(VAR, "ressources/lvl3.txt");
                        copier_matrice(VAR);
                        jeu_lance = 1;
                        choix_menu = -1;
                        break;
                    }
                case 4:
                    {
                        VAR->fin = 1;
                        stop_sample(VAR->SON->Music);
                        load_matrice(VAR, "ressources/lvl4.txt");
                        copier_matrice(VAR);
                        jeu_lance = 1;
                        choix_menu = -1;
                        break;
                    }
                case 5:
                    {
                        VAR->fin = 1;
                        stop_sample(VAR->SON->Music);
                        load_matrice(VAR, "ressources/lvl5.txt");
                        copier_matrice(VAR);
                        jeu_lance = 1;
                        choix_menu = -1;
                        break;
                    }
                }
                rest(100);
                break;
            }
        case 2:
            {
                clear_bitmap(VAR->buffer);
                textprintf_ex(VAR->buffer, font, SCREEN_W/2-100, SCREEN_H-100, makecol(255,255,255), -1, "IMPOSSIBLE DE CHARGER UNE MAP");
                blit(VAR->buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
                while(VAR->fin == 1)
                {
                    if (readkey() != 0)
                        VAR->fin = 2;
                    else if (mouse_b&1)
                        VAR->fin = 2;
                    else if (mouse_b&2)
                        VAR->fin = 2;
                }
                VAR->fin = 1;
                choix_menu = 0;
                break;
            }
        case 3:
            {
                regles_du_jeu(VAR);
                rest(100);
                choix_menu = 0;
                break;
            }

        case 4:
            {
                VAR->fin = 0;
            }
        }


        if (jeu_lance == 1)
        {
            molette(VAR);
            hitbox_ctrl(VAR);
            clic_perso(VAR);
            deplacer_terrain(VAR);
            if (VAR->prgm_lance == 0)
            {
                hitbox_delete_programme(VAR);
                hitbox_bouton(VAR);
            }
            blit(VAR->IMG->overlay_hb, VAR->IMG->overlay_hb2, 0,0,0,0, SCREEN_W, SCREEN_H);
            clear_bitmap(VAR->buffer);
            afficher(VAR);


            if ((VAR->prgm_lance == 1 || VAR->prgm_lance == 2) && clock() > delai_perso)
            {
                if (VAR->prgm_fin > 0)
                {
                    VAR->prgm_fin++;
                }
                if (VAR->prgm_lance == 2)
                {
                    for (i=0; i<VAR->nbr_perso; i++)
                    {
                        if(VAR->perso[i].prgm->first != NULL)
                        {
                            VAR->perso[i].executer_prgm = 1;
                            VAR->perso[i].charge = VAR->perso[i].prgm->first;
                        }
                        else
                        {
                            VAR->perso[i].executer_prgm = 0;
                        }
                    }
                    VAR->prgm_fin = 0;
                }
                VAR->prgm_lance = 1;
                delai_perso = clock() + (0.5*CLOCKS_PER_SEC);

                for(i=0; i< VAR->nbr_perso; i++)
                {
                    deplacer_perso(VAR,i);
                }



                if(VAR->MAP->nbr_bouton == 0 && VAR->prgm_fin < 100)
                {
                    VAR->prgm_fin = 100;
                }
                else if (verifier_tourelle(VAR) == 1 && VAR->prgm_fin < 50)
                {
                    play_sample(VAR->SON->Machine_gun, 100, 100, 1000, 0);
                    VAR->prgm_fin = 50;
                }

                if (VAR->prgm_fin == 0)
                {
                    VAR->prgm_fin = 50;
                    for (i=0; i<VAR->nbr_perso; i++)
                    {
                        if(VAR->perso[i].executer_prgm == 1)
                        {
                            VAR->prgm_fin = 0;
                            i = VAR->nbr_perso;
                        }
                    }
                }


                if (VAR->prgm_fin == 51) //Perdu
                {
                    jeu_lance = 0;
                    assombrissement(VAR->buffer, 30, &(buffer2));
                    draw_sprite(buffer2, VAR->IMG->fin_echec, 0, 0);
                }
                else if (VAR->prgm_fin == 101) //Gagné
                {
                    if (VAR->progression < NBR_NIVEAU && VAR->progression == VAR->deplacement)
                    {
                        VAR->progression++;
                        save_progression(VAR);
                    }
                    ouvrir_porte(VAR);
                    creer_map(VAR);
                    afficher(VAR);


                    jeu_lance = 0;
                    assombrissement(VAR->buffer, 30, &(buffer2));
                    draw_sprite(buffer2, VAR->IMG->fin_reussite, 0, 0);
                }
            }
        }


        if (VAR->prgm_fin == 51)
        {
            ///C'est perdu
            jeu_lance = 0;
            printf(" \r");
            blit(buffer2, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
            /*if ((VAR->clicD.prev) && !(VAR->clicD.now))
            {
                if ((getpixel(VAR->IMG->fin_hb, mouse_x, mouse_y) == makecol(255,0,255)) || (getpixel(VAR->IMG->fin_hb, mouse_x, mouse_y) == makecol(0,255,255)) || (getpixel(VAR->IMG->fin_hb, mouse_x, mouse_y) == makecol(0,0,255)))
                {
                    VAR->prgm_fin = -20;
                }
            }
            else*/ if (key[KEY_BACKSPACE])
            {
                VAR->prgm_fin = -20;
            }
        }
        else if (VAR->prgm_fin == 101)
        {
            ///C'est gagné
            jeu_lance = 0;
            blit(buffer2, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
            printf(" \r");

            /*if ((VAR->clicD.prev) && !(VAR->clicD.now))
            {
                if ((getpixel(VAR->IMG->fin_hb, mouse_x, mouse_y) == makecol(0,255,0)) || (getpixel(VAR->IMG->fin_hb, mouse_x, mouse_y) == makecol(0,255,255)))
                {
                    VAR->prgm_fin = -10;
                }
                else if ((getpixel(VAR->IMG->fin_hb, mouse_x, mouse_y) == makecol(255,0,0)) || (getpixel(VAR->IMG->fin_hb, mouse_x, mouse_y) == makecol(255,0,255)))
                {
                    VAR->prgm_fin = -20;
                }

            }
            else*/ if (key[KEY_ENTER])
            {
                VAR->prgm_fin = -10;
            }
            else if (key[KEY_BACKSPACE])
            {
                VAR->prgm_fin = -20;
            }
        }

        if (VAR->prgm_fin == -10)
        {
            ///Si on gagne et qu'on passe a la suite
            reset_carte(VAR);
            VAR->prgm_fin = 0;
            jeu_lance = 0;
            choix_menu = 1;
            play_sample(VAR->SON->Music, 50, 50, 1000, 1);
        }
        else if (VAR->prgm_fin == -20)
        {
            ///Si on recommence le niveau;
            reset_carte(VAR);
            VAR->prgm_fin = 0;
            VAR->prgm_lance = 0;
            jeu_lance = 1;
        }
    }

    return 0;
}END_OF_MAIN();
