/**
 * @file utility/list.h
 * Fichier définissant les fonctions permettant d'utiliser des piles génériques.
 * La généricité est rendue possible en connaissant la taille des éléments que contiendra la pile.
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
 * Créé une pile.
 * @param size_of_elements La taille des éléments qui seront stockés dans la pile.
 * @return Le pointeur sur la pile créée.
 */
Stack * new_stack(unsigned int size_of_elements);

/**
 * Supprime la pile.
 * @param stack La pile.
 */
void stack_free(Stack * stack);

/**
 * Permet de vérifier si la pile est vide.
 * @param stack La pile.
 * @return Si la pile est vide ou non.
 */
boolean stack_empty(Stack * stack);

/**
 * Permet d'obtenir la taille de la pile.
 * @param stack La pile.
 * @return La taille de la pile.
 */
unsigned int stack_size(Stack * stack);

/**
 * Empile un élément au sommet de la pile.
 * @param stack La pile.
 * @param value Le pointeur vers la valeur à empiler.
 */
void stack_push(Stack * stack, void * value);

/**
 * Dépile l'élément au sommet de la file et le stocke à l'adresse indiquée.
 * @param stack La pile.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void stack_pop(Stack * stack, void * pointer);

/**
 * Retire l'élément au sommet de la pile.
 * @param stack La pile.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void stack_remove(Stack * stack);

/**
 * Permet d'acceder à l'élément au sommet de la file.
 * @param stack La pile.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void stack_get(Stack * stack, void * pointer);

/**
 * Vide la pile.
 * @param stack La pile.
 */
void stack_clear(Stack * stack);

#endif
