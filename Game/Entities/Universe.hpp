#pragma once

#include "Entities.hpp"
#include "EntityHandle.hpp"
#include "..\Utilities\StaticLinkedList.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <map>
#include <unordered_map>
#include <string>

namespace entity
{

	template<typename T> using visibility_collidability_map = std::map<visibility_class, std::map<collidability_class, utils::StaticLinkedList<T>>>;
	using StaticEntityMap = visibility_collidability_map<StaticEntity>;
	using DynamicEntityMap = std::map<engine_type, visibility_collidability_map<DynamicEntity>>;

	//The class responsible for managing all in-game entities.
	class Universe
	{
	public:

		Universe();
		Universe(std::string);
		~Universe();
		bool EntityHandleInput(def::time, def::entity_id);
		bool EntityTurnLeft(def::time, def::entity_id);
		bool EntityTurnRight(def::time, def::entity_id);
		bool EntityThrust(def::time, def::entity_id);
		bool EntityBrake(def::time, def::entity_id);
		bool EntityFire(def::time, def::entity_id);
		void UpdateState(def::time);
		void TestCollisions();
		void TestVisibility();

	private:
		
		std::unordered_map<def::entity_id, EntityHandle> entity_registry; //TODO: Compare the speed of map and unordered map wherever possible.
		StaticEntityMap static_entities;
		DynamicEntityMap dynamic_entities;

	};

}
