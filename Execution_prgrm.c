#include "main.h"

//Permet de trouver l'adresse du maillon sur lequel la souris est, et le retourne dans le double pointeur t_maillon passé en paramètres.
//(J'ai du faire comme ca, car la compilation plantais, et me refusait que j'ai une fonction de type t_maillon*) .
void trouver_maillon_prgm(t_global* VAR, t_maillon** retour)
{
    int numero_ligne = 0, numero_colone = 0, numero_action = 0;;
    int fin = 0;
    t_maillon* charge;

    while(fin != 1)
    {
        if (mouse_y-Y_PRGM + VAR->perso[VAR->perso_select].defilement_prgm >= numero_ligne*(ECHELLE_PRGM + ECART_PRGM) && mouse_y-Y_PRGM + VAR->perso[VAR->perso_select].defilement_prgm <= numero_ligne*(ECHELLE_PRGM + ECART_PRGM)+ECHELLE_PRGM)
        {
            fin = 1;
        }
        else
        {
            numero_ligne++;
        }
    }

    for (fin=0; fin<4; fin++)
    {
        if (mouse_x-X_PRGM >= fin*(ECHELLE_PRGM + ECART_PRGM) && mouse_x-X_PRGM <= fin*(ECHELLE_PRGM + ECART_PRGM)+ECHELLE_PRGM)
        {
            numero_colone = fin;
            fin = 4;
        }
    }

    numero_action = numero_ligne*4 + numero_colone;
    charge = VAR->perso[VAR->perso_select].prgm->first;
    for (fin = 0; fin< numero_action; fin++)
    {
        charge = charge->next;
    }

    *retour = charge;
}

//Ajoute un maillon à la fin de la chaine du programme actuellement chargé.
void ajouter_action_fin(t_global* VAR)
{
    t_maillon* new_maillon;
    creer_maillon(&new_maillon);

    VAR->perso[VAR->perso_select].charge = new_maillon;


    if(VAR->perso[VAR->perso_select].prgm->first == NULL)
    {
        VAR->perso[VAR->perso_select].prgm->first = new_maillon;
        VAR->perso[VAR->perso_select].prgm->last = new_maillon;
    }

    else
    {
        VAR->perso[VAR->perso_select].prgm->last->next = new_maillon;
        new_maillon->prev = VAR->perso[VAR->perso_select].prgm->last;
        VAR->perso[VAR->perso_select].prgm->last = new_maillon;
    }
}

//Crééer dynamiquement un maillon, sans le relier à rien. Idem, il le retour dans le double pointeur passé en paramètres.
void creer_maillon(t_maillon** retour)
{
    t_maillon* new_maillon = malloc(sizeof(t_maillon));
    new_maillon->next = NULL;
    new_maillon->prev = NULL;
    new_maillon->objet = malloc(sizeof(t_prgm));
    new_maillon->objet->action = 'A';

    *retour = new_maillon;
}

//Supprimme le maillon passé en paramètre, tout en gardant la chaine liée.
void supprimer_maillon(t_global* VAR, t_maillon** charge)
{
    if((*charge)->prev == NULL && (*charge)->next == NULL)
    {
        VAR->perso[VAR->perso_select].prgm->first = NULL;
        VAR->perso[VAR->perso_select].prgm->last = NULL;
        VAR->perso[VAR->perso_select].compteur_prgm--;
    }
    else if((*charge)->prev == NULL)
    {
        VAR->perso[VAR->perso_select].prgm->first = VAR->perso[VAR->perso_select].prgm->first->next;
        VAR->perso[VAR->perso_select].prgm->first->prev = NULL;
        VAR->perso[VAR->perso_select].compteur_prgm--;
    }
    else if ((*charge)->next == NULL)
    {
        VAR->perso[VAR->perso_select].prgm->last = VAR->perso[VAR->perso_select].prgm->last->prev;
        VAR->perso[VAR->perso_select].prgm->last->next = NULL;
        VAR->perso[VAR->perso_select].compteur_prgm--;
    }
    else
    {
        (*charge)->next->prev = (*charge)->prev;
        (*charge)->prev->next = (*charge)->next;
        VAR->perso[VAR->perso_select].compteur_prgm--;
    }

    free((*charge)->objet);
    free(*charge);
}

//Supprime totalement la liste chainée chargée.
void supprimer_programme(t_global* VAR)
{
    if (VAR->perso[VAR->perso_select].prgm->first != NULL)
    {
        t_maillon* charge = VAR->perso[VAR->perso_select].prgm->first;
        VAR->perso[VAR->perso_select].prgm->first = NULL;
        VAR->perso[VAR->perso_select].prgm->last = NULL;
        VAR->perso[VAR->perso_select].charge = NULL;
        VAR->perso[VAR->perso_select].compteur_prgm = 0;


        while(charge->next != VAR->perso[VAR->perso_select].prgm->last || charge->next != NULL)
        {
            charge = charge->next;
            free(charge->prev);
        }
        free(charge);
    }
}

