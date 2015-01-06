/**
 * @file utility/list.h
 * Fichier définissant les fonctions permettant d'utiliser des liste génériques.
 * La généricité est rendue possible en connaissant la taille des éléments que contiendra la liste.
 * La liste ne doît contenir que des éléments de même type.
 * Lorsque des éléments sont ajoutés à la liste, ils sont copiés.
 * @author Hector Basset
 * @date 12 décembre 2014
 */

#ifndef UTILITY_STACK_H

#define UTILITY_STACK_H

//librairies utilitaires
#include "boolean.h"

/**
 * Structure de donnée représentant une liste.
 * Ce type est opaque, ainsi le programmeur ne peut modifier la liste qu'à l'aide des fonctions et ne pas effectuer d'actions interdites dessus.
 */
typedef struct Stack Stack;

/**
 * Créé une liste.
 * @param size_of_elements La taille des éléments qui seront stockés dans la liste.
 * @return Le pointeur sur la liste créée.
 */
Stack * new_stack(unsigned int size_of_elements);

/**
 * Supprime la liste.
 * @param list La liste.
 */
void stack_free(Stack * stack);

/**
 * Permet de vérifier si la liste est vide.
 * @param list La liste.
 * @return Si la liste est vide ou non.
 */
boolean stack_empty(Stack * stack);

/**
 * Permet d'obtenir la taille de la liste.
 * @param list La liste.
 * @return La taille de la liste.
 */
unsigned int stack_size(Stack * stack);

/**
 * Retourne la valeur de l'élément courant.
 * @param list La liste.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void stack_push(Stack * stack, void * value);

/**
 * Retourne la valeur de l'élément courant.
 * @param list La liste.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void stack_pop(Stack * stack, void * pointer);

/**
 * Retourne la valeur de l'élément courant.
 * @param list La liste.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void stack_remove(Stack * stack);

/**
 * Retourne la valeur de l'élément courant.
 * @param list La liste.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void stack_get(Stack * stack, void * pointer);

/**
 * Vide la liste.
 * @param list La liste.
 */
void stack_clear(Stack * stack);

#endif
