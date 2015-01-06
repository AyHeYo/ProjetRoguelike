
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

static List * temp;

/*static void resolve() {
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
}*/

static void resolve() {
	Square * square, * near, * n;
	Location location;
	for (list_begin(last) ; !list_out(last) ; list_next(last)) {
		list_get_value(last, &square);
		if (square->type != WALL) {
			near = get_near_square(square, NORTH);
			if (near != NULL && !list_contains(viewed_squares, &near) && !list_contains(last, &near) && !list_contains(temp, &near)) {
				location = get_square_location(near);
				if (location.column == viewer_location.column) {
					list_add_end(temp, &near);
				} else {
					n = get_near_square(near, EAST);
					if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
						list_add_end(temp, &near);
					} else {
						n = get_near_square(near, WEST);
						if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
							list_add_end(temp, &near);
						}
					}
				}
			}
			near = get_near_square(square, EAST);
			if (near != NULL && !list_contains(viewed_squares, &near) && !list_contains(last, &near) && !list_contains(temp, &near)) {
				location = get_square_location(near);
				if (location.row == viewer_location.row) {
					list_add_end(temp, &near);
				} else {
					n = get_near_square(near, NORTH);
					if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
						list_add_end(temp, &near);
					} else {
						n = get_near_square(near, SOUTH);
						if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
							list_add_end(temp, &near);
						}
					}
				}
			}
			near = get_near_square(square, SOUTH);
			if (near != NULL && !list_contains(viewed_squares, &near) && !list_contains(last, &near) && !list_contains(temp, &near)) {
				location = get_square_location(near);
				if (location.column == viewer_location.column) {
					list_add_end(temp, &near);
				} else {
					n = get_near_square(near, EAST);
					if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
						list_add_end(temp, &near);
					} else {
						n = get_near_square(near, WEST);
						if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
							list_add_end(temp, &near);
						}
					}
				}
			}
			near = get_near_square(square, WEST);
			if (near != NULL && !list_contains(viewed_squares, &near) && !list_contains(last, &near) && !list_contains(temp, &near)) {
				location = get_square_location(near);
				if (location.row == viewer_location.row) {
					list_add_end(temp, &near);
				} else {
					n = get_near_square(near, NORTH);
					if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
						list_add_end(temp, &near);
					} else {
						n = get_near_square(near, SOUTH);
						if (n != NULL && (list_contains(viewed_squares, &n) || list_contains(last, &n))) {
							list_add_end(temp, &near);
						}
					}
				}
			}
		}
	}
	for (list_begin(last) ; !list_out(last) ; list_next(last)) {
		list_get_value(last, &square);
		list_add_end(viewed_squares, &square);
	}
	list_clear(last);
	if (!list_empty(temp)) {
		for (list_begin(temp) ; !list_out(temp) ; list_next(temp)) {
			list_get_value(temp, &square);
			list_add_end(last, &square);
		}
		list_clear(temp);
		resolve();
	}
}

void resolve_entity_view(Entity * entity, List * list) {
	list_clear(list);
	viewed_squares = list;
	temp = new_list(sizeof(Square *));
	last = new_list(sizeof(Square *));
	viewer = entity;
	viewer_location = get_square_location(entity->square);
	list_add_end(last, &(entity->square));
	resolve();
	list_free(temp);
	list_free(last);
}
