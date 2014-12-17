/**
 * @file model/maze.c
 * Fichier implémentant les fonctions permettant la création, la supression et la gestion du labyrinthe et de ses cases.
 * @author Hector Basset
 * @date 16 décembre 2014
 */

//librairies du système
#include <stdlib.h>

//librairies du modèle
#include "maze.h"

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
	short row, column;
	if (g_maze == NULL) {
		g_maze = malloc(sizeof(Maze));
		g_maze->size = MIN_SIZE;
	} else {
		free_squares();
		g_maze->size *= GROWING_SPEED;
	}
	g_maze->squares = malloc(g_maze->size * g_maze->size * sizeof(Square));
	for (row = 0 ; row < g_maze->size ; row++) {
		for (column = 0 ; column < g_maze->size ; column++) {
			g_maze->squares[row * g_maze->size + column].type = WALL;
			g_maze->squares[row * g_maze->size + column].entity = NULL;
		}
	}
	for (row = 1 ; row < (g_maze->size - 1) ; row++) {
		for (column = 1 ; column < (g_maze->size - 1) ; column++) {
			g_maze->squares[row * g_maze->size + column].type = AIR;
		}
	}
	int rang, col, i, j, nb_piece = 5;
	Rectangle salle;
	free(maze);//libération de l'espace mémoire alloué au labyrinthe, inutile de vérifier si NULL car free(NULL) n'a tout simplement aucun effet
	maze = (Square *) malloc(20 * 20 * sizeof(Square));//allocation de la mémoire nécessaire pour stocker le labyrinthe
	maze_dimension.horizontal = maze_dimension.vertical = 20;//sélection des dimensions du labyrinthe, pour l'instant constante à 20
	

  //  Initialisation de toutes les positions partant du coté gauche du mur
    for (rang = 0; rang < maze_dimension.vertical ; rang++ ) {
		for (col = 0; col < maze_dimension.horizontal; col++) {
        	maze[rang * maze_dimension.horizontal + col] = WALL;
    	}
    }
	//choix du nombre de pièces...
	//nb_piece = rand() %5;
	nb_piece = 1;
	for(i =0; i< nb_piece; i++) {
		salle.a.line = rand() % 5;
		salle.a.row = rand() % 5;
		salle.c.line = rand() % 5 + 5;
		salle.c.row = rand() % 5 + 5;
		for (rang = salle.a.line ; rang < salle.b.line ; rang++) {
			for (col = salle.a.row ; col < salle.b.row ; col++) {
				maze[rang * maze_dimension.horizontal + col] = AIR;
			}
		}
	}
	//choix de leur taille et de leur placement...
	for(i=0; i<col;i++) {
		for(j=0; j<rang; j++) {
			salle.a.line = 
			salle.a.row =
			salle.c.line =
			salle.c.row =
	//génération des couloirs
	player_location.line = player_location.row = 2;//placement du joueur, pour l'instant arbitrairement à 2:2
	maze[player_location.line * maze_dimension.horizontal + player_location.row] = PLAYER;
}

void free_maze() {
	free_squares();
	free(g_maze);
}
