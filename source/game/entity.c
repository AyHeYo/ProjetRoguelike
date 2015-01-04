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
#include "events.h"
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
	EntityMoveGameEventData * event_data = malloc(sizeof(EntityMoveGameEventData));
	event_data->entity = entity;
	event_data->old = entity->square;
	Square * square = get_near_square(entity->square, direction);
	square->entity = entity;
	entity->square->entity = NULL;
	entity->square = square;
	add_new_event(ENTITY_MOVE, event_data);
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
			weapon = new_entity(ARROW);
			weapon->direction = entity->direction;
			
			for (weapon->square = square = get_near_square(entity->square, entity->direction) ; square != NULL ; square = get_near_square(square, weapon->direction)) {
				weapon->square->entity = NULL;
				weapon->square = square;
				square->entity = weapon;
				usleep(75000);
			}
			break;
		case MAGIC:
			break;
	}
}

void entity_set_direction(Entity * entity, Direction direction) {
	EntityDirectionChangeGameEventData * event_data = malloc(sizeof(EntityDirectionChangeGameEventData));
	event_data->entity = entity;
	event_data->old = entity->direction;
	entity->direction = direction;
	add_new_event(ENTITY_DIRECTION_CHANGE, event_data);
}
