
#include <stddef.h>

#include "direction.h"
#include "entity.h"
#include "maze.h"

#include "../utility/boolean.h"
#include "../utility/list.h"

static Entity * viewer;

static Location viewer_location;

static List * viewed_squares;

static List * last;

static void resolve() {
	Square * square, * near, * n;
	Location location;
	for (list_begin(last) ; !list_empty(last) ; list_remove(last)) {
		list_get_value(last, &square);
		if (square->type != WALL) {
			near = get_near_square(square, NORTH);
			if (near != NULL && !list_contains(viewed_squares, &near) && !list_contains(last, &near)) {
				location = get_square_location(near);
				if (location.column == viewer_location.column) {
					list_add_end(last, &near);
				} else {
					n = get_near_square(near, EAST);
					if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
						list_add_end(last, &near);
					} else {
						n = get_near_square(near, WEST);
						if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
							list_add_end(last, &near);
						}
					}
				}
			}
			near = get_near_square(square, EAST);
			if (near != NULL && !list_contains(viewed_squares, &near) && !list_contains(last, &near)) {
				location = get_square_location(near);
				if (location.row == viewer_location.row) {
					list_add_end(last, &near);
				} else {
					n = get_near_square(near, NORTH);
					if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
						list_add_end(last, &near);
					} else {
						n = get_near_square(near, SOUTH);
						if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
							list_add_end(last, &near);
						}
					}
				}
			}
			near = get_near_square(square, SOUTH);
			if (near != NULL && !list_contains(viewed_squares, &near) && !list_contains(last, &near)) {
				location = get_square_location(near);
				if (location.column == viewer_location.column) {
					list_add_end(last, &near);
				} else {
					n = get_near_square(near, EAST);
					if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
						list_add_end(last, &near);
					} else {
						n = get_near_square(near, WEST);
						if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
							list_add_end(last, &near);
						}
					}
				}
			}
			near = get_near_square(square, WEST);
			if (near != NULL && !list_contains(viewed_squares, &near) && !list_contains(last, &near)) {
				location = get_square_location(near);
				if (location.row == viewer_location.row) {
					list_add_end(last, &near);
				} else {
					n = get_near_square(near, NORTH);
					if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
						list_add_end(last, &near);
					} else {
						n = get_near_square(near, SOUTH);
						if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
							list_add_end(last, &near);
						}
					}
				}
			}
		}
		list_add_end(viewed_squares, &square);
	}
}

void resolve_entity_view(Entity * entity, List * list) {
	list_clear(list);
	viewed_squares = list;
	last = new_list(sizeof(Square *));
	viewer = entity;
	viewer_location = get_square_location(entity->square);
	list_add_end(last, &(entity->square));
	resolve();
	list_free(last);
}
