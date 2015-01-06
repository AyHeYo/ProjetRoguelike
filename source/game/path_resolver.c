
#include <stdlib.h>

#include "direction.h"
#include "maze.h"

#include "../utility/list.h"
#include "../utility/math.h"
#include "../utility/stack.h"

typedef struct Branch Branch;

struct Branch {
	List * children;
	List * parents;
	Square * square;
	List * directions;
};

static Branch * new_branch(Square * square) {
	Branch * branch = malloc(sizeof(Branch));
	branch->children = new_list(sizeof(Branch *));
	branch->parents = new_list(sizeof(Branch *));
	branch->square = square;
	branch->directions = new_list(sizeof(Direction));
	return branch;
}

static void branch_free(Branch * branch) {
	Branch * temp;
	for (list_begin(branch->children) ; !list_empty(branch->children) ; list_remove(branch->children)) {
		list_get_value(branch->children, &temp);
		list_remove_value(temp->parents, &branch);
		if (list_empty(temp->parents)) {
			branch_free(temp);
		}
	}
	for (list_begin(branch->parents) ; !list_empty(branch->parents) ; list_remove(branch->parents)) {
		list_get_value(branch->parents, &temp);
		list_remove_value(temp->children, &branch);
	}
	list_free(branch->children);
	list_free(branch->parents);
	list_free(branch->directions);
	free(branch);
}

Branch * root;

static Square * destination;

static List * founds;

static Branch * get_branche_from_square(Square * square, List * list) {
	Branch * branch;
	for (list_begin(list) ; !list_out(list) ; list_next(list)) {
		list_get_value(list, &branch);
		if (branch->square == square) {
			return branch;
		}
	}
	return NULL;
}

static void resolve() {
	Square * near;
	Direction direction;
	Branch * branch, * temp;
	List * past = new_list(sizeof(Branch *)), * actuals = new_list(sizeof(Branch *));
	founds = new_list(sizeof(Branch *));
	list_add_end(past, &root);
	while (!list_empty(past) && list_empty(founds)) {
		for (list_begin(past) ; !list_empty(past) ; list_remove(past)) {
			list_get_value(past, &branch);
			direction = SOUTH;
			if (!list_contains(branch->directions, &direction)) {
				direction = NORTH;
				near = get_near_square(branch->square, direction);
				if (near != NULL) {
					temp = get_branche_from_square(near, actuals);
					if (temp != NULL) {
						list_add_end(branch->children, &temp);
						list_add_end(temp->parents, &branch);
						list_add_end(temp->directions, &direction);
					} else if (near == destination) {
						temp = new_branch(near);
						list_add_end(branch->children, &temp);
						list_add_end(temp->parents, &branch);
						list_add_end(temp->directions, &direction);
						list_add_end(actuals, &temp);
						list_add_end(founds, &temp);
					} else if ((near->type != WALL) && (near->entity == NULL || list_contains(branch->parents, &root))) {
						temp = new_branch(near);
						list_add_end(branch->children, &temp);
						list_add_end(temp->parents, &branch);
						list_add_end(temp->directions, &direction);
						list_add_end(actuals, &temp);
					}
				}
			}
			direction = WEST;
			if (!list_contains(branch->directions, &direction)) {
				direction = EAST;
				near = get_near_square(branch->square, direction);
				if (near != NULL) {
					temp = get_branche_from_square(near, actuals);
					if (temp != NULL) {
						list_add_end(branch->children, &temp);
						list_add_end(temp->parents, &branch);
						list_add_end(temp->directions, &direction);
					} else if (near == destination) {
						temp = new_branch(near);
						list_add_end(branch->children, &temp);
						list_add_end(temp->parents, &branch);
						list_add_end(temp->directions, &direction);
						list_add_end(actuals, &temp);
						list_add_end(founds, &temp);
					} else if ((near->type != WALL) && (near->entity == NULL || list_contains(branch->parents, &root))) {
						temp = new_branch(near);
						list_add_end(branch->children, &temp);
						list_add_end(temp->parents, &branch);
						list_add_end(temp->directions, &direction);
						list_add_end(actuals, &temp);
					}
				}
			}
			direction = NORTH;
			if (!list_contains(branch->directions, &direction)) {
				direction = SOUTH;
				near = get_near_square(branch->square, direction);
				if (near != NULL) {
					temp = get_branche_from_square(near, actuals);
					if (temp != NULL) {
						list_add_end(branch->children, &temp);
						list_add_end(temp->parents, &branch);
						list_add_end(temp->directions, &direction);
					} else if (near == destination) {
						temp = new_branch(near);
						list_add_end(branch->children, &temp);
						list_add_end(temp->parents, &branch);
						list_add_end(temp->directions, &direction);
						list_add_end(actuals, &temp);
						list_add_end(founds, &temp);
					} else if ((near->type != WALL) && (near->entity == NULL || list_contains(branch->parents, &root))) {
						temp = new_branch(near);
						list_add_end(branch->children, &temp);
						list_add_end(temp->parents, &branch);
						list_add_end(temp->directions, &direction);
						list_add_end(actuals, &temp);
					}
				}
			}
			direction = EAST;
			if (!list_contains(branch->directions, &direction)) {
				direction = WEST;
				near = get_near_square(branch->square, direction);
				if (near != NULL) {
					temp = get_branche_from_square(near, actuals);
					if (temp != NULL) {
						list_add_end(branch->children, &temp);
						list_add_end(temp->parents, &branch);
						list_add_end(temp->directions, &direction);
					} else if (near == destination) {
						temp = new_branch(near);
						list_add_end(branch->children, &temp);
						list_add_end(temp->parents, &branch);
						list_add_end(temp->directions, &direction);
						list_add_end(actuals, &temp);
						list_add_end(founds, &temp);
					} else if ((near->type != WALL) && (near->entity == NULL || list_contains(branch->parents, &root))) {
						temp = new_branch(near);
						list_add_end(branch->children, &temp);
						list_add_end(temp->parents, &branch);
						list_add_end(temp->directions, &direction);
						list_add_end(actuals, &temp);
					}
				}
			}
		}
		for (list_begin(actuals) ; !list_empty(actuals) ; list_remove(actuals)) {
			list_get_value(actuals, &branch);
			list_add_end(past, &branch);
		}
	}
	list_free(past);
	list_free(actuals);
}

static void to_stack(Stack * stack) {
	Branch * branch;
	Direction direction;
	int index, i;
	stack_clear(stack);
	if (!list_empty(founds)) {
		list_begin(founds);
		if (list_size(founds) > 1) {
			index = rand_between(0, list_size(founds) - 1);
			for (i = 0 ; i < index ; i++) {
				list_next(founds);
			}
		}
		list_get_value(founds, &branch);
		while (!list_empty(branch->parents)) {
			index = rand_between(0, list_size(branch->parents) - 1);
			list_begin(branch->parents);
			list_begin(branch->directions);
			for (i = 0 ; i < index ; i++) {
				list_next(branch->parents);
				list_next(branch->directions);
			}
			list_get_value(branch->directions, &direction);
			stack_push(stack, &direction);
			list_get_value(branch->parents, &branch);
		}
	}
	list_free(founds);
	branch_free(root);
}

void resolve_path(Square * start, Square * arrival, Stack * stack) {
	root = new_branch(start);
	destination = arrival;
	resolve();
	to_stack(stack);
}
