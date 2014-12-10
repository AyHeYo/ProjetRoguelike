/**
 * @file roguelike.c
 * Fichier implémentant les types et les fonctions du Roguelike.
 * @author Hector Basset
 * @author Youssef Lamniy
 * @author Ayas Oukache
 * @date 20 novembre 2014
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "geo.h"
#include "roguelike.h"

/**
 * Le pointeur vers la matrice de case contenant le labyrinthe.
 */
Square * maze;

/**
 * Les dimensions du labyrinthe.
 */
Dimension maze_dimension;

/**
 * La localisation du joueur dans le labyrinthe.
 */
Location player_location;

/**
 * La vie du joueur.
 */
char player_life;

/**
 * La vie maximale du joueur.
 */
#define MAX_PLAYER_LIFE 100

void init_roguelike() {
	srand(time(NULL));
	maze = NULL;
	maze_dimension.horizontal = maze_dimension.vertical = -1;
	player_location.line = player_location.row = -1;
	player_life = MAX_PLAYER_LIFE;
}

void final_roguelike() {
	free(maze);//libération de l'espace mémoire alloué au labyrinthe, inutile de vérifier si NULL car free(NULL) n'a tout simplement aucun effet
}

Square * get_maze() {
	return maze;
}

Dimension * get_maze_dimension() {
	return &maze_dimension;
}

void generate_maze() {//fonction de génération via un fichier pour continuer le développement des autres fonctionnalité en attendant la vraie fonction de génération aléatoire
	int i;
	FILE * file = fopen("level.txt", "r");
	free(maze);//libération de l'espace mémoire alloué au labyrinthe, inutile de vérifier si NULL car free(NULL) n'a tout simplement aucun effet
	fscanf(file, "%i %i \n", &maze_dimension.horizontal, &maze_dimension.vertical);
	maze = (Square *) malloc(maze_dimension.horizontal * maze_dimension.vertical * sizeof(Square));//allocation de la mémoire nécessaire pour stocker le labyrinthe
	for (i = 0 ; i < maze_dimension.horizontal * maze_dimension.vertical ; i++) {//remplissage du labyrinthe par des mur
		maze[i] = fgetc(file);
		if (maze[i] == '\n') {
			i--;
		} else {
			maze[i] -= '0';
		}
	}
	fclose(file);
	player_location.line = player_location.row = 2;//placement du joueur, pour l'instant arbitrairement à 2:2
	maze[player_location.line * maze_dimension.horizontal + player_location.row] = PLAYER;
	player_life = min(player_life + player_life / 4, MAX_PLAYER_LIFE);
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

Location * get_player_location() {
	return &player_location;
}

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

char * get_player_life() {
	return &player_life;
}

void modify_player_life(char amount) {
	player_life += amount;
}
