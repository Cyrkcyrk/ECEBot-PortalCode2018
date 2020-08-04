#include "main.h"

//Charge l'image passé en paramètre dans la bitmap passé en paramètre.
void charger_img(BITMAP** bmp, char string[])
{
    *bmp = load_bitmap(string, NULL);
    if (*bmp != NULL)
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

//Petmet de charger l'intégralitée des images dont on a besoins.
void charger_tout_img(t_global* VAR)
{
    charger_img(&(VAR->IMG->cube_clair), "images/terrain/cube_clair.bmp");
    charger_img(&(VAR->IMG->cube_sombre), "images/terrain/cube_sombre.bmp");
    charger_img(&(VAR->IMG->compagnion_cube), "images/terrain/CompagnionCube.bmp");
    charger_img(&(VAR->IMG->boutton), "images/terrain/boutton.bmp");
    charger_img(&(VAR->IMG->boutton_presse), "images/terrain/boutton_presse.bmp");
    charger_img(&(VAR->IMG->boutton_cube), "images/terrain/boutton_cube.bmp");
    charger_img(&(VAR->IMG->porte[0]), "images/terrain/porte_D.bmp");
    charger_img(&(VAR->IMG->porte[1]), "images/terrain/porte_G.bmp");
    charger_img(&(VAR->IMG->porte_ouverte[0]), "images/terrain/porte_ouverte_D.bmp");
    charger_img(&(VAR->IMG->porte_ouverte[1]), "images/terrain/porte_ouverte_G.bmp");
    charger_img(&(VAR->IMG->Atlas[0]), "images/Atlas/Atlas0.bmp");
    charger_img(&(VAR->IMG->Atlas[1]), "images/Atlas/Atlas1.bmp");
    charger_img(&(VAR->IMG->Atlas[2]), "images/Atlas/Atlas2.bmp");
    charger_img(&(VAR->IMG->Atlas[3]), "images/Atlas/Atlas3.bmp");
    charger_img(&(VAR->IMG->Atlas_cube[0]), "images/Atlas/Atlas0_cube.bmp");
    charger_img(&(VAR->IMG->Atlas_cube[1]), "images/Atlas/Atlas1_cube.bmp");
    charger_img(&(VAR->IMG->Atlas_cube[2]), "images/Atlas/Atlas2_cube.bmp");
    charger_img(&(VAR->IMG->Atlas_cube[3]), "images/Atlas/Atlas3_cube.bmp");
    charger_img(&(VAR->IMG->tourelle[0]), "images/Tourelles/Tour0.bmp");
    charger_img(&(VAR->IMG->tourelle[1]), "images/Tourelles/Tour1.bmp");
    charger_img(&(VAR->IMG->tourelle[2]), "images/Tourelles/Tour2.bmp");
    charger_img(&(VAR->IMG->tourelle[3]), "images/Tourelles/Tour3.bmp");
    charger_img(&(VAR->IMG->overlay), "images/overlay.bmp");
    charger_img(&(VAR->IMG->overlay_hb), "images/overlay_hb.bmp");
    charger_img(&(VAR->IMG->action_attendre), "images/actions/attendre.bmp");
    charger_img(&(VAR->IMG->action_avancer), "images/actions/avancer.bmp");
    charger_img(&(VAR->IMG->action_porter), "images/actions/porter2.bmp");
    charger_img(&(VAR->IMG->action_pousser), "images/actions/pousser.bmp");
    charger_img(&(VAR->IMG->action_sauter), "images/actions/Sauter.bmp");
    charger_img(&(VAR->IMG->action_tourner_droite), "images/actions/Droite.BMP");
    charger_img(&(VAR->IMG->action_tourner_gauche), "images/actions/Gauche.bmp");
    charger_img(&(VAR->IMG->action_selecteur), "images/actions/Selecteur.bmp");

    charger_img(&(VAR->IMG->fin_echec), "images/Reussite-Echec/echec.bmp");
    charger_img(&(VAR->IMG->fin_reussite), "images/Reussite-Echec/reussite.bmp");
    charger_img(&(VAR->IMG->fin_hb), "images/Reussite-Echec/Hitbox.bmp");


    charger_img(&(VAR->IMG->fond_panoramique), "images/Menu/background_flou5.bmp");
    assombrissement(VAR->IMG->fond_panoramique, 40, &VAR->IMG->fond_panoramique_assombris);///Création de l'image assombris du panorama
    VAR->r_menu1 = creation_rectangle();
    VAR->IMG->hitbox1 = creation_hitbox(VAR->r_menu1);///Création hitbox avec rectangles de sélection du menu principal

    charger_img(&(VAR->IMG->hitbox2), "images/Menu/overlay_menu.bmp");
    charger_img(&(VAR->IMG->hitbox2_assombris), "images/Menu/overlay_menu_sombre.bmp");
    charger_img(&(VAR->IMG->carte_monde), "images/Menu/ArrierePlan.bmp");
    charger_img(&(VAR->IMG->regles_du_jeu), "images/Menu/Regle.bmp");

    charger_img(&(VAR->IMG->personnage_principal[0]) , "images/Menu/Shell/Shell_marche1_D.bmp");
    charger_img(&(VAR->IMG->personnage_principal[1]) , "images/Menu/Shell/Shell_marche1_G.bmp");
    charger_img(&(VAR->IMG->personnage_principal[2]) , "images/Menu/Shell/Shell_marche2_D.bmp");
    charger_img(&(VAR->IMG->personnage_principal[3]) , "images/Menu/Shell/Shell_marche2_G.bmp");
    charger_img(&(VAR->IMG->personnage_principal[4]) , "images/Menu/Shell/Shell_stop_D.bmp");
    charger_img(&(VAR->IMG->personnage_principal[5]) , "images/Menu/Shell/Shell_stop_G.bmp");



    VAR->IMG->overlay_hb2 = create_bitmap(SCREEN_W, SCREEN_H);
    VAR->IMG->vide = create_bitmap(100,100);
    clear_to_color(VAR->IMG->vide, makecol(255,0,255));
}
