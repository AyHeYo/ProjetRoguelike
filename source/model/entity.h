
#include "maze.h"

typedef struct Entity Entity;

typedef enum EntityType EntityType;

struct Entity {
	EntityType type;
	short max_life;
	short life;
	Square * square;
}

enum EntityType {
	PLAYER,
	GOBLIN,
	GHOST
};
