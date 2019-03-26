#include "cmp_enemy_ai.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 17th November 2018
// cmp_enemy_ai.cpp

using namespace std;
using namespace sf;

void EnemyAIComponent::update(double dt) {
  auto mov = _direction * (float)(dt * _speed);
  mov.x += _direction.x * 16.f;
  if (!validMove(_parent->getPosition() + mov)) {
    _direction *= -1.f;
  }

  move(_direction * (float)(dt * _speed));
  ActorMovementComponent::update(dt);
}

EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p) {
  _direction = Vector2f(1.0f, 0);
  _speed = 100.0f;
}
