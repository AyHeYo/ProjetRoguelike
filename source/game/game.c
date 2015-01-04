/**
 * @file model/roguelike.c
 * Fichier implémentant les types et les fonctions du Roguelike.
 * @author Hector Basset
 * @author Youssef Lamniy
 * @author Ayas Oukache
 * @date 20 novembre 2014
 */

//librairies du système
#include <stdlib.h>

//librairies du modèle
#include "entity.h"
#include "game.h"
#include "maze.h"
#include "player.h"

//librairies utilitaires
#include "../utility/direction.h"
#include "../utility/geo.h"
#include "../utility/math.h"
#include "../utility/time.h"

void game_init() {
	srand(utime(NULL));
	g_game_running = false;
	g_maze = NULL;
	g_player = NULL;
}

void game_end() {
	g_game_running = false;
	g_player = NULL;
	free_maze();//libération de l'espace mémoire alloué au labyrinthe
}

void new_game() {
	g_game_running = true;
	g_level = 0;
	g_player = new_entity(PLAYER);//céation du joueur
	new_level();
}

void new_level() {
	short row, column;
	Entity * entity;
	//niveau supérieur
	g_level++;
	//génération du labyrinthe
	generate_maze();
	//placement du joueur
	do {
		row = rand_between(0, g_maze->size - 1);
		column = rand_between(0, g_maze->size - 1);
	} while (!entity_can_spawn(g_maze->squares + (row * g_maze->size + column)));
	entity_spawn(g_player, g_maze->squares + (row * g_maze->size + column), NORTH);
	//placement des monstres
	do {
		row = rand_between(0, g_maze->size - 1);
		column = rand_between(0, g_maze->size - 1);
	} while (!entity_can_spawn(g_maze->squares + (row * g_maze->size + column)));
	entity = new_entity(GOBLIN);
	entity_spawn(entity, g_maze->squares + (row * g_maze->size + column), NORTH);
}

void turn() {
}
