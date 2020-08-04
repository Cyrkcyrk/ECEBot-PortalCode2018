#include "main.h"

//Moteur de jeu: Permet de d'executer laction programmé.
void deplacer_perso(t_global* VAR, int i)
{
    if (VAR->perso[i].executer_prgm == 1)
    {
        switch(VAR->perso[i].charge->objet->action)
        {
        case 'A':
            {

                switch (VAR->perso[i].orientation)
                {
                case 0:
                    {
                        if (collision_avancer_yM(VAR, i))
                        {
                            if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')
                            {
                                VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'b';
                                play_sample(VAR->SON->Button_release, 255, 255, 1000, 0);
                                VAR->MAP->nbr_bouton++;
                            }
                            VAR->perso[i].y--;
                            son_pas(VAR);
                        }

                        break;
                    }
                case 1:
                    {
                        if (collision_avancer_xP(VAR, i))
                        {
                            if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')
                            {
                                VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'b';
                                play_sample(VAR->SON->Button_release, 255, 255, 1000, 0);
                                VAR->MAP->nbr_bouton++;
                            }
                            VAR->perso[i].x++;
                            son_pas(VAR);
                        }

                        break;
                    }
                case 2:
                    {
                        if (collision_avancer_yP(VAR, i))
                        {
                            if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')
                            {
                                VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'b';
                                play_sample(VAR->SON->Button_release, 255, 255, 1000, 0);
                                VAR->MAP->nbr_bouton++;
                            }
                            VAR->perso[i].y++;
                            son_pas(VAR);
                        }

                        break;
                    }
                case 3:
                    {
                        if (collision_avancer_xM(VAR, i))
                        {
                            if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')
                            {
                                VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'b';
                                play_sample(VAR->SON->Button_release, 255, 255, 1000, 0);
                                VAR->MAP->nbr_bouton++;
                            }
                            VAR->perso[i].x--;
                            son_pas(VAR);
                        }

                        break;
                    }
                }

                if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'b')
                {
                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'B';
                    play_sample(VAR->SON->Button_press, 255, 255, 1000, 0);
                    VAR->MAP->nbr_bouton--;
                }

                break;
            }
        case 'D':
            {
                VAR->perso[i].orientation = (VAR->perso[i].orientation+1) % 4;
                break;
            }
        case 'G':
            {
                VAR->perso[i].orientation = VAR->perso[i].orientation-1;
                if (VAR->perso[i].orientation < 0)
                    VAR->perso[i].orientation = 3;
                break;
            }
        case 'P':
            {
                if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'c' && VAR->perso[i].inventaire == 0)
                {
                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = '0';
                    VAR->perso[i].inventaire = 1;
                }
                else if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == '0' && VAR->perso[i].inventaire == 1)
                {
                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'c';
                    VAR->perso[i].inventaire = 0;
                }
                else if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'C' && VAR->perso[i].inventaire == 0)
                {
                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'B';
                    VAR->perso[i].inventaire = 1;
                }
                else if ((VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'b' || VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')&& VAR->perso[i].inventaire == 1)
                {
                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'C';
                    VAR->perso[i].inventaire = 0;
                }

                break;
            }
        case 'p':
            {
                switch (VAR->perso[i].orientation)
                {
                case 0:
                    {
                        switch(collision_pousser_yM(VAR, i))
                        {
                        case 2:
                            {
                                if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')
                                {
                                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'b';
                                    play_sample(VAR->SON->Button_release, 255, 255, 1000, 0);
                                }
                                VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y-2][VAR->perso[i].z-1] = '2';
                                VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y-1][VAR->perso[i].z] = '0';
                                VAR->perso[i].y--;
                                son_pas(VAR);
                                son_frottement(VAR);
                                break;
                            }
                        case 1:
                            {
                                if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')
                                {
                                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'b';
                                    play_sample(VAR->SON->Button_release, 255, 255, 1000, 0);
                                }
                                VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y-2][VAR->perso[i].z] = '2';
                                VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y-1][VAR->perso[i].z] = '0';
                                VAR->perso[i].y--;
                                son_pas(VAR);
                                son_frottement(VAR);
                                break;
                            }
                        }

                        break;
                    }
                case 1:
                    {
                        switch(collision_pousser_xP(VAR, i))
                        {
                        case 2:
                            {
                                if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')
                                {
                                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'b';
                                    play_sample(VAR->SON->Button_release, 255, 255, 1000, 0);
                                }
                                VAR->MAP->matrice[VAR->perso[i].x+2][VAR->perso[i].y][VAR->perso[i].z-1] = '2';
                                VAR->MAP->matrice[VAR->perso[i].x+1][VAR->perso[i].y][VAR->perso[i].z] = '0';
                                VAR->perso[i].x++;
                                son_pas(VAR);
                                son_frottement(VAR);
                                break;
                            }
                        case 1:
                            {
                                if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')
                                {
                                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'b';
                                    play_sample(VAR->SON->Button_release, 255, 255, 1000, 0);
                                }
                                VAR->MAP->matrice[VAR->perso[i].x+2][VAR->perso[i].y][VAR->perso[i].z] = '2';
                                VAR->MAP->matrice[VAR->perso[i].x+1][VAR->perso[i].y][VAR->perso[i].z] = '0';
                                VAR->perso[i].x++;
                                son_pas(VAR);
                                son_frottement(VAR);
                                break;
                            }
                        }

                        break;
                    }
                case 2:
                    {
                        switch(collision_pousser_yP(VAR, i))
                        {
                        case 2:
                            {
                                if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')
                                {
                                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'b';
                                    play_sample(VAR->SON->Button_release, 255, 255, 1000, 0);
                                }

                                VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y+2][VAR->perso[i].z-1] = '2';
                                VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y+1][VAR->perso[i].z] = '0';
                                VAR->perso[i].y++;
                                son_pas(VAR);
                                son_frottement(VAR);
                                break;
                            }
                        case 1:
                            {
                                if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')
                                {
                                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'b';
                                    play_sample(VAR->SON->Button_release, 255, 255, 1000, 0);
                                }

                                VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y+2][VAR->perso[i].z] = '2';
                                VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y+1][VAR->perso[i].z] = '0';
                                VAR->perso[i].y++;
                                son_pas(VAR);
                                son_frottement(VAR);
                                break;
                            }
                        }

                        break;
                    }
                case 3:
                    {
                        switch(collision_pousser_xM(VAR, i))
                        {
                        case 2:
                            {
                                if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')
                                {
                                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'b';
                                    play_sample(VAR->SON->Button_release, 255, 255, 1000, 0);
                                }

                                VAR->MAP->matrice[VAR->perso[i].x-2][VAR->perso[i].y][VAR->perso[i].z-1] = '2';
                                VAR->MAP->matrice[VAR->perso[i].x-1][VAR->perso[i].y][VAR->perso[i].z] = '0';
                                VAR->perso[i].x--;
                                son_pas(VAR);
                                son_frottement(VAR);
                                break;
                            }
                        case 1:
                            {
                                if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] == 'B')
                                {
                                    VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y][VAR->perso[i].z] = 'b';
                                    play_sample(VAR->SON->Button_release, 255, 255, 1000, 0);
                                }
                                VAR->MAP->matrice[VAR->perso[i].x-2][VAR->perso[i].y][VAR->perso[i].z] = '2';
                                VAR->MAP->matrice[VAR->perso[i].x-1][VAR->perso[i].y][VAR->perso[i].z] = '0';
                                VAR->perso[i].x--;
                                son_pas(VAR);
                                son_frottement(VAR);
                                break;
                            }
                        }

                        break;
                    }
                }
            }
        }

        if (VAR->perso[i].charge->next != NULL)
        {
            VAR->perso[i].charge = VAR->perso[i].charge->next;
        }
        else
        {
            VAR->perso[i].executer_prgm = 0;
        }
    }
}

