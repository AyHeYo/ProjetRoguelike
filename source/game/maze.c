/**
 * @file model/maze.c
 * Fichier implémentant les fonctions permettant la création, la supression et la gestion du labyrinthe et de ses cases.
 * @author Hector Basset
 * @date 16 décembre 2014
 */

//librairies du système
#include <stdlib.h>

//librairies du modèle
#include "events.h"
#include "maze.h"

//librairies utilitaires
#include "../utility/direction.h"
#include "../utility/geo.h"
#include "../utility/math.h"

/**
 * La taille minimum (taille du niveau 1).
 */
#define MIN_SIZE 30

/**
 * La vitesse d'accroissement de la taille du labyrinthe.
 */
#define GROWING_SPEED 1.1

/**
 * Fonction libérant l'espace mémoire occupé par les cases du labyrinthe.
 * Cette fonction détruit aussi les entités se trouvant sur ces cases.
 */
static void free_squares() {
	short row, column;
	for (row = 0 ; row < g_maze->size ; row++) {
		for (column = 0 ; column < g_maze->size ; column++) {
			free(g_maze->squares[row * g_maze->size + column].entity);
		}
	}
	free(g_maze->squares);
}

void generate_maze() {
	short row, column, nb_piece, i;
	Rectangle salle;
	if (g_maze == NULL) {
		g_maze = malloc(sizeof(Maze));
		g_maze->size = MIN_SIZE;
	} else {
		free_squares();
		g_maze->size *= GROWING_SPEED;
	}
	g_maze->squares = malloc(g_maze->size * g_maze->size * sizeof(Square));
	//génération
	for (row = 0 ; row < g_maze->size ; row++) {
		for (column = 0 ; column < g_maze->size ; column++) {
			g_maze->squares[row * g_maze->size + column].type = WALL;
			g_maze->squares[row * g_maze->size + column].entity = NULL;
		}
	}
/*	for (row = 1 ; row < (g_maze->size - 1) ; row++) {
		for (column = 1 ; column < (g_maze->size - 1) ; column++) {
			g_maze->squares[row * g_maze->size + column].type = AIR;
		}
	}*/
	
	//choix du nombre de pièces...
	//nb_piece = rand() %5;
	nb_piece = 1;
	for(i =0; i< nb_piece; i++) {
		salle.a.row = rand_between(0,5);
		salle.a.column = rand_between(0,5);
		salle.c.row = rand_between(6,10);
		salle.c.column = rand_between(6,10);
		for (row = salle.a.row ; row < salle.c.row ; row++) {
			for (column = salle.a.column ; column < salle.c.column ; column++) {
				g_maze->squares[row * g_maze->size + column].type = AIR;
			}
		}
	}
	//choix de leur taille et de leur placement...
	
	//génération des couloirs
	add_new_event(MAZE_GENERATE, NULL);
}

void free_maze() {
	free_squares();
	free(g_maze);
	g_maze = NULL;
	add_new_event(MAZE_GENERATE, NULL);
}

Square * get_near_square(Square * square, Direction direction) {
	switch (direction) {
		case NORTH:
			if ((square - g_maze->squares) < g_maze->size) {
				return NULL;
			} else {
				 return square - g_maze->size;
			}
		case SOUTH:
			if ((square + g_maze->size) >= (g_maze->squares + g_maze->size * g_maze->size)) {
				return NULL;
			} else {
				return square + g_maze->size;
			}
		case EAST:
			if (((square - g_maze->squares) % g_maze->size) == (g_maze->size - 1)) {
				return NULL;
			} else {
				return square + 1;
			}
		case WEST:
			if (((square - g_maze->squares) % g_maze->size) == 0) {
				return NULL;
			} else {
				return square - 1;
			}
	}
}

Location get_square_location(Square * square) {
	Location location;
	location.row = (square - g_maze->squares) / g_maze->size;
	location.column = (square - g_maze->squares) % g_maze->size;
	return location;
}
