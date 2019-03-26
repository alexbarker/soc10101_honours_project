#pragma once

#include <engine.h>

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 10th October 2018
// xxx.h - XXX.

// Output from a steering behaviour
struct SteeringOutput
{
	// Direction of travel
	sf::Vector2f direction;
	// Rotation of travel
	float rotation;
};

// Base class for steering behaviour
class StreeringBehaviour
{
public:
	virtual ~StreeringBehaviour() = default;

	// Gets the output from steering behaviour
	virtual SteeringOutput getSteering() const noexcept = 0;
};

// Seek steering behaviour
class Seek : public StreeringBehaviour
{
private:
	Entity* _character;
	Entity* _target;
	float _maxSpeed;
	
public:
	Seek() = delete;
	Seek(Entity* character, Entity* target, float maxSpeed)
		: _character(character), _target(target), _maxSpeed(maxSpeed) {}
	SteeringOutput getSteering() const noexcept;
};

class Flee : public StreeringBehaviour
{
private:
	Entity* _character;
	Entity* _target;
	float _maxSpeed;

public:
	Flee() = delete;
	Flee(Entity* character, Entity* target, float maxSpeed)
		: _character(character), _target(target), _maxSpeed(maxSpeed) {}
	SteeringOutput getSteering() const noexcept;
};