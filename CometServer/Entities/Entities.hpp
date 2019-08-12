#pragma once

#include "AbstractCollisionShape.hpp"
#include "..\Geometry\Geometry.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"


namespace entity
{

	//A stationary entity that has a collision shape.
	struct StaticEntity //TODO: Add AbstractPartition pointer.
	{
		def::entity_id id;
		geo::degree orientation;
		geo::vector_2d position;
	};

	//A dynamic entity that can move and possibly be moved by other entities.
	struct DynamicEntity: public StaticEntity
	{
		geo::degree angular_velocity;
		geo::vector_2d velocity;
		geo::real max_speed;
		geo::vector_2d inertial_velocity; //TODO: Maybe call this external_velocity.
		geo::vector_2d acceleration;
		geo::vector_2d inertial_acceleration; //TODO: Maybe call this external_acceleration.
		geo::real friction;
	};

}
