/**
 * @file model/entity.h
 * Fichier définissant les fonctions et les structures de données permettant la création, la supression et la gestion des entité.
 * Une entité est tout objet, qui n'est pas fixe, peut se déplacer et interagir avec d'autres entités (joueur, monstre, gobelin).
 * Les entités se déplacent sur les cases.
 * @author Hector Basset
 * @date 16 décembre 2014
 */

#ifndef GAME_ENTITY_H

#define GAME_ENTITY_H

//librairies du modèle
#include "direction.h"
#include "maze.h"

//librairies utilitaires
#include "../utility/boolean.h"
#include "../utility/list.h"

/**
 * Type énuméré définissant les différents types d'entité.
 */
typedef enum {

	/**
	 * Un joueur.
	 */
	PLAYER,

	/**
	 * Un gobelin.
	 */
	GOBLIN,

	/**
	 * Un fantôme.
	 */
	GHOST,

	/**
	 * Une clé.
	 */
	KEY,

	/**
	 * Une épée.
	 */
	SWORD,

	/**
	 * Une flêche.
	 */
	ARROW,

	/**
	 * Une boulle magique.
	 */
	BALL
} EntityType;

/**
 * Type énuméré définissant les différents types d'armes des entités.
 */
typedef enum {

	/**
	 * Aucune arme.
	 */
	NONE,

	/**
	 * Combat rapproché.
	 */
	MELEE,

	/**
	 * Attaque à distance.
	 */
	RANGED,

	/**
	 * Magie.
	 */
	MAGIC
} WeaponType;

typedef struct Entity Entity;

/**
 * Structure de données représentant une entité.
 */
struct Entity {

	/**
	 * Le type de l'entité.
	 */
	EntityType type;

	/**
	 * La vie maximum de l'entité.
	 */
	short max_life;

	/**
	 * La vie de l'entité.
	 */
	short life;

	/**
	 * Le type d'arme de l'entité.
	 */
	WeaponType weapon;

	/**
	 * La direction de l'entité (vers où elle regarde).
	 */
	Direction direction;

	/**
	 * La case de l'entité.
	 */
	struct Square * square;
};

List * g_entities;

/**
 * Créé une nouvelle entité.
 * @param type g_maze_heightLe type de l'entité.
 * @return Le pointeur sur la nouvelle entité.
 */
Entity * new_entity(EntityType type);

/**
 * Retourne si une entité peut se déplacer dans une direction donnée.
 * @param entity L'entité.
 * @param direction La direction vers laquelle l'entité doit se déplacer.
 * @return Si l'entité peut ce déplacer dans la direction donnée ou non.
 */
boolean entity_can_move(Entity * entity, Direction direction);

/**
 * Déplace l'entité dans la direction donnée.
 * @param entity L'entité.
 * @param direction La direction.
 */
void entity_move(Entity * entity, Direction direction);

/**
 * Ajoute de la vie à une entité.
 * @param entity L'entité.
 * @param amount Le montant à ajouter.
 */
void entity_heal(Entity * entity, short amount);

/**
 * Retire de la vie à une entité.
 * @param entity L'entité.
 * @param amount Le montant à retirer.
 */
void entity_hurt(Entity * entity, short amount);

/**
 * Fait qu'une entité attaque.
 * @param entity L'entité.
 */
void entity_attack(Entity * entity);

void entity_set_direction(Entity * entity, Direction direction);

boolean entity_can_spawn(struct Square * square);

void entity_spawn(Entity * entity, struct Square * square, Direction direction);

void entity_despawn(Entity * entity);

void entity_remove(Entity * entity);

void entity_die(Entity * entity);

void entity_view(Entity * entity, List * list);

boolean entity_can_see(Entity * entity, Entity * otherEntity);

#endif
