#include "main.h"

//Charge le son passé en paramètre dans la sample passé en paramètre.
void charger_son(SAMPLE** son, char string[])
{
    *son = load_sample(string);
    if (*son != NULL)
    {
        printf("Chargement: %s - Succes\n", string);
    }
    else
    {
        printf("Chargement: %s - ECHEC\n", string);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

//Petmet de charger l'intégralitée des sample dont on a besoins.
//Déclare aussi les clocks utilisée individuels a chaques sample pour éviter des bugs en cas de comparaison.
void charger_tout_son(t_global* VAR)
{
    charger_son(&(VAR->SON->Button_press), "son/button_press.wav");
    charger_son(&(VAR->SON->Button_release), "son/button_Unpress.wav");
    charger_son(&(VAR->SON->Music), "son/music.wav");
    charger_son(&(VAR->SON->Select), "son/selection.wav");
    charger_son(&(VAR->SON->Buzzer), "son/Buzzer.wav");
    charger_son(&(VAR->SON->Machine_gun), "son/Turret_Machine_gun.wav");
    charger_son(&(VAR->SON->ouverture_porte), "son/porte_ouverte.wav");
    charger_son(&(VAR->SON->Glados_Intro), "son/Glados/Intro.wav");

    charger_son(&(VAR->SON->pas[0]), "son/pas/pas-1.wav");
    charger_son(&(VAR->SON->pas[1]), "son/pas/pas-2.wav");
    charger_son(&(VAR->SON->pas[2]), "son/pas/pas-3.wav");
    charger_son(&(VAR->SON->pas[3]), "son/pas/pas-4.wav");
    charger_son(&(VAR->SON->pas[4]), "son/pas/pas-5.wav");

    charger_son(&(VAR->SON->frottement[0]), "son/frottement/frottement-1.wav");
    charger_son(&(VAR->SON->frottement[1]), "son/frottement/frottement-2.wav");
    charger_son(&(VAR->SON->frottement[2]), "son/frottement/frottement-3.wav");
    charger_son(&(VAR->SON->frottement[3]), "son/frottement/frottement-4.wav");

    VAR->SON->c_Button_press = clock();
    VAR->SON->c_Button_release = clock();
    VAR->SON->c_Glados_But = clock();
    VAR->SON->c_Glados_Intro = clock();
    VAR->SON->c_Music = clock();
    VAR->SON->c_Buzzer = clock();
    VAR->SON->c_Machine_gun = clock();
    VAR->SON->c_ouverture_porte = clock();
    VAR->SON->c_Select= clock();
    VAR->SON->c_frottement= clock();
    VAR->SON->c_pas= clock();
}

//Joue le son d'un pas aléatoire.
void son_pas(t_global* VAR)
{
    if (clock() > VAR->SON->c_pas)
    {
        switch(rand()%5)
        {
        case 0:
            {
                play_sample(VAR->SON->pas[0], 255, 255, 1000, 0);
                VAR->SON->c_pas = clock() + (0.333 * CLOCKS_PER_SEC);
                break;
            }
        case 1:
            {
                play_sample(VAR->SON->pas[1], 255, 255, 1000, 0);
                VAR->SON->c_pas = clock() + (0.312 * CLOCKS_PER_SEC);
                break;
            }
        case 2:
            {
                play_sample(VAR->SON->pas[2], 255, 255, 1000, 0);
                VAR->SON->c_pas = clock() + (0.412 * CLOCKS_PER_SEC);
                break;
            }
        case 3:
            {
                play_sample(VAR->SON->pas[3], 255, 255, 1000, 0);
                VAR->SON->c_pas = clock() + (0.295 * CLOCKS_PER_SEC);
                break;
            }
        case 4:
            {
                play_sample(VAR->SON->pas[4], 255, 255, 1000, 0);
                VAR->SON->c_pas = clock() + (0.398 * CLOCKS_PER_SEC);
                break;
            }
        }
    }
}

//Joue le son d'un frottement aléatoire.
void son_frottement(t_global* VAR)
{
    if (clock() > VAR->SON->c_frottement)
    {
        switch(rand()%4)
        {
        case 0:
            {
                play_sample(VAR->SON->frottement[0], 255, 255, 1000, 0);
                VAR->SON->c_frottement = clock() + (0.929 * CLOCKS_PER_SEC);
                break;
            }
        case 1:
            {
                play_sample(VAR->SON->frottement[1], 255, 255, 1000, 0);
                VAR->SON->c_frottement = clock() + (0.638 * CLOCKS_PER_SEC);
                break;
            }
        case 2:
            {
                play_sample(VAR->SON->frottement[2], 255, 255, 1000, 0);
                VAR->SON->c_frottement = clock() + (0.712 * CLOCKS_PER_SEC);
                break;
            }
        case 3:
            {
                play_sample(VAR->SON->frottement[3], 255, 255, 1000, 0);
                VAR->SON->c_frottement = clock() + (1.522 * CLOCKS_PER_SEC);
                break;
            }
        }
    }
}
