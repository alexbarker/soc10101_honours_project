#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 17th November 2018
// xxx.cpp - XXX.

class TextComponent : public Component {
public:
  TextComponent() = delete;
  explicit TextComponent(Entity* p, const std::string& str = "");
  void update(double dt) override;

  void render() override;

  ~TextComponent() override = default;

  void SetText(const std::string& str);
  sf::Text& getText();

protected:
  std::shared_ptr<sf::Font> _font;
  std::string _string;
  sf::Text _text;
  sf::Color _color;
};
