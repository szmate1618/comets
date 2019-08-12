#pragma once

#include "Entities.hpp"
#include "EntityHandle.hpp"
#include "SimplePartitioner.hpp"
#include "SimpleVisionPartitioner.hpp"
#include "..\Utilities\StaticLinkedList.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

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

		struct EntityShape
		{
			std::vector<float> vertices;
			std::vector<geo::vector_2d> collision_vertices;
			std::vector<float> uvs;
			std::vector<uint16_t> triangles;
		};

		EntityShape& GetShape(def::entity_id); //TODO: entity_id and shape_id should be incompatible types.

	private:

		std::unordered_map<def::entity_id, EntityHandle> entity_registry; //TODO: Compare the speed of map and unordered map wherever possible.
		std::unordered_map<def::shape_id, EntityShape> shape_registry;
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

		void EntityTurnDegree(DynamicEntity&, engine_type, geo::degree);
		void SpawnEntity(def::entity_id,
			def::owner_id,
			def::shape_id,
			def::texture_id,
			engine_type,
			dynamics_class,
			visibility_class,
			collidability_class,
			geo::degree,
			geo::point_2d,
			geo::vector_2d); //TODO: This is not a valid parameter when creating static entities.

	};

}
