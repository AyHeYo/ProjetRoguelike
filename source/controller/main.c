/**
 * @file controller/main.c
 * Fichier de la fonction principale.
 * @author Hector Basset
 * @author Youssef Lamniy
 * @author Ayas Oukache
 * @date 20 novembre 2014
 */

//librairies du système
#include <stdlib.h>

//librairies du modèle
#include "../model/entity.h"
#include "../model/player.h"
#include "../model/roguelike.h"

//librairies de la vue
#include "../view/interface.h"
#include "../view/maze.h"
#include "../view/window.h"

/**
 * Fonction principale.
 * @return Le code d'erreur.
 */
int main() {//pour l'instant, fonction main pour tester l'interface et la génération
	init_roguelike();
	new_level();
	init_interface();
	while (1) {
		switch (wait_action()) {
			case TOP:
				g_player->direction = NORTH;
				if (entity_can_move(g_player, NORTH)) {
					entity_move(g_player, NORTH);
				}
				break;
			case BOTTOM:
				g_player->direction = SOUTH;
				if (entity_can_move(g_player, SOUTH)) {
					entity_move(g_player, SOUTH);
				}
				break;
			case RIGHT:
				g_player->direction = EAST;
				if (entity_can_move(g_player, EAST)) {
					entity_move(g_player, EAST);
				}
				break;
			case LEFT:
				g_player->direction = WEST;
				if (entity_can_move(g_player, WEST)) {
					entity_move(g_player, WEST);
				}
				break;
			case HIT:
				entity_attack(g_player);
				break;
			case EXIT:
				set_message("Au revoir !");
				final_interface();
				final_roguelike();
				return EXIT_SUCCESS;
		}
	}
}
