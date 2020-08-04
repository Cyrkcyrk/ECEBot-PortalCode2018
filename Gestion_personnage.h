#ifndef GESTION_PERSONNAGE_H_INCLUDED
#define GESTION_PERSONNAGE_H_INCLUDED

void deplacer_perso(t_global* VAR, int i);
int verifier_tourelle(t_global* VAR);
int collision_avancer_yM(t_global* VAR, int i);
int collision_avancer_xP(t_global* VAR, int i);
int collision_avancer_yP(t_global* VAR, int i);
int collision_avancer_xM(t_global* VAR, int i);
int collision_pousser_yM(t_global* VAR, int i);
int collision_pousser_xP(t_global* VAR, int i);
int collision_pousser_yP(t_global* VAR, int i);
int collision_pousser_xM(t_global* VAR, int i);

#endif // GESTION_PERSONNAGE_H_INCLUDED
