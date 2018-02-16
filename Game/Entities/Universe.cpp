#include "Universe.hpp"


namespace entity
{

	Universe::Universe() {}

	Universe::Universe(std::string) {} //TODO: Implement this.

	Universe::~Universe() {}

	bool Universe::EntityHandleInput(def::time duration, def::entity_id entity_id, def::user_input input)
	{
		switch (input)
		{
		case def::turn_left:
			return EntityTurnLeft(duration, entity_id);
		case def::turn_right:
			return EntityTurnRight(duration, entity_id);
		case def::thrust:
			return EntityThrust(duration, entity_id);
		case def::brake:
			return EntityBrake(duration, entity_id);
		case def::fire:
			return EntityFire(duration, entity_id);
		default:
			return false; //TODO: Do some warnlogging here.
		}
	}

	bool Universe::EntityTurnLeft(def::time duration, def::entity_id entity_id)
	{

	}

	bool Universe::EntityTurnRight(def::time duration, def::entity_id entity_id)
	{

	}

	bool Universe::EntityThrust(def::time duration, def::entity_id entity_id)
	{

	}

	bool Universe::EntityBrake(def::time duration, def::entity_id entity_id)
	{

	}

	bool Universe::EntityFire(def::time duration, def::entity_id entity_id)
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
