
#ifndef MODEL_MAZE_H

#define MODEL_MAZE_H

#include "entity.h"

typedef struct Square Square;

typedef enum SquareType SquareType;

enum SquareType {
	AIR,
	WALL,
	WATER,
	FIRE
};

struct Square {
	SquareType type;
	struct Entity * entity;
};

typedef struct {
	Square * squares;
	unsigned short size;
} Maze;

/**
 * Le pointeur vers la matrice de case contenant le labyrinthe.
 */
Maze * g_maze;

void generate_maze();

void free_maze();

#endif
