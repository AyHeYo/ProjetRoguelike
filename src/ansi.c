/**
 * @file ansi.c
 * Implémentation de ansi.h.
 * @author Hector Basset
 * @date 1 décembre 2014
 */

#include <stdio.h>

#include "ansi.h"

/**
 * La séquence d'échappement.
 */
const char CSI[5] = "\033[";

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

void ansi_save_position() {
	printf("%ss", CSI);
}

void ansi_restore_position() {
	printf("%su", CSI);
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

void ansi_set_color_index(unsigned char index) {
	printf("%s385;%um", CSI, index);
}

void ansi_set_bg_color_index(unsigned char index) {
	printf("%s485;%um", CSI, index);
}

void ansi_set_color_rgb(unsigned char red, unsigned char green, unsigned char blue) {
	printf("%s382;%u;%u;%um", CSI, red, green, blue);
}

void ansi_set_bg_color_rgb(unsigned char red, unsigned char green, unsigned char blue) {
	printf("%s482;%u;%u;%um", CSI, red, green, blue);
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

void ansi_underlined(boolean underlined) {
	printf("%s%um", CSI, underlined ? 4 : 24);
}

void ansi_overlined(boolean overlined) {
	printf("%s%um", CSI, overlined ? 53 : 55);
}

void ansi_italic(boolean italic) {
	printf("%s%um", CSI, italic ? 3 : 23);
}

void ansi_framed(boolean framed) {
	printf("%s%um", CSI, framed ? 51 : 54);
}
