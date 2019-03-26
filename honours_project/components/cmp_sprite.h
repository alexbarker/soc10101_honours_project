#pragma once

#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 17th November 2018
// xxx.cpp - XXX.

class SpriteComponent : public Component {
protected:
  std::shared_ptr<sf::Sprite> _sprite;

public:
  SpriteComponent() = delete;

  explicit SpriteComponent(Entity* p);
  void update(double dt) override;
  void render() override;

  sf::Sprite& getSprite() const;

  template <typename... Targs> void setSprite(Targs... params) {
    _sprite.reset(new sf::Sprite(params...));
  }
};

class ShapeComponent : public Component {
protected:
  std::shared_ptr<sf::Shape> _shape;

public:
  ShapeComponent() = delete;

  explicit ShapeComponent(Entity* p);

  void update(double dt) override;
  void render() override;
  sf::Shape& getShape() const;
  template <typename T, typename... Targs> void setShape(Targs... params) {
    _shape.reset(new T(params...));
  }
};