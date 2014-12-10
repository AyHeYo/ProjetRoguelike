
#ifndef WINDOW_H

/**
 * Affiche le haut de la fenêtre.
 */
void print_window_top();

/**
 * Affiche une ligne vide de fenêtre.
 */
void print_window_line();

/**
 * Affiche le bas de la fenêtre.
 */
void print_window_bottom();

/**
 * Affiche un message à l'utilisateur.
 * @param message Le message à afficher à l'utilisateur.
 */
void display_message(char message[]);

/**
 * Efface le message affiché à l'utilisateur.
 */
void clear_message();

#define WINDOW_H

#endif
