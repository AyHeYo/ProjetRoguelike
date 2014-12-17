/**
 * @file utility/time.h
 * Fichier définissant des fonctions simplifiant certaines fonctionnalités en rapport au temps.
 * @author Hector Basset
 * @date 17 décembre 2014
 */

#ifndef UTILITY_TIME_H

#define UTILITY_TIME_H

/**
 * Retourne le temps actuel depuis Epoch en millisecondes.
 * @param timer L'adresse à laquelle stocker le temps en milliseconde (NULL pour ne pas le stocker).
 * @return Le temps en milliseconde.
 */
unsigned long mtime(unsigned long * timer);

/**
 * Retourne le temps actuel depuis Epoch en microsecondes.
 * @param timer L'adresse à laquelle stocker le temps en microsecondes (NULL pour ne pas le stocker).
 * @return Le temps en microsecondes.
 */
unsigned long utime(unsigned long * timer);

#endif
