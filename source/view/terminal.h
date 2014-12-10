
#ifndef TERMINAL_H

#define TERMINAL_H

#include <termios.h>

#include "../utility/boolean.h"

typedef struct {
	int rows;
	int columns;
} TerminalSize;

TerminalSize get_terminal_size();

int get_terminal_height();

int get_terminal_width();

typedef struct termios TerminalAttributs;

void get_terminal_attributs(TerminalAttributs * attributs);

void set_terminal_attributs(TerminalAttributs * attributs);

boolean get_terminal_mode(TerminalAttributs * attributs);

void set_terminal_mode(TerminalAttributs * attributs, boolean canonical);

boolean get_terminal_echo_input(TerminalAttributs * attributs);

void set_terminal_echo_input(TerminalAttributs * attributs, boolean echo);

int get_terminal_min_char(TerminalAttributs * attributs);

void set_terminal_min_char(TerminalAttributs * attributs, int min_char);

int get_terminal_min_time(TerminalAttributs * attributs);

void set_terminal_min_time(TerminalAttributs * attributs, int min_time);

#endif
