#include "main.h"

//Affiche la bitmap contenant les règles du jeu, et permet de la déplacer verticalement avec les flèches ou la molette, jusqu'a ce que l'utilisateur appuie sur échap.
void regles_du_jeu(t_global *VAR)
{
    ///Variables locales
    int defilement = 0;

    while(!key[KEY_ESC])
    {
        VAR->clicD.prev = VAR->clicD.now;
        VAR->clicD.now = mouse_b&1;
        VAR->molette.prev = VAR->molette.now - mouse_z;
        VAR->molette.now= mouse_z;
        ///Affichage des règles du jeu
        blit(VAR->IMG->regles_du_jeu, screen, 0, defilement, 0, 0, SCREEN_W, SCREEN_H);

        ///Défilement vers le bas
        if(key[KEY_DOWN])///Défilement vers le bas
        {
            if(defilement <= (VAR->IMG->regles_du_jeu->h - SCREEN_H))
            {
                defilement = defilement + 1;
            }
        }
        else if(VAR->molette.prev > 0)
        {
            if(defilement <= (VAR->IMG->regles_du_jeu->h - SCREEN_H))
            {
                defilement = defilement + 10;
            }
        }

        if(key[KEY_UP])///Défilement vers le haut
        {
            if(defilement >= 0)
            {
                defilement = defilement - 1;
            }
        }
        else if(VAR->molette.prev < 0)
        {
            if(defilement >= 0)
            {
                defilement = defilement - 10;
            }
        }
    }
}
