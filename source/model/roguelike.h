/**
 * @file model/roguelike.h
 * Fichier définissant les types et les fonctions du Roguelike.
 * @author Hector Basset
 * @author Youssef Lamniy
 * @author Ayas Oukache
 * @date 20 novembre 2014
 */

#ifndef MODEL_ROGUELIKE_H

#define MODEL_ROGUELIKE_H

#include "maze.h"

//librairies utilitaires
#include "../utility/boolean.h"
#include "../utility/geo.h"

/**
 * Fonction initialisant le jeu, ne doit être appellée qu'une seule fois et avant toutes les autres relatives au jeu.
 */
void init_roguelike();

/**
 * Fonction terminant le jeu, ne doit être appellée qu'une seule fois et après toutes les autres relatives au jeu.
 */
void final_roguelike();

void generate();

#endif
