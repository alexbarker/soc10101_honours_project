#pragma once

#include "cmp_actor_movement.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 17th November 2018
// cmp_enemy_ai.h

class EnemyAIComponent : public ActorMovementComponent {
protected:
  sf::Vector2f _direction;

public:
  void update(double dt) override;

  explicit EnemyAIComponent(Entity* p);

  EnemyAIComponent() = delete;
};
