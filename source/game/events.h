
#ifndef GAME_GAME_EVENTS_H

#define GAME_GAME_EVENTS_H

#include "entity.h"
#include "maze.h"

#include "../utility/boolean.h"

typedef enum {
	CONFIRM,
	ENTITY_ATTACK,
	ENTITY_DIRECTION_CHANGE,
	ENTITY_MOVE,
	MAIN_MENU,
	MAZE_GENERATE,
	STOP_GAME
} GameEventType;

typedef struct {
	GameEventType type;
	void * data;
} GameEvent;

typedef struct {
	Entity * entity;
} EntityAttackGameEventData;

typedef struct {
	Entity * entity;
	Direction old;
} EntityDirectionChangeGameEventData;

typedef struct {
	Entity * entity;
	Square * old;
} EntityMoveGameEventData;

void events_init();

void event_final();

boolean has_event();

void get_event(GameEvent * event);

void remove_event();

void clear_events();

void add_event(GameEvent * event);

void add_new_event(GameEventType type, void * data);

#endif
