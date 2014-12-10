/**
 * @file ansi.h
 * Fichier définissant les fonctions générant des séquences ANSI permettant d'interagir avec le terminal et de modifier la mise en forme du texte.
 * @author Hector Basset
 * @date 1 décembre 2014
 */

#ifndef ANSI_H

#define ANSI_H

#include "../utility/boolean.h"

/**
 * Type énuméré définissant les différentes couleurs directement sélectionnables en ANSI.
 */
typedef enum {

	/**
	 * Noir.
	 */
	ANSI_BLACK = 30,

	/**
	 * Rouge.
	 */
	ANSI_RED,

	/**
	 * Vert.
	 */
	ANSI_GREEN,

	/**
	 * Orange/Marron.
	 */
	ANSI_BROWN,

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
	 * Gris clair.
	 */
	ANSI_LIGHT_GREY,

	/**
	 * Gris.
	 */
	ANSI_GREY = 90,

	/**
	 * Rouge clair.
	 */
	ANSI_LIGHT_RED,

	/**
	 * Vert clair.
	 */
	ANSI_LIGHT_GREEN,

	/**
	 * Jaune.
	 */
	ANSI_YELLOW,

	/**
	 * Bleu clair.
	 */
	ANSI_LIGHT_BLUE,

	/**
	 * Rose.
	 */
	ANSI_PINK,

	/**
	 * Cyan clair.
	 */
	ANSI_LIGHT_CYAN,

	/**
	 * Blanc.
	 */
	ANSI_WHITE,

	/**
	 * Couleur par défaut, varie selon les terminaux.
	 */
	ANSI_DEFAULT_COLOR = 39
} ANSIColor;

/**
 * Type énuméré définissant les différentes valeurs possibles de police de caractère dans le terminal.
 */
typedef enum {

	/**
	 * Police par défaut du terminal.
	 */
	ANSI_DEFAULT_FONT = 10,

	/**
	 * Police alternative 1.
	 */
	ANSI_ALTERNATE_FONT_1,

	/**
	 * Police alternative 2.
	 */
	ANSI_ALTERNATE_FONT_2,

	/**
	 * Police alternative 3.
	 */
	ANSI_ALTERNATE_FONT_3,

	/**
	 * Police alternative 4.
	 */
	ANSI_ALTERNATE_FONT_4,

	/**
	 * Police alternative 5.
	 */
	ANSI_ALTERNATE_FONT_5,

	/**
	 * Police alternative 6.
	 */
	ANSI_ALTERNATE_FONT_6,

	/**
	 * Police alternative 7.
	 */
	ANSI_ALTERNATE_FONT_7,

	/**
	 * Police alternative 8.
	 */
	ANSI_ALTERNATE_FONT_8,

	/**
	 * Police alternative 9.
	 */
	ANSI_ALTERNATE_FONT_9
} ANSIFont;

/**
 * Déplace le curseur vers le haut.
 * @param n Le nombre de lignes dont le curseur va monter.
 */
void ansi_up(unsigned int n);

/**
 * Déplace le curseur vers le bas.
 * @param n Le nombre de lignes dont le curseur va descendre.
 */
void ansi_down(unsigned int n);

/**
 * Déplace le curseur vers la droite.
 * @param n Le nombre de colonnes dont le curseur va être décalé.
 */
void ansi_right(unsigned int n);

/**
 * Déplace le curseur vers la gauche.
 * @param n Le nombre de colonnes dont le curseur va être décalé.
 */
void ansi_left(unsigned int n);

/**
 * Déplace le curseur vers le bas et le place en début de ligne.
 * @param n Le nombre de lignes dont le curseur va descendre.
 */
void ansi_next_line(unsigned int n);

/**
 * Déplace le curseur vers le haut et le place en début de ligne.
 * @param n Le nombre de lignes dont le curseur va monter.
 */
void ansi_previous_line(unsigned int n);

