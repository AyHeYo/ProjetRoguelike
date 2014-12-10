
#include <stdlib.h>

int rand_between(int a, int b) {
	a += 1;
	return (rand() % (b - a)) + a;
}

char cmin(char a, char b) {
	return a < b ? a : b;
}
