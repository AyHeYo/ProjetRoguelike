
#include "maze.h"

#define MIN_SIZE 20

#define GROWING_SPEED 1.1

static void free_squares(Maze * maze) {
	short row, column;
	for (row = 0 ; row < maze->size ; row++) {
		for (column = 0 ; column < size ; column++) {
			free(maze->squares[row * size + column].entity);
		}
	}
	free(maze->squares);
}

Maze * generate_maze(Maze * maze) {
	short row, column;
	if (maze == NULL) {
		maze = malloc(sizeof(Maze));
		maze->size = MIN_SIZE;
	} else {
		free_squares(maze);
		maze->size *= GROWING_SPEED;
	}
	maze->squares = malloc(maze->size * maze->size * sizeof(Square));
	for (row = 0 ; row < size ; row++) {
		for (column = 0 ; column < size ; column++) {
			maze->squares[row * size + column].type = WALL;
			maze->squares[row * size + column].entity = NULL;
		}
	}
	for (row = 1 ; row < (size - 1) ; row++) {
		for (column = 1 ; column < (size - 1) ; column++) {
			maze->squares[row * size + column].type = AIR;
		}
	}
}

void free_maze(Maze * maze) {
	free_squares(maze);
	free(maze);
}
