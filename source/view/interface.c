/**
 * @file view/interface.c
 * Fichier implémentant les actions de base de l'interface avec l'utilisateur.
 * Cette implémentation utilise le terminal.
 * Elle le met en mode non canonique et désactive l'affichage de la saisie afin d'une meilleure interaction avec l'utilisateur.
 * Elle utilise les séquences ANSI pour les couleurs, la mise en forme tu texte et le déplacement du curseur.
 * @author Hector Basset
 * @date 1 décembre 2014
 */

//librairies du système
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

//librairies de la vue
#include "ansi.h"
#include "interface.h"
#include "maze.h"
#include "terminal.h"
#include "window.h"

//librairies du modèle
#include "../model/roguelike.h"

//librairies utilitaires
#include "../utility/boolean.h"
#include "../utility/geo.h"

/**
 * Marge entre la fenêtre et le labyrinthe.
 */
#define MAZE_WINDOW_MARGIN 2

/**
 * Variable servant à stocker les attributs du terminal avant le jeu.
 */
TerminalAttributs before;

void init_interface() {
	TerminalAttributs actual;
	get_terminal_attributs(&before);//sauvegarde des attributs du terminal avant le jeu
	actual = before;//copie de ces attributs
	#ifdef __APPLE__
		#ifdef TARGET_OS_MAC
			set_terminal_min_char(&actual, 1);//nombre minimum de caractères pour la lecture à 1
		#endif
	#else
		set_terminal_min_char(&actual, 0);//nombre minimum de caractères pour la lecture à 0
	#endif
	set_terminal_max_time(&actual, 0);//temps d'attente lors de la lecture à 0
	set_terminal_echo_input(&actual, false);//désactivation de l'affichage de la saisie
	set_terminal_mode(&actual, false);//passage en mode non canonique
	set_terminal_attributs(&actual);//appliquation des attributs au terminal
	ansi_set_bg_color(ANSI_BLACK);
	ansi_set_font(ANSI_DEFAULT_FONT);
	ansi_hide_cursor(true);
	ansi_clear_screen();
}

void final_interface() {
	ansi_down(get_window_height() + MAZE_WINDOW_MARGIN + get_maze_height());
	putchar('\n');
	ansi_set_color(ANSI_DEFAULT_COLOR);
	ansi_set_bg_color(ANSI_DEFAULT_COLOR);
	ansi_hide_cursor(false);
	set_terminal_attributs(&before);//réappliquation des attributs d'avant le jeu
	putchar('\n');
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
		usleep(10000);
	}
}

void wait_ready() {
	fflush(stdout);
}

void cursor_at_top() {
	ansi_previous_line(get_window_height() + MAZE_WINDOW_MARGIN + get_maze_height());
}

int get_maze_window_margin() {
	return MAZE_WINDOW_MARGIN;
}

pthread_t interface_thread;

void * interface_routine(void * arg) {
	clock_t now = clock();
	while (((clock() - now) / CLOCKS_PER_SEC) * 1000 < 100) {
	}
	display_maze();
}

void start_interface() {
	
}
