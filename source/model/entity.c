/**
 * @file model/entity.c
 * Fichier implémentant les fonctions permettant la création, la supression et la gestion des entité.
 * @author Hector Basset
 * @date 16 décembre 2014
 */

//librairies du système
#include <stdlib.h>

//librairies du modèle
#include "entity.h"
#include "maze.h"

//librairies utilitaires
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
			entity->weapon = RANGED;
			break;
		case GOBLIN:
			entity->max_life = 20;
			entity->life = 20;
			entity->weapon = MELEE;
			break;
		case GHOST:
			entity->max_life = 35;
			entity->life = 35;
			entity->weapon = NONE;
			break;
		case KEY:
			entity->max_life = 1;
			entity->life = 1;
			entity->weapon = NONE;
			break;
		case SWORD:
			entity->max_life = 1;
			entity->life = 1;
			entity->weapon = NONE;
			break;
		case ARROW:
			entity->max_life = 1;
			entity->life = 1;
			entity->weapon = NONE;
			break;
		case BALL:
			entity->max_life = 1;
			entity->life = 1;
			entity->weapon = NONE;
			break;
	}
	return entity;
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

void entity_attack(Entity * entity) {
	switch (entity->weapon) {
		case NONE:
			break;
		case MELEE:
			break;
		case RANGED:
			break;
		case MAGIC:
			break;
	}
}
