#include "enemy_states.h"
#include "components/cmp_sprite.h"

using namespace sf;

void NormalState::execute(Entity *owner, double dt) noexcept
{
	auto s = owner->GetCompatibleComponent<ShapeComponent>()[0];
	// or get_components?
	s->getShape().setFillColor(Color::Blue);

	if (length(owner->getPosition() - _player->getPosition()) < 100.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("near");
	}
}

void NearState::execute(Entity *owner, double dt) noexcept
{
	auto s = owner->get_components<ShapeComponent>()[0];
	s->getShape().setFillColor(Color::Green);

	if (length(owner->getPosition() - _player->getPosition()) > 100.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("normal");
	}
}