#pragma once
#include "engine.h"

class AddEntity {
public:
	static std::shared_ptr<Entity> makePlayer(Scene* scene, const sf::Vector2f& pos);
	static std::shared_ptr<Entity> makeTutorialPlayer(Scene* scene, const sf::Vector2f& pos);
	static std::shared_ptr<Entity> makeFakePlayer1(Scene* scene, const sf::Vector2f& pos, const sf::Vector2f& distance, float time);
	static std::shared_ptr<Entity> makeFakePlayer2(Scene* scene, const sf::Vector2f& pos, const sf::Vector2f& distance, float time);
	static void makeWalls(Scene* scene);
	static std::shared_ptr<Entity> makeSentinel(Scene* scene, const sf::Vector2f& pos);
	static std::shared_ptr<Entity> makeEnemy1(Scene* scene, const sf::Vector2f& pos);
	static std::shared_ptr<Entity> makeEnemy2(Scene* scene, const sf::Vector2f& pos);
	static std::shared_ptr<Entity> makeEnemy3(Scene* scene, const sf::Vector2f& pos);
	static std::shared_ptr<Entity> makeEnergyCrystal(Scene *scene, const sf::Vector2f &pos);
	AddEntity() = delete;

	/*	
	static std::shared_ptr<Entity> makeBubble(Scene *scene, const sf::Vector2f &pos);
	*/
};