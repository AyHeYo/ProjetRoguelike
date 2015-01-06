/**
 * @file model/maze.h
 * Fichier définissant les fonctions et les structures de données permettant la création, la supression et la gestion du labyrinthe et de ses cases.
 * @author Hector Basset
 * @date 16 décembre 2014
 */

#ifndef GAME_MAZE_H

#define GAME_MAZE_H

//librairies du modèle
#include "direction.h"
#include "entity.h"

//librairies utilitaires
#include "../utility/geo.h"

/**
 * Type énuméré définissant les différents types de case.
 */
typedef enum {

	/**
	 * Case vide.
	 */
	AIR,

	/**
	 * Case de mur.
	 */
	WALL,

	/**
	 * Case d'eau.
	 */
	WATER,

	/**
	 * Case brûlante.
	 */
	FIRE
} SquareType;

typedef struct Square Square;

/**
 * Structure de données représentant une case.
 */
struct Square {

	/**
	 * Le type de la case.
	 */
	SquareType type;

	/**
	 * L'entité présente sur la case.
	 */
	struct Entity * entity;
};

/**
 * Structure de données représentant le labyrinthe.
 */
typedef struct {

	/**
	 * Pointeur vers la première de ses cases (tableau dynamique de cases).
	 */
	Square * squares;

	/**
	 * La taille du labyrinthe (nombre de case pour chaque côtés).
	 */
	unsigned short size;

	Square * door;
} Maze;

/**
 * Le labyrinthe.
 */
Maze * g_maze;

/**
 * Fonction générant le labyrinthe.
 */
void generate_maze();

/**
 * Fonction libérant l'espace mémoire occupé par le labyrinthe.
 */
void free_maze();

Square * get_near_square(Square * square, Direction direction);

Location get_square_location(Square * square);

#endif
