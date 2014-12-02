/**
 * @file ansi.h
 * Fichier définissant les fonctions générant des séquences ANSI permettant d'interagir avec le terminal et de modifier la mise en forme du texte.
 * @author Hector Basset
 * @date 1 décembre 2014
 */

#ifndef ANSI_H

#define ANSI_H

/**
 * Type énuméré définissant les différentes couleurs directement sélectionnables en ANSI.
 */
typedef enum {

	/**
	 * Noir.
	 */
	ANSI_BLACK,

	/**
	 * Rouge.
	 */
	ANSI_RED,

	/**
	 * Vert.
	 */
	ANSI_GREEN,

	/**
	 * Jaune.
	 */
	ANSI_YELLOW,

	/**
	 * Bleu.
	 */
	ANSI_BLUE,

	/**
	 * Magenta.
	 */
	ANSI_MAGENTA,

	/**
	 * Cyan.
	 */
	ANSI_CYAN,

	/**
	 * Blanc.
	 */
	ANSI_WHITE,

	/**
	 * Couleur par défaut, varie selon les terminaux.
	 */
	ANSI_DEFAULT_COLOR = 9
} ANSIColor;

void ansi_up(unsigned int n);

void ansi_down(unsigned int n);

void ansi_right(unsigned int n);

void ansi_left(unsigned int n);

void ansi_next_line(unsigned int n);

void ansi_previous_line(unsigned int n);

void ansi_set_column(unsigned int a);

void ansi_set_position(unsigned int a, unsigned int b);

void ansi_clear_screen();

void ansi_clear_screen_before();

void ansi_clear_screen_after();

void ansi_clear_line();

void ansi_clear_line_before();

void ansi_clear_line_after();

void ansi_scroll_up(unsigned int n);

void ansi_scroll_down(unsigned int n);

void ansi_save_position();

void ansi_restore_position();

void ansi_hide_cursor();

void ansi_show_cursor();

void ansi_set_color(ANSIColor color);

void ansi_set_bg_color(ANSIColor color);

void ansi_set_color_index(unsigned char color);

void ansi_set_bg_color_index(unsigned char color);

void ansi_set_color_rgb(unsigned char red, unsigned char green, unsigned char blue);

void ansi_set_bg_color_rgb(unsigned char red, unsigned char green, unsigned char blue);

void ansi_normal();

#endif