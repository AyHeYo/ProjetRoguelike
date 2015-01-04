
#ifndef GAME_GAME_H

#define GAME_GAME_H

#include "../utility/boolean.h"

boolean g_game_running;

/**
 * Le niveau actuel.
 */
int g_level;

void game_init();

void game_end();

void new_game();

/**
 * Créé un nouveau niveau.
 */
void new_level();

void turn();

#endif
