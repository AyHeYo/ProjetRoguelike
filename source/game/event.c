
#include "event.h"

#include "../gui/gui.h"

void dispatch_event(Event * event) {
	gui_warn(event);
}

void dispatch_new_event(EventType type, void * data) {
	Event event;
	event.type = type;
	event.data = data;
	dispatch_event(&event);
}
