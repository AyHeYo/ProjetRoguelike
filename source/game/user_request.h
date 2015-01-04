
#ifndef USER_REQUEST_H

#define USER_REQUEST_H

typedef enum {

	STARTUP,
	NEW_GAME,
	LOAD_GAME,
	SAVE_GAME,

	/**
	 * Aller vers le Nord.
	 */
	MOVE_NORTH,

	/**
	 * Aller vers le Sud.
	 */
	MOVE_SOUTH,

	/**
	 * Aller à l'Est.
	 */
	MOVE_EAST,

	/**
	 * Aller à l'Ouest.
	 */
	MOVE_WEST,

	/**
	 * Regarder vers le Nord.
	 */
	SEE_NORTH,

	/**
	 * Regarder vers le Sud.
	 */
	SEE_SOUTH,

	/**
	 * Regarder à l'Est.
	 */
	SEE_EAST,

	/**
	 * Regarder à l'Ouest.
	 */
	SEE_WEST,

	/**
	 * Attaquer.
	 */
	ATTACK,

	/**
	 * Accepter.
	 */
	ACCEPT,

	/**
	 * Refuser.
	 */
	DENY,

	/**
	 * Quitter/Sortir.
	 */
	EXIT
} UserRequest;

#endif
