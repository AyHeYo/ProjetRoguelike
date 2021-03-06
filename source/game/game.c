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
#include "direction.h"
#include "entity.h"
#include "event.h"
#include "game.h"
#include "maze.h"
#include "path_resolver.h"
#include "player.h"

//librairies utilitaires
#include "../utility/geo.h"
#include "../utility/list.h"
#include "../utility/math.h"
#include "../utility/stack.h"
#include "../utility/time.h"

void game_init() {
	srand(utime(NULL));
	g_game_running = false;
	g_maze = NULL;
	g_player = NULL;
	g_player_view = NULL;
	g_entities = NULL;
}

void game_end() {
	g_game_running = false;
	g_player = NULL;
	g_player_view = NULL;
	list_free(g_entities);
	g_entities = NULL;
	free_maze();//libération de l'espace mémoire alloué au labyrinthe
	dispatch_new_event(MAZE_GENERATE, NULL);
}

void new_game() {
	g_game_running = true;
	g_level = 0;
	g_entities = new_list(sizeof(Entity *));
	g_player = new_entity(PLAYER);//céation du joueur
	g_player_view = new_list(sizeof(Square *));
	new_level();
}

void new_level() {
	short row, column;
	Entity * entity;
	list_clear(g_entities);
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
	resolve_entity_view(g_player, g_player_view);
	dispatch_new_event(MAZE_GENERATE, NULL);
	//placement des monstres
	do {
		row = rand_between(0, g_maze->size - 1);
		column = rand_between(0, g_maze->size - 1);
	} while (!entity_can_spawn(g_maze->squares + (row * g_maze->size + column)));
	entity = new_entity(GOBLIN);
	entity_spawn(entity, g_maze->squares + (row * g_maze->size + column), NORTH);
	do {
		row = rand_between(0, g_maze->size - 1);
		column = rand_between(0, g_maze->size - 1);
	} while (!entity_can_spawn(g_maze->squares + (row * g_maze->size + column)));
	entity = new_entity(GOBLIN);
	entity_spawn(entity, g_maze->squares + (row * g_maze->size + column), NORTH);
	do {
		row = rand_between(0, g_maze->size - 1);
		column = rand_between(0, g_maze->size - 1);
	} while (!entity_can_spawn(g_maze->squares + (row * g_maze->size + column)));
	entity = new_entity(GOBLIN);
	entity_spawn(entity, g_maze->squares + (row * g_maze->size + column), NORTH);
	do {
		row = rand_between(0, g_maze->size - 1);
		column = rand_between(0, g_maze->size - 1);
	} while (!entity_can_spawn(g_maze->squares + (row * g_maze->size + column)));
	entity = new_entity(GOBLIN);
	entity_spawn(entity, g_maze->squares + (row * g_maze->size + column), NORTH);
}

void turn() {
	Direction direction;
	Stack * path;
	Entity * entity;
	for (list_begin(g_entities) ; !list_out(g_entities) ; list_next(g_entities)) {
		list_get_value(g_entities, &entity);
		switch (entity->type) {
			case GOBLIN:
			case GHOST:
				if (entity_can_see(entity, g_player)) {
					if (entity_can_attack(entity, g_player)) {
						entity_attack(entity);
					} else {
						path = new_stack(sizeof(Direction));
						resolve_path(entity->square, g_player->square, path);
						if (!stack_empty(path)) {
							stack_pop(path, &direction);
							if (direction != entity->direction) {
								entity_set_direction(entity, direction);
							}
							if (entity_can_attack(entity, g_player)) {
								entity_attack(entity);
							} else {
								if (entity_can_move(entity, direction)) {
									entity_move(entity, direction);
								}
								if (!stack_empty(path)) {
									stack_pop(path, &direction);
									if (direction != entity->direction) {
										entity_set_direction(entity, direction);
									}
								}
							}
							stack_free(path);
						}
					}
				}
			case PLAYER:
				if (entity->square->type == FIRE) {
					entity_hurt(entity, 10);
				}
				break;
			case SWORD:
			case ARROW:
			case BALL:
			default:
				break;
		}
	}
}
