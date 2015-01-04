
#ifndef GAME_GAME_EVENTS_H

#define GAME_GAME_EVENTS_H

#include "entity.h"
#include "maze.h"

#include "../utility/boolean.h"

typedef enum {
	CONFIRM,
	ENTITY_ATTACK,
	ENTITY_DESPAWN,
	ENTITY_DIRECTION_CHANGE,
	ENTITY_MOVE,
	ENTITY_SPAWN,
	MAIN_MENU,
	MAZE_GENERATE,
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

void dispatch_event(Event * event);

void dispatch_new_event(EventType type, void * data);

#endif
