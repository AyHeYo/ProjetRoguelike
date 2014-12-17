
#include <stdlib.h>
#include <sys/time.h>

unsigned long mtime(unsigned long * timer) {
	unsigned long mtime;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	mtime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (timer != NULL) {
		*timer = mtime;
	}
	return mtime;
}

unsigned long utime(unsigned long * timer) {
	unsigned long utime;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	utime = tv.tv_sec * 1000000 + tv.tv_usec;
	if (timer != NULL) {
		*timer = utime;
	}
	return utime;
}
