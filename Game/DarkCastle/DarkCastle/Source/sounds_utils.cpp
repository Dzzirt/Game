#include "../Headers/sounds_utils.h"

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
	std::vector<sf::Sound*>* sounds = new std::vector<sf::Sound*>();
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
	for (size_t i = 0; i < MaxGameSounds; i++) {
		sf::Sound * sound = new sf::Sound();
		sound->setVolume(SoundsVolume);
		sounds.push_back(sound);
	}
}


std::string GetRandomSoundNameByType(SoundType type, const SoundNamesMap & sound_names) {
	int count = GetSoundsCountFromType(type);
	return sound_names.at(type).at(rand() % count);
}

int GetSoundsCountFromType(SoundType type) {
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

void PlaySound(SoundType type, SoundsVec & sounds, SoundBuffersMap & buffers) {
	for (size_t i = 0; i < sounds.size(); i++) {
		if (sounds[i]->getStatus() == sf::SoundSource::Stopped) {
			sounds[i]->setBuffer(*buffers.at(type).at(rand() % GetSoundsCountFromType(type)));
			sounds[i]->play();
			break;
		}
	}
}

void SoundBuffersInit(SoundBuffersMap & buffers, SoundNamesMap & sound_names) {
	buffers.insert(std::pair<SoundType, std::vector<sf::SoundBuffer*>>(HIT, *CreateSoundBuffersVec(HIT,sound_names)));
	buffers.insert(std::pair<SoundType, std::vector<sf::SoundBuffer*>>(MISS, *CreateSoundBuffersVec(MISS, sound_names)));
	buffers.insert(std::pair<SoundType, std::vector<sf::SoundBuffer*>>(BONUS_PICK, *CreateSoundBuffersVec(BONUS_PICK, sound_names)));
	buffers.insert(std::pair<SoundType, std::vector<sf::SoundBuffer*>>(JUMP, *CreateSoundBuffersVec(JUMP, sound_names)));
	buffers.insert(std::pair<SoundType, std::vector<sf::SoundBuffer*>>(GET_HIT, *CreateSoundBuffersVec(GET_HIT, sound_names)));
}

void SoundNamesMapInit(SoundNamesMap & sound_names) {
	sound_names.insert(std::pair<SoundType, std::vector<std::string>>(HIT, *CreateSoundNamesVec(HIT)));
	sound_names.insert(std::pair<SoundType, std::vector<std::string>>(MISS, *CreateSoundNamesVec(MISS)));
	sound_names.insert(std::pair<SoundType, std::vector<std::string>>(BONUS_PICK, *CreateSoundNamesVec(BONUS_PICK)));
	sound_names.insert(std::pair<SoundType, std::vector<std::string>>(JUMP, *CreateSoundNamesVec(JUMP)));
	sound_names.insert(std::pair<SoundType, std::vector<std::string>>(GET_HIT, *CreateSoundNamesVec(GET_HIT)));
}

std::vector<sf::SoundBuffer*>* CreateSoundBuffersVec(SoundType type, SoundNamesMap & sound_names) {
	std::vector<sf::SoundBuffer*>* buffers = new std::vector<sf::SoundBuffer*>();
	SoundBuffersVecInit(*buffers, sound_names.at(type),  type);
	return buffers;
}
std::vector<std::string>* CreateSoundNamesVec(SoundType type) {
	std::vector<std::string>* names = new std::vector<std::string>();
	SoundNamesVecInit(*names, type);
	return names;
}

void SoundNamesVecInit(std::vector<std::string> & names, SoundType type) {
	int count = GetSoundsCountFromType(type);
	for (size_t i = 0; i < count; i++) {
		std::string name = SoundTypeToString(type);
		std::stringstream number;
		number << i + 1;
		name += number.str() + ".wav";
		names.push_back(name);
	}
}

void SoundBuffersVecInit(std::vector<sf::SoundBuffer*> & buffers, std::vector<std::string> & names, SoundType type) {
	int count = GetSoundsCountFromType(type);
	for (size_t i = 0; i < count; i++) {
		sf::SoundBuffer* buffer = new sf::SoundBuffer();
		buffer->loadFromFile("Resourses/Sounds/" + SoundTypeToString(type) + '/' + names.at(i));
		buffers.push_back(buffer);
	}
}

void DestroySoundBuffersVec(std::vector<sf::SoundBuffer*> & buffers) {
	for (size_t i = 0; i < buffers.size(); i++) {
		delete buffers[i];
	}
}

void DestroySoundBuffers(SoundBuffersMap & buffers) {
	DestroySoundBuffersVec(buffers.at(HIT));
	DestroySoundBuffersVec(buffers.at(MISS));
	DestroySoundBuffersVec(buffers.at(BONUS_PICK));
	DestroySoundBuffersVec(buffers.at(JUMP));
	delete &buffers;
}

void DestroySoundsNames(SoundNamesMap& names) {
	delete &names;
}

void DestroySounds(SoundsVec& sounds) {
	for (sf::Sound * sound : sounds) {
		delete sound;
	}
	delete &sounds;
}