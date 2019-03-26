#include "add_entity.h"
#include "animation.h"
#include "ai/steering.h"
#include "ai/steering_states.h"
#include "ai/steering_decisions.h"
#include "components/cmp_state_machine.h"
#include "components/cmp_path_follow.h"
#include "components/cmp_enemy_ai.h"
#include "components/cmp_decision_tree.h"
#include "components/cmp_ai_steering.h"
#include "components/cmp_basic_movement.h"
#include "components/cmp_actor_movement.h"
#include "components/cmp_sprite.h"
#include "components/cmp_hurt_player.h"
#include "system_resources.h"
#include "components/cmp_physics.h"
#include "components/cmp_player_physics.h"
#include "components/cmp_enemy_turret.h"
#include "components/cmp_bullet.h"
#include <LevelSystem.h>
#include <SFML/Graphics/Transformable.hpp>

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 26th March 2019
// add_entity.cpp - This file is used to create and expand entities.

using namespace sf;
using namespace std;

std::shared_ptr<Entity> AddEntity::makePlayer(Scene* scene, const Vector2f& pos) {
	auto player = scene->makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->addTag("player");

	auto s = player->addComponent<ShapeComponent>();
	s->setShape<CircleShape>(10.f, 10.f);
	s->getShape().setFillColor(Color::White);
	s->getShape().setOrigin(Vector2f(5.f, 5.f));
	/*
	auto animation = player->addComponent<AnimationComponent>(Vector2f(46.f, 46.f));
	sf::Texture s = *Resources::load<Texture>("PlayerSpritesheet.png");
	animation->setSpritesheet(s);
	animation->setFrameCount(15);
	animation->setFrameTime(0.06f);
	*/
	player->addComponent<PlayerPhysicsComponent>(Vector2f(10.f, 10.f));

	return player;
}

void AddEntity::makeWalls(Scene* scene) {
	auto walls = ls::findTiles(ls::WALL);
	for (auto w : walls) {
		auto pos = ls::getTilePosition(w);
		pos += Vector2f(10.f, 10.f);
		auto e = scene->makeEntity();
		e->setPosition(pos);
		e->addComponent<PhysicsComponent>(false, Vector2f(20.f, 20.f));
	}
}

