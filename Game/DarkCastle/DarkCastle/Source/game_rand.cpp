#include  "../Headers/game_rand.h"


State GetRandomDir(State first, State second) {
	return rand() % 2 ? LEFT : RIGHT;
}

int GetRandomInt(int from, int to) {
	return rand() % (to - from + 1) + from;
}

float GetRandomFloat(int from, int to) {
	return rand() % (to - from + 1) + from + (rand() % 10) / 10.f;
}