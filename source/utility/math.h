/**
 * @file utility/math.h
 * Fichier définissant des fonctions mathématiques utilitaires.
 * @author Hector Basset
 * @date 10 décembre 2014
 */

#ifndef UTILITY_MATH_H

#define UTILITY_MATH_H

#include "boolean.h"

/**
 * Retourne un entier au hasard compris entre a et b inclu.
 * @param a Le minimum (inclu).
 * @param b Le maximum (inclu).
 * @return Un entier au hasard entre a et b inclu.
 */
int rand_between(int a, int b);

/**
 * Retourne vrai ou faux au hasard.
 * @return Vrai ou faux
 */
boolean rand_boolean();

/**
 * Retourne le plus petit de deux nombres entiers codés sur un short.
 * @param a Le premier nombre.
 * @param b Le deuxième nombre.
 * @return Le plus petit des deux nombres.
 */
char mins(short a, short b);

/**
 * Retourne le plus grand de deux nombres entiers codés sur un short.
 * @param a Le premier nombre.
 * @param b Le deuxième nombre.
 * @return Le plus grand des deux nombres.
 */
char maxs(short a, short b);

#endif