/**
 * Place le curseur sur la colonne donnée.
 * @param column Le numéro de colonne (commence à 1).
 */
void ansi_set_column(unsigned int column);

/**
 * Place le curseur sur la position donnée.
 * @param line Le numéro de ligne (commence à 1).
 * @param column Le numéro de colonne (commence à 1).
 */
void ansi_set_position(unsigned int line, unsigned int column);

/**
 * Efface l'écran.
 */
void ansi_clear_screen();

/**
 * Efface du début de l'écran jusqu'au le curseur.
 */
void ansi_clear_screen_before();

/**
 * Efface de la fin de l'écran jusqu'au le curseur.
 */
void ansi_clear_screen_after();

/**
 * Efface la ligne.
 */
void ansi_clear_line();

/**
 * Efface du début de la ligne jusqu'au curseur.
 */
void ansi_clear_line_before();

/**
 * Efface de la fin de la ligne jusqu'au curseur.
 */
void ansi_clear_line_after();

/**
 * Décale l'écran vers le haut.
 * @param n Le nombre de lignes dont l'écran va être décalé.
 */
void ansi_scroll_up(unsigned int n);

/**
 * Décale l'écran vers le bas.
 * @param n Le nombre de lignes dont l'écran va être décalé.
 */
void ansi_scroll_down(unsigned int n);

/**
 * Sauvegarde la position du curseur.
 */
void ansi_save_position();

/**
 * Restaure la position du curseur à celle sauvegardée.
 */
void ansi_restore_position();

/**
 * Change si le curseur doit être caché ou non.
 * @param hide Si le curseur doit être caché ou non.
 */
void ansi_hide_cursor(boolean hide);

/**
 * Change la couleur du texte.
 * @param color La couleur.
 */
void ansi_set_color(ANSIColor color);

/**
 * Change la couleur de l'arrière plan.
 * @param color La couleur.
 */
void ansi_set_bg_color(ANSIColor color);

/**
 * Change la couleur du texte via l'index de la couleur.
 * @param index L'index de la couleur (de 0 à 255).
 */
void ansi_set_color_index(unsigned char index);

/**
 * Change la couleur de l'arrière plan via l'index de la couleur.
 * @param index L'index de la couleur (de 0 à 255).
 */
void ansi_set_bg_color_index(unsigned char index);

/**
 * Change la couleur du texte via une composition RGB.
 * @param red La valeur de rouge.
 * @param green La valeur de vert.
 * @param blue La valeur de bleu.
 */
void ansi_set_color_rgb(unsigned char red, unsigned char green, unsigned char blue);

/**
 * Change la couleur de l'arrière plan via une composition RGB.
 * @param red La valeur de rouge.
 * @param green La valeur de vert.
 * @param blue La valeur de bleu.
 */
void ansi_set_bg_color_rgb(unsigned char red, unsigned char green, unsigned char blue);

/**
 * Change la police de caractère.
 * @param font La police de caractère.
 */
void ansi_set_font(ANSIFont font);

/**
 * Remet le formattage du texte à normal.
 */
void ansi_normal();

/**
 * Change si le texte doit être en gras ou non.
 * @param bold Si le texte doit être en gras ou non.
 */
void ansi_bold(boolean bold);

/**
 * Change si le texte doit être souligné ou non.
 * @param underlined Si le texte doit être souligné ou non.
 */
void ansi_underlined(boolean underlined);

/**
 * Change si le texte doit être surligné ou non.
 * @param overlined Si le texte doit être surligné ou non.
 */
void ansi_overlined(boolean overlined);

/**
 * Change si le texte doit être en italique ou non.
 * @param italic Si le texte doit être en italique ou non.
 */
void ansi_italic(boolean italic);

/**
 * Change si le texte doit être encadré ou non.
 * @param framed Si le texts=e doit être encadré ou non.
 */
void ansi_framed(boolean framed);

#endif
