#include "../Headers/button.h"
#include "iostream"
using namespace sf;

void StartGameButton::Init()
{
	texture.loadFromFile("Resourses/Screens/start_game_buttons.png");
	curr_state = IntRect(0, 0, texture.getSize().x, texture.getSize().y / StatesCount);
	sprite.setTexture(texture);
	SetPosition(Vector2f(0, 0));
	SetState(State::Normal);
}

bool StartGameButton::DoesHit(sf::Vector2f const& point) const
{
	return sprite.getGlobalBounds().contains(point);
}

void StartGameButton::SetPosition(const Vector2f& point)
{
	sprite.setPosition(point.x, point.y);
}

void StartGameButton::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

bool StartGameButton::OnEvent(const Event& event)
{
	auto mouseButtonHits = [&]() {
		Vector2f mousePoint(float(event.mouseButton.x), float(event.mouseButton.y));
		return (event.mouseButton.button == sf::Mouse::Left) && DoesHit(mousePoint);
	};
	auto mouseMoveHits = [&]() {
		Vector2f mousePoint(float(event.mouseMove.x), float(event.mouseMove.y));
		return DoesHit(mousePoint);
	};

	switch (event.type) {
	case sf::Event::MouseMoved:
		if (state != State::Pressed)
		{
			SetState(mouseMoveHits() ? State::Hovered : State::Normal);
		}
		break;
	case sf::Event::MouseButtonPressed:
		if (mouseButtonHits())
		{
			SetState(State::Pressed);
			return true;
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (state == State::Pressed)
		{
			SetState(mouseButtonHits() ? State::Hovered : State::Normal);
			if (handler)
			{
				handler();
			}
			return true;
		}
		break;
	case sf::Event::MouseLeft:
		SetState(State::Normal);
		break;
	default:
		break;
	}

	return false;
}

void StartGameButton::SetState(StartGameButton::State newState)
{
	state = newState;
	switch (newState)
	{
	case State::Normal:
		curr_state.top = 0;
		sprite.setTextureRect(curr_state);
		break;
	case State::Hovered:
		curr_state.top = int(texture.getSize().y / StatesCount);
		sprite.setTextureRect(curr_state);
		break;
	case State::Pressed:
		curr_state.top = int((texture.getSize().y / StatesCount) * 2.f);
		sprite.setTextureRect(curr_state);
		break;
	}
}
