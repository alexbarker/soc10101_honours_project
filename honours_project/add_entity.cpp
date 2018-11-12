#include "add_entity.h"
#include "animation.h"
#include "steering.h"
#include "steering_states.h"
#include "steering_decisions.h"
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

// SET09121 2017-8 TR2 001 - Games Engineering
// Picobots
// Version 0.7.0
// Alexander Barker 
// 40333139
// Last Updated on 1st May 2018
// add_entity.cpp - This file is used to create and expand entities.

using namespace sf;
using namespace std;

std::shared_ptr<Entity> AddEntity::makePlayer(Scene* scene, const Vector2f& pos) {
	auto player = scene->makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->addTag("player");

	auto animation = player->addComponent<AnimationComponent>(Vector2f(46.f, 46.f));
	sf::Texture s = *Resources::load<Texture>("PlayerSpritesheet.png");
	animation->setSpritesheet(s);
	animation->setFrameCount(15);
	animation->setFrameTime(0.06f);

	player->addComponent<PlayerPhysicsComponent>(Vector2f(22.f, 17.f));

	return player;
}

std::shared_ptr<Entity> AddEntity::makeFakePlayer1(Scene* scene, const Vector2f& pos, const sf::Vector2f& distance, float time) {
	auto fakePlayer1 = scene->makeEntity();
	fakePlayer1->setPosition(pos);
	fakePlayer1->addTag("fakePlayer1");

	auto physics = fakePlayer1->addComponent<PhysicsComponent>(true, sf::Vector2f(46.f, 46.f));
	physics->impulse(sf::Vector2f(-7.5f, 0));
	physics->setMass(25000.f);

	auto animation = fakePlayer1->addComponent<AnimationComponent>(Vector2f(46.f, 46.f));
	sf::Texture s = *Resources::load<Texture>("PlayerSpritesheet.png");
	animation->setSpritesheet(s);
	animation->setFrameCount(15);
	animation->setFrameTime(0.07f);

	return fakePlayer1;
}

std::shared_ptr<Entity> AddEntity::makeFakePlayer2(Scene* scene, const Vector2f& pos, const sf::Vector2f& distance, float time) {
	auto makeFakePlayer2 = scene->makeEntity();
	makeFakePlayer2->setPosition(pos);
	makeFakePlayer2->addTag("fakePlayer2");

	auto physics = makeFakePlayer2->addComponent<PhysicsComponent>(true, sf::Vector2f(46.f, 46.f));
	physics->impulse(sf::Vector2f(7.5f, 0));
	physics->setMass(25000.f);

	auto animation = makeFakePlayer2->addComponent<AnimationComponent>(Vector2f(46.f, 46.f));
	sf::Texture s = *Resources::load<Texture>("PlayerSpritesheet.png");
	animation->setSpritesheet(s);
	animation->setFrameCount(15);
	animation->setFrameTime(0.07f);

	return makeFakePlayer2;
}

std::shared_ptr<Entity> AddEntity::makeTutorialPlayer(Scene* scene, const Vector2f& pos) {
	auto player = scene->makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->addTag("player");

	auto animation = player->addComponent<AnimationComponent>(Vector2f(46.f, 46.f));
	sf::Texture s = *Resources::load<Texture>("PlayerSpritesheet.png");
	animation->setSpritesheet(s);
	animation->setFrameCount(15);
	animation->setFrameTime(0.06f);

	player->addComponent<PlayerPhysicsComponent>(Vector2f(22.f, 17.f));

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

std::shared_ptr<Entity> AddEntity::makeEnergyCrystal(Scene* scene, const Vector2f& pos) {
	auto makeEnergyCrystal = scene->makeEntity();
	makeEnergyCrystal->setPosition(pos);
	makeEnergyCrystal->addTag("crystal");
	//makeEnergyCrystal->addComponent<PhysicsComponent>(false, Vector2f(20.f, 20.f));

	auto animation = makeEnergyCrystal->addComponent<AnimationComponent>(Vector2f(30.f, 30.f));
	sf::Texture s = *Resources::load<Texture>("crystal.png");
	animation->setSpritesheet(s);
	animation->setFrameCount(1);
	animation->setFrameTime(0.06f);

	return makeEnergyCrystal;
}

std::shared_ptr<Entity> AddEntity::makeEnemy1(Scene* scene, const Vector2f& pos) {
	auto makeEnemy1 = scene->makeEntity();
	makeEnemy1->setPosition(pos);
	makeEnemy1->addComponent<HurtComponent>();
	auto s = makeEnemy1->addComponent<ShapeComponent>();
	s->setShape<CircleShape>(10.f, 10.f);
	s->getShape().setFillColor(Color::Red);
	s->getShape().setOrigin(Vector2f(16.f, 16.f));
	makeEnemy1->addComponent<EnemyAIComponent>();
	return makeEnemy1;
}

std::shared_ptr<Entity> AddEntity::makeEnemy2(Scene* scene, const Vector2f& pos) {
	auto makeEnemy2 = scene->makeEntity();
	makeEnemy2->setPosition(pos);
	auto s = makeEnemy2->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(16.f, 3);
	s->getShape().setFillColor(Color::Red);
	s->getShape().setOrigin(16.f, 16.f);
	makeEnemy2->addComponent<EnemyTurretComponent>();

	return makeEnemy2;
}
std::shared_ptr<Entity> AddEntity::makeEnemy3(Scene* scene, const Vector2f& pos) {
	auto makeEnemy3 = scene->makeEntity();
	makeEnemy3->setPosition(pos);
	makeEnemy3->addComponent<BulletComponent>(120.f);
	makeEnemy3->addComponent<HurtComponent>();
	auto s = makeEnemy3->addComponent<ShapeComponent>();
	s->setShape<sf::CircleShape>(50.f);
	s->getShape().setFillColor(Color::Black);
	s->getShape().setOrigin(40.f, 40.f);
	auto p = makeEnemy3->addComponent<PhysicsComponent>(true, Vector2f(100.f, 100.f));
	p->setRestitution(.4f);
	p->setFriction(.0f);
	p->impulse(Vector2f(0.f, 0));
	p->setMass(0.f);
	p->setGravityScale(0);

	return makeEnemy3;
}

std::shared_ptr<Entity> AddEntity::makeSentinel(Scene* scene, const Vector2f& pos) {

	auto makeSentinel = scene->makeEntity();
	makeSentinel->setPosition(pos);
	makeSentinel->addTag("sentinel");
	auto s = makeSentinel->addComponent<ShapeComponent>();
	s->setShape<CircleShape>(10.0f);
	s->getShape().setFillColor(Color::Blue);
	makeSentinel->addComponent<HurtComponent>();

	auto x = scene->ents.find("player")[0];
	auto sm = makeSentinel->addComponent<StateMachineComponent>();
	sm->addState("seek", make_shared<SeekState>(makeSentinel, x));

	auto decision = make_shared<DistanceDecision>(
		x,
		50.0f,
		make_shared<FleeDecision>(),
		make_shared<DistanceDecision>(
			x,
			100.0f,
			make_shared<RandomDecision>(
				make_shared<SeekDecision>(),
				make_shared<StationaryDecision>()),
			make_shared<SeekDecision>()
			)
		);

	makeSentinel->addComponent<DecisionTreeComponent>(decision);

	return makeSentinel;
}
