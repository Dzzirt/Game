#include "../Headers/sounds_utils.h"
#include "../Headers/safe_delete.h"

std::string SoundTypeToString(SoundType type) {
	switch (type) {
		case HIT: 
			return "Hit";
		case MISS:
			return "Miss";
		case JUMP:
			return "Jump";
		case BONUS_PICK:
			return "Bonus";
		case GET_HIT:
			return "GetHit";
		default:
			return "invalid type";
	}
}


SoundsVec* CreateSounds() {
	std::vector<sf::Sound*>* sounds = new std::vector<sf::Sound*>(MaxGameSounds);
	SoundsInit(*sounds);
	return sounds;
}

SoundBuffersMap* CreateSoundBuffers(SoundNamesMap & sound_names) {
	SoundBuffersMap* buffers = new SoundBuffersMap();
	SoundBuffersInit(*buffers, sound_names);
	return buffers;
}

SoundNamesMap* CreateSoundNames() {
	SoundNamesMap * sound_names = new SoundNamesMap();
	SoundNamesMapInit(*sound_names);
	return sound_names;
}

void SoundsInit(SoundsVec & sounds) {
	auto setVolume = []()
	{
		sf::Sound * sound = new sf::Sound();
		sound->setVolume(SoundsVolume);
		return sound;
	};
	std::generate(sounds.begin(), sounds.end(), setVolume);
}


std::string GetRandomSoundNameByType(SoundType type, const SoundNamesMap & sound_names) {
	size_t count = GetSoundsCountFromType(type);
	return sound_names.at(type)->at(rand() % count);
}

unsigned int GetSoundsCountFromType(SoundType type) {
	switch (type) {
		case HIT: 
			return HitSoundsCount;
		case MISS: 
			return MissSoundsCount;
		case JUMP: 
			return JumpSoundsCount;
		case BONUS_PICK:
			return BonusSoundsCount;
		case GET_HIT:
			return GetHitSoundsCount;
	}
	return 0;
}

void PlaySounds(SoundType type, SoundsVec & sounds, SoundBuffersMap & buffers) {
	for (auto& sound : sounds) {
		if (sound->getStatus() == sf::SoundSource::Stopped)
		{
			sound->setBuffer(*buffers.at(type)->at(rand() % GetSoundsCountFromType(type)));
			sound->play();
			break;
		}
	}
}


void SoundBuffersInit(SoundBuffersMap & buffers, SoundNamesMap & sound_names) {
	buffers.insert({ HIT, CreateSoundBuffersVec(HIT, sound_names) });
	buffers.insert({ MISS, CreateSoundBuffersVec(MISS, sound_names) });
	buffers.insert({ BONUS_PICK, CreateSoundBuffersVec(BONUS_PICK, sound_names) });
	buffers.insert({ JUMP, CreateSoundBuffersVec(JUMP, sound_names) });
	buffers.insert({ GET_HIT, CreateSoundBuffersVec(GET_HIT, sound_names) });
}

void SoundNamesMapInit(SoundNamesMap & sound_names) {
	sound_names.insert({ HIT, CreateSoundNamesVec(HIT) });
	sound_names.insert({ MISS, CreateSoundNamesVec(MISS) });
	sound_names.insert({ BONUS_PICK, CreateSoundNamesVec(BONUS_PICK) });
	sound_names.insert({ JUMP, CreateSoundNamesVec(JUMP) });
	sound_names.insert({ GET_HIT, CreateSoundNamesVec(GET_HIT) });
}

std::vector<sf::SoundBuffer*>* CreateSoundBuffersVec(SoundType type, SoundNamesMap & sound_names) {
	std::vector<sf::SoundBuffer*>* buffers = new std::vector<sf::SoundBuffer*>();
	SoundBuffersVecInit(*buffers, *sound_names.at(type),  type);
	return buffers;
}
std::vector<std::string>* CreateSoundNamesVec(SoundType type) {
	std::vector<std::string>* names = new std::vector<std::string>();
	SoundNamesVecInit(*names, type);
	return names;
}

void SoundNamesVecInit(std::vector<std::string> & names, SoundType type) {
	size_t count = GetSoundsCountFromType(type);
	for (size_t i = 0; i < count; i++) {
		std::string name = SoundTypeToString(type);
		name += std::to_string(i + 1) + ".wav";
		names.push_back(name);
	}
}

void SoundBuffersVecInit(std::vector<sf::SoundBuffer*> & buffers, std::vector<std::string> & names, SoundType type) {
	size_t count = GetSoundsCountFromType(type);
	for (size_t i = 0; i < count; i++) {
		sf::SoundBuffer* buffer = new sf::SoundBuffer();
		buffer->loadFromFile("Resourses/Sounds/" + SoundTypeToString(type) + '/' + names.at(i));
		buffers.push_back(buffer);
	}
}

void DestroySoundBuffersVec(std::vector<sf::SoundBuffer*> *& buffers) {
	for (auto & buffer : *buffers)
	{
		SafeDelete(buffer);
	}
	SafeDelete(buffers);
}

void DestroySoundNamesVec(std::vector<std::string> *& names) {
	SafeDelete(names);
}

void DestroySoundBuffers(SoundBuffersMap *& buffers) {
	DestroySoundBuffersVec(buffers->at(HIT));
	DestroySoundBuffersVec(buffers->at(MISS));
	DestroySoundBuffersVec(buffers->at(BONUS_PICK));
	DestroySoundBuffersVec(buffers->at(JUMP));
	DestroySoundBuffersVec(buffers->at(GET_HIT));
	SafeDelete(buffers);
}

void DestroySoundsNames(SoundNamesMap *& names) {
	DestroySoundNamesVec(names->at(HIT));
	DestroySoundNamesVec(names->at(MISS));
	DestroySoundNamesVec(names->at(BONUS_PICK));
	DestroySoundNamesVec(names->at(JUMP));
	DestroySoundNamesVec(names->at(GET_HIT));
	SafeDelete(names);
}

void DestroySounds(SoundsVec *& sounds) {
	for (sf::Sound * sound : *sounds) {
		SafeDelete(sound);
	}
	SafeDelete(sounds);
}