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

void init_roguelike() {
	srand(time(NULL));
	g_maze = NULL;
	level = 0;
}

void final_roguelike() {
	free_maze();//libération de l'espace mémoire alloué au labyrinthe, inutile de vérifier si NULL car free(NULL) n'a tout simplement aucun effet
}

void generate() {//fonction de génération via un fichier pour continuer le développement des autres fonctionnalité en attendant la vraie fonction de génération aléatoire
	short row, column;
	level++;
	generate_maze();
	do {
		row = rand_between(0, g_maze->size - 1);
		column = rand_between(0, g_maze->size - 1);
	} while (g_maze->squares[row * g_maze->size + column].type != AIR);
	//maze->squares[row * maze->size + column];
}
