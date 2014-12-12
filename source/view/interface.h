/**
 * @file view/interface.h
 * Fichier définissant les actions de bases de l'interface avec l'utilisateur.
 * @author Hector Basset
 * @date 1 décembre 2014
 */

#ifndef VIEW_INTERFACE_H

#define VIEW_INTERFACE_H

//librairies du modèle
#include "../model/roguelike.h"

//librairies utilitaires
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
 * Attent que l'utilisateur effectue une action.
 * @return Le type d'action souhaitée par l'utilisateur.
 */
Action wait_action();

/**
 * Attent que l'interface soit à jour.
 */
void wait_ready();

/**
 * Remet le curseur en haut.
 */
void cursor_at_top();

/**
 * Retourne la marge entre le labyrinthe et la fenêtre.
 * @return La marge entre le labyrinthe et la fenêtre.
 */
int get_maze_window_margin();

#endif
