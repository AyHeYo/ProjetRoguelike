
#include <stddef.h>

#include "events.h"

#include "../utility/boolean.h"
#include "../utility/queue.h"

static Queue * events;

void events_init() {
	events = new_queue(sizeof(GameEvent));
}

void event_final() {
	queue_free(events);
}

boolean has_event() {
	return !queue_empty(events);
}

void get_event(GameEvent * event) {
	queue_get(events, event);
}

void remove_event() {
	GameEvent event;
	queue_get(events, &event);
	free(event.data);
	queue_remove(events);
}

void clear_events() {
	queue_clear(events);
}

void add_event(GameEvent * event) {
	queue_add(events, event);
}

void add_new_event(GameEventType type, void * data) {
	GameEvent event;
	event.type = type;
	event.data = data;
	add_event(&event);
}
