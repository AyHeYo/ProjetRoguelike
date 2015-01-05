
#include <stddef.h>

#include "direction.h"
#include "entity.h"
#include "maze.h"

#include "../utility/boolean.h"
#include "../utility/list.h"

static Entity * viewer;

static Location viewer_location;

static List * squares;

static void resolve_square(Square * square) {
	Square * near, * temp;
	Location location;
	boolean contain;
	if (!list_contains(squares, &square)) {
		list_add_end(squares, &square);
		if (square->type != WALL) {
			near = get_near_square(square, NORTH);
			if (near != NULL) {
				location = get_square_location(near);
				if (location.column == viewer_location.column) {
					resolve_square(near);
				} else {
					temp = get_near_square(near, EAST);
					contain = temp != NULL && list_contains(squares, temp);
					if (!contain) {
						temp = get_near_square(near, WEST);
						contain = temp != NULL && list_contains(squares, temp);
					}
					if (contain) {
						resolve_square(near);
					}
				}
			}
			near = get_near_square(square, SOUTH);
			if (near != NULL) {
				location = get_square_location(near);
				if (location.column == viewer_location.column) {
					resolve_square(near);
				} else {
					temp = get_near_square(near, EAST);
					contain = temp != NULL && list_contains(squares, temp);
					if (!contain) {
						temp = get_near_square(near, WEST);
						contain = temp != NULL && list_contains(squares, temp);
					}
					if (contain) {
						resolve_square(near);
					}
				}
			}
			near = get_near_square(square, EAST);
			if (near != NULL) {
				location = get_square_location(near);
				if (location.row == viewer_location.row) {
					resolve_square(near);
				} else {
					temp = get_near_square(near, NORTH);
					contain = temp != NULL && list_contains(squares, temp);
					if (!contain) {
						temp = get_near_square(near, SOUTH);
						contain = temp != NULL && list_contains(squares, temp);
					}
					if (contain) {
						resolve_square(near);
					}
				}
			}
			near = get_near_square(square, WEST);
			if (near != NULL) {
				location = get_square_location(near);
				if (location.row == viewer_location.row) {
					resolve_square(near);
				} else {
					temp = get_near_square(near, NORTH);
					contain = temp != NULL && list_contains(squares, temp);
					if (!contain) {
						temp = get_near_square(near, SOUTH);
						contain = temp != NULL && list_contains(squares, temp);
					}
					if (contain) {
						resolve_square(near);
					}
				}
			}
		}
	}
}

void resolve_entity_view(Entity * entity, List * list) {
	list_clear(list);
	squares = list;
	viewer = entity;
	viewer_location = get_square_location(entity->square);
	resolve_square(entity->square);
	printf("%i", list_size(list));
}
