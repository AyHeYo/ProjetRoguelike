
#ifndef MODEL_ENTITY_H

#define MODEL_ENTITY_H

#include "maze.h"

#include "../utility/boolean.h"
#include "../utility/direction.h"

typedef struct Entity Entity;

typedef enum EntityType EntityType;

enum EntityType {
	PLAYER,
	GOBLIN,
	GHOST
};

struct Entity {
	EntityType type;
	short max_life;
	short life;
	Direction direction;
	struct Square * square;
};

Entity * new_entity(EntityType type);

boolean entity_can_move(Entity * entity, Direction direction);

void entity_move(Entity * entity, Direction direction);

void entity_heal(Entity * entity, short amount);

void entity_hurt(Entity * entity, short amount);

#endif
