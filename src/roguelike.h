/**
 * @file roguelike.h
 * Fichier définissant les types et les fonctions du Roguelike.
 * @author Hector Basset
 * @author Youssef Lamniy
 * @author Ayas Oukache
 * @date 20 novembre 2014
 */

#ifndef ROGUELIKE_H

#define ROGUELIKE_H

#include "boolean.h"
#include "geo.h"

/**
 * Type énuméré représentant les différents types de case possibles.
 */
typedef enum {

	/**
	 * Case vide.
	 */
	AIR,

	/**
	 * Case étant un mur.
	 */
	WALL,

	/**
	 * Case contenant le joueur.
	 */
	PLAYER
} Square;

/**
 * Type énuméré représentant les différents directions vers lesquelles le personnage peut se déplacer.
 */
typedef enum {

	/**
	 * Nord (haut).
	 */
	NORTH,

	/**
	 * Est (droite).
	 */
	EAST,

	/**
	 * Sud (bas).
	 */
	SOUTH,

	/**
	 * Ouest (gauche).
	 */
	WEST
} Direction;

/**
 * Fonction initialisant le jeu, ne doit être appellée qu'une seule fois et avant toutes les autres relatives au jeu.
 */
void init_roguelike();

/**
 * Fonction terminant le jeu, ne doit être appellée qu'une seule fois et après toutes les autres relatives au jeu.
 */
void final_roguelike();

/**
 * Fonction retournant le labyrinthe.
 * @return Le pointeur sur la matrice de case contenant le labyrinthe.
 */
Square * get_maze();

/**
 * Fonction retournant les dimensions du labyrinthe.
 * @return Le pointeur vers la dimension du labyrinthe.
 */
Dimension * get_maze_dimension();

/**
 * Fonction générant le labyrinthe.
 */
void generate_maze();

/**
 * Fonction retournant la localisation du joueur.
 * @return Le pointeur vers la localisation du joueur.
 */
Location * get_player_location();

/**
 * Déplace le joueur vers la direction donnée.
 * @param direction La direction vers laquelle le joueur doit se déplacer.
 */
void move_player(Direction direction);

/**
 * Calcule si le joueur peut se déplacer dans la direction demandée.
 * @param direction La direction à tester.
 * @return Si le joueur peut se déplacer dans la direction demandée.
 */
boolean player_can_move(Direction direction);

/**
 * Fonction retournant la vie du joueur.
 * @return La vie du joueur.
 */
char * get_player_life();

/**
 * Modifie la vie du joueur du montant donné.
 * @param amount Le montant dont la vie est modifié.
 */
void modify_player_life(char amount);

#endif
