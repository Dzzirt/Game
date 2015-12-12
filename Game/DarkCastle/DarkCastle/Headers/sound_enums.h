#pragma once


enum SoundType {
	HIT,
	MISS,
	JUMP,
	BONUS_PICK,
	GET_HIT,
};

const int HitSoundsCount = 6;
const int StepSoundsCount = 1;
const int BonusSoundsCount = 3;
const int JumpSoundsCount = 2;
const int MissSoundsCount = 2;
const int GetHitSoundsCount = 1;

const int MaxGameSounds = 5;
const float SoundsVolume = 25.f;
const float BGMusicVolume = 50.f;

