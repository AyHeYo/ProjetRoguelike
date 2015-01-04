
#ifndef GAME_MAZE_H

#define GAME_MAZE_H

#include "user_request.h"

/**
 * Le niveau actuel.
 */
int g_level;

void game_init();

void game_final();

/**
 * Créé un nouveau niveau.
 */
void new_level();

void perform_request(UserRequest request);

#endif
