/**
 * @file view/ansi.c
 * Implémentation de ansi.h.
 * @author Hector Basset
 * @date 1 décembre 2014
 */

//bibliothèques du système
#include <stdio.h>

//bibliothèques de la vue
#include "ansi.h"

//bibliothèques utilitaires
#include "../utility/boolean.h"

/**
 * La séquence d'échappement.
 */
static const char CSI[5] = "\033[";

void ansi_up(unsigned int n) {
	printf("%s%uA", CSI, n);
}

void ansi_down(unsigned int n) {
	printf("%s%uB", CSI, n);
}

void ansi_right(unsigned int n) {
	printf("%s%uC", CSI, n);
}

void ansi_left(unsigned int n) {
	printf("%s%uD", CSI, n);
}

void ansi_next_line(unsigned int n) {
	printf("%s%uE", CSI, n);
}

void ansi_previous_line(unsigned int n) {
	printf("%s%uF", CSI, n);
}

void ansi_set_column(unsigned int column) {
	printf("%s%uG", CSI, column);
}

void ansi_set_position(unsigned int a, unsigned int b) {
	printf("%s%u;%uH", CSI, a, b);
}

void ansi_clear_screen() {
	printf("%s2J", CSI);
}

void ansi_clear_screen_before() {
	printf("%s1J", CSI);
}

void ansi_clear_screen_after() {
	printf("%s0J", CSI);
}

void ansi_clear_line() {
	printf("%s2K", CSI);
}

void ansi_clear_line_before() {
	printf("%s1K", CSI);
}

void ansi_clear_line_after() {
	printf("%s0K", CSI);
}

void ansi_scroll_up(unsigned int n) {
	printf("%s%uS", CSI, n);
}

void ansi_scroll_down(unsigned int n) {
	printf("%s%uT", CSI, n);
}

void ansi_hide_cursor(boolean hide) {
	printf("%s?25%c", CSI, hide ? 'l' : 'h');
}

void ansi_set_color(ANSIColor color) {
	printf("%s%um", CSI, color);
}

void ansi_set_bg_color(ANSIColor color) {
	printf("%s%um", CSI, color + 10);
}

void ansi_set_font(ANSIFont font) {
	printf("%s%um", CSI, font);
}

void ansi_normal() {
	printf("%s0m", CSI);
}

void ansi_bold(boolean bold) {
	printf("%s%um", CSI, bold ? 1 : 21);
}
