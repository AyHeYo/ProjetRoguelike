
#include <stdio.h>

#include "ansi.h"
#include "terminal.h"
#include "window.h"

#include "../model/roguelike.h"

/**
 * Hauteur actuelle du labyrinthe.
 */
int maze_height = 0;

/**
 * Fonction interne permettant d'afficher une case en fonction de son type.
 * @param square Le type de case à afficher.
 */
void print_square(Square square) {
	switch (square) {
		case AIR:
			ansi_set_bg_color(ANSI_BLACK);
			putchar(' ');
			break;
		case WALL:
			ansi_set_bg_color(ANSI_LIGHT_GREY);
			putchar(' ');
			break;
		case PLAYER:
			ansi_set_color(ANSI_GREEN);
			ansi_set_bg_color(ANSI_BLACK);
			fputs("☻", stdout);
			break;
	}
}

void display_maze(Square * maze, Dimension * dimension) {
	const int width = get_terminal_width();
	int i, j;
	ansi_clear_screen_after();
	for (i = 0 ; i < dimension->vertical ; i++) {
		ansi_set_column((width - dimension->horizontal) / 2);
		for (j = 0 ; j < dimension->horizontal ; j++) {
			print_square(maze[i * dimension->vertical + j]);
		}
		ansi_set_bg_color(ANSI_BLACK);
		putchar('\n');
	}
	maze_height = dimension->vertical;
	ansi_previous_line(maze_height);
	clear_message();//on affiche un message vide
}

int get_maze_height() {
	return maze_height;
}
