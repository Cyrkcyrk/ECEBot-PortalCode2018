#include "main.h"

//Permet d'avoir, à partir d'une coordonnée 3D, une coordonnée isométrique 2D.
void projection(t_global* VAR, int *pxe, int *pye, int x, int y, int z) /// Cours de M. Fercoq
{
    int echelleINT = ECHELLE;
    x = x*echelleINT;
    y = y*echelleINT;
    z = z*echelleINT;

    *pxe = 1.85*x - 1.85*y + VAR->MAP->bmp_w/2.15;
    *pye = 1*x + 1.12*y - 2.1*z + VAR->MAP->bmp_h/12;
}

//Charge le terrain de jeu depuis un fichier texte (passé en paramètre) dans la matrice de VAR.
void load_matrice(t_global* VAR, char string[])
{
    int i,j,k, w, h, nbr;
    char c;

    FILE* fichier = fopen(string, "r");
    if(fichier == NULL)
    {
        allegro_message("Probleme pour charger: %s", string);
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    else
    {

        ///Si il y avais déjà une map de chargée, on la free
        if (VAR->MAP->bmp_h != 0)
        {
            for (i=0; i< VAR->nbr_perso; i++)
            {   for (j=0; j<4; j++)
                {
                    destroy_bitmap(VAR->perso[i].skin_hb[j]);
                }
                VAR->perso_select = i;
                supprimer_programme(VAR);

                free(VAR->perso[i].prgm);
                free(VAR->perso);

            }
            VAR->perso_select = 0;

            for (i=0; i<VAR->MAP->tailleZ; i++)
            {
                for (j=0; j<VAR->MAP->tailleX; j++)
                {
                    free(VAR->MAP->matrice[i][j]);
                    free(VAR->MAP->matriceS[i][j]);
                }
                free(VAR->MAP->matrice[i]);
                free(VAR->MAP->matriceS[i]);
            }
            free(VAR->MAP->matrice);
            free(VAR->MAP->matriceS);

            free(VAR->perso);
            VAR->MAP->nbr_bouton = 0;
            VAR->MAP->nbr_boutonS = 0;
            VAR->MAP->nbr_tourelle = 0;
            VAR->MAP->nbr_tourelleS = 0;
            VAR->MAP->deplacement_x[2] = 0;
            VAR->MAP->deplacement_y[2] = 0;

            destroy_bitmap(VAR->MAP->terrain);
            destroy_bitmap(VAR->MAP->terrain_hb);
        }

        fscanf(fichier, "%d %d %d %d %d %d\n", &i, &j, &k, &nbr, &w, &h);

        VAR->MAP->tailleX = i;
        VAR->MAP->tailleY = j;
        VAR->MAP->tailleZ = k;
        VAR->nbr_perso = nbr;
        VAR->MAP->bmp_w = w;
        VAR->MAP->bmp_h = h;




        ///Et on definis la nouvelle

        definir_perso(VAR, fichier);


        VAR->MAP->matrice = malloc(VAR->MAP->tailleX* sizeof(char**));
        VAR->MAP->matriceS = malloc(VAR->MAP->tailleX* sizeof(char**));

        for (i=0; i< VAR->MAP->tailleX; i++)
        {
            VAR->MAP->matrice[i] = malloc(VAR->MAP->tailleY*sizeof(char*));
            VAR->MAP->matriceS[i] = malloc(VAR->MAP->tailleY*sizeof(char*));

            for(j=0; j<VAR->MAP->tailleY; j++)
            {
                VAR->MAP->matrice[i][j] = malloc(VAR->MAP->tailleZ*sizeof(char));
                VAR->MAP->matriceS[i][j] = malloc(VAR->MAP->tailleZ*sizeof(char));
            }
        }

        VAR->MAP->terrain = create_bitmap(VAR->MAP->bmp_w, VAR->MAP->bmp_h);
        VAR->MAP->terrain_hb = create_bitmap(VAR->MAP->bmp_w, VAR->MAP->bmp_h);

        VAR->MAP->grossissement = 1;
        while(VAR->MAP->bmp_w/VAR->MAP->grossissement > 563 && VAR->MAP->bmp_h/VAR->MAP->grossissement > 442)
        {
            VAR->MAP->grossissement = VAR->MAP->grossissement+ 0.1;
        }

        ///On recupere la nouvelle
        for (i=0; i< VAR->MAP->tailleZ; i++)
        {
            for (j=0; j< VAR->MAP->tailleY; j++)
            {
                for(k=0; k< VAR->MAP->tailleX; k++)
                {
                    fscanf(fichier, "%c", &c);
                    if (c == '\n')
                    {
                        k--;
                    }
                    else if (c=='t' || c=='T' || c=='u' || c=='U')
                    {
                        VAR->MAP->nbr_tourelle++;
                        VAR->MAP->nbr_tourelleS++;
                        VAR->MAP->matriceS[k][j][i] = c;
                    }
                    else if (c=='b')
                    {
                        VAR->MAP->nbr_bouton++;
                        VAR->MAP->nbr_boutonS++;
                        VAR->MAP->matriceS[k][j][i] = c;
                    }
                    else
                    {
                        VAR->MAP->matriceS[k][j][i] = c;
                    }
                }
            }
        }
        fclose(fichier);
    }
}

//Copie la matrice d'origine du terrain à la place de celle modifiée par le jeu et les actions du joueur.
void copier_matrice(t_global* VAR)
{
    int i,j,k;
    for (i=0; i< VAR->MAP->tailleZ; i++)
    {
        for (j=0; j< VAR->MAP->tailleY; j++)
        {
            for(k=0; k< VAR->MAP->tailleX; k++)
            {
                    VAR->MAP->matrice[k][j][i] = VAR->MAP->matriceS[k][j][i];
            }
        }
    }
}

//Créer, à partir de la matrice chargé précédément, de créer le terrain de jeu sur lequel évoluent les bots.
void creer_map(t_global* VAR)
{

    BITMAP* vide = VAR->IMG->vide;
    BITMAP* img = vide;
    clear_bitmap(VAR->MAP->terrain);
    clear_to_color(VAR->MAP->terrain_hb, makecol(255,0,255));
    int i,j,k,l;
    int x,y;

    for(k=0; k< VAR->MAP->tailleX; k++)
    {
        for (i=0; i< VAR->MAP->tailleZ; i++)
        {
            for (j=0; j< VAR->MAP->tailleY; j++)
            {
                switch(VAR->MAP->matrice[k][j][i])
                {
                case '1':
                    {
                        img = VAR->IMG->cube_sombre;
                        break;
                    }
                case '2':
                    {
                        img = VAR->IMG->cube_clair;
                        break;
                    }
                case 'p':
                    {
                        img = VAR->IMG->porte[0];
                        break;
                    }
                case 'P':
                    {
                        img = VAR->IMG->porte[1];
                        break;
                    }
                case 'q':
                    {
                        img = VAR->IMG->porte_ouverte[0];
                        break;
                    }
                case 'Q':
                    {
                        img = VAR->IMG->porte_ouverte[1];
                        break;
                    }
                case 'd':
                    {
                        img = VAR->IMG->porte_ouverte[0];
                        break;
                    }
                case 'D':
                    {
                        img = VAR->IMG->porte_ouverte[1];
                        break;
                    }
                case 'b':
                    {
                        img = VAR->IMG->boutton;
                        break;
                    }
                case 'B':
                    {
                        img = VAR->IMG->boutton_presse;
                        break;
                    }
                case 'c':
                    {
                        img = VAR->IMG->compagnion_cube;
                        break;
                    }
                case 'C':
                    {
                        img = VAR->IMG->boutton_cube;
                        break;
                    }
                case 'u':
                    {
                        img = VAR->IMG->tourelle[0];
                        break;
                    }
                case 'U':
                    {
                        img = VAR->IMG->tourelle[1];
                        break;
                    }
                case 't':
                    {
                        img = VAR->IMG->tourelle[2];
                        break;
                    }
                case 'T':
                    {
                        img = VAR->IMG->tourelle[3];
                        break;
                    }

                case '0':
                    {
                        img = vide;
                        break;
                    }
                default:
                    {
                        img = vide;
                        break;
                    }
                }

                projection(VAR, &x, &y, k, j, i);
                stretch_sprite(VAR->MAP->terrain, img, x, y, TAILLE, TAILLE);

                for (l=0; l< VAR->nbr_perso; l++)
                {
                    if (VAR->perso[l].x == k && VAR->perso[l].y == j && VAR->perso[l].z == i)
                    {
                        projection(VAR, &x, &y, k, j, i);
                        if(l == VAR->perso_select)
                        {
                            ellipsefill(VAR->MAP->terrain, x+(TAILLE*0.5), y+(TAILLE*0.7875), 15, 14, makecol(255, 100, 0));
                        }

                        img = VAR->perso[l].skin[VAR->perso[l].inventaire][VAR->perso[l].orientation];
                        stretch_sprite(VAR->MAP->terrain, img, x, y, TAILLE, TAILLE);

                        img = VAR->perso[l].skin_hb[VAR->perso[l].orientation];
                        stretch_sprite(VAR->MAP->terrain_hb, img, x, y, TAILLE, TAILLE);

                    }
                }
            }
        }
    }
}

//Créer et "configure" tous les bots utilisés dans le niveau, à partir du fichier passé en paramètres.
void definir_perso (t_global* VAR, FILE* fichier)
{
    int i, j;
    char c;

    VAR->perso = malloc(VAR->nbr_perso*sizeof(t_perso));
    for (i=0; i< VAR->nbr_perso; i++)
    {
        VAR->perso[i].compteur_prgm = 0;
        VAR->perso[i].defilement_prgm = 0;
        VAR->perso[i].prgm = malloc(sizeof(t_ancre));
        VAR->perso[i].prgm->first = NULL;
        VAR->perso[i].prgm->last = NULL;
        VAR->perso[i].defilement_prgm = 0;
        VAR->perso[i].inventaire = 0;

        int x,y,z, type, orientation;
        fscanf(fichier, "%d %d %d %d %d ", &x, &y, &z, &type, &orientation);
        VAR->perso[i].x = x;
        VAR->perso[i].xS = x;
        VAR->perso[i].y = y;
        VAR->perso[i].yS = y;
        VAR->perso[i].z = z;
        VAR->perso[i].zS = z;
        VAR->perso[i].orientation = orientation;
        VAR->perso[i].orientationS = orientation;



        BITMAP*** nouveau = malloc(2*sizeof(BITMAP**));
        for (j=0; j<2; j++)
        {
            nouveau[j] = malloc(4*sizeof(BITMAP*));
        }
        VAR->perso[i].skin = nouveau;

        switch(type)
        {
        case 1:
            {
                VAR->perso[i].skin[0][0] = VAR->IMG->Atlas[0];
                VAR->perso[i].skin[0][1] = VAR->IMG->Atlas[1];
                VAR->perso[i].skin[0][2] = VAR->IMG->Atlas[2];
                VAR->perso[i].skin[0][3] = VAR->IMG->Atlas[3];

                VAR->perso[i].skin[1][0] = VAR->IMG->Atlas_cube[0];
                VAR->perso[i].skin[1][1] = VAR->IMG->Atlas_cube[1];
                VAR->perso[i].skin[1][2] = VAR->IMG->Atlas_cube[2];
                VAR->perso[i].skin[1][3] = VAR->IMG->Atlas_cube[3];
                break;
            }
        }
        creer_hitbox_perso(VAR, i);



        for (j=0; j<9; j++)
        {
            fscanf(fichier, "%c", &c);
            if (c != '\n')
                VAR->perso[i].actions[j] = c;
            else
            {
                VAR->perso[i].actions[j] = '\0';
                j = 9;
            }
        }
    }
}

//Créer sur une bitmap parallèle une hitbox particulière pour chacun des bots, permettant ainsi de detecter les clics sur le bots.
void creer_hitbox_perso(t_global* VAR, int i)
{
    int j, k, l;
    for (j=0; j<4;j++)
    {
        VAR->perso[i].skin_hb[j] = create_bitmap(VAR->perso[i].skin[VAR->perso[i].inventaire][j]->w,VAR->perso[i].skin[VAR->perso[i].inventaire][j]->h);

        clear_to_color(VAR->perso[i].skin_hb[j], makecol(255,0,255));

        for(k=0; k<VAR->perso[i].skin[VAR->perso[i].inventaire][j]->w; k++)
        {
            for(l=0; l< VAR->perso[i].skin[VAR->perso[i].inventaire][j]->h; l++)
            {
                if (getpixel(VAR->perso[i].skin[VAR->perso[i].inventaire][j],k,l) != makecol(255,0,255))
                {
                    putpixel(VAR->perso[i].skin_hb[j], k,l, makecol(255,100+i,0));
                }
            }
        }
    }
}
