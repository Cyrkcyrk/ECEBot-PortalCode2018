#include "main.h"

//Détecte les clics dans la zone de programmation, les potentiels drag&drop...
void hitbox_bouton(t_global* VAR)
{
    int i;
    if (!(VAR->clicD.prev) && (VAR->clicD.now) && VAR->drag.actif == 0)
    {
        if (getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(0,0,255) &&
            getpixel(VAR->bmp_bouton, mouse_x, mouse_y) != makecol(255,0,255) &&
            mouse_y - Y_BOUTON > 0 &&
            mouse_y - Y_BOUTON < ECHELLE_BOUTON)
        {
            VAR->drag.actif = 1;
            VAR->drag.delay = clock() + (0.1*CLOCKS_PER_SEC);
            for (i=0; i<8; i++)
            {
                if (mouse_x > X_BOUTON+i*(ECHELLE_BOUTON+ECART_BOUTON) &&
                     mouse_x < X_BOUTON+i*(ECHELLE_BOUTON+ECART_BOUTON)+ ECHELLE_BOUTON &&
                     mouse_y > Y_BOUTON &&
                     mouse_y < Y_BOUTON+ECHELLE_BOUTON)
                {
                   VAR->drag.action = VAR->perso[VAR->perso_select].actions[i];
                }
            }
        }
    }

    else if ((VAR->clicD.prev) && !(VAR->clicD.now) && VAR->drag.actif == 1)
    {
        if (getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(0,0,255) && clock() < VAR->drag.delay)
        {
            ajouter_action_fin(VAR);
            VAR->perso[VAR->perso_select].charge->objet->action = VAR->drag.action;
            VAR->perso[VAR->perso_select].compteur_prgm ++;
        }
        else if (getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(0,255,0) && VAR->drag.actif == 1 &&
                 getpixel(VAR->bmp_prgm, mouse_x-X_PRGM, mouse_y-Y_PRGM + VAR->perso[VAR->perso_select].defilement_prgm) != makecol(255,0,255) &&
                 mouse_y-Y_PRGM + VAR->perso[VAR->perso_select].defilement_prgm < VAR->bmp_prgm->h &&
                 mouse_y-Y_PRGM  + VAR->perso[VAR->perso_select].defilement_prgm >= 0 &&
                 mouse_x-X_PRGM >=0)
        {
            t_maillon* nouveau = NULL;
            creer_maillon(&nouveau);
            nouveau->objet->action = VAR->drag.action;

            t_maillon* precedent = NULL;
            t_maillon* suivant = NULL;
            trouver_maillon_prgm(VAR, &precedent);


            if (precedent->next == NULL)
            {
                nouveau->next = NULL;
                nouveau->prev = precedent;

                precedent->next = nouveau;
                VAR->perso[VAR->perso_select].prgm->last = nouveau;
            }
            else
            {
                suivant = precedent->next;

                nouveau->next = suivant;
                nouveau->prev = precedent;

                suivant->prev = nouveau;
                precedent->next = nouveau;
            }
            VAR->perso[VAR->perso_select].compteur_prgm ++;
            VAR->perso[VAR->perso_select].charge = VAR->perso[VAR->perso_select].prgm->last;
        }
        else if (getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(0,255,0))
        {
            ajouter_action_fin(VAR);
            VAR->perso[VAR->perso_select].charge->objet->action = VAR->drag.action;
            VAR->perso[VAR->perso_select].compteur_prgm ++;
        }
        VAR->drag.actif = 0;
        VAR->drag.action = 0;
    }
}

//Detecte les clics dans la zone programmée, pour supprimer une action.
void hitbox_delete_programme(t_global* VAR)
{

    if (getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(0,255,0) &&
        (VAR->clicD.prev) && !(VAR->clicD.now) &&
        VAR->drag.actif == 0 &&
        getpixel(VAR->bmp_prgm, mouse_x-X_PRGM, mouse_y-Y_PRGM + VAR->perso[VAR->perso_select].defilement_prgm) != makecol(255,0,255) &&
        mouse_y-Y_PRGM + VAR->perso[VAR->perso_select].defilement_prgm < VAR->bmp_prgm->h &&
        mouse_y-Y_PRGM  + VAR->perso[VAR->perso_select].defilement_prgm >= 0 &&
        mouse_x-X_PRGM >=0 )

    {
        t_maillon* charge = NULL;
        trouver_maillon_prgm(VAR, &charge);

        supprimer_maillon(VAR, &charge);
    }
}

