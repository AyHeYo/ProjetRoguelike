
#ifndef GAME_EVENT_H

#define GAME_EVENT_H

#include "entity.h"
#include "maze.h"

#include "../utility/boolean.h"

typedef enum {
	CONFIRM,
	ENTITY_ATTACK,
	ENTITY_DESPAWN,
	ENTITY_DIE,
	ENTITY_DIRECTION_CHANGE,
	ENTITY_HEAL,
	ENTITY_HURT,
	ENTITY_MOVE,
	ENTITY_SPAWN,
	MAIN_MENU,
	MAZE_GENERATE,
	PLAYER_VIEW,
	STOP_GAME
} EventType;

typedef struct {
	EventType type;
	void * data;
} Event;

typedef struct {
	Entity * entity;
} EntityAttackEventData;

typedef struct {
	Entity * entity;
	Direction old;
} EntityDirectionChangeEventData;

typedef struct {
	struct Square * new;
	struct Square * old;
} EntityMoveEventData;

typedef struct {
	struct Square * square;
} EntityDespawnEventData;

typedef struct {
	Entity * entity;
} EntitySpawnEventData;

typedef struct {
	Entity * entity;
} EntityDieEventData;

typedef struct {
	Entity * entity;
	short amount;
} EntityHurtEventData;

typedef struct {
	Entity * entity;
	short amount;
} EntityHealEventData;

void dispatch_event(Event * event);

void dispatch_new_event(EventType type, void * data);

#endif
