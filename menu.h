#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

int menu_principal(t_global *VAR, m_rectangle *r_menu1);
m_rectangle *creation_rectangle();
BITMAP *creation_hitbox(m_rectangle *r_menu1);
void assombrissement(BITMAP *image_a_assombrir, int facteur_assombrissement, BITMAP** retour);


#endif // MENU_H_INCLUDED
