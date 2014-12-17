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
static TerminalAttributs before;

/**
 * Thread de l'affichage.
 */
static pthread_t interface_thread;

/**
 * Si le thread de l'affichage soit s'arrêter.
 */
static boolean stop_thread;

#define DISPLAY_FREQUENCY 11

/**
 * La fonction executée par le thread de l'affchage.
 * @param arg Ne prend pas d'argument.
 * @return Ne retourne rien.
 */
static void * interface_routine(void * arg) {
	int i;
	(void) arg;//pas s'argument
	while (1) {
		ansi_clear_screen_after();
		display_maze();
		for (i = 0 ; i < MAZE_WINDOW_MARGIN ; i++) {
			putchar('\n');
		}
		display_message();
		ansi_previous_line(g_window_height + MAZE_WINDOW_MARGIN + g_maze_height);
		fflush(stdout);
		if (stop_thread) {
			pthread_exit(NULL);
		} else {
			usleep(1000000 / DISPLAY_FREQUENCY);
		}
	}
}

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
	g_maze_height = 0;
	g_window_height = 0;
	clear_message();
	stop_thread = false;
	pthread_create(&interface_thread, NULL, &interface_routine, NULL);
}

void final_interface() {
	stop_thread = true;
	pthread_join(interface_thread, NULL);
	ansi_down(g_window_height + MAZE_WINDOW_MARGIN + g_maze_height);
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
