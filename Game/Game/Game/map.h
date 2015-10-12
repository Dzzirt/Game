#pragma once
#include <SFML/Graphics.hpp>


const int MapHeight = 40;
const int MapWidth = 40;
const int MapTextureSize = 30;
const float GroundY = (MapHeight - 1) * MapTextureSize - 90;
const float FallingSpeedCoef = 1.6f;
const float JumpingSpeedCoef = 1.3f;
