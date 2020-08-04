#ifndef CHARGER_MAP_H_INCLUDED
#define CHARGER_MAP_H_INCLUDED

void projection(t_global* VAR, int *pxe, int *pye, int x, int y, int z);
void load_matrice(t_global* VAR, char string[]);
void copier_matrice(t_global* VAR);
void creer_map(t_global* VAR);
void definir_perso (t_global* VAR, FILE* fichier);
void creer_hitbox_perso(t_global* VAR, int i);


#endif // CHARGER_MAP_H_INCLUDED
