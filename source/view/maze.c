/**
 * @file view/maze.h
 * Fichier implémentant les fonctions permettant de contrôler l'affichage du labyrinthe.
 * @author Hector Basset
 * @date 12 décembre 2014
 */

//librairies du système
#include <stdio.h>

//librairies de la vue
#include "ansi.h"
#include "terminal.h"
#include "window.h"

//librairies du modèle
#include "../model/maze.h"

/**
 * Hauteur actuelle du labyrinthe.
 */
int maze_height = 0;

/**
 * Fonction interne permettant d'afficher une case en fonction de son type.
 * @param square Le type de case à afficher.
 */
static void print_square(Square * square) {
	switch (square->type) {
		case AIR:
			ansi_set_bg_color(ANSI_BLACK);
			break;
		case WALL:
			ansi_set_bg_color(ANSI_LIGHT_GREY);
			break;
		case WATER:
			ansi_set_bg_color(ANSI_LIGHT_BLUE);
			break;
		case FIRE:
			ansi_set_bg_color(ANSI_LIGHT_RED);
			break;
	}
	if (square->entity == NULL) {
		putchar(' ');
	} else {
		switch (square->entity->type) {
			case PLAYER:
				ansi_set_color(ANSI_GREEN);
				fputs("☻", stdout);
				break;
			case GOBLIN:
				ansi_set_color(ANSI_RED);
				fputs("⚉", stdout);
				break;
			case GHOST:
				ansi_set_color(ANSI_WHITE);
				fputs("⚇", stdout);
				break;
		}
	}
}

void display_maze() {
	const int width = get_terminal_width();
	int i, j;
	ansi_clear_screen_after();
	for (i = 0 ; i < g_maze->size ; i++) {
		ansi_set_column((width - g_maze->size) / 2);
		for (j = 0 ; j < g_maze->size ; j++) {
			print_square(&(g_maze->squares[i * g_maze->size + j]));
		}
		ansi_set_bg_color(ANSI_BLACK);
		putchar('\n');
	}
	maze_height = g_maze->size;
	ansi_previous_line(maze_height);
	clear_message();//on affiche un message vide
}

int get_maze_height() {
	return maze_height;
}
