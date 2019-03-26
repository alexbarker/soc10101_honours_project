#pragma once

#include "../components/cmp_state_machine.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.1.0
// Alexander Barker 
// 40333139
// Last Updated on 10th October 2018
// xxx.h - XXX.

class NormalState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:
	NormalState(std::shared_ptr<Entity> player)
		: _player(player)
	{
	}
	void execute(Entity*, double) noexcept override;
};

class NearState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:
	NearState(std::shared_ptr<Entity> player)
		: _player(player)
	{
	}
	void execute(Entity*, double) noexcept override;
};