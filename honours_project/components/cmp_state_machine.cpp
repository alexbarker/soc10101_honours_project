#include "cmp_state_machine.h"

// SOC10101 - Honours Project (40 Credits)
// Snake Prototype 3
// Version 0.x.x
// Alexander Barker 
// 40333139
// Last Updated on 17th November 2018
// xxx.cpp - XXX.

using namespace std;

StateMachineComponent::StateMachineComponent(Entity* p)
	: _current_state(nullptr), Component(p)
{
}

void StateMachineComponent::update(double dt)
{
	if (_current_state != nullptr)
		_current_state->execute(_parent, dt);
}

void StateMachineComponent::addState(const string& name, shared_ptr<State> state) noexcept
{
	_states[name] = state;
}

shared_ptr<State> StateMachineComponent::getState(const string &name) const noexcept
{
	auto found = _states.find(name);
	if (found != _states.end())
	{
		return found->second;
	}
	else
	{
		return nullptr;
	}
}

void StateMachineComponent::removeState(const string &name) noexcept
{
	_states.erase(name);
}

void StateMachineComponent::changeState(const string &name) noexcept
{
	auto found = _states.find(name);
	if (found != _states.end())
	{
		_current_state = found->second;
		_current_state_name = name;
	}
}