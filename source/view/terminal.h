/**
 * @file view/terminal.h
 * Fichier définissant les fonctions permettant de contrôler le terminal.
 * @author Hector Basset
 * @date 10 décembre 2014
 */

#ifndef VIEW_TERMINAL_H

#define VIEW_TERMINAL_H

//librairies du système
#include <termios.h>

//librairies utilitaires
#include "../utility/boolean.h"

/**
 * Structure représentant la taille d'un terminal (en nombre de colonne et de lignes de caractères).
 */
typedef struct {

	/**
	 * Le nombre de lignes.
	 */
	int rows;

	/**
	 * Le nombre de colonnes.
	 */
	int columns;
} TerminalSize;

/**
 * Retourne la taille du terminal.
 * @return La taille du terminal.
 */
TerminalSize get_terminal_size();

/**
 * Retourne la hauteur du terminal.
 * @return La hauteur du terminal.
 */
int get_terminal_height();

/**
 * Retourne la largeur du terminal.
 * @return La largeur du terminal.
 */
int get_terminal_width();

/**
 * Définission pour plus de lisibilité.
 */
typedef struct termios TerminalAttributs;

/**
 * Stocke les attributs courants du terminal.
 * @param attributs Le pointeur vers la structure dans laquelle seront stockés les attributs.
 */
void get_terminal_attributs(TerminalAttributs * attributs);

/**
 * Applique les attributs aux terminal courant.
 * @param attributs Le pointeur vers la structure dans laquelle sont les attributs à appliquer.
 */
void set_terminal_attributs(TerminalAttributs * attributs);

/**
 * Permet de choisir le mode du terminal (canonique ou non canonique).
 * @param attributs Le pointeur vers la structure dans laquelle sera stocké le mode.
 * @param canonical Si le nouveau mode est le mode canonique ou non.
 */
void set_terminal_mode(TerminalAttributs * attributs, boolean canonical);

/**
 * Permet de choisir si le terminal doit afficher la saisie de l'utilisateur.
 * @param attributs Le pointeur vers la structure dans laquelle sera stocké cette propriété.
 * @param echo Si le terminal doit afficher la saisie de l'utilisateur ou non.
 */
void set_terminal_echo_input(TerminalAttributs * attributs, boolean echo);

/**
 * Permet de choisir si le nombre minimum de caractères attendus lors d'une lecture en mode non canonique.
 * @param attributs Le pointeur vers la structure dans laquelle sera stocké cette propriété.
 * @param min_char Le nombre minimum de caractères attendus.
 */
void set_terminal_min_char(TerminalAttributs * attributs, int min_char);

/**
 * Permet de choisir si le délai maximum en dixième de seconde lors d'une lecture en mode non canonique.
 * @param attributs Le pointeur vers la structure dans laquelle sera stocké cette propriété.
 * @param max_time Le délai maximum.
 */
void set_terminal_max_time(TerminalAttributs * attributs, int max_time);

#endif
