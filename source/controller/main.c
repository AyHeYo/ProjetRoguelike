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
	init_interface();
	generate();
	while (1) {
		display_maze();
		switch (wait_action()) {
			case TOP:
				if (entity_can_move(g_player, NORTH)) {
					entity_move(g_player, NORTH);
				}
				break;
			case BOTTOM:
				if (entity_can_move(g_player, SOUTH)) {
					entity_move(g_player, SOUTH);
				}
				break;
			case RIGHT:
				if (entity_can_move(g_player, EAST)) {
					entity_move(g_player, EAST);
				}
				break;
			case LEFT:
				if (entity_can_move(g_player, WEST)) {
					entity_move(g_player, WEST);
				}
				break;
			case EXIT:
				display_message("Au revoir !");
				final_interface();
				final_roguelike();
				return EXIT_SUCCESS;
			default:
				break;
		}
	}
}
