/**
 * @file view/maze.h
 * Fichier définissant les fonctions permettant de contrôler l'affichage du labyrinthe.
 * @author Hector Basset
 * @date 12 décembre 2014
 */

#ifndef VIEW_MAZE_H

#define VIEW_MAZE_H

//librairies du modèle
#include "../model/roguelike.h"

/**
 * Affiche le labyrinthe dans son ensemble.
 * @param maze Le pointeur vers la matrice représentant le labyrinthe.
 * @param dimension La dimension du labyrinthe.
 */
void display_maze(Square * maze, Dimension dimension);

/**
 * Retourne la hauteur du labyrinthe.
 * @return La hauteur du labyrinthe.
 */
int get_maze_height();

#endif
