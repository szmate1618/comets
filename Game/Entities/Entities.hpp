#pragma once

#include "AbstractCollisionShape.hpp"
#include "..\Geometry\Geometry.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"


namespace entity
{

	//A stationary entity that has a collision shape.
	struct StaticEntity
	{
		def::entity_id id;
		AbstractCollisionShape* shape;
		geo::vector_2d orientation;
		geo::vector_2d position;
	};

	//A dynamic entity that can move and possibly be moved by other entities.
	struct DynamicEntity: public StaticEntity
	{
		geo::vector_2d velocity;
		geo::real max_speed;
		geo::vector_2d inertial_velocity;
		geo::vector_2d acceleration;
		geo::vector_2d inertial_acceleration;
		geo::real friction;
	};

}
