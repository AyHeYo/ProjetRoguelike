/**
 * @file interface.c
 * Fichier implémentant l'interface avec l'utilisateur.
 * Cette implémentation utilise le terminal.
 * Elle le met en mode non canonique et désactive l'affichage de la saisie afin d'une meilleure interaction avec l'utilisateur.
 * Elle utilise les séquences ANSI pour les couleurs, la mise en forme tu texte et le déplacement du curseur.
 * @author Hector Basset
 * @date 1 décembre 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "ansi.h"
#include "boolean.h"
#include "geo.h"
#include "interface.h"
#include "roguelike.h"

/**
 * Type renommant termios pour plus de clarté
 */
typedef struct termios TerminalAttribut;

/**
 * Variable servant à stocker les attributs du terminal avant le jeu.
 */
TerminalAttribut before;

/**
 * Variable servant à stocker les attributs du terminal pendant le jeu.
 */
TerminalAttribut actual;

/**
 * La dimension actuelle du labyrinthe.
 */
Dimension current_dimension = {-1, -1};

/**
 * Fonction interne permettant d'afficher une case en fonction de son type.
 * @param square Le type de case à afficher.
 */
void print_square(Square square) {
	switch (square) {
		case AIR:
			ansi_set_bg_color(ANSI_BLACK);
			putchar(' ');
			ansi_set_bg_color(ANSI_DEFAULT_COLOR);
			break;
		case WALL:
			ansi_set_bg_color(ANSI_LIGHT_GREY);
			putchar(' ');
			ansi_set_bg_color(ANSI_DEFAULT_COLOR);
			break;
		case PLAYER:
			ansi_set_bg_color(ANSI_BLACK);
			ansi_set_color(ANSI_GREEN);
			ansi_bold(true);
			fputs("☻", stdout);
			ansi_bold(false);
			ansi_set_color(ANSI_DEFAULT_COLOR);
			ansi_set_bg_color(ANSI_DEFAULT_COLOR);
			break;
	}
}

short get_terminal_width() {
	struct winsize size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	return size.ws_col;
}

void init_interface() {
	tcgetattr(STDIN_FILENO, &before);//sauvegarde des attributs du terminal avant le jeu
	actual = before;//copie de ces attributs
#ifdef __APPLE__
#ifdef TARGET_OS_MAC
	actual.c_cc[VMIN] = 1;//nombre minimum de caractères pour la lecture à 1
#endif
#else
	actual.c_cc[VMIN] = 0;//nombre minimum de caractères pour la lecture à 0
#endif
	actual.c_cc[VTIME] = 0;//temps d'attente lors de la lecture à 0
	actual.c_lflag &= ~ECHO;//désactivation de l'affichage de la saisie
	actual.c_lflag &= ~ICANON;//passage en mode non canonique
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &actual);//appliquation des attributs au terminal
	ansi_set_color(ANSI_DEFAULT_COLOR);
	ansi_set_bg_color(ANSI_DEFAULT_COLOR);
	ansi_set_font(ANSI_DEFAULT_FONT);
	ansi_hide_cursor(true);
	ansi_clear_screen();
	ansi_save_position();
}

void final_interface() {
	clear_message();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &before);//réappliquation des atributs d'avant le jeu
	ansi_set_color(ANSI_DEFAULT_COLOR);
	ansi_set_bg_color(ANSI_DEFAULT_COLOR);
	putchar('\n');
	ansi_hide_cursor(false);
}

void display_message(char message[]) {
	char * temp_string;
	int length = strlen(message), width = get_terminal_width(), i = 0;
	ansi_clear_screen_after();
	if (length > width) {
		temp_string = (char *) malloc((width + 1) * sizeof(char));
		for (; length > 0 ; length -= width) {
			strncpy(temp_string, message + i * width, width);
			temp_string[length > width ? width : length] = '\0';
			fputs(temp_string, stdout);
			putchar('\n');
			ansi_set_column(1);
			i++;
		}
		free(temp_string);
		ansi_previous_line(i);
		ansi_save_position();
	} else {
		fputs(message, stdout);
		ansi_restore_position();
	}
}

void clear_message() {
	ansi_clear_screen_after();
}

void display_maze(Square * maze, Dimension * dimension) {
	int i, j;
	if (dimension->horizontal != current_dimension.horizontal || dimension->vertical != current_dimension.vertical) {
		current_dimension = *dimension;
		ansi_clear_screen();
		ansi_down(current_dimension.vertical);
		ansi_save_position();
	}
	ansi_up(current_dimension.vertical);
	for (i = 0 ; i < current_dimension.vertical ; i++) {
		for (j = 0 ; j < current_dimension.horizontal ; j++) {
			print_square(maze[i * current_dimension.vertical + j]);
		}
		putchar('\n');
		ansi_set_column(1);
	}
	ansi_restore_position();
}

void update_square(Square square, Location * location) {
	ansi_up(current_dimension.vertical);
	ansi_right(location->row);
	ansi_down(location->line);
	print_square(square);
	ansi_restore_position();
}

Action wait_action() {
	while (1) {
		switch (getchar()) {
			case 27://code retourné par cetraines touche comme ECHAP ou les touches flêchées
				usleep(1);
				if (getchar() == 91) {//la pression d'une touche flêche provoque la saisie de trois caractères (27 91 6x), les instructions suivantes permettent de voir si il s'agit donc d'une touche flêchée ou d'une autre touche spéciale 
					switch (getchar()) {
						case 65:
							return TOP;
						case 66:
							return BOTTOM;
						case 67:
							return RIGHT;
						case 68:
							return LEFT;
					}
				} else {
					return EXIT;
				}
			case ' ':
				return HIT;
			case 'o':
			case 'O':
				return ACCEPT;
			case 'n':
			case 'N':
				return DENY;
		}
	}
}

void wait_ready() {
	fflush(stdout);
}
