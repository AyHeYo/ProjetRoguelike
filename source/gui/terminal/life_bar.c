
#include <stdio.h>

#include "ansi.h"
#include "maze.h"
#include "terminal.h"

#include "../../game/game.h"
#include "../../game/player.h"

#define LIFE_BAR_MARGIN 18

void display_life_bar() {
	short width, i;
	float bar;
	if (g_player != NULL) {
		width = get_terminal_width() - 2 * LIFE_BAR_MARGIN;
		ansi_set_position(1 + 2 + g_maze_height, 1 + LIFE_BAR_MARGIN);
		ansi_set_bg_color(ANSI_BLACK);
		ansi_set_color(ANSI_LIGHT_GREY);
		fputs("┌", stdout);
		for (i = 0 ; i < width - 2 ; i++) {
			fputs("─", stdout);
		}
		fputs("┐", stdout);
		putchar('\n');
		ansi_set_column(1 + LIFE_BAR_MARGIN);
		fputs("│", stdout);
		ansi_right(width - 2);
		fputs("│", stdout);
		ansi_left(width - 1);
		bar = g_player->life * ( (width - 2) / ((float) g_player->max_life));
		ansi_set_bg_color(ANSI_GREEN);
		for (i = 0 ; i < bar ; i++) {
			putchar(' ');
		}
		ansi_set_bg_color(ANSI_BLACK);
		putchar('\n');
		ansi_set_column(1 + LIFE_BAR_MARGIN);
		fputs("└", stdout);
		for (i = 0 ; i < width - 2 ; i++) {
			fputs("─", stdout);
		}
		fputs("┘", stdout);
	}
	fflush(stdout);
}
