/**
 * @file utility/list.h
 * Fichier définissant les fonctions permettant d'utiliser des liste génériques.
 * La généricité est rendue possible en connaissant la taille des éléments que contiendra la liste.
 * La liste ne doît contenir que des éléments de même type.
 * Lorsque des éléments sont ajoutés à la liste, ils sont copiés.
 * @author Hector Basset
 * @date 12 décembre 2014
 */

#ifndef UTILITY_QUEUE_H

#define UTILITY_QUEUE_H

//librairies utilitaires
#include "boolean.h"

/**
 * Structure de donnée représentant une liste.
 * Ce type est opaque, ainsi le programmeur ne peut modifier la liste qu'à l'aide des fonctions et ne pas effectuer d'actions interdites dessus.
 */
typedef struct Queue Queue;

/**
 * Créé une liste.
 * @param size_of_elements La taille des éléments qui seront stockés dans la liste.
 * @return Le pointeur sur la liste créée.
 */
Queue * new_queue(unsigned int size_of_elements);

/**
 * Supprime la liste.
 * @param list La liste.
 */
void queue_free(Queue * queue);

/**
 * Permet de vérifier si la liste est vide.
 * @param list La liste.
 * @return Si la liste est vide ou non.
 */
boolean queue_empty(Queue * queue);

/**
 * Permet d'obtenir la taille de la liste.
 * @param list La liste.
 * @return La taille de la liste.
 */
unsigned int queue_size(Queue * queue);

/**
 * Retourne la valeur de l'élément courant.
 * @param list La liste.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void queue_add(Queue * queue, void * value);

/**
 * Retourne la valeur de l'élément courant.
 * @param list La liste.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void queue_pop(Queue * queue, void * pointer);

/**
 * Retourne la valeur de l'élément courant.
 * @param list La liste.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void queue_remove(Queue * queue);

/**
 * Retourne la valeur de l'élément courant.
 * @param list La liste.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void queue_get(Queue * queue, void * pointer);

/**
 * Vide la liste.
 * @param list La liste.
 */
void queue_clear(Queue * queue);

#endif
