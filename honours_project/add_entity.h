#pragma once
#include "engine.h"

class AddEntity {
public:
	static std::shared_ptr<Entity> makePlayer(Scene* scene, const sf::Vector2f& pos);
	static void makeWalls(Scene* scene);

	AddEntity() = delete;

};