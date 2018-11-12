#include "cmp_path_follow.h"
#include "../astar.h"
#include <LevelSystem.h>

using namespace sf;
using namespace std;

void PathfinidngComponent::update(double dt)
{
	_elapsed += dt;
	if (_elapsed >= 0.1)
	{
		_elapsed = 0.0;
		if (_index < _path.size())
		{
			float new_x = ls::getOffset().x + _path[_index].x * ls::getTileSize();
			float new_y = ls::getOffset().y + _path[_index].y * ls::getTileSize();
			_parent->setPosition(Vector2f(new_x, new_y));
			++_index;
		}
	}
}

PathfinidngComponent::PathfinidngComponent(Entity* p) : Component(p) {}

void PathfinidngComponent::setPath(vector<Vector2i>& path)
{
	_index = 0;
	_path = path;
}