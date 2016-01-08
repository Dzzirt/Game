#pragma once
#include "consts_and_enums.h"
#include <random>

State GetRandomOf(State first, State second);

// Returns value in range [from, to]
// 'from' and 'to' must be more than 0
int GetRandomInt(int from, int to);

// Returns value in range [from, to] to 'precision' signs
// 'from', 'to' and 'precision' must be more than 0
float GetRandomFloat(int from, int to, int precision);