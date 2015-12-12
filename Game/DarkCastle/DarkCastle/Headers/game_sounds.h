#pragma once
#include "SFML/Audio.hpp"
#include "sounds_utils.h"
#include <map>

struct GameSounds {
	sf::Music bg_sound;
	SoundsVec* sounds;
	SoundBuffersMap* sound_buffers;
	SoundNamesMap* sound_names;
};

GameSounds* CreateGameSounds();

void GameSoundsInit(GameSounds & game_sounds);

void DestroyGameSounds(GameSounds & game_sounds);