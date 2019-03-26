#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 17th November 2018
// xxx.cpp - XXX.

using namespace std;
using namespace sf;

void TextComponent::update(double dt) { _text.setPosition(_parent->getPosition()); }

void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
    : Component(p), _string(str) {
  _text.setString(_string);
  _font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
  _text.setFont(*_font);
  _text.setCharacterSize(20);
}

Text& TextComponent::getText() { return _text; }

void TextComponent::SetText(const std::string& str) {
  _string = str;
  _text.setString(_string);
}