//Vérifie si un bot est dans le champ d'une des tourelles.
int verifier_tourelle(t_global* VAR)
{
    int n, m;
    int i,j,k;

    int* x = malloc(VAR->MAP->nbr_tourelle*sizeof(int));
    int*y = malloc(VAR->MAP->nbr_tourelle*sizeof(int));
    int*z = malloc(VAR->MAP->nbr_tourelle*sizeof(int));
    int*o = malloc(VAR->MAP->nbr_tourelle*sizeof(int));

    n=0;
    for (i=0; i<VAR->MAP->tailleX; i++)
    {
        for (j=0; j<VAR->MAP->tailleY; j++)
        {
            for (k=0; k<VAR->MAP->tailleZ; k++)
            {
                if (VAR->MAP->matrice[i][j][k] == 'u')
                {
                    x[n] = i;
                    y[n] = j;
                    z[n] = k;
                    o[n] = 0;
                    n++;
                }
                else if (VAR->MAP->matrice[i][j][k] == 'U')
                {
                    x[n]=i;
                    y[n]=j;
                    z[n]=k;
                    o[n]=1;
                    n++;
                }
                if (VAR->MAP->matrice[i][j][k] == 't')
                {
                    x[n]=i;
                    y[n]=j;
                    z[n]=k;
                    o[n]=2;
                    n++;
                }
                else if (VAR->MAP->matrice[i][j][k] == 'T')
                {
                    x[n]=i;
                    y[n]=j;
                    z[n]=k;
                    o[n]=3;
                    n++;
                }
            }
        }
    }

    for (n=0; n<VAR->MAP->nbr_tourelle; n++)
    {
        for (m=0; m<VAR->nbr_perso; m++)
        {
            switch(o[n])
            {
            case 0:
                {
                    for (i=0; i< VAR->MAP->tailleY; i++)
                    {
                        if ((VAR->perso[m].x == x[n]) && (VAR->perso[m].y == y[n] + i) && (VAR->perso[m].z == z[n]))
                        {
                            free(x); free(y); free(z); free(o);
                            return 1;
                        }
                        else if (VAR->MAP->matrice[x[n]][y[n]+i][z[n]] == '1' || VAR->MAP->matrice[x[n]][y[n]+i][z[n]] == '2')
                        {
                            i = VAR->MAP->tailleY;
                        }
                    }
                    break;
                }
            case 1:
                {
                    for (i=0; i< VAR->MAP->tailleX; i++)
                    {
                        if ((VAR->perso[m].x == x[n]+i) && (VAR->perso[m].y == y[n]) && (VAR->perso[m].z == z[n]))
                        {
                            free(x); free(y); free(z); free(o);
                            return 1;
                        }
                        else if (VAR->MAP->matrice[x[n]+i][y[n]][z[n]] == '1' || VAR->MAP->matrice[x[n]+i][y[n]][z[n]] == '2')
                        {
                            i = VAR->MAP->tailleX;
                        }
                    }
                    break;
                }
            case 2:
                {
                    for (i=0; i< VAR->MAP->tailleY; i++)
                    {
                        if ((VAR->perso[m].x == x[n]) && (VAR->perso[m].y == y[n] - i) && (VAR->perso[m].z == z[n]))
                        {
                            free(x); free(y); free(z); free(o);
                            return 1;
                        }
                        else if (VAR->MAP->matrice[x[n]][y[n]-i][z[n]] == '1' || VAR->MAP->matrice[x[n]][y[n]-i][z[n]] == '2')
                        {
                            i = VAR->MAP->tailleY;
                        }
                    }
                    break;
                }
            case 3:
                {
                    for (i=0; i< VAR->MAP->tailleX; i++)
                    {
                        if ((VAR->perso[m].x == x[n]-i) && (VAR->perso[m].y == y[n]) && (VAR->perso[m].z == z[n]))
                        {
                            free(x); free(y); free(z); free(o);
                            return 1;
                        }
                        else if (VAR->MAP->matrice[x[n]-i][y[n]][z[n]] == '1' || VAR->MAP->matrice[x[n]-i][y[n]][z[n]] == '2')
                        {
                            i = VAR->MAP->tailleX;
                        }
                    }
                    break;
                }
            }
        }
    }
    free(x); free(y); free(z); free(o);
    return 0;
}

