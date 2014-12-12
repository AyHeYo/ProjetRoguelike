
#include <stdio.h>
#include <string.h>

#include "ansi.h"
#include "interface.h"
#include "terminal.h"

/**
 * Marge entre la fenre et le bord du terminal.
 */
#define WINDOW_MARGIN 6

/**
 * Nombre de lignes qui composent la fenêtre quand le message est vide.
 */
#define NB_LINES_ON_EMPTY_MSG 5

/**
 * Hauteur actuelle de la fenêtre.
 */
int window_height;

void print_window_top() {
	const int width = get_terminal_width() - 2 * WINDOW_MARGIN;
	int i;
	ansi_set_bg_color(ANSI_BLACK);
	ansi_set_column(WINDOW_MARGIN + 1);
	ansi_set_color(ANSI_LIGHT_BLUE);
	fputs("╔", stdout);
	for (i = 0 ; i < width - 2 ; i++) {
		fputs("═", stdout);
	}
	fputs("╗", stdout);
}

void print_window_line() {
	const int width = get_terminal_width() - 2 * WINDOW_MARGIN;
	ansi_set_bg_color(ANSI_BLACK);
	ansi_clear_line();
	ansi_set_column(WINDOW_MARGIN + 1);
	ansi_set_color(ANSI_LIGHT_BLUE);
	fputs("║", stdout);
	ansi_set_column(WINDOW_MARGIN + width);
	fputs("║", stdout);
}

void print_window_bottom() {
	const int width = get_terminal_width() - 2 * WINDOW_MARGIN;
	int i;
	ansi_set_bg_color(ANSI_BLACK);
	ansi_set_column(WINDOW_MARGIN + 1);
	ansi_set_color(ANSI_LIGHT_BLUE);
	fputs("╠", stdout);
	for (i = 0 ; i < width - 2 ; i++) {
		fputs("═", stdout);
	}
	fputs("╣", stdout);
	putchar('\n');
	print_window_line();
	ansi_set_column(WINDOW_MARGIN + 4);
	ansi_set_color(ANSI_LIGHT_GREY);
	fputs("Oui : ", stdout);
	ansi_set_color(ANSI_LIGHT_GREEN);
	putchar('O');
	ansi_set_color(ANSI_LIGHT_BLUE);
	ansi_set_column(WINDOW_MARGIN + width - 9);
	ansi_set_color(ANSI_LIGHT_GREY);
	fputs("Non : ", stdout);
	ansi_set_color(ANSI_LIGHT_RED);
	putchar('N');
	ansi_set_color(ANSI_LIGHT_BLUE);
	putchar('\n');
	print_window_line();
	ansi_set_column(WINDOW_MARGIN + 4);
	ansi_set_color(ANSI_LIGHT_GREY);
	fputs("Frapper : ", stdout);
	ansi_set_color(ANSI_GREY);
	fputs("ESPACE", stdout);
	ansi_set_color(ANSI_LIGHT_BLUE);
	ansi_set_column(WINDOW_MARGIN + width - 17);
	ansi_set_color(ANSI_LIGHT_GREY);
	fputs("Quitter : ", stdout);
	ansi_set_color(ANSI_RED);
	fputs("ECHAP", stdout);
	ansi_set_color(ANSI_LIGHT_BLUE);
	putchar('\n');
	ansi_set_column(WINDOW_MARGIN + 1);
	fputs("╚", stdout);
	for (i = 0 ; i < width - 2 ; i++) {
		fputs("═", stdout);
	}
	fputs("╝", stdout);
}

void display_message(char message[]) {
	const int width = get_terminal_width() - 2 * WINDOW_MARGIN, length = strlen(message);
	int i, lines = -1;
	ansi_down(get_maze_height());
	for (i = 0 ; i < get_maze_window_margin() ; i++) {
		putchar('\n');
	}
	print_window_top();
	for (i = 0 ; i < length ; i++) {
		if (i % (width - 4) == 0) {
			putchar('\n');
			print_window_line();
			lines++;
			ansi_set_color(ANSI_LIGHT_GREY);
			ansi_set_column(WINDOW_MARGIN + 3);
		}
		putchar(message[i]);
	}
	putchar('\n');
	print_window_bottom();
	ansi_clear_screen_after();
	window_height = NB_LINES_ON_EMPTY_MSG + lines;
	cursor_at_top();
}

void clear_message() {
	int i;
	ansi_down(get_maze_height());
	for (i = 0 ; i < get_maze_window_margin() ; i++) {
		putchar('\n');
	}
	print_window_top();
	putchar('\n');
	print_window_line();
	putchar('\n');
	print_window_bottom();
	ansi_clear_screen_after();
	window_height = NB_LINES_ON_EMPTY_MSG;
	cursor_at_top();
}

int get_window_height() {
	return window_height;
}
