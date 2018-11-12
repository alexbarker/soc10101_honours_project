#pragma once

#include <SFML/Graphics.hpp>
//#include "cmp_sprite.h"

namespace Renderer {
void initialise(sf::RenderWindow&);

void shutdown();

void update(const double&);

void queue(const sf::Drawable* s);

void queueAnimation(const sf::Sprite& sprite);

void render();
}; // namespace Renderer
