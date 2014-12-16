
#include <stdlib.h>

#include "entity.h"
#include "maze.h"

#include "../utility/boolean.h"
#include "../utility/direction.h"
#include "../utility/math.h"

Entity * new_entity(EntityType type) {
	Entity * entity = malloc(sizeof(Entity));
	entity->type = type;
	switch (type) {
		case PLAYER:
			entity->max_life = 100;
			entity->life = 100;
			break;
		case GOBLIN:
			entity->max_life = 20;
			entity->life = 20;
			break;
		case GHOST:
			entity->max_life = 35;
			entity->life = 35;
			break;
	}
}

boolean entity_can_move(Entity * entity, Direction direction) {
	Square * square;
	switch (direction) {
		case NORTH:
			if ((entity->square - g_maze->squares) < g_maze->size) {
				return false;
			} else {
				 square = entity->square - g_maze->size;
				 break;
			}
		case SOUTH:
			if ((entity->square + g_maze->size) >= (g_maze->squares + g_maze->size * g_maze->size)) {
				return false;
			} else {
				square = entity->square + g_maze->size;
				break;
			}
		case EAST:
			if (((entity->square - g_maze->squares) % g_maze->size) == (g_maze->size - 1)) {
				return false;
			} else {
				square = entity->square + 1;
				break;
			}
		case WEST:
			if (((entity->square - g_maze->squares) % g_maze->size) == 0) {
				return false;
			} else {
				square = entity->square - 1;
				break;
			}
	}
	return (square->type != WALL) && (square->entity == NULL);
}

void entity_move(Entity * entity, Direction direction) {
	Square * square;
	switch (direction) {
		case NORTH:
			square = entity->square - g_maze->size;
			break;
		case SOUTH:
			square = entity->square + g_maze->size;
			break;
		case EAST:
			square = entity->square + 1;
			break;
		case WEST:
			square = entity->square - 1;
			break;
	}
	square->entity = entity;
	entity->square->entity = NULL;
	entity->square = square;
}

void entity_heal(Entity * entity, short amount) {
	entity->life = mins(entity->life + amount, entity->max_life);
}

void entity_hurt(Entity * entity, short amount) {
	entity->life = maxs(entity->life - amount, 0);
}