//Créer la bitmap des boutons clickables pour créer les programmes (les boutons qui peuvent être drag&drop), en fonction de chaque bots.
void afficher_boutons_prgm(t_global* VAR)
{
    int i;
    BITMAP* buffer;
    clear_to_color(VAR->bmp_bouton, makecol(255,0,255));

    for(i=0; i<8; i++)
    {
        switch(VAR->perso[VAR->perso_select].actions[i])
        {
        case 'A': //Avancer
            {
                buffer = VAR->IMG->action_avancer;
                break;
            }
        case 'W': //Attendre / wait
            {
                buffer = VAR->IMG->action_attendre;
                break;
            }
        case 'P': //Porter
            {
                buffer =  VAR->IMG->action_porter;
                break;
            }
        case 'S': //Sauter
            {
                buffer =  VAR->IMG->action_sauter;
                break;
            }
        case 'D': //Droite
            {
                buffer =  VAR->IMG->action_tourner_droite;
                break;
            }
        case 'G': //Gauche
            {
                buffer =  VAR->IMG->action_tourner_gauche;
                break;
            }
        case 'p': //Gauche
            {
                buffer =  VAR->IMG->action_pousser;
                break;
            }
        default:
            {
                buffer = VAR->IMG->vide;
            }
        }
        stretch_sprite(VAR->bmp_bouton, buffer , X_BOUTON+i*(ECHELLE_BOUTON+ECART_BOUTON), Y_BOUTON, ECHELLE_BOUTON, ECHELLE_BOUTON);
    }

    if (VAR->drag.actif == 1 && clock() > VAR->drag.delay)
    {
        switch(VAR->drag.action)
        {
        case 'A': //Avancer
            {
                buffer = VAR->IMG->action_avancer;
                break;
            }
        case 'W': //Attendre / wait
            {
                buffer = VAR->IMG->action_attendre;
                break;
            }
        case 'P': //Porter
            {
                buffer =  VAR->IMG->action_porter;
                break;
            }
        case 'S': //Sauter
            {
                buffer =  VAR->IMG->action_sauter;
                break;
            }
        case 'D': //Droite
            {
                buffer =  VAR->IMG->action_tourner_droite;
                break;
            }
        case 'G': //Gauche
            {
                buffer =  VAR->IMG->action_tourner_gauche;
                break;
            }
        case 'p': //Gauche
            {
                buffer =  VAR->IMG->action_pousser;
                break;
            }
        default:
            {
                buffer = VAR->IMG->vide;
            }
        }
        stretch_sprite(VAR->bmp_bouton, buffer , mouse_x, mouse_y, ECHELLE_PRGM, ECHELLE_PRGM);
    }
}

//Créer une bitmap qui permet d'avoir l'intégralitée du programme chargé affiché dessus. (Elle est ensuite recouvert par l'overlay.)
void afficher_prgm(t_global* VAR)
{
    int new_bmp_h;
    int nbr_action = VAR->perso[VAR->perso_select].compteur_prgm;
    int i , j;
    BITMAP* buffer = VAR->bmp_prgm;
    t_maillon* charge = NULL;

    clear_to_color(VAR->bmp_prgm, makecol(255,0,255));
    if (VAR->perso[VAR->perso_select].prgm->first != NULL)
    {
        charge = VAR->perso[VAR->perso_select].prgm->first;
        switch(nbr_action%4)
        {
        case 1:
            {
                nbr_action = (nbr_action+3)/4;
                break;
            }
        case 2:
            {
                nbr_action = (nbr_action+2)/4;
                break;
            }
        case 3:
            {
                nbr_action = (nbr_action+1)/4;
                break;
            }
        case 0:
            {
                break;
            }
        }

        new_bmp_h = nbr_action * (ECHELLE_PRGM + ECART_PRGM);

        if (new_bmp_h != VAR->bmp_prgm->h)
        {
            buffer = VAR->bmp_prgm;
            BITMAP* nouveau = create_bitmap(4*(ECHELLE_PRGM + ECART_PRGM), nbr_action*(ECHELLE_PRGM + ECART_PRGM));
            clear_to_color(nouveau, makecol(255,0,255));
            blit(buffer, nouveau, 0,0,0,0, buffer->w, buffer->h);
            destroy_bitmap(buffer);
            VAR->bmp_prgm = nouveau;
        }


        j=0;
        for (i=0; i<VAR->perso[VAR->perso_select].compteur_prgm; i++)
        {
            if (i!=0 && i%4 == 0)
                j++;

            switch(charge->objet->action)
            {
            case 'A':
                {
                    buffer = VAR->IMG->action_avancer;
                    break;
                }
            case 'W':
                {
                    buffer = VAR->IMG->action_attendre;
                    break;
                }
            case 'P':
                {
                    buffer = VAR->IMG->action_porter;
                    break;
                }
            case 'S':
                {
                    buffer = VAR->IMG->action_sauter;
                    break;
                }
            case 'D':
                {
                    buffer = VAR->IMG->action_tourner_droite;
                    break;
                }
            case 'G':
                {
                    buffer = VAR->IMG->action_tourner_gauche;
                    break;
                }
            case 'p': //Gauche
                {
                    buffer =  VAR->IMG->action_pousser;
                    break;

                }
            }
            stretch_sprite(VAR->bmp_prgm, buffer, (i%4)*(ECHELLE_PRGM + ECART_PRGM), j*(ECHELLE_PRGM + ECART_PRGM), ECHELLE_PRGM, ECHELLE_PRGM);

            if (charge->next == VAR->perso[VAR->perso_select].charge && VAR->perso[VAR->perso_select].executer_prgm == 1)
                stretch_sprite(VAR->bmp_prgm, VAR->IMG->action_selecteur, (i%4)*(ECHELLE_PRGM + ECART_PRGM), j*(ECHELLE_PRGM + ECART_PRGM), ECHELLE_PRGM, ECHELLE_PRGM);
            charge = charge->next;
        }
    }
}
