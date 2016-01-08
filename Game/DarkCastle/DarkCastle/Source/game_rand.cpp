#include  "../Headers/game_rand.h"
#include "cassert"
#include "cmath"

State GetRandomOf(State first, State second) {
	return rand() % 2 ? LEFT : RIGHT;
}

int GetRandomInt(int from, int to) {
	assert(from > 0 && to > 0);
	return rand() % (to - from + 1) + from;
}

float GetRandomFloat(int from, int to, int precision) {
	assert(from > 0 && to > 0 && precision > 0);
	int signs = pow(10.f, float(precision));
	return rand() % (to - from + 1) + from + (rand() % signs) / float(signs);
}