/**
 * @file model/maze.c
 * Fichier implémentant les fonctions permettant la création, la supression et la gestion du labyrinthe et de ses cases.
 * @author Hector Basset
 * @date 16 décembre 2014
 */

//librairies du système
#include <stdlib.h>

//librairies du modèle
#include "direction.h"
#include "entity.h"
#include "event.h"
#include "maze.h"

//librairies utilitaires
#include "../utility/geo.h"
#include "../utility/math.h"

/**
 * La taille minimum (taille du niveau 1).
 */
#define MIN_SIZE 20

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
#include <stdio.h>
void generate_maze() {
	short row, column, nb_room, i;
	Rectangle * rooms;
	Direction direction;
	if (g_maze == NULL) {
		g_maze = malloc(sizeof(Maze));
		g_maze->size = MIN_SIZE;
	} else {
		free_squares();
		g_maze->size *= GROWING_SPEED;
	}
	g_maze->squares = malloc(g_maze->size * g_maze->size * sizeof(Square));
	//génération
	//remplissage par des murs
	for (row = 0 ; row < g_maze->size ; row++) {
		for (column = 0 ; column < g_maze->size ; column++) {
			g_maze->squares[row * g_maze->size + column].type = WALL;
			g_maze->squares[row * g_maze->size + column].entity = NULL;
		}
	}
	//choix du nombre de pièces...
	//nb_room = rand_between(1 + g_maze->size / 15, (1 + g_maze->size / 15) + (((g_maze->size % 15) > 7) ? rand_between(0, 1) : 0));
	nb_room = 2;
	rooms = malloc(sizeof(Rectangle) * nb_room);
	//première pièce
	i = 0;
	if (rand_boolean()) {
		rooms[i].a.row = 1;
		rooms[i].a.column = rand_between(1, g_maze->size / 7);
		rooms[i].c.row = rand_between(3, g_maze->size / nb_room - 2);
		rooms[i].c.column = rand_between(rooms[i].a.column + 1, g_maze->size / nb_room - 2);
		g_maze->door = g_maze->squares + rand_between(rooms[i].a.column, rooms[i].c.column);
	} else {
		rooms[i].a.row = rand_between(1, g_maze->size / 7);
		rooms[i].a.column = 1;
		rooms[i].c.row = rand_between(rooms[i].a.row + 1, g_maze->size / nb_room - 2);
		rooms[i].c.column = rand_between(3, g_maze->size / nb_room - 2);
		g_maze->door = g_maze->squares + g_maze->size * rand_between(rooms[i].a.column, rooms[i].c.column);
	}
	g_maze->door->type = AIR;
	if (((rooms[i].c.row - rooms[i].a.row) == 2) && (rand_boolean() || rand_boolean())) {
		rooms[i].c.row++;
	}
	if (((rooms[i].c.column - rooms[i].a.column) == 2) && (rand_boolean() || rand_boolean())) {
		rooms[i].c.column++;
	}
	if (((rooms[i].c.row - rooms[i].a.row) <= 3) && (rand_boolean())) {
		rooms[i].c.row++;
	}
	if (((rooms[i].c.column - rooms[i].a.column) <= 3) && (rand_boolean())) {
		rooms[i].c.column++;
	}
	/*//dernière pièce
	i = nb_room - 1;
	if (rand_boolean()) {
		rooms[i].c.row = g_maze->size - 2;
		rooms[i].c.column = rand_between(g_maze->size - 1 - g_maze->size / 7, g_maze->size - 2);
		rooms[i].a.row = rand_between(g_maze->size - 1 - g_maze->size / nb_room + 2, g_maze->size - 4);
		rooms[i].a.column = rand_between(g_maze->size - 1 - g_maze->size / nb_room + 2, rooms[i].c.column - 1);
	} else {
		rooms[i].c.row = rand_between(g_maze->size - 1 - g_maze->size / 7, g_maze->size - 2);
		rooms[i].c.column = g_maze->size - 2;
		rooms[i].a.row = rand_between(g_maze->size - 1 - g_maze->size / nb_room + 2, rooms[i].c.row - 1);
		rooms[i].a.column = rand_between(g_maze->size - 1 - g_maze->size / nb_room + 2, g_maze->size - 4);
	}
	if (((rooms[i].c.row - rooms[i].a.row) == 2) && (rand_boolean() || rand_boolean())) {
		rooms[i].a.row--;
	}
	if (((rooms[i].c.column - rooms[i].a.column) == 2) && (rand_boolean() || rand_boolean())) {
		rooms[i].a.column--;
	}
	if (((rooms[i].c.row - rooms[i].a.row) <= 3) && (rand_boolean())) {
		rooms[i].a.row--;
	}
	if (((rooms[i].c.column - rooms[i].a.column) <= 3) && (rand_boolean())) {
		rooms[i].a.column--;
	}*/
	//
	for (; i < nb_room ; i++) {
		
	}
	//
	for(i = 0; i < nb_room; i++) {
		for (row = rooms[i].a.row ; row <= rooms[i].c.row ; row++) {
			for (column = rooms[i].a.column ; column <= rooms[i].c.column ; column++) {
				g_maze->squares[row * g_maze->size + column].type = AIR;
			}
		}
	}
	//choix de leur taille et de leur placement...
	
	//génération des couloirs
	dispatch_new_event(MAZE_GENERATE, NULL);
}

void free_maze() {
	free_squares();
	free(g_maze);
	g_maze = NULL;
	dispatch_new_event(MAZE_GENERATE, NULL);
}

Square * get_near_square(Square * square, Direction direction) {
	Square * near;
	switch (direction) {
		case NORTH:
			if ((square - g_maze->squares) < g_maze->size) {
				near = NULL;
			} else {
				near = square - g_maze->size;
			}
			break;
		case SOUTH:
			if ((square + g_maze->size) >= (g_maze->squares + g_maze->size * g_maze->size)) {
				near = NULL;
			} else {
				near = square + g_maze->size;
			}
			break;
		case EAST:
			if (((square - g_maze->squares) % g_maze->size) == (g_maze->size - 1)) {
				near = NULL;
			} else {
				near = square + 1;
			}
			break;
		case WEST:
			if (((square - g_maze->squares) % g_maze->size) == 0) {
				near = NULL;
			} else {
				near = square - 1;
			}
			break;
	}
	return near;
}

Location get_square_location(Square * square) {
	Location location;
	location.row = (square - g_maze->squares) / g_maze->size;
	location.column = (square - g_maze->squares) % g_maze->size;
	return location;
}
