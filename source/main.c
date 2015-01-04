
#include <stdlib.h>

#include "game/game.h"
#include "gui/gui.h"

int main() {
	gui_init();//initialisation de l'interface
	gui_start();//utilisation de l'interface
	gui_final();//finalisation de l'interface
	return EXIT_SUCCESS;
}
