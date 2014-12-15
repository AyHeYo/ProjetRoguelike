
#include "entity.h"

typedef struct Square Square;

typedef enum SquareType SquareType;

struct Square {
	SquareType type;
	Entity * entity;
}

enum SquareType {
	AIR,
	WALL,
	WATER,
	FIRE
};

typedef struct {
	Square * squares;
	unsigned short size;
} Maze;

Maze * generate_maze(Maze * maze);

void free_maze(Maze * maze);