//Detecte les clics sur les 3 boutons de controles (play, pause, reset/delete).
void hitbox_ctrl(t_global* VAR)
{
    if (getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(0,0,100) && (VAR->clicD.prev) && !(VAR->clicD.now) && VAR->prgm_lance == 0)
    {
        VAR->prgm_lance = 2;
    }
    else if (getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(0,0,100) && (VAR->clicD.prev) && !(VAR->clicD.now) && VAR->prgm_lance == 3)
    {
        VAR->prgm_lance = 1;
    }


    else if (getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(0,0,101) && (VAR->clicD.prev) && !(VAR->clicD.now) && VAR->prgm_lance == 1)
    {
        VAR->prgm_lance = 3;
    }


    else if (getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(0,0,102) && (VAR->clicD.prev) && !(VAR->clicD.now) && (VAR->prgm_lance == 1 || VAR->prgm_lance == 3))
    {
        VAR->prgm_lance = 0;
        VAR->prgm_fin = -20;
    }
    else if (getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(0,0,102) && (VAR->clicD.prev) && !(VAR->clicD.now) && VAR->prgm_lance == 0)
    {
        supprimer_programme(VAR);
    }

}

//Detecte si le joueur clic sur le terrain, pour le deplacer en fonction de la souris.
void deplacer_terrain(t_global* VAR)
{
    if(!mouse_b&1)
    {
        VAR->MAP->deplacement_x[0] = mouse_x + VAR->MAP->deplacement_x[2];
        VAR->MAP->deplacement_y[0] = mouse_y + VAR->MAP->deplacement_y[2];
        VAR->MAP->deplacement_ok = 0;
    }
    else if (VAR->MAP->deplacement_ok == 1 && mouse_b&1)
    {
        VAR->MAP->deplacement_x[1] = mouse_x;
        VAR->MAP->deplacement_y[1] = mouse_y;

        VAR->MAP->deplacement_x[2] = VAR->MAP->deplacement_x[0] - VAR->MAP->deplacement_x[1];
        VAR->MAP->deplacement_y[2] = VAR->MAP->deplacement_y[0] - VAR->MAP->deplacement_y[1];
    }
    else if (!(VAR->clicD.prev) && VAR->clicD.now && getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(255,0,0))
    {
        VAR->MAP->deplacement_ok = 1;
    }


    if (VAR->MAP->deplacement_x[2] > 500)
    {
        VAR->MAP->deplacement_x[2] = 500;
    }
    else if (VAR->MAP->deplacement_x[2] < -500)
    {
        VAR->MAP->deplacement_x[2] = -500;
    }
    if (VAR->MAP->deplacement_y[2] > 200)
    {
        VAR->MAP->deplacement_y[2] = 200;
    }
    else if (VAR->MAP->deplacement_y[2] < -270)
    {
        VAR->MAP->deplacement_y[2] = -270;
    }
}

//Detecte si l'utilisateur clics sur un des personnages, pour changer lequel est actuellement chargé (lequel dont on modifiera/affichera le programme).
void clic_perso(t_global* VAR)
{
    if (!(VAR->clicD.prev) && VAR->clicD.now && getr(getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y)) == 255 && getg(getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y)) >= 100)
    {
        VAR->perso_select = getg(getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y)) - 100;
    }
}

//Detecte si l'utilisateur utilise la molette de la souris dans une certaine zone de l'écran.
//Par exemple, si elle est utilisée sur le terrain de jeu, alors on zoom.
//Si elle est utilisée sur la zone programmée, alors on deplace verticalement la-dîte zone...
void molette(t_global* VAR)
{
    if(VAR->molette.prev != 0)
    {
        if (getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(255,0,0))
        {
            if(VAR->molette.prev < 0)
            {
                VAR->MAP->grossissement = VAR->MAP->grossissement - 0.1;
            }
            else
            {
                VAR->MAP->grossissement = VAR->MAP->grossissement + 0.1;
            }
        }
        else if (getpixel(VAR->IMG->overlay_hb2, mouse_x, mouse_y) == makecol(0,255,0))
        {
            if(VAR->molette.prev > 0)
            {
                VAR->perso[VAR->perso_select].defilement_prgm += 5;
            }
            else
            {
                VAR->perso[VAR->perso_select].defilement_prgm -= 5;
            }
        }
    }
}
