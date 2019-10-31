#pragma once

#include "Entities.hpp"
#include "EntityHandle.hpp"
#include "SimplePartitioner.hpp"
#include "SimpleVisionPartitioner.hpp"
#include "..\Utilities\sqlite3.h"
#include "..\Utilities\StaticLinkedList.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"
#include "..\Definitions\Gameplay.hpp"

#include <map>
#include <unordered_map>
#include <string>
#include <vector>


namespace entity
{

	template<typename T> using visibility_collidability_map = std::map<visibility_class, std::map<collidability_class, utils::StaticLinkedList<T>>>;
	using StaticEntityMap = visibility_collidability_map<StaticEntity>;
	using DynamicEntityMap = visibility_collidability_map<DynamicEntity>;

	//The class responsible for managing all in-game entities.
	class Universe
	{
	public:

		Universe();
		Universe(std::string);
		~Universe();
		void LoadShapes(sqlite3*);
		void LoadCollisionBehaviors(sqlite3*);
		void LoadEntities(sqlite3*);
		bool EntityHandleInput(def::time, def::entity_id, def::user_input);
		void EntityTurnLeft(def::time, DynamicEntity&, engine_type);
		void EntityTurnRight(def::time, DynamicEntity&, engine_type);
		void EntityThrust(def::time, DynamicEntity&, engine_type);
		void EntityBrake(def::time, DynamicEntity&, engine_type);
		void EntityFire(def::time, DynamicEntity&);
		void EntityFireWithCooldown(def::time, DynamicEntity&);
		void EntityWarp(def::time, DynamicEntity&);
		void UpdateState(def::time);
		void TestCollisions();
		void TestVisibility();
		SimplePartition& GetVision(def::entity_id);
		void ExecuteQueuedOperations();
		const EntityHandle& GetEntityHandle(def::entity_id);

		struct EntityShape
		{
			std::vector<float> vertices;
			std::vector<geo::vector_2d> collision_vertices;
			std::vector<float> uvs;
			std::vector<uint16_t> triangles;
		};

		EntityShape& GetShape(def::entity_id); //TODO: entity_id and shape_id should be incompatible types.

		struct CollisionBehavior
		{
			enum class Condition { on_collision_take, on_collision_give } condition;
			enum class Action { explode } action;
			def::behavior_parameter parameter1;
			def::behavior_parameter parameter2;
			def::behavior_parameter parameter3;
		};

		CollisionBehavior& GetCollisionBehavior(def::entity_id); //TODO: entity_id and shape_id should be incompatible types.

	private:

		def::entity_id max_used_entity_id = 0; //TODO: Factor this into an EntityRegistry class.
		std::unordered_map<def::entity_id, EntityHandle> entity_registry; //TODO: Compare the speed of map and unordered map wherever possible.
		std::unordered_map<def::shape_id, EntityShape> shape_registry;
		std::unordered_map<def::shape_id, CollisionBehavior> collision_behavior_registry;
		std::unordered_map<def::entity_id, std::unique_ptr<AbstractCollisionShape>> collision_shape_registry;
		StaticEntityMap static_entities =
		{
			{ visible,{ { collidable,{} },{ uncollidable,{} } } },
			{ invisible,{ { collidable,{} },{ uncollidable,{} } } }
		};
		DynamicEntityMap dynamic_entities =
		{
			{ visible,{ { collidable,{} },{ uncollidable,{} } } },
			{ invisible,{ { collidable,{} },{ uncollidable,{} } } }
		};
		SimplePartitioner collision_partitioner;
		SimpleVisionPartitioner vision_partitioner;

		//TODO: Maybe these should go into a separate class.
		std::vector<def::entity_id> entities_to_remove;
		std::vector<EntityHandle> entity_handles_to_add;
		std::vector<DynamicEntity> entities_to_add;

		void EntityTurnDegree(DynamicEntity&, engine_type, geo::radian);
		void SpawnEntity(def::entity_id,
			def::owner_id,
			def::shape_id,
			def::texture_id,
			engine_type,
			dynamics_class,
			visibility_class,
			collidability_class,
			geo::radian,
			geo::point_2d,
			geo::vector_2d); //TODO: This is not a valid parameter when creating static entities.
		void QueueEntitySpawn( //No entity_id parameter. That can only be assigned right before insertion.
			def::owner_id,
			def::shape_id,
			def::texture_id,
			engine_type,
			dynamics_class,
			visibility_class,
			collidability_class,
			geo::radian,
			geo::point_2d,
			geo::vector_2d); //TODO: This is not a valid parameter when creating static entities.
		void QueueEntityDestruct(def::entity_id);

	};

}
