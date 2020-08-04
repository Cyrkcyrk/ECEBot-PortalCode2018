#include "main.h"

///Affichage de l'interface du Menu Principal
int menu_principal(t_global *VAR, m_rectangle *r_menu1)
{
    ///Variables locales
        ///Coordonnées d'affichage du panorama
    float panorama_x = 0;///A modifier selon l'avancée du panorama
    int panorama_y = 0;
    int sens = 1;///Définition du sens de défilement du panorama
        ///Choix du joueur
    int choix = 0;///Enregistre le choix du joueur
    int choix1 = makecol(255, 0, 0);///Couleur du choix : Lancer une partie
    int choix2 = makecol(0, 255, 0);///Couleur du choix : Charger une partie
    int choix3 = makecol(0, 0, 255);///Couleur du choix : Règles du jeu
    int choix4 = makecol(0, 255, 255);///Couleur du choix : Quitter
    int couleur_pixel = 0;///Variable pour enregistrer la couleur du pixel désigné par la souris lors du clic du joueur

    BITMAP* buffer_couleur = NULL;

    while(choix == 0)
    {
        VAR->clicD.prev = VAR->clicD.now;
        VAR->clicD.now = mouse_b&1;
        VAR->molette.prev = VAR->molette.now - mouse_z;
        VAR->molette.now= mouse_z;
        ///Affichage du Menu Principal
            ///Progression du Panorama
        blit(VAR->IMG->fond_panoramique, VAR->buffer, panorama_x, panorama_y, 0, 0, SCREEN_W, SCREEN_H);
            ///Affichage des rectangles assombris
        int i;
        for(i = 0; i < NBR_MENU; i++)
        {
            blit(VAR->IMG->fond_panoramique_assombris, VAR->buffer, (panorama_x + r_menu1[i].x1), (panorama_y + r_menu1[i].y1), r_menu1[i].x1, r_menu1[i].y1, (r_menu1[i].x2 - r_menu1[i].x1), (r_menu1[i].y2 - r_menu1[i].y1));
        }

                ///Modification du sens de défilement
        if((panorama_x + SCREEN_W) >= VAR->IMG->fond_panoramique->w)///Détection limite droite du panorama
        {
            sens = 0;
        }
        if(panorama_x <= 0)///Détection limite gauche du panorama
        {
            sens = 1;
        }
        if(sens == 1)///Défilement vers la droite
        {
            panorama_x = panorama_x + 0.1;
        }
        else if(sens == 0)///Défilement vers la gauche
        {
            panorama_x = panorama_x - 0.1;
        }


        draw_sprite(VAR->buffer, VAR->IMG->hitbox2, 0, 0);

        ///Détection du choix du joueur

        ///Récupération de la couleur du pixel désigné par la souris lors du clic du joueur
        couleur_pixel = getpixel(VAR->IMG->hitbox1, mouse_x, mouse_y);
        if(mouse_b&1 && couleur_pixel != makecol(255,0,255))///Détection clic gauche de la souris
        {
            ///Identification du choix
            if(couleur_pixel == choix1)
            {
                choix = 1;
            }
            if(couleur_pixel == choix2)
            {
                choix = 2;
            }
            if(couleur_pixel == choix3)
            {
                choix = 3;
            }
            if(couleur_pixel == choix4)
            {
                choix = 4;
            }
        }



        else if (couleur_pixel != makecol(255,0,255))
        {
            buffer_couleur = create_bitmap(400, 50);
            if(couleur_pixel == choix1)
            {
                blit(VAR->IMG->hitbox2_assombris, buffer_couleur, r_menu1[0].x1, r_menu1[0].y1, 0, 0, 400, 50);
                draw_sprite(VAR->buffer, buffer_couleur, r_menu1[0].x1, r_menu1[0].y1);
            }
            if(couleur_pixel == choix2)
            {
                blit(VAR->IMG->hitbox2_assombris, buffer_couleur, r_menu1[1].x1, r_menu1[1].y1, 0, 0, 400, 50);
                draw_sprite(VAR->buffer, buffer_couleur, r_menu1[1].x1, r_menu1[1].y1);
            }
            if(couleur_pixel == choix3)
            {
               blit(VAR->IMG->hitbox2_assombris, buffer_couleur, r_menu1[2].x1, r_menu1[2].y1, 0, 0, 400, 50);
               draw_sprite(VAR->buffer, buffer_couleur, r_menu1[2].x1, r_menu1[2].y1);
            }
            if(couleur_pixel == choix4)
            {
                blit(VAR->IMG->hitbox2_assombris, buffer_couleur, r_menu1[3].x1, r_menu1[3].y1, 0, 0, 400, 50);
                draw_sprite(VAR->buffer, buffer_couleur, r_menu1[3].x1, r_menu1[3].y1);
            }
            destroy_bitmap(buffer_couleur);
        }

        if (couleur_pixel != VAR->couleur_precedente && VAR->couleur_precedente == makecol(0,0,0)) // && clock() > VAR->SON->c_Select
        {
            play_sample(VAR->SON->Select, 255, 128, 1000, 0);
            VAR->SON->c_Select = clock() + (0.743*CLOCKS_PER_SEC);
        }

        blit(VAR->buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        VAR->couleur_precedente = couleur_pixel;
    }


    return(choix);
}


m_rectangle *creation_rectangle()
{
    ///Variables
    m_rectangle *r_menu1;///1-rouge / 2-vert / 3-bleu / 4-jaune / 5-cyan
    int taille_menu = 4;
        ///Dimensions du rectangle

    ///Initialisation variables
        ///Initialisation rectangles du menu1
    r_menu1 = (m_rectangle *)malloc(taille_menu * sizeof(m_rectangle));

        ///Rectangle 1 : Lancer une partie
    r_menu1[0].x1 = 200;
    r_menu1[0].y1 = 50;
    r_menu1[0].x2 = 600;
    r_menu1[0].y2 = 100;
    r_menu1[0].color = makecol(255, 0, 0);///Rouge
        ///Rectangle 2 : Charger une partie
    r_menu1[1].x1 = 200;
    r_menu1[1].y1 = 150;
    r_menu1[1].x2 = 600;
    r_menu1[1].y2 = 200;
    r_menu1[1].color = makecol(0, 255, 0);///Vert
        ///Rectangle 3 : Règles du jeu
    r_menu1[2].x1 = 200;
    r_menu1[2].y1 = 250;
    r_menu1[2].x2 = 600;
    r_menu1[2].y2 = 300;
    r_menu1[2].color = makecol(0, 0, 255);///Rouge
        ///Rectangle 4 : Quitter le jeu
    r_menu1[3].x1 = 200;
    r_menu1[3].y1 = 500;
    r_menu1[3].x2 = 600;
    r_menu1[3].y2 = 550;
    r_menu1[3].color = makecol(0, 255, 255);///Cyan

    return(r_menu1);
}


///Sous-programme de création des rectangles de détection de choix
///Créer des rectangles, correspondant aux différents choix du menu, sur une BITMAP non visible.
BITMAP *creation_hitbox(m_rectangle *r_menu1)
{
    ///Variables
        ///BITMAP
    BITMAP *hitbox;

    ///Initialisation variables
        ///Initialisation BITMAP
    hitbox = create_bitmap(SCREEN_W, SCREEN_H);

    ///Création des rectangles
    rectfill(hitbox, r_menu1[0].x1, r_menu1[0].y1, r_menu1[0].x2, r_menu1[0].y2, r_menu1[0].color);///Rouge
    rectfill(hitbox, r_menu1[1].x1, r_menu1[1].y1, r_menu1[1].x2, r_menu1[1].y2, r_menu1[1].color);///Vert
    rectfill(hitbox, r_menu1[2].x1, r_menu1[2].y1, r_menu1[2].x2, r_menu1[2].y2, r_menu1[2].color);///Bleu
    rectfill(hitbox, r_menu1[3].x1, r_menu1[3].y1, r_menu1[3].x2, r_menu1[3].y2, r_menu1[3].color);///Jaune
    rectfill(hitbox, r_menu1[4].x1, r_menu1[4].y1, r_menu1[4].x2, r_menu1[4].y2, r_menu1[4].color);///Cyan

    return(hitbox);
}


///Sous-programme d'assombrissement d'une image selon un facteur d'assombrissement
void assombrissement(BITMAP *image_a_assombrir, int facteur_assombrissement, BITMAP** retour)///facteur d'assombrissement, BITMAP à assombrir
{
    ///Variables locales
    BITMAP *image_assombrie;///Image assombrie
    image_assombrie = create_bitmap(image_a_assombrir->w, image_a_assombrir->h);
    int pixel;///Manipulation des pixels
    int color1, color2, color3;///Manipulation des composantes

    ///Assombrissement
    int i,j;
    for( i = 0; i < image_a_assombrir->h; i++)
    {
        for( j = 0; j < image_a_assombrir->w; j++)
        {
            pixel = getpixel(image_a_assombrir, j, i);
            ///Récupération des composantes du pixel
            color1 = getr(pixel);
            color2 = getg(pixel);
            color3 = getb(pixel);
            ///Blindage de l'assombrissement
            if((color1 - facteur_assombrissement) <= 0)
            {
                color1 = 0;
            }
            else
            {
                color1 = color1 - facteur_assombrissement;
            }
            if((color2 - facteur_assombrissement) <= 0)
            {
                color2 = 0;
            }
            else
            {
                color2 = color2 - facteur_assombrissement;
            }
            if((color3 - facteur_assombrissement) <= 0)
            {
                color3 = 0;
            }
            else
            {
                color3 = color3 - facteur_assombrissement;
            }
            pixel = makecol(color1, color2, color3);
            ///Création de l'image assombris
            putpixel(image_assombrie, j, i, pixel);
        }
    }

    *retour = image_assombrie;
}