//Pour les 4 sous programmes suivants: Permet de savoir si le bot peut se deplacer dans la direction voulue. (yP = y+, xM = x-, etc.).
int collision_avancer_yM(t_global* VAR, int i)
{
    int j;
    for (j=0; j<VAR->nbr_perso; j++)
    {
        if (j != i && (VAR->perso[j].x == VAR->perso[i].x && VAR->perso[j].y == VAR->perso[i].y-1))
            return 0;
    }
    if (VAR->perso[i].y <= 0)
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y -1][VAR->perso[i].z] == '1')
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y -1][VAR->perso[i].z] == '2')
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y -1][VAR->perso[i].z-1] == '0')
        return 0;

    return 1;

}
int collision_avancer_xP(t_global* VAR, int i)
{
    int j;
    for (j=0; j<VAR->nbr_perso; j++)
    {
        if (j != i && (VAR->perso[j].x == VAR->perso[i].x+1 && VAR->perso[j].y == VAR->perso[i].y))
            return 0;
    }
    if (VAR->perso[i].x >= VAR->MAP->tailleX-1)
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x +1][VAR->perso[i].y][VAR->perso[i].z] == '1')
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x +1][VAR->perso[i].y][VAR->perso[i].z] == '2')
        return 0;

    if (VAR->MAP->matrice[VAR->perso[i].x +1][VAR->perso[i].y][VAR->perso[i].z-1] == '0')
        return 0;

    return 1;
}
int collision_avancer_yP(t_global* VAR, int i)
{
    int j;
    for (j=0; j<VAR->nbr_perso; j++)
    {
        if (j != i && (VAR->perso[j].x == VAR->perso[i].x && VAR->perso[j].y == VAR->perso[i].y+1))
            return 0;
    }
    if(VAR->perso[i].y >= VAR->MAP->tailleY-1)
        return 0;
    if(VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y +1][VAR->perso[i].z] == '1')
        return 0;
    if(VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y +1][VAR->perso[i].z] == '2')
        return 0;

    if(VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y +1][VAR->perso[i].z-1] == '0')
        return 0;

    return 1;
}
int collision_avancer_xM(t_global* VAR, int i)
{
    int j;
    for (j=0; j<VAR->nbr_perso; j++)
    {
        if (j != i && (VAR->perso[j].x == VAR->perso[i].x-1 && VAR->perso[j].y == VAR->perso[i].y))
            return 0;
    }
    if(VAR->perso[i].x <= 0)
        return 0;
    if(VAR->MAP->matrice[VAR->perso[i].x -1][VAR->perso[i].y][VAR->perso[i].z] == '1')
        return 0;
    if(VAR->MAP->matrice[VAR->perso[i].x -1][VAR->perso[i].y][VAR->perso[i].z] == '2')
        return 0;

    if(VAR->MAP->matrice[VAR->perso[i].x -1][VAR->perso[i].y][VAR->perso[i].z-1] == '0')
        return 0;
    return 1;
}


