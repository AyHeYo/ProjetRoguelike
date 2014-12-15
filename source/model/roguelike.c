/**
 * @file model/roguelike.c
 * Fichier implémentant les types et les fonctions du Roguelike.
 * @author Hector Basset
 * @author Youssef Lamniy
 * @author Ayas Oukache
 * @date 20 novembre 2014
 */

//librairies du système
#include <math.h>
#include <stdlib.h>
#include <time.h>

//librairies du modèle
#include "maze.h"
#include "roguelike.h"

//librairies utilitaires
#include "../utility/geo.h"
#include "../utility/math.h"

unsigned short level;

/**
 * Le pointeur vers la matrice de case contenant le labyrinthe.
 */
Maze * maze;

void init_roguelike() {
	srand(time(NULL));
	maze = NULL;
	level = 0;
}

void final_roguelike() {
	free_maze(maze);//libération de l'espace mémoire alloué au labyrinthe, inutile de vérifier si NULL car free(NULL) n'a tout simplement aucun effet
}

Square * get_maze() {
	return maze;
}

void generate() {//fonction de génération via un fichier pour continuer le développement des autres fonctionnalité en attendant la vraie fonction de génération aléatoire
	short row, column;
	level++;
	maze = generate_maze(maze);
	do {
		row = random_between(0, maze->size - 1);
		column = random_between(0, maze->size - 1);
	} while (maze->squares[row * maze->size + column].type != AIR);
	maze->squares[row * maze->size + column]
}

/*void generate_maze() {//vraie fonction de génération à finir d'implémenter
	int i;
	free(maze);//libération de l'espace mémoire alloué au labyrinthe, inutile de vérifier si NULL car free(NULL) n'a tout simplement aucun effet
	maze = (Square *) malloc(20 * 20 * sizeof(Square));//allocation de la mémoire nécessaire pour stocker le labyrinthe
	maze_dimension.horizontal = maze_dimension.vertical = 20;//sélection des dimensions du labyrinthe, pour l'instant constante à 20
	for (i = 0 ; i < maze_dimension.horizontal * maze_dimension.vertical ; i++) {//remplissage du labyrinthe par des murs
		maze[i] = WALL;
	}
	//choix du nombre de pièces...
	//choix de leur taille et de leur placement...
	//génération des couloirs
	player_location.line = player_location.row = 2;//placement du joueur, pour l'instant arbitrairement à 2:2
	maze[player_location.line * maze_dimension.horizontal + player_location.row] = PLAYER;
}*/

void move_player(Direction direction) {
	maze[player_location.line * maze_dimension.horizontal + player_location.row] = AIR;
	switch (direction) {
		case NORTH:
			player_location.line--;
			break;
		case EAST:
			player_location.row++;
			break;
		case SOUTH:
			player_location.line++;
			break;
		case WEST:
			player_location.row--;
			break;
	}
	maze[player_location.line * maze_dimension.horizontal + player_location.row] = PLAYER;
}

boolean player_can_move(Direction direction) {
	switch (direction) {
		case NORTH:
			return maze[maze_dimension.horizontal * (player_location.line - 1) + player_location.row] == AIR;
		case SOUTH:
			return maze[maze_dimension.horizontal * (player_location.line + 1) + player_location.row] == AIR;
		case EAST:
			return maze[maze_dimension.horizontal * player_location.line + player_location.row + 1] == AIR;
		case WEST:
			return maze[maze_dimension.horizontal * player_location.line + player_location.row - 1] == AIR;
		default:
			return false;
	}
}
