#include "Universe.hpp"


namespace entity
{

	Universe::Universe() {}

	Universe::Universe(std::string) {} //TODO: Implement this.

	Universe::~Universe() {}

	bool Universe::EntityHandleInput(def::time duration, def::entity_id entity_id, def::user_input input)
	{
		if (entity_registry.count(entity_id) == 0 ||
			entity_registry[entity_id].dynamics == static_ ||
			entity_registry[entity_id].engine == pre_programmed) return false;
		DynamicEntity& entity = *(entity_registry[entity_id].de_pointer);
		switch (input)
		{
		case def::turn_left:
			EntityTurnLeft(duration, entity, entity_registry[entity_id].engine);
			break;
		case def::turn_right:
			EntityTurnRight(duration, entity, entity_registry[entity_id].engine);
			break;
		case def::thrust:
			EntityThrust(duration, entity, entity_registry[entity_id].engine);
			break;
		case def::brake:
			EntityBrake(duration, entity, entity_registry[entity_id].engine);
			break;
		case def::fire:
			EntityFire(duration, entity);
			break;
		default:
			return false; //TODO: Do some warnlogging here.
		}
		return true;
	}

	void Universe::EntityTurnLeft(def::time duration, DynamicEntity& entity, engine_type engine)
	{
		geo::degree rotation = entity.angular_velocity * duration.count();
		EntityTurnDegree(entity, engine, rotation);
	}

	void Universe::EntityTurnRight(def::time duration, DynamicEntity& entity, engine_type engine)
	{
		geo::degree rotation = entity.angular_velocity * duration.count();
		EntityTurnDegree(entity, engine, -rotation);
	}

	void Universe::EntityThrust(def::time duration, DynamicEntity& entity, engine_type engine)
	{
		entity.velocity = geo::add(entity.velocity, geo::mul(entity.acceleration, duration.count()));
	}

	void Universe::EntityBrake(def::time duration, DynamicEntity& entity, engine_type engine)
	{
		entity.velocity = geo::add(entity.velocity, geo::mul(entity.acceleration, -duration.count()));
	}

	void Universe::EntityFire(def::time duration, DynamicEntity& entity)
	{
		//TODO: Implement this.
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

	void Universe::EntityTurnDegree(DynamicEntity& entity, engine_type engine, geo::degree rotation)
	{
		switch (engine)
		{
		case entity::para_inertial:
			geo::rotate_point_2d(entity.velocity, rotation);
			[[fallthrough]];
		case entity::inertial:
			geo::rotate_point_2d(entity.acceleration, rotation);
			[[fallthrough]];
		case entity::anti_intertial:
			entity.orientation += rotation;
			break;
		default:
			//TODO: Warnlogging.
			break;
		}
	}

}
