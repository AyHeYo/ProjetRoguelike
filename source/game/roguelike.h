/**
 * @file model/roguelike.h
 * Fichier définissant les types et les fonctions du Roguelike.
 * @author Hector Basset
 * @author Youssef Lamniy
 * @author Ayas Oukache
 * @date 20 novembre 2014
 */

#ifndef GAME_ROGUELIKE_H

#define GAME_ROGUELIKE_H

//librairies du modèle
#include "maze.h"

//librairies utilitaires
#include "../utility/boolean.h"
#include "../utility/geo.h"

/**
 * Le niveau actuel.
 */
int g_level;

/**
 * Fonction initialisant le jeu, ne doit être appellée qu'une seule fois et avant toutes les autres relatives au jeu.
 */
void init_roguelike();

/**
 * Fonction terminant le jeu, ne doit être appellée qu'une seule fois et après toutes les autres relatives au jeu.
 */
void final_roguelike();

/**
 * Créé un nouveau niveau.
 */
void new_level();

#endif
