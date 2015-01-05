
#include "direction.h"
#include "maze.h"

#include "../utility/list.h"
#include "../utility/math.h"
#include "../utility/stack.h"

typedef struct Branch Branch;

struct Branch {
	List * branches;
	Branch * from;
	Square * square;
	Direction direction;
};

static Branch * root;

static Square * destination;

static List * to_resolve;

static List * founds;

static void free_branch(Branch * branch) {
	Branch * sub;
	for (list_begin(branch->branches) ; !list_out(branch->branches) ; list_next(branch->branches)) {
		list_get_value(&sub);
		free_branch(sub);
	}
	list_free(branch->branches);
}

static void resolve_branches() {
	Square * near;
	Branch * branch, new;
	List * temp = new_list(sizeof(Branch *));
	for (list_begin(to_resolve) ; !list_out(to_resolve) ; list_next(to_resolve)) {
		list_get_value(list, &branch);
		near = get_near_square(branch->square, NORTH);
		if (near != NULL && near->type != WALL || near == destination) {
			new = malloc(sizeof(Branch));
			new->branches = new_list(sizeof(Branch *));
			new->from = branch;
			new->square = near;
			new->destination = NORTH;
			list_add(branch->branches, &new);
			list_add_end(temp, &new);
			if (near = destination) {
				list_add_end(founds, &new);
			}
		}
		near = get_near_square(branch->square, SOUTH);
		if (near != NULL && near->type != WALL || near == destination) {
			new = malloc(sizeof(Branch));
			new->branches = new_list(sizeof(Branch *));
			new->from = branch;
			new->square = near;
			new->destination = SOUTH;
			list_add(branch->branches, &new);
			list_add_end(temp, &new);
			if (near = destination) {
				list_add_end(founds, &new);
			}
		}
		near = get_near_square(branch->square, EAST);
		if (near != NULL && near->type != WALL || near == destination) {
			new = malloc(sizeof(Branch));
			new->branches = new_list(sizeof(Branch *));
			new->from = branch;
			new->square = near;
			new->destination = EAST;
			list_add(branch->branches, &new);
			list_add_end(temp, &new);
			if (near = destination) {
				list_add_end(founds, &new);
			}
		}
		near = get_near_square(branch->square, WEST);
		if (near != NULL && near->type != WALL || near == destination) {
			new = malloc(sizeof(Branch));
			new->branches = new_list(sizeof(Branch *));
			new->from = branch;
			new->square = near;
			new->destination = WEST;
			list_add(branch->branches, &new);
			list_add_end(temp, &new);
			if (near = destination) {
				list_add_end(founds, &new);
			}
		}
	}
	list_free(to_resolve);
	if (list_empty(founds)) {
		to_resolve = temp;
		resolve_branches();
	} else {
		list_free(temp);
	}
}

static void to_stack(Stack * stack) {
	Branch * branch;
	int index, i;
	stack_clear(stack);
	list_begin(founds);
	if (list_size(founds) > 1) {
		index = rand_between(0, list_size(founds) - 1);
		for (i = 0 ; i < index ; i++) {
			list_next(founds);
		}
	}
	list_get_value(founds, &branch);
	for ( ; branch != NULL ; branch = branch->from) {
		stack_push(&(branch->destination));
	}
}

void resolve_path(Square * from, Square * to, Stack * stack) {
	founds = new_list(sizeof(Branch *));
	root = malloc(sizeof(Branch));
	root->branches = new_list(sizeof(Branch *));
	root->from = NULL;
	root->square = from;
	destination = to;
	to_resolve = new_list(sizeof(Branch *));
	list_add_end(to_resolve, &root);
	resolve_branches();
	to_stack(stack);
	free_branch(root);
}
