#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// generate random number from min to max
int rand_num(int min, int max) {

	static bool initialized = false;
	if (!initialized) {
		initialized = true;
		// srand(time(NULL));
	}

	return rand() % max + min;
}

int rand_color() {
	return rand_num(0, 255);
}

unsigned int funny_hash(unsigned int seed) {
	seed ^= 2747636419;
	seed *= 2654435769;
	seed ^= seed >> 16;
	seed *= 2654435769;
	seed ^= seed >> 16;
	seed *= 2654435769;
	return seed;
}