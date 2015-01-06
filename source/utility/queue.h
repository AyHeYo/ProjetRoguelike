/**
 * @file utility/list.h
 * Fichier définissant les fonctions permettant d'utiliser des files génériques.
 * La généricité est rendue possible en connaissant la taille des éléments que contiendra la file.
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
 * Créé une file.
 * @param size_of_elements La taille des éléments qui seront stockés dans la file.
 * @return Le pointeur sur la file créée.
 */
Queue * new_queue(unsigned int size_of_elements);

/**
 * Supprime la file.
 * @param queue La file.
 */
void queue_free(Queue * queue);

/**
 * Permet de vérifier si la file est vide.
 * @param queue La file.
 * @return Si la file est vide ou non.
 */
boolean queue_empty(Queue * queue);

/**
 * Permet d'obtenir la taille de la file.
 * @param queue La file.
 * @return La taille de la file.
 */
unsigned int queue_size(Queue * queue);

/**
 * Ajoute un élément à la fin de la file.
 * @param queue La file.
 * @param value Le pointeur vers la valeur à ajouter.
 */
void queue_add(Queue * queue, void * value);

/**
 * Retire l'élément en tête de la file et le stocke à l'adresse indiquée.
 * @param queue La file.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void queue_pop(Queue * queue, void * pointer);

/**
 * Retire l'élément en tête de la file.
 * @param queue La file.
 */
void queue_remove(Queue * queue);

/**
 * Permet d'acceder à l'élément en tête de la file.
 * @param queue La file.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void queue_get(Queue * queue, void * pointer);

/**
 * Vide la file.
 * @param queue La file.
 */
void queue_clear(Queue * queue);

#endif
