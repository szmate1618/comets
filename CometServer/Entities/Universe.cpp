#include "Universe.hpp"
#include "TriangulatedPolyNaiveRotation.hpp"
#include "Circle.hpp"
#include "..\Utilities\sqlite3.h"
#include "..\Utilities\Logger.hpp"

#include <sstream>


namespace entity
{

	Universe::Universe() {}

	Universe::Universe(std::string filename) //TODO: Add error handling.
	{
		sqlite3* db_connection;
		sqlite3_open(filename.c_str(), &db_connection); //TODO: Add error handling.
		sqlite3_exec //TODO: Add error handling.
		(
			db_connection,
			"SELECT ShapeID, Shape FROM Shapes;",
			[](void* void_universe, int, char** argv, char**) //TODO: This belongs in Utilities.
			{
				Universe* universe = static_cast<Universe*>(void_universe);
				def::shape_id shape_id = std::atoi(argv[0]);
				std::stringstream shape(argv[1]);
				size_t vertex_count;
				size_t triangle_count;
				shape >> vertex_count >> triangle_count; //NOTE: This allows both space and newline separators.
				universe->shape_registry.emplace
				(shape_id, EntityShape{
					std::vector<float>(vertex_count * 2),
					std::vector<geo::vector_2d>(vertex_count),
					std::vector<float>(vertex_count * 2),
					std::vector<uint16_t>(triangle_count * 3)
				});
				EntityShape& entity_shape = universe->shape_registry.at(shape_id);
				for (size_t i = 0; i < vertex_count * 2; i++)
				{
					shape >> entity_shape.vertices[i];
				}
				for (size_t i = 0; i < vertex_count; i++)
				{
					entity_shape.collision_vertices[i].x = static_cast<geo::real>(entity_shape.vertices[2 * i]);
					entity_shape.collision_vertices[i].y = static_cast<geo::real>(entity_shape.vertices[2 * i + 1]);
				}
				for (size_t i = 0; i < vertex_count * 2; i++)
				{
					shape >> entity_shape.uvs[i];
				}
				for (size_t i = 0; i < triangle_count * 3; i++)
				{
					shape >> entity_shape.triangles[i];
				}
				return 0;
			},
			static_cast<void*>(this),
			nullptr
		);
		sqlite3_exec //TODO: Add error handling.
		(
			db_connection,
			"SELECT EntityID, OwnerID, ShapeID, TextureID, Engine, Dynamics, Visibility, Collidability, PositionX, PositionY FROM Entities;",
			[](void* void_universe, int, char** argv, char**) //TODO: This belongs in Utilities.
			{
				Universe* universe = static_cast<Universe*>(void_universe);
				def::entity_id entity = std::atoi(argv[0]);
				def::owner_id owner = std::atoi(argv[1]);
				def::shape_id shape = std::atoi(argv[2]);
				def::texture_id texture = std::atoi(argv[3]);
				engine_type engine;
				if (std::strcmp("inertial", argv[4]) == 0) engine = inertial;
				else if (std::strcmp("anti_inertial", argv[4]) == 0) engine = anti_intertial;
				else if (std::strcmp("para_inertial", argv[4]) == 0) engine = para_inertial;
				else if (std::strcmp("pre_programmed", argv[4]) == 0) engine = pre_programmed;
				dynamics_class dynamics;
				if (std::strcmp("static_", argv[5]) == 0) dynamics = static_;
				else if (std::strcmp("dynamic", argv[5]) == 0) dynamics = dynamic;
				visibility_class visibility;
				if (std::strcmp("visible", argv[6]) == 0) visibility = visible;
				else if (std::strcmp("invisible", argv[6]) == 0) visibility = invisible;
				collidability_class collidability;
				if (std::strcmp("collidable", argv[7]) == 0) collidability = collidable;
				else if (std::strcmp("uncollidable", argv[7]) == 0) collidability = uncollidable;
				geo::radian orientation{ 0 };
				geo::point_2d position{ std::atof(argv[8]), std::atof(argv[9]) };
				geo::vector_2d velocity{ 0, 0 };
				universe->SpawnEntity(entity, owner, shape, texture, engine, dynamics, visibility, collidability, orientation, position, velocity);
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
			EntityFireWithCooldown(duration, entity);
			break;
		case def::warp:
			EntityWarp(duration, entity);
			break;
		default:
			return false; //TODO: Do some warnlogging here.
		}
		return true;
	}

	void Universe::EntityTurnLeft(def::time duration, DynamicEntity& entity, engine_type engine)
	{
		geo::radian rotation = entity.angular_velocity * duration.count();
		EntityTurnDegree(entity, engine, rotation);
	}

	void Universe::EntityTurnRight(def::time duration, DynamicEntity& entity, engine_type engine)
	{
		geo::radian rotation = entity.angular_velocity * duration.count();
		EntityTurnDegree(entity, engine, -rotation);
	}

	void Universe::EntityThrust(def::time duration, DynamicEntity& entity, engine_type engine)
	{
		switch (engine)
		{
		case entity::para_inertial:
			[[fallthrough]];
		case entity::inertial:
			entity.velocity = entity.velocity + entity.acceleration * duration.count();
			break;
		case entity::anti_intertial:
			entity.velocity = geo::vector_2d{ entity.max_speed, 0 }.rotated(entity.orientation);
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
			entity.velocity = entity.velocity - entity.acceleration * duration.count();
			break;
		case entity::anti_intertial:
			entity.velocity = geo::vector_2d{ -entity.max_speed, 0 }.rotated(entity.orientation);
			break;
		default:
			//TODO: Warnlogging.
			break;
		}
	}

	void Universe::EntityFire(def::time duration, DynamicEntity& entity)
	{
		SpawnEntity(static_cast<def::entity_id>(entity_registry.size() + 1), //TODO: Actually avoid collisions.
			entity_registry[entity.id].owner,
			4, //Completely arbitrary shape_id. TODO: Make this less arbitrary.
			1, //Completely arbitrary texture_id. TODO: Same as above.
			entity::anti_intertial,
			entity::dynamic,
			entity::visible,
			entity::collidable,
			entity.orientation,
			entity.position,
			geo::vector_2d{ 0, 10.0 }.rotated(entity.orientation) //TODO: Make this configurable.
		);
	}

	void Universe::EntityFireWithCooldown(def::time duration, DynamicEntity& entity)
	{
		if (entity_registry[entity.id].weapon_cooldown <= def::zero_seconds)
		{
			EntityFire(duration, entity);
			entity_registry[entity.id].weapon_cooldown = def::default_weapon_cooldown;
		}
		entity_registry[entity.id].weapon_cooldown -= duration;
	}

	void Universe::EntityWarp(def::time duration, DynamicEntity& entity)
	{
		entity.position = { 0, 0 }; //TODO: Make the warp point configureable.
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
					geo::real speed = entity.velocity.length();
					if (speed > entity.max_speed) entity.velocity = entity.velocity / (speed / entity.max_speed);
					entity.inertial_velocity = entity.inertial_acceleration * duration.count(); //TODO: Do we need to store this intermediate value? Can't just use inertial_acceleration only?
					entity.position = entity.position + (entity.velocity + entity.inertial_velocity) * duration.count();
					entity.velocity = entity.velocity / (1 + entity.friction); //TODO: Is this really how we want to define friction?
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
					AbstractCollisionShape& shape1 = *collision_shape_registry.at(p_entity1->id);
					AbstractCollisionShape& shape2 = *collision_shape_registry.at(p_entity2->id);
					//TODO: Crop bounding boxes to the current partition.
					if (shape1.InviteForCollision(shape1.GetBoundingBox(), shape2.GetBoundingBox(), shape2))
					{
						util::Log(util::trace, "Entity " + std::to_string(p_entity2->id) + " collided into entity " + std::to_string(p_entity1->id) + ".");
					}
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

	void Universe::EntityTurnDegree(DynamicEntity& entity, engine_type engine, geo::radian rotation)
	{
		switch (engine)
		{
		case entity::para_inertial:
			entity.velocity.rotate(rotation);
			[[fallthrough]];
		case entity::inertial:
			entity.acceleration.rotate(rotation);
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
		def::shape_id shape,
		def::texture_id texture,
		engine_type engine,
		dynamics_class dynamics,
		visibility_class visibility,
		collidability_class collidability,
		geo::radian orientation,
		geo::point_2d position,
		geo::vector_2d velocity)
	{
		if (entity_registry.count(entity) > 0) return;

		EntityHandle handle{ owner, shape, texture, engine, dynamics, visibility, collidability, nullptr };
		if (dynamics == dynamic)
		{
			DynamicEntity dynamic_entity;
			//TODO: Also add shape, and make all the following values configurable.
			dynamic_entity.id = entity;
			dynamic_entity.orientation = orientation;
			dynamic_entity.position = position;
			dynamic_entity.angular_velocity = 3; //TODO: Clean up the logic around this, and/or maybe rename to max_angular_velocity, or even max_angular_speed.
			dynamic_entity.velocity = velocity;
			dynamic_entity.max_speed = 10;
			dynamic_entity.inertial_velocity = { 0, 0 };
			dynamic_entity.acceleration = { 0, 5 };
			dynamic_entity.inertial_acceleration = { 0, 0 };
			dynamic_entity.friction = 0;
			auto index = dynamic_entities[visibility][collidability].InsertAtFirstGap(dynamic_entity);
			handle.de_pointer = &(dynamic_entities[visibility][collidability].elements[index].element); //TODO: Add a member method for this.
		}
		else
		{
			StaticEntity static_entity;
			static_entity.id = entity;
			static_entity.orientation = orientation;
			static_entity.position = position; //TODO: Also add shape.
			auto index = static_entities[visibility][collidability].InsertAtFirstGap(static_entity);
			handle.se_pointer = &(static_entities[visibility][collidability].elements[index].element);
		}
		//TODO: Common code in the above branches should be executed unconditionally.
		entity_registry[entity] = handle;

		const StaticEntity* static_entity = handle.dynamics == dynamic ? handle.de_pointer : handle.se_pointer;
		const std::vector<geo::vector_2d>& collision_vertices = GetShape(entity).collision_vertices;
		const std::vector<uint16_t>& triangles = GetShape(entity).triangles;
		if (GetShape(entity).collision_vertices.size() != 2) //If it's a polygon.
		{
			collision_shape_registry.emplace
			(
				entity, new TriangulatedPolyNaiveRotation{ static_entity->orientation, static_entity->position, collision_vertices, triangles }
			);
		}
		else //If it's a circle.
		{
			geo::real radius = (collision_vertices[1] - collision_vertices[0]).length();
			collision_shape_registry.emplace
			(
				entity, new Circle{ static_entity->orientation, static_entity->position, radius }
			);
		}
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

	Universe::EntityShape& Universe::GetShape(def::entity_id entity)
	{
		return shape_registry.at(entity_registry.at(entity).shape);
	}

}
