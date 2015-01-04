
#ifndef GUI_GUI_H

#define GUI_GUI_H

#include "../game/event.h"

void gui_init();

void gui_final();

void gui_start();

void gui_stop();

void gui_set_message(char * message);

void gui_clear_message();

void gui_warn(Event * event);

#endif
