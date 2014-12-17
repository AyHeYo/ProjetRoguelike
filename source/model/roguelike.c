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

//librairies du modèle
#include "maze.h"
#include "player.h"
#include "roguelike.h"

//librairies utilitaires
#include "../utility/direction.h"
#include "../utility/geo.h"
#include "../utility/math.h"
#include "../utility/time.h"

unsigned short level;

void init_roguelike() {
	srand(utime(NULL));
	g_maze = NULL;
	g_player = new_entity(PLAYER);
	level = 0;
}

void final_roguelike() {
	free_maze();//libération de l'espace mémoire alloué au labyrinthe, inutile de vérifier si NULL car free(NULL) n'a tout simplement aucun effet
}

void new_level() {//fonction de génération via un fichier pour continuer le développement des autres fonctionnalité en attendant la vraie fonction de génération aléatoire
	short row, column;
	level++;
	generate_maze();
	do {
		row = rand_between(0, g_maze->size - 1);
		column = rand_between(0, g_maze->size - 1);
	} while (g_maze->squares[row * g_maze->size + column].type != AIR);
	g_maze->squares[row * g_maze->size + column].entity = g_player;
	g_player->square = &(g_maze->squares[row * g_maze->size + column]);
	g_player->direction = NORTH;
}
