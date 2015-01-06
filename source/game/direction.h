
#ifndef GAME_DIRECTION_H

#define GAME_DIRECTION_H

/**
 * Type énuméré représentant les différents directions vers lesquelles le personnage peut se déplacer.
 */
typedef enum {

	/**
	 * Nord (haut).
	 */
	NORTH,

	/**
	 * Est (droite).
	 */
	EAST,

	/**
	 * Sud (bas).
	 */
	SOUTH,

	/**
	 * Ouest (gauche).
	 */
	WEST
} Direction;

Direction get_random_direction();

#endif
