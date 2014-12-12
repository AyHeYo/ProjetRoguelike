/**
 * @file main.c
 * Fichier de la fonction principale.
 * @author Hector Basset
 * @author Youssef Lamniy
 * @author Ayas Oukache
 * @date 20 novembre 2014
 */

#include <stdlib.h>

#include "../model/roguelike.h"

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
	generate_maze();
	while (1) {
		display_maze(get_maze(), get_maze_dimension());
		switch (wait_action()) {
			case TOP:
				if (player_can_move(NORTH)) {
					move_player(NORTH);
				}
				break;
			case BOTTOM:
				if (player_can_move(SOUTH)) {
					move_player(SOUTH);
				}
				break;
			case RIGHT:
				if (player_can_move(EAST)) {
					move_player(EAST);
				}
				break;
			case LEFT:
				if (player_can_move(WEST)) {
					move_player(WEST);
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
