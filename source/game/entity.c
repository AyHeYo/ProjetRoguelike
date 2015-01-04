/**
 * @file model/entity.c
 * Fichier implémentant les fonctions permettant la création, la supression et la gestion des entité.
 * @author Hector Basset
 * @date 16 décembre 2014
 */

//librairies du système
#include <stdlib.h>
#include <unistd.h>

//librairies du modèle
#include "entity.h"
#include "event.h"
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
	Square * square = get_near_square(entity->square, direction);
	return (square != NULL) && (square->type != WALL) && (square->entity == NULL);
}

void entity_move(Entity * entity, Direction direction) {
	Square * square = get_near_square(entity->square, direction);
	EntityMoveEventData * event_data = malloc(sizeof(EntityMoveEventData));
	event_data->new = square;
	event_data->old = entity->square;
	square->entity = entity;
	entity->square->entity = NULL;
	entity->square = square;
	dispatch_new_event(ENTITY_MOVE, event_data);
}

void entity_heal(Entity * entity, short amount) {
	entity->life = mins(entity->life + amount, entity->max_life);
}

void entity_hurt(Entity * entity, short amount) {
	entity->life = maxs(entity->life - amount, 0);
}

void entity_attack(Entity * entity) {
	Entity * weapon;
	Square * square;
	switch (entity->weapon) {
		case NONE:
			break;
		case MELEE:
			break;
		case RANGED:
			square = get_near_square(entity->square, entity->direction);
			if (square != NULL && entity_can_spawn(square)) {
				weapon = new_entity(ARROW);
				entity_spawn(weapon, square, entity->direction);
				while (entity_can_move(weapon, entity->direction)) {
					usleep(100000);
					entity_move(weapon, entity->direction);
				}
				usleep(100000);
				entity_remove(weapon);
			}
			break;
		case MAGIC:
			square = get_near_square(entity->square, entity->direction);
			if (square != NULL && entity_can_spawn(square)) {
				weapon = new_entity(BALL);
				entity_spawn(weapon, square, entity->direction);
				while (entity_can_move(weapon, entity->direction)) {
					usleep(100000);
					entity_move(weapon, entity->direction);
				}
				usleep(100000);
				entity_remove(weapon);
			}
			break;
	}
}

void entity_set_direction(Entity * entity, Direction direction) {
	EntityDirectionChangeEventData * event_data = malloc(sizeof(EntityDirectionChangeEventData));
	event_data->entity = entity;
	event_data->old = entity->direction;
	entity->direction = direction;
	dispatch_new_event(ENTITY_DIRECTION_CHANGE, event_data);
}

boolean entity_can_spawn(Square * square) {
	return (square->type == AIR) && (square->entity == NULL);
}

void entity_spawn(Entity * entity, Square * square, Direction direction) {
	EntitySpawnEventData * event_data = malloc(sizeof(EntitySpawnEventData));
	event_data->entity = entity;
	entity->square = square;
	square->entity = entity;
	entity->direction = direction;
	dispatch_new_event(ENTITY_SPAWN, event_data);
}

void entity_despawn(Entity * entity) {
	EntityDespawnEventData * event_data = malloc(sizeof(EntityDespawnEventData));
	event_data->square = entity->square;
	entity->square->entity = NULL;
	entity->square = NULL;
	dispatch_new_event(ENTITY_DESPAWN, event_data);
}

void entity_remove(Entity * entity) {
	if (entity->square != NULL) {
		entity_despawn(entity);
	}
	free(entity);
}
