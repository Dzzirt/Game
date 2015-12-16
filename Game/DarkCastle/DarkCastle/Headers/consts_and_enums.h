#pragma once
#include <SFML/System/Time.hpp>

	const unsigned int WindowWidth = 800;
	const unsigned int WindowHeight = 600;


	const float FallingSpeedCoef = 1.6f;
	const float JumpingSpeedCoef = 1.3f;

	const float ForceOfGravity = 200.f;

	const int XEnemySize = 48;
	const int YEnemySize = 84;

	const float AtkUpDuration = 10.f;
	const float SpeedUpDuration = 5.f;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	enum State {
		LEFT,
		RIGHT,
		NONE
	};

	enum Type {
		PLAYER,
		SPEARMAN,
		SWORDSMAN
	};

	enum BonusType {
		HP_REGEN,
		SPEED_UP,
		ATK_UP,
	};

	enum AnimType {
		MOVE,
		ATTACK,
		JUMPING,
		GRAVITY,
	};


