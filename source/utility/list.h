/**
 * @file utility/list.h
 * Fichier définissant les fonctions permettant d'utiliser des liste génériques.
 * La généricité est rendue possible en connaissant la taille des éléments que contiendra la liste.
 * La liste ne doît contenir que des éléments de même type.
 * Lorsque des éléments sont ajoutés à la liste, ils sont copiés.
 * @author Hector Basset
 * @date 12 décembre 2014
 */

#ifndef UTILITY_LIST_H

#define UTILITY_LIST_H

//librairies utilitaires
#include "boolean.h"

/**
 * Structure de donnée représentant une liste.
 * Ce type est opaque, ainsi le programmeur ne peut modifier la liste qu'à l'aide des fonctions et ne pas effectuer d'actions interdites dessus.
 */
typedef struct List List;

/**
 * Créé une liste.
 * @param size_of_elements La taille des éléments qui seront stockés dans la liste.
 * @return Le pointeur sur la liste créée.
 */
List * new_list(unsigned int size_of_elements);

/**
 * Supprime la liste.
 * @param list La liste.
 */
void list_free(List * list);

/**
 * Permet de vérifier si la liste est vide.
 * @param list La liste.
 * @return Si la liste est vide ou non.
 */
boolean list_empty(List * list);

/**
 * Permet d'obtenir la taille de la liste.
 * @param list La liste.
 * @return La taille de la liste.
 */
unsigned int list_size(List * list);

/**
 * Se place au début de la liste.
 * @param list La liste.
 */
void list_begin(List * list);

/**
 * Se place à la fin de la liste.
 * @param list La liste.
 */
void list_end(List * list);

/**
 * Se place sur l'élément précédant de la liste.
 * @param list La liste.
 */
void list_previous(List * list);

/**
 * Se place sur l'élément suivant de la liste.
 * @param list La liste.
 */
void list_next(List * list);

/**
 * Retourne si l'on est au début de la liste.
 * @param list La liste.
 * @return Si l'on est au début de la liste ou non.
 */
boolean list_at_begin(List * list);

/**
 * Retourne si l'on est à la fin de la liste.
 * @param list La liste.
 * @return Si l'on est à la fin de la liste ou non.
 */
boolean list_at_end(List * list);

/**
 * Retourne si l'on est en dehors de la liste.
 * @param list La liste.
 * @return Si l'on est en dehors de la liste ou non.
 */
boolean list_out(List * list);

/**
 * Ajoute un élément avant l'élément courant.
 * @param list La liste.
 * @param value Le pointeur vers l'élément à ajouter.
 */
void list_add_before(List * list, void * value);

/**
 * Ajoute un élément après l'élément courant.
 * @param list La liste.
 * @param value Le pointeur vers l'élément à ajouter.
 */
void list_add_after(List * list, void * value);

/**
 * Ajoute un élément au début de la liste.
 * @param list La liste.
 * @param value Le pointeur vers l'élément à ajouter.
 */
void list_add_begin(List * list, void * value);

/**
 * Ajoute un élément à la fin de la liste.
 * @param list La liste.
 * @param value Le pointeur vers l'élément à ajouter.
 */
void list_add_end(List * list, void * value);

/**
 * Retire l'élément courant.
 * @param list La liste.
 */
void list_remove(List * list);

/**
 * Retire le premier élément de la liste.
 * @param list La liste.
 */
void list_remove_first(List * list);

/**
 * Retire le dernier élément de la liste.
 * @param list La liste.
 */
void list_remove_last(List * list);

/**
 * Retire toutes les occurences d'un élément dans la liste.
 * @param list La liste.
 * @param value L'élément à retirer.
 */
void list_remove_value(List * list, void * value);

/**
 * Vide la liste.
 * @param list La liste.
 */
void list_clear(List * list);

/**
 * Retourne la valeur de l'élément courant.
 * @param list La liste.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void list_get_value(List * list, void * pointer);

/**
 * Retourne la valeur de l'élément du début de la liste.
 * @param list La liste.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void list_get_first(List * list, void * pointer);

/**
 * Retourne la valeur de l'élément à la fin de la liste.
 * @param list La liste.
 * @param pointer L'addresse à laquelle la valeur de l'élément sera stockée.
 */
void list_get_last(List * list, void * pointer);

#endif
