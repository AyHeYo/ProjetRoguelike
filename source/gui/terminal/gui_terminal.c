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
#include <stdio.h>
#include <unistd.h>

//librairies de la vue
#include "ansi.h"
#include "maze.h"
#include "terminal.h"
#include "window.h"
#include "../gui.h"

//librairies du modèle
#include "../../game/events.h"
#include "../../game/game.h"
#include "../../game/user_request.h"

//librairies utilitaires
#include "../../utility/boolean.h"
#include "../../utility/geo.h"

/**
 * Variable servant à stocker les attributs du terminal avant le jeu.
 */
static TerminalAttributs before;

static boolean must_run;

static void refresh() {
	display_maze();
	display_message();
}

void gui_init() {
	TerminalAttributs actual;
	get_terminal_attributs(&before);//sauvegarde des attributs du terminal avant le jeu
	actual = before;//copie de ces attributs
	#ifdef TARGET_OS_MAC
		set_terminal_min_char(&actual, 1);//nombre minimum de caractères pour la lecture à 1
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
	refresh();
}

void gui_final() {
	ansi_set_position(1 + g_window_height + g_maze_height, 1);
	putchar('\n');
	ansi_set_color(ANSI_DEFAULT_COLOR);
	ansi_set_bg_color(ANSI_DEFAULT_COLOR);
	ansi_hide_cursor(false);
	set_terminal_attributs(&before);//réappliquation des attributs d'avant le jeu
	putchar('\n');
}

void gui_start() {
	boolean waiting_request = true;
	GameEvent event;
	perform_request(STARTUP);
	must_run = true;
	while (must_run) {
		while (has_event()) {
			get_event(&event);
			switch (event.type) {
				case CONFIRM:
					gui_set_message("Etes-vous sur ?");
					break;
				case ENTITY_ATTACK:
					break;
				case ENTITY_DIRECTION_CHANGE:
					update_square(((EntityDirectionChangeGameEventData *) event.data)->entity->square);
					break;
				case ENTITY_MOVE:
					update_square(((EntityMoveGameEventData *) event.data)->old);
					update_square(((EntityMoveGameEventData *) event.data)->entity->square);
					break;
				case MAIN_MENU:
					gui_set_message("Voulez-vous démarrer une nouvelle partie (d), ou en charger une existante (c) ? Vous pouvez quitter avec la touche ECHAP.");
					break;
				case MAZE_GENERATE:
					gui_clear_message();
					refresh();
					break;
				case STOP_GAME:
					gui_set_message("Au revoir !");
					return;
					break;
			}
			remove_event();
		}
		waiting_request = true;
		while (waiting_request) {
			waiting_request = false;
			switch (getchar()) {
				case 27://code retourné par cetraines touche comme ECHAP ou les touches flêchées
					usleep(1);
					if (getchar() == 91) {//la pression d'une touche flêche provoque la saisie de trois caractères (27 91 6x), les instructions suivantes permettent de voir si il s'agit donc d'une touche flêchée ou d'une autre touche spéciale 
						switch (getchar()) {
							case 65:
								perform_request(MOVE_NORTH);
								break;
							case 66:
								perform_request(MOVE_SOUTH);
								break;
							case 67:
								perform_request(MOVE_EAST);
								break;
							case 68:
								perform_request(MOVE_WEST);
								break;
						}
					} else {
						perform_request(EXIT);
						break;
					}
				case ' ':
					perform_request(ATTACK);
					break;
				case 'o':
				case 'O':
					perform_request(ACCEPT);
					break;
				case 'n':
				case 'N':
					perform_request(DENY);
					break;
				case 'd':
				case 'D':
					perform_request(NEW_GAME);
					break;
				case 'c':
				case 'C':
					perform_request(LOAD_GAME);
					break;
				case 's':
				case 'S':
					perform_request(SAVE_GAME);
					break;
				default:
					waiting_request = true;
			}
			usleep(10000);
		}
	}
}

void gui_stop() {
	must_run = false;
}

void gui_set_message(char * message) {
	set_message(message);
	display_message();
}

void gui_clear_message() {
	gui_set_message(" ");
}
