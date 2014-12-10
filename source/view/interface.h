/**
 * @file interface.h
 * Fichier définissant l'interface avec l'utilisateur.
 * @author Hector Basset
 * @date 1 décembre 2014
 */

#ifndef INTERFACE_H

#define INTERFACE_H

#include "../model/roguelike.h"
#include "../utility/geo.h"

/**
 * Type énuméré définissant les différentes actions voulues par l'utilisateur.
 */
typedef enum {

	/**
	 * Aller vers le haut.
	 */
	TOP,

	/**
	 * Aller vers le bas.
	 */
	BOTTOM,

	/**
	 * Aller à droite.
	 */
	RIGHT,

	/**
	 * Aller à gauche.
	 */
	LEFT,

	/**
	 * Quitter/Sortir.
	 */
	EXIT,

	/**
	 * Frapper.
	 */
	HIT,

	/**
	 * Accepter.
	 */
	ACCEPT,

	/**
	 * Refuser.
	 */
	DENY
} Action;

/**
 * Initialise l'interface, ne doit être appellée qu'une seule fois et avant toutes les autres fonctions relatives à l'interface.
 */
void init_interface();

/**
 * Termine l'interface, ne doit être appellée qu'une seule fois et après toutes les autres fonctions relatives à l'interface.
 */
void final_interface();

/**
 * Affiche le labyrinthe dans son ensemble.
 * @param maze Le pointeur vers la matrice représentant le labyrinthe.
 * @param dimension les dimensions du labyrinthe.
 */
void display_maze(Square * maze, Dimension * dimension);

/**
 * Attent que l'utilisateur effectue une action.
 * @return Le type d'action souhaitée par l'utilisateur.
 */
Action wait_action();

/**
 * Attent que l'interface qoit à jour.
 */
void wait_ready();

void cursor_at_top();

#endif
