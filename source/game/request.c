
#include <stddef.h>

#include "direction.h"
#include "entity.h"
#include "event.h"
#include "game.h"
#include "maze.h"
#include "player.h"
#include "request.h"

#include "../utility/geo.h"

void request(Request request) {
	switch (request) {
		case STARTUP:
			game_init();
			dispatch_new_event(MAIN_MENU, NULL);
			break;
		case EXIT:
			if (g_game_running) {
				game_end();
				dispatch_new_event(MAIN_MENU, NULL);
			} else {
				dispatch_new_event(STOP_GAME, NULL);
			}
			break;
		case NEW_GAME:
			if (!g_game_running) {
				new_game();
			}
			break;
		case LOAD_GAME:
			if (!g_game_running) {
			}
			break;
		case SAVE_GAME:
			break;
		case ACCEPT:
			break;
		case DENY:
			break;
		case MOVE_NORTH:
			if (g_player->direction != NORTH) {
				entity_set_direction(g_player, NORTH);
			}
			if (entity_can_move(g_player, NORTH)) {
				entity_move(g_player, NORTH);
				resolve_entity_view(g_player, g_player_view);
				dispatch_new_event(MAZE_GENERATE, NULL);
				turn();
			}
			break;
		case MOVE_SOUTH:
			if (g_player->direction != SOUTH) {
				entity_set_direction(g_player, SOUTH);
			}
			if (entity_can_move(g_player, SOUTH)) {
				entity_move(g_player, SOUTH);
				resolve_entity_view(g_player, g_player_view);
				dispatch_new_event(MAZE_GENERATE, NULL);
				turn();
			}
			break;
		case MOVE_EAST:
			if (g_player->direction != EAST) {
				entity_set_direction(g_player, EAST);
			}
			if (entity_can_move(g_player, EAST)) {
				entity_move(g_player, EAST);
				resolve_entity_view(g_player, g_player_view);
				dispatch_new_event(MAZE_GENERATE, NULL);
				turn();
			}
			break;
		case MOVE_WEST:
			if (g_player->direction != WEST) {
				entity_set_direction(g_player, WEST);
			}
			if (entity_can_move(g_player, WEST)) {
				entity_move(g_player, WEST);
				resolve_entity_view(g_player, g_player_view);
				dispatch_new_event(MAZE_GENERATE, NULL);
				turn();
			}
			break;
		case SEE_NORTH:
			if (g_player->direction != NORTH) {
				entity_set_direction(g_player, NORTH);
			}
			break;
		case SEE_SOUTH:
			if (g_player->direction != SOUTH) {
				entity_set_direction(g_player, SOUTH);
			}
			break;
		case SEE_EAST:
			if (g_player->direction != EAST) {
				entity_set_direction(g_player, EAST);
			}
			break;
		case SEE_WEST:
			if (g_player->direction != WEST) {
				entity_set_direction(g_player, WEST);
			}
			break;
		case ATTACK:
			entity_attack(g_player);
			turn();
			break;
	}
}
