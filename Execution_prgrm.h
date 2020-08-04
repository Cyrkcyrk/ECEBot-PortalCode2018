#ifndef EXECUTION_PRGRM_H_INCLUDED
#define EXECUTION_PRGRM_H_INCLUDED

void trouver_maillon_prgm(t_global* VAR, t_maillon** retour);
void ajouter_action_fin(t_global* VAR);
void creer_maillon(t_maillon** retour);
void supprimer_maillon(t_global* VAR, t_maillon** charge);
void supprimer_programme(t_global* VAR);
void afficher_boutons_prgm(t_global* VAR);
void afficher_prgm(t_global* VAR);

#endif // EXECUTION_PRGRM_H_INCLUDED
