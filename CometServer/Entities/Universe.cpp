#include "Universe.hpp"
#include "..\Utilities\sqlite3.h"


namespace entity
{

	Universe::Universe() {}

	Universe::Universe(std::string filename) //TODO: Add error handling.
	{
		sqlite3* db_connection;
		sqlite3_open("game_data.sqlite3", &db_connection); //TODO: Add error handling.
		sqlite3_exec //TODO: Add error handling.
		(
			db_connection,
			"SELECT EntityID, OwnerID, Engine, Dynamics, Visibility, Collidability, PositionX, PositionY FROM Entities;",
			[](void* universe, int, char** argv, char**) //TODO: This belongs in Utilities.
			{
				def::entity_id entity = std::atoi(argv[0]);
				def::owner_id owner = std::atoi(argv[1]);
				engine_type engine;
				if (std::strcmp("inertial", argv[2]) == 0) engine = inertial;
				else if (std::strcmp("anti_inertial", argv[2]) == 0) engine = anti_intertial;
				else if (std::strcmp("para_inertial", argv[2]) == 0) engine = para_inertial;
				else if (std::strcmp("pre_programmed", argv[2]) == 0) engine = pre_programmed;
				dynamics_class dynamics;
				if (std::strcmp("static_", argv[3]) == 0) dynamics = static_;
				else if (std::strcmp("dynamic", argv[3]) == 0) dynamics = dynamic;
				visibility_class visibility;
				if (std::strcmp("visible", argv[4]) == 0) visibility = visible;
				else if (std::strcmp("invisible", argv[4]) == 0) visibility = invisible;
				collidability_class collidability;
				if (std::strcmp("collidable", argv[5]) == 0) collidability = collidable;
				else if (std::strcmp("uncollidable", argv[5]) == 0) collidability = uncollidable;
				geo::point_2d position{ std::atof(argv[6]), std::atof(argv[7]) };
				static_cast<Universe*>(universe)->SpawnEntity(entity, owner, engine, dynamics, visibility, collidability, position);
				return 0;
			},
			static_cast<void*>(this),
			nullptr
		);
		sqlite3_close(db_connection);
	}

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

	void Universe::UpdateState(def::time duration)
	{
		for (visibility_class v : {visible, invisible})
		{
			for (collidability_class c : {collidable, uncollidable})
			{
				for (DynamicEntity& entity : dynamic_entities[v][c])
				{
					//TODO: Handle angular_velocity.
					geo::real speed = geo::length(entity.velocity);
					if (speed > entity.max_speed) entity.velocity = geo::div(entity.velocity, speed / entity.max_speed);
					entity.inertial_velocity = geo::mul(entity.inertial_acceleration, duration.count()); //TODO: Do we need to store this intermediate value? Can't just use inertial_acceleration only?
					entity.position = geo::add(entity.position, geo::mul(geo::add(entity.velocity, entity.inertial_velocity), duration.count()));
					entity.velocity = geo::div(entity.velocity, 1 + entity.friction); //TODO: Is this really how we want to define friction?
					entity.inertial_acceleration = { 0, 0 };
				}
			}
		}
	}

	void Universe::TestCollisions()
	{
		collision_partitioner.Reset();
		for (visibility_class v : {visible, invisible})
		{
			for (StaticEntity& entity : static_entities[v][collidable])
			{
				//Insert all elements into a collision partitioner.
				collision_partitioner.Insert(&entity);
			}
			for (DynamicEntity& entity : dynamic_entities[v][collidable])
			{
				//Insert all elements into a collision partitioner.
				collision_partitioner.Insert(&entity);
			}
		}
		//Iterate over all the partitions, inside of a partition check collisions for everything with everything.
		for (const auto& partition : collision_partitioner)
		{
			for (const StaticEntity* p_entity1 : partition)
			{
				for (const StaticEntity* p_entity2 : partition)
				{
					if (p_entity1 == p_entity2) continue;
					//Test for collision.
					#ifndef NO_COLLISION
					AbstractCollisionShape& shape1 = *p_entity1->shape;
					AbstractCollisionShape& shape2 = *p_entity2->shape;
					shape1.InviteForCollision(shape1.GetBoundingBox(), shape2.GetBoundingBox(), shape2);
					#endif
				}
			}
		}
	}

	void Universe::TestVisibility() //TODO: Maybe call this TestVision?
	{
		vision_partitioner.Reset();
		for (collidability_class c : {collidable, uncollidable})
		{
			for (StaticEntity& entity : static_entities[visible][c])
			{
				//Insert all elements into a vision partitioner.
				vision_partitioner.Insert(&entity);
			}
			for (DynamicEntity& entity : dynamic_entities[visible][c])
			{
				//Insert all elements into a vision partitioner.
				vision_partitioner.Insert(&entity);
			}
		}
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
			//TODO: Also add shape, and make all the following values configurable.
			dynamic_entity.id = entity;
			dynamic_entity.orientation = 0;
			dynamic_entity.position = position;
			dynamic_entity.angular_velocity = 3; //TODO: Clean up the logic around this, and/or maybe rename to max_angular_velocity, or even max_angular_speed.
			dynamic_entity.velocity = { 0, 0 };
			dynamic_entity.max_speed = 10;
			dynamic_entity.inertial_velocity = { 0, 0 };
			dynamic_entity.acceleration = { 5, 0 };
			dynamic_entity.inertial_acceleration = { 0, 0 };
			dynamic_entity.friction = 0;
			auto index = dynamic_entities[visibility][collidability].InsertAtFirstGap(dynamic_entity);
			handle.de_pointer = &(dynamic_entities[visibility][collidability].elements[index].element); //TODO: Add a member method for this.
		}
		else
		{
			StaticEntity static_entity;
			static_entity.id = entity;
			static_entity.position = position; //TODO: Also add shape.
			auto index = static_entities[visibility][collidability].InsertAtFirstGap(static_entity);
			handle.se_pointer = &(static_entities[visibility][collidability].elements[index].element);
		}
		entity_registry[entity] = handle;
	}

	SimplePartition& Universe::GetVision(def::entity_id entity)
	{
		if (entity_registry[entity].dynamics == dynamics_class::static_)
		{
			return vision_partitioner.GetPartition(entity_registry[entity].se_pointer);
		}
		else
		{
			return vision_partitioner.GetPartition(entity_registry[entity].de_pointer);
		}
	}

}
