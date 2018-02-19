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
		switch (engine)
		{
		case entity::para_inertial:
			[[fallthrough]];
		case entity::inertial:
			entity.velocity = geo::add(entity.velocity, geo::mul(entity.acceleration, duration.count()));
			break;
		case entity::anti_intertial:
			entity.velocity = geo::point_2d_rotated({ entity.max_speed, 0 }, entity.orientation);
			break;
		default:
			//TODO: Warnlogging.
			break;
		}
	}

	void Universe::EntityBrake(def::time duration, DynamicEntity& entity, engine_type engine)
	{
		switch (engine)
		{
		case entity::para_inertial:
			[[fallthrough]];
		case entity::inertial:
			entity.velocity = geo::sub(entity.velocity, geo::mul(entity.acceleration, duration.count()));
			break;
		case entity::anti_intertial:
			entity.velocity = geo::point_2d_rotated({ -entity.max_speed, 0 }, entity.orientation);
			break;
		default:
			//TODO: Warnlogging.
			break;
		}
	}

	void Universe::EntityFire(def::time duration, DynamicEntity& entity)
	{
		//TODO: Implement this.
	}

	void Universe::SpawnEntity(def::entity_id entity,
	                 def::owner_id owner,
	                 engine_type engine,
	                 dynamics_class dynamics,
	                 visibility_class visibility,
	                 collidability_class collidability,
	                 geo::point_2d position)
	{
		if (entity_registry.count(entity) > 0) return;

		EntityHandle handle{ owner, engine, dynamics, visibility, collidability, nullptr };
		if (dynamics == dynamic)
		{
			DynamicEntity dynamic_entity;
			dynamic_entity.position = position;
			auto index = dynamic_entities[visibility][collidability].InsertAtFirstGap(dynamic_entity);
			handle.de_pointer = &(dynamic_entities[visibility][collidability].elements[index].element); //TODO: Add a member method for this.
		}
		else
		{
			StaticEntity static_entity;
			static_entity.position = position;
			auto index = static_entities[visibility][collidability].InsertAtFirstGap(static_entity);
			handle.se_pointer = &(static_entities[visibility][collidability].elements[index].element);
		}
		entity_registry[entity] = handle;
	}

	void Universe::UpdateState(def::time duration)
	{
		for (visibility_class v : {visible, invisible})
		{
			for (collidability_class c : {collidable, uncollidable})
			{
				for (DynamicEntity& entity : dynamic_entities[v][c])
				{
					geo::real speed = geo::length(entity.velocity);
					if (speed > entity.max_speed) entity.velocity = geo::div(entity.velocity, speed / entity.max_speed);
					entity.inertial_velocity = geo::mul(entity.inertial_acceleration, duration.count()); //TODO: Do we need to store this intermediate value? Can't just use inertial_acceleratin only?
					entity.position = geo::add(entity.position, geo::mul(geo::add(entity.velocity, entity.inertial_velocity), duration.count()));
					entity.velocity = geo::div(entity.velocity, entity.friction);
					entity.inertial_acceleration = { 0, 0 };
				}
			}
		}
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
