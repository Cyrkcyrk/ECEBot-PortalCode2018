#include "main.h"


int menu_selection_niveaux(t_global *VAR)
{
    ///Variables
        ///Choix du joueur
    int choix = 0;

    int vitesse_deplacement = 10;
        ///Position cases des niveaux
    int niveau_x[NBR_NIVEAU+1];
        ///Position personnage sur l'écran (au point d'apparition)
    int position_x = 375;///Au centre de l'écran : 800/2 - 50/2
    int position_y = 280;///Au centre de l'écran : 600/2 - 40/2
        ///Position de l'image de fond par rapport au personnage
        ///Déplacement
	///VAR->Deplacement///-1 personnage à un niveau (doit revenir au centre) / 0-personnage au centre / 1-personnage se déplace au niveau 1 / 2-personnage se déplace au niveau 2 / 3-déplacement au niveau 3 / 4-déplacement au niveau 4
    int en_cours_droite = 0;///Indique la direction du personnage
    int en_cours_gauche = 0;///Indique la direction du personnage
        ///Animation du personnage
    int pas = 0;///Indiquant le moment où on change de sprite : 0-marche avant / 1-marche arrière
    int cote = 0;///Indique le côté vers lequel est tourné le personnage lorsqu'il est à l'arrêt : 0-droite / 1-gauche
        ///Timer
    clock_t temps;
    int changement = 0;///Variable de ralentissement

    ///Initialisation des variables
        ///Position des cases de niveaux
            ///Point d'apparition
    int i;
    for (i=0; i< NBR_NIVEAU+1; i++)
    {
        niveau_x[i] = position_x + i*400;
    }


    ///Affichage de la carte de sélection des niveaux(carte du monde)
    blit(VAR->IMG->carte_monde, VAR->buffer, VAR->scrolling_x, 0, 0, 0, SCREEN_W, SCREEN_H);
    ///Affichage du personnage de sélection
    draw_sprite(VAR->buffer, VAR->IMG->personnage_principal[4], position_x, position_y);

    rest(100);
    while(choix == 0)
    {
        ///Retour vers le menu principal
        if(key[KEY_ESC])///Touche ECHAP pour quitter
        {
            choix = -1;
        }

        ///Sélection du déplacement du personnage
        if((en_cours_droite == 0) && (en_cours_gauche == 0))
        {
            if(key[KEY_RIGHT])///Choix déplacement vers la droite
            {
                cote = 0;
                if((VAR->deplacement < NBR_NIVEAU-1) && (en_cours_droite == 0))
                {
                    VAR->deplacement++;
                    en_cours_droite = 1;
                }
                rest(200);
            }
            if(key[KEY_LEFT])///Choix déplacement vers la gauche
            {
                cote = 1;
                if((VAR->deplacement > 0) && (en_cours_gauche == 0))
                {
                    VAR->deplacement--;
                    en_cours_gauche = 1;
                }
                else if (VAR->deplacement == 0 && en_cours_gauche == 0)
                {
                    en_cours_gauche = -1;
                }
                rest(200);
            }
            if(key[KEY_ENTER])///Validation du niveau choisi
            {
                if(VAR->deplacement != 0)///Niveau 1 choisi
                {
                    choix = VAR->deplacement;
                }
            }

            blit(VAR->IMG->carte_monde, VAR->buffer, VAR->scrolling_x, 0, 0, 0, SCREEN_W, SCREEN_H);

            if(cote == 0)
            {
                draw_sprite(VAR->buffer, VAR->IMG->personnage_principal[4], position_x, position_y);
            }
            else
            {
                draw_sprite(VAR->buffer, VAR->IMG->personnage_principal[5], position_x, position_y);
            }


            blit(VAR->buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }

        else
        {
            ///Déplacement vers la droite
            for (i=0; i< NBR_NIVEAU; i++)
            {
                if((VAR->deplacement == i) && (en_cours_droite == 1))
                {
                    ///Vérification de la progression
                    if(VAR->progression >= i)
                    {
                        ///Déplacement vers le niveau 2
                        if((position_x + VAR->scrolling_x) <= niveau_x[i])
                        {
                            VAR->scrolling_x = VAR->scrolling_x + vitesse_deplacement;
                        }
                        else
                        {
                            en_cours_droite = 0;
                        }
                    }
                    else
                    {
                        ///Affichage message : IMPOSSIBLE
                        if (clock() > VAR->SON->c_Buzzer)
                        {
                            play_sample(VAR->SON->Buzzer, 150, 150, 1000, 0);
                            VAR->SON->c_Buzzer = clock() + (1.109 * CLOCKS_PER_SEC);
                        }
                        VAR->deplacement--;
                    }
                }
                else if((VAR->deplacement == i) && (en_cours_gauche == 1) )
                {
                    if((position_x + VAR->scrolling_x) >= niveau_x[i])
                    {
                        VAR->scrolling_x = VAR->scrolling_x - vitesse_deplacement;
                    }
                    else
                    {
                        en_cours_gauche = 0;
                    }
                }
                else if (en_cours_gauche == -1 && clock() > temps)
                {
                    temps = clock() + (0.015*CLOCKS_PER_SEC);
                    if(position_x > -10)
                    {
                        position_x = position_x - vitesse_deplacement;
                    }
                    else
                    {
                        en_cours_gauche = 0;
                        return -1;
                    }
                }
            }


           blit(VAR->IMG->carte_monde, VAR->buffer, VAR->scrolling_x, 0, 0, 0, SCREEN_W, SCREEN_H);

            ///Affichage du personnage
            if((cote == 0) && (pas == 0))
            {
                draw_sprite(VAR->buffer, VAR->IMG->personnage_principal[0], position_x, position_y);
            }
            if((cote == 0) && (pas == 1))
            {
                draw_sprite(VAR->buffer, VAR->IMG->personnage_principal[2], position_x, position_y);
            }
            if((cote == 1) && (pas == 0))
            {
                draw_sprite(VAR->buffer, VAR->IMG->personnage_principal[1], position_x, position_y);
            }
            if((cote == 1) && (pas == 1))
            {
                draw_sprite(VAR->buffer, VAR->IMG->personnage_principal[3], position_x, position_y);
            }

            ///Changement du pas
            if(changement == 10)
            {
                if(pas == 0)
                {
                    pas = 1;
                }
                else
                {
                    pas = 0;
                }

                son_pas(VAR);

                changement = 0;
            }
            changement = changement + 1;


            blit(VAR->buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            rest(10);
        }
    }

    return(choix);
}
