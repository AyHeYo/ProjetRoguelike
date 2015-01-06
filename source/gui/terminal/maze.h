/**
 * @file view/maze.h
 * Fichier définissant les fonctions permettant de contrôler l'affichage du labyrinthe.
 * @author Hector Basset
 * @date 12 décembre 2014
 */

#ifndef GUI_TERMINAL_MAZE_H

#define GUI_TERMINAL_MAZE_H

#include "../../game/maze.h"

/**
 * La hauteur actuelle du labyrinthe dans l'affichage.
 */
int g_maze_height;

void update_square(Square * square);

void blink_square(Square * square);

/**
 * Affiche le labyrinthe dans son ensemble.
 */
void display_maze();

#endif
