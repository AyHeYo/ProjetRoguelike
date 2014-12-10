
#ifndef MATH_H

#define MATH_H

/**
 * Retourne un entier au hasard compris entre a et b inclu.
 * @param a Le minimum (inclu).
 * @param b Le maximum (inclu).
 * @return Un entier au hasard entre a et b inclu.
 */
int rand_between(int a, int b);

/**
 * Retourne le plus petit de deux nombres entiers codés sur un char.
 * @param a Le premier nombre.
 * @param b Le deuxième nombre.
 * @return Le plus petit des deux nombres.
 */
char cmin(char a, char b);

#endif