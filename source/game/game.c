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
#include "events.h"
#include "maze.h"
#include "player.h"
#include "roguelike.h"
#include "user_request.h"

//librairies utilitaires
#include "../utility/direction.h"
#include "../utility/geo.h"
#include "../utility/math.h"
#include "../utility/time.h"

void game_init() {
	g_level = 0;
	g_player = new_entity(PLAYER);//céation du joueur
	new_level();
}

void game_final() {
	free_maze();//libération de l'espace mémoire alloué au labyrinthe
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
	} while (g_maze->squares[row * g_maze->size + column].type != AIR);
	g_maze->squares[row * g_maze->size + column].entity = g_player;
	g_player->square = &(g_maze->squares[row * g_maze->size + column]);
	g_player->direction = NORTH;
	//placement des monstres
	do {
		row = rand_between(0, g_maze->size - 1);
		column = rand_between(0, g_maze->size - 1);
	} while (g_maze->squares[row * g_maze->size + column].type != AIR);
	entity = new_entity(GOBLIN);
	g_maze->squares[row * g_maze->size + column].entity = entity;
	entity->square = &(g_maze->squares[row * g_maze->size + column]);
	entity->direction = NORTH;
}

static boolean game_running = false;

void perform_request(UserRequest request) {
	GameEvent event;
	switch (request) {
		case STARTUP:
			if (!game_running) {
				srand(utime(NULL));
				events_init();
				add_new_event(MAIN_MENU, NULL);
			}
			break;
		case EXIT:
			if (game_running) {
				game_running = false;
				game_final();
				add_new_event(MAIN_MENU, NULL);
			} else {
				add_new_event(STOP_GAME, NULL);
			}
			break;
		case NEW_GAME:
			if (!game_running) {
				game_running = true;
				game_init();
			}
			break;
		case LOAD_GAME:
			if (!game_running) {
			}
			break;
		case MOVE_NORTH:
			entity_set_direction(g_player, NORTH);
			if (entity_can_move(g_player, NORTH)) {
				entity_move(g_player, NORTH);
			}
			break;
		case MOVE_SOUTH:
			entity_set_direction(g_player, SOUTH);
			if (entity_can_move(g_player, SOUTH)) {
				entity_move(g_player, SOUTH);
			}
			break;
		case MOVE_EAST:
			entity_set_direction(g_player, EAST);
			if (entity_can_move(g_player, EAST)) {
				entity_move(g_player, EAST);
			}
			break;
		case MOVE_WEST:
			entity_set_direction(g_player, WEST);
			if (entity_can_move(g_player, WEST)) {
				entity_move(g_player, WEST);
			}
			break;
		case SEE_NORTH:
			entity_set_direction(g_player, NORTH);
			break;
		case SEE_SOUTH:
			entity_set_direction(g_player, SOUTH);
			break;
		case SEE_EAST:
			entity_set_direction(g_player, EAST);
			break;
		case SEE_WEST:
			entity_set_direction(g_player, WEST);
			break;
		case ATTACK:
			entity_attack(g_player);
			break;
	}
}
