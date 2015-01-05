
#include "direction.h"
#include "entity.h"
#include "maze.h"

#include "../utility/boolean.h"
#include "../utility/list.h"

static void resolve_square(List * list, Square * square) {
	Square * near, temp;
	Location sLocation, pLocation;
	boolean contain;
	if (!list_contains(list, &square)) {
		list_add_end(list, &square);
		if (square->type != WALL) {
			pLocation = get_square_location(g_player->square);
			near = get_near_square(square, NORTH);
			if (near != NULL) {
				sLocation = get_square_location(near);
				if (sLocation.column == pLocation.column) {
					resolve_square(list, square);
				} else {
					temp = get_near_square(near, EAST);
					contain = temp != NULL && list_contains(list, temp);
					if (!contain) {
						temp = get_near_square(near, WEST);
						contain = temp != NULL && list_contains(list, temp);
					}
					if (contain) {
						resolve_square(list, square);
					}
				}
			}
			near = get_near_square(square, SOUTH);
			if (near != NULL) {
				sLocation = get_square_location(near);
				if (sLocation.column == pLocation.column) {
					resolve_square(list, square);
				} else {
					temp = get_near_square(near, EAST);
					contain = temp != NULL && list_contains(list, temp);
					if (!contain) {
						temp = get_near_square(near, WEST);
						contain = temp != NULL && list_contains(list, temp);
					}
					if (contain) {
						resolve_square(list, square);
					}
				}
			}
			near = get_near_square(square, EAST);
			if (near != NULL) {
				sLocation = get_square_location(near);
				if (sLocation.row == pLocation.row) {
					resolve_square(list, square);
				} else {
					temp = get_near_square(near, NORTH);
					contain = temp != NULL && list_contains(list, temp);
					if (!contain) {
						temp = get_near_square(near, SOUTH);
						contain = temp != NULL && list_contains(list, temp);
					}
					if (contain) {
						resolve_square(list, square);
					}
				}
			}
			near = get_near_square(square, WEST);
			if (near != NULL) {
				sLocation = get_square_location(near);
				if (sLocation.row == pLocation.row) {
					resolve_square(list, square);
				} else {
					temp = get_near_square(near, NORTH);
					contain = temp != NULL && list_contains(list, temp);
					if (!contain) {
						temp = get_near_square(near, SOUTH);
						contain = temp != NULL && list_contains(list, temp);
					}
					if (contain) {
						resolve_square(list, square);
					}
				}
			}
		}
	}
}

void resolve_entity_view(List * list, Entity * entity) {
	list_clear(list);
	resolve_square(list, entity->square);
}
