#pragma once

#include "Entities.hpp"
#include "..\Utilities\StaticLinkedList.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <map>
#include <string>

namespace entity
{

	enum engine { inertial, anti_intertial, para_inertial, pre_programmed };
	enum visibility { visible, invisible};
	enum collidability { collidable, uncollidable };

	template<typename T> using visibility_collidability_map = std::map<visibility, std::map<collidability, utils::StaticLinkedList<T>>>;
	using StaticEntityMap = visibility_collidability_map<StaticEntity>;
	using DynamicEntityMap = std::map<engine, visibility_collidability_map<DynamicEntity>>;

	//The class responsible for managing all in-game entities.
	class Universe
	{
	public:

		Universe();
		Universe(std::string);
		~Universe();
		bool EntityTurnLeft(def::entity_id);
		bool EntityTurnRight(def::entity_id);
		bool EntityThrust(def::entity_id);
		bool EntityBrake(def::entity_id);
		bool EntityFire(def::entity_id);

	private:
		
		StaticEntityMap static_entities;
		DynamicEntityMap dynamic_entities;

	};

}
