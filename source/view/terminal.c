/**
 * @file view/terminal.c
 * Fichier implémentant les fonctions permettant de contrôler le terminal.
 * @author Hector Basset
 * @date 10 décembre 2014
 */

//librairies du système
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

//librairies de la vue
#include "terminal.h"

//librairies utilitaires
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

void get_terminal_attributs(TerminalAttributs * attributs) {
	tcgetattr(STDIN_FILENO, attributs);
}

void set_terminal_attributs(TerminalAttributs * attributs) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, attributs);
}

void set_terminal_mode(TerminalAttributs * attributs, boolean canonical) {
	if (canonical) {
		attributs->c_lflag |= ICANON;
	} else {
		attributs->c_lflag &= ~ICANON;
	}
}

void set_terminal_echo_input(TerminalAttributs * attributs, boolean echo) {
	if (echo) {
		attributs->c_lflag |= ECHO;
	} else {
		attributs->c_lflag &= ~ECHO;
	}
}

void set_terminal_min_char(TerminalAttributs * attributs, int min_char) {
	attributs->c_cc[VMIN] = min_char;
}

void set_terminal_max_time(TerminalAttributs * attributs, int max_time) {
	attributs->c_cc[VTIME] = max_time;
}
