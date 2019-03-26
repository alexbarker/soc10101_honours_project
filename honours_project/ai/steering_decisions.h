#pragma once

#include <engine.h>
#include "components/cmp_decision_tree.h"
#include "components/cmp_state_machine.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 10th October 2018
// xxx.h - XXX.

class DistanceDecision : public Decision
{
private:
	std::shared_ptr<Entity> _player;
	float _distance;
protected:
	std::shared_ptr<DecisionTreeNode> getBranch(Entity* owner) final
	{
		double dist = sf::length(owner->getPosition() - _player->getPosition());
		if (dist < _distance)
			return _trueNode;
		else
			return _falseNode;
	}
public:
	DistanceDecision(std::shared_ptr<Entity> player, float distance, std::shared_ptr<DecisionTreeNode> trueNode, std::shared_ptr<DecisionTreeNode> falseNode)
		: _player(player), _distance(distance), Decision(trueNode, falseNode)
	{
	}
};

class StationaryDecision : public DecisionTreeNode
{
public:
	void makeDecision(Entity* owner) final
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("stationary");
	}
};

class SeekDecision : public DecisionTreeNode
{
public:
	void makeDecision(Entity* owner) final
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("seek");
	}
};

class FleeDecision : public DecisionTreeNode
{
public:
	void makeDecision(Entity* owner) final
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("flee");
	}
};