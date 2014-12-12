
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "terminal.h"

#include "../utility/boolean.h"

TerminalSize get_terminal_size() {
	struct winsize wsize;
	TerminalSize tsize;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
	tsize.rows = wsize.ws_row;
	tsize.columns = wsize.ws_col;
	return tsize;
}

int get_terminal_height() {
	struct winsize wsize;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
	return wsize.ws_row;
}

int get_terminal_width() {
	struct winsize wsize;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
	return wsize.ws_col;
}

typedef struct termios TerminalAttributs;

void get_terminal_attributs(TerminalAttributs * attributs) {
	tcgetattr(STDIN_FILENO, attributs);
}

void set_terminal_attributs(TerminalAttributs * attributs) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, attributs);
}

boolean get_terminal_mode(TerminalAttributs * attributs) {
	return (attributs->c_lflag & ICANON) != 0;
}

void set_terminal_mode(TerminalAttributs * attributs, boolean canonical) {
	if (canonical) {
		attributs->c_lflag |= ICANON;
	} else {
		attributs->c_lflag &= ~ICANON;
	}
}

boolean get_terminal_echo_input(TerminalAttributs * attributs) {
	return (attributs->c_lflag & ECHO) != 0;
}

void set_terminal_echo_input(TerminalAttributs * attributs, boolean echo) {
	if (echo) {
		attributs->c_lflag |= ECHO;
	} else {
		attributs->c_lflag &= ~ECHO;
	}
}

int get_terminal_min_char(TerminalAttributs * attributs) {
	return attributs->c_cc[VMIN];
}

void set_terminal_min_char(TerminalAttributs * attributs, int min_char) {
	attributs->c_cc[VMIN] = min_char;
}

int get_terminal_min_time(TerminalAttributs * attributs) {
	return attributs->c_cc[VTIME];
}

void set_terminal_min_time(TerminalAttributs * attributs, int min_time) {
	attributs->c_cc[VTIME] = min_time;
}
