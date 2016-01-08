#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

const int StatesCount = 3;

struct StartGameButton
{
	enum class State {
		Normal,
		Hovered,
		Pressed
	};

	void Init();

	bool DoesHit(sf::Vector2f const& point) const;
	void SetPosition(sf::Vector2f const& point);
	void Draw(sf::RenderWindow &window);
	/// @returns true if event handled by button.
	bool OnEvent(sf::Event const& event);
	void SetState(State newState);

	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect curr_state;

	std::function<void()> handler;
	State state;
};
