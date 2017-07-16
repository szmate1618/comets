#ifndef SZM_ENTITIES
#define SZM_ENTITIES

#include "AbstractCollisionShape.hpp"
#include "..\Geometry\Geometry.hpp"


namespace entity
{

	//An entity that has a collision shape.
	struct AbstractEntity{AbstractCollisionShape* shape;};

	//A stationary entity.
	struct StaticEntity: public AbstractEntity
	{
		geo::vector_2d orientation;
		geo::vector_2d position;
	};

	//A dynamic entity that can move and possibly moved by other entities.
	struct DynamicEntity: public AbstractEntity
	{
		geo::vector_2d orientation;
		geo::vector_2d position;
		geo::vector_2d velocity;
		geo::real max_speed;
		geo::vector_2d inertial_velocity;
		geo::vector_2d acceleration;
		geo::vector_2d inertial_acceleration;
		geo::real friction;
	};

}

#endif
