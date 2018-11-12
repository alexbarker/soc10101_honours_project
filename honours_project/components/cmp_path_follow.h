#pragma once
#include <ecm.h>

class PathfinidngComponent : public Component
{
protected:
	std::vector<sf::Vector2i> _path;
	size_t _index = 0;
	double _elapsed = 0.0f;

public:
	void update(double) override;
	void render() override {};
	void setPath(std::vector<sf::Vector2i>& path);
	explicit PathfinidngComponent(Entity* p);
	PathfinidngComponent() = delete;
};