//Pour les 4 sous programmes suivants: Permet de savoir si le bot peut se deplacer et pousser un bloc dans la coordonnée voulue. (yP = y+, xM = x-, etc.).
int collision_pousser_yM(t_global* VAR, int i)
{
    int j;

    if (VAR->perso[i].y <= 1)
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y -1][VAR->perso[i].z] == '1')
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y -1][VAR->perso[i].z-1] == '0')
        return 0;


    if(VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y -1][VAR->perso[i].z] != '2')
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y -2][VAR->perso[i].z] != '0')
        return 0;

    for (j=0; j<VAR->nbr_perso; j++)
    {
        if (j != i && (VAR->perso[j].x == VAR->perso[i].x && VAR->perso[j].y == VAR->perso[i].y-1))
            return 0;
        if (j != i && (VAR->perso[j].x == VAR->perso[i].x && VAR->perso[j].y == VAR->perso[i].y-2))
            return 0;
    }
    if(VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y-2][VAR->perso[i].z-1] == '0')
        return 2;
    return 1;

}
int collision_pousser_xP(t_global* VAR, int i)
{
    int j;
    if (VAR->perso[i].x >= VAR->MAP->tailleX-2)
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x+1][VAR->perso[i].y][VAR->perso[i].z-1] == '0')
        return 0;

    if(VAR->MAP->matrice[VAR->perso[i].x+1][VAR->perso[i].y][VAR->perso[i].z] != '2')
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x+2][VAR->perso[i].y][VAR->perso[i].z] != '0')
        return 0;

    for (j=0; j<VAR->nbr_perso; j++)
    {
        if (j != i && (VAR->perso[j].x == VAR->perso[i].x+1 && VAR->perso[j].y == VAR->perso[i].y))
            return 0;
        if (j != i && (VAR->perso[j].x == VAR->perso[i].x+2 && VAR->perso[j].y == VAR->perso[i].y))
            return 0;
    }

    if(VAR->MAP->matrice[VAR->perso[i].x+2][VAR->perso[i].y][VAR->perso[i].z-1] == '0')
        return 2;

    return 1;
}
int collision_pousser_yP(t_global* VAR, int i)
{
    int j;
    if (VAR->perso[i].y >= VAR->MAP->tailleY-2)
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y +1][VAR->perso[i].z-1] == '0')
        return 0;

    if(VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y +1][VAR->perso[i].z] != '2')
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y +2][VAR->perso[i].z] != '0')
        return 0;

    for (j=0; j<VAR->nbr_perso; j++)
    {
        if (j != i && (VAR->perso[j].x == VAR->perso[i].x && VAR->perso[j].y == VAR->perso[i].y+1))
            return 0;
        if (j != i && (VAR->perso[j].x == VAR->perso[i].x && VAR->perso[j].y == VAR->perso[i].y+2))
            return 0;
    }

    if (VAR->MAP->matrice[VAR->perso[i].x][VAR->perso[i].y+2][VAR->perso[i].z-1] == '0')
        return 2;

    return 1;
}
int collision_pousser_xM(t_global* VAR, int i)
{
    int j;
    if (VAR->perso[i].x <= 1)
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x-1][VAR->perso[i].y][VAR->perso[i].z-1] == '0')
        return 0;

    if(VAR->MAP->matrice[VAR->perso[i].x-1][VAR->perso[i].y][VAR->perso[i].z] != '2')
        return 0;
    if (VAR->MAP->matrice[VAR->perso[i].x-2][VAR->perso[i].y][VAR->perso[i].z] != '0')
        return 0;

    for (j=0; j<VAR->nbr_perso; j++)
    {
        if (j != i && (VAR->perso[j].x == VAR->perso[i].x-1 && VAR->perso[j].y == VAR->perso[i].y))
            return 0;
        if (j != i && (VAR->perso[j].x == VAR->perso[i].x-2 && VAR->perso[j].y == VAR->perso[i].y))
            return 0;
    }

    if (VAR->MAP->matrice[VAR->perso[i].x-2][VAR->perso[i].y][VAR->perso[i].z-1] == '0')
        return 2;

    return 1;
}
