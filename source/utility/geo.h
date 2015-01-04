/**
 * @file utility/geo.h
 * Fichier définissant des strucutures de données géométriques.
 * @author Hector Basset
 * @date 2 décembre 2014
 */

#ifndef GEO_H

#define GEO_H

/**
 * Structure représentant la localisation d'une case sur une matrice.
 */
typedef struct {

	/**
	 * La ligne.
	 */
	int row;

	/**
	 * La colonne.
	 */
	int column;
} Location;

/**
 * Structure représentant un rectangle sur une matrice à l'aide de deux points opposés.
 */
typedef struct {

	/**
	 * Point en haut à gauche.
	 */
	Location a;

	/**
	 * Point en bas à droite.
	 */
	Location c;
} Rectangle;

/**
 * Structure représentant les dimensions d'une zone rectangulaire.
 */
typedef struct {

	/**
	 * La taille horizontale.
	 */
	int horizontal;

	/**
	 * La taille verticale.
	 */
	int vertical;
} Dimension;

#endif
