#include "steering.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 10th October 2018
// xxx.h - XXX.

using	namespace sf;

SteeringOutput Seek::getSteering() const noexcept
{
	SteeringOutput steering;
	steering.direction = _target->getPosition() - _character->getPosition();
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = 0.0f;
	return steering;
}

SteeringOutput Flee::getSteering() const noexcept
{
	SteeringOutput steering;
	steering.direction = _character->getPosition() - _target->getPosition();
	steering.direction = normalize(steering.direction);
	steering.direction *= _maxSpeed;
	steering.rotation = 0.0f;
	return steering;
}