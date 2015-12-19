#include "../Headers/game_sounds.h"
#include "../Headers/safe_delete.h"

GameSounds* CreateGameSounds() {
	GameSounds* game_sounds = new GameSounds();
	GameSoundsInit(*game_sounds);
	return game_sounds;
}

void GameSoundsInit(GameSounds& game_sounds) {
	game_sounds.bg_sound.openFromFile("Resourses/Sounds/bg.ogg");
	game_sounds.bg_sound.setLoop(true);
	game_sounds.bg_sound.setVolume(BGMusicVolume);
	game_sounds.bg_sound.play();
	game_sounds.sound_names = CreateSoundNames();
	game_sounds.sound_buffers = CreateSoundBuffers(*game_sounds.sound_names);
	game_sounds.sounds = CreateSounds();
}

void DestroyGameSounds(GameSounds *& game_sounds) {
	DestroySoundsNames(game_sounds->sound_names);
	DestroySoundBuffers(game_sounds->sound_buffers);
	DestroySounds(game_sounds->sounds);
	SafeDelete(game_sounds);
}