#pragma once
#include "SFML/Audio.hpp"
#include <map>
#include "sound_enums.h"
#include <sstream>

typedef std::map<SoundType, std::vector<sf::SoundBuffer*>> SoundBuffersMap;
typedef std::map<SoundType, std::vector<std::string>> SoundNamesMap;
typedef std::vector<sf::Sound*> SoundsVec;







SoundBuffersMap* CreateSoundBuffers(SoundNamesMap & sound_names);

SoundNamesMap* CreateSoundNames();

SoundsVec* CreateSounds();

void PlaySounds(SoundType type, SoundsVec & sounds, SoundBuffersMap & buffers);

void SoundsInit(SoundsVec & sounds);

void SoundBuffersInit(SoundBuffersMap & buffers, SoundNamesMap & sound_names);

std::vector<sf::SoundBuffer*>* CreateSoundBuffersVec(SoundType type, SoundNamesMap & sound_names);

void SoundBuffersVecInit(std::vector<sf::SoundBuffer*> & buffers, std::vector<std::string> & names, SoundType type);

void SoundNamesMapInit(SoundNamesMap & sound_names);

std::vector<std::string>* CreateSoundNamesVec(SoundType type);

void SoundNamesVecInit(std::vector<std::string> & names, SoundType type);

void DestroySoundBuffers(SoundBuffersMap & buffers);

void DestroySoundBuffersVec(std::vector<sf::SoundBuffer*> & buffers);

void DestroySoundsNames(SoundNamesMap & names);

void DestroySounds(SoundsVec & sounds);


unsigned int GetSoundsCountFromType(SoundType type);

std::string GetRandomSoundNameByType(SoundType type, const SoundNamesMap & sound_names);

std::string SoundTypeToString(SoundType type);