#include "cmp_basic_movement.h"
#include <SFML\Window\Keyboard.hpp>
#include <engine.h>

using namespace sf;
using namespace std;

// Checks keyboard and moves the player
void BasicMovementComponent::update(double dt)
{
	Vector2f direction(0.0f, 0.0f);
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		direction.x -= 1.0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		direction.x += 1.0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		direction.y -= 1.0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		direction.y += 1.0;
	}

	move(normalize(direction) * _speed * (float)dt);
}

// Initialise the component
BasicMovementComponent::BasicMovementComponent(Entity* p)
	:_speed(200.f), Component(p) {}


// Checks if the proposed move is valid
bool BasicMovementComponent::validMove(const sf::Vector2f& pos)
{
	if (pos.x < 0.0f || pos.x > Engine::GetWindow().getSize().x ||
		pos.y < 0.0f || pos.y > Engine::GetWindow().getSize().y)
	{
		return false;
	}
	return true;
}

// Moves the component's parent
void BasicMovementComponent::move(const sf::Vector2f& pos)
{
	auto new_pos = _parent->getPosition() + pos;
	if (validMove(new_pos))
	{
		_parent->setPosition(new_pos);
	}
}

// Moves the component's parent
void BasicMovementComponent::move(float x, float y)
{
	move(Vector2f(x, y));
}