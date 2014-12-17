/**
 * @file model/maze.h
 * Fichier définissant les fonctions et les structures de données permettant la création, la supression et la gestion du labyrinthe et de ses cases.
 * @author Hector Basset
 * @date 16 décembre 2014
 */

#ifndef MODEL_MAZE_H

#define MODEL_MAZE_H

//librairies du modèle
#include "entity.h"

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

#endif
