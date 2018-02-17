#include "Universe.hpp"


namespace entity
{

	Universe::Universe() {}

	Universe::Universe(std::string) {} //TODO: Implement this.

	Universe::~Universe() {}

	bool Universe::EntityHandleInput(def::time duration, def::entity_id entity_id, def::user_input input)
	{
		if (entity_registry.count(entity_id) == 0 || entity_registry[entity_id].dynamics == static_) return false;
		DynamicEntity& entity = *(entity_registry[entity_id].de_pointer);
		switch (input)
		{
		case def::turn_left:
			EntityTurnLeft(duration, entity);
			break;
		case def::turn_right:
			EntityTurnRight(duration, entity);
			break;
		case def::thrust:
			EntityThrust(duration, entity);
			break;
		case def::brake:
			EntityBrake(duration, entity);
			break;
		case def::fire:
			EntityFire(duration, entity);
			break;
		default:
			return false; //TODO: Do some warnlogging here.
		}
		return true;
	}

	void Universe::EntityTurnLeft(def::time duration, DynamicEntity& entity)
	{
	}

	void Universe::EntityTurnRight(def::time duration, DynamicEntity& entity)
	{
	}

	void Universe::EntityThrust(def::time duration, DynamicEntity& entity)
	{
	}

	void Universe::EntityBrake(def::time duration, DynamicEntity& entity)
	{
	}

	void Universe::EntityFire(def::time duration, DynamicEntity& entity)
	{
	}

	void Universe::UpdateState(def::time duration)
	{

	}

	void Universe::TestCollisions()
	{

	}

	void Universe::TestVisibility()
	{

	}


}
