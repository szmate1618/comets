#include "AbstractCollisionShape.hpp"


namespace entity 
{

	AbstractCollisionShape::AbstractCollisionShape(const geo::radian& orientation, const geo::vector_2d& position) :
		orientation{ orientation }, position{ position }
	{
	}

	AbstractCollisionShape::~AbstractCollisionShape()
	{
	}

	const geo::radian& AbstractCollisionShape::GetOrientation() const
	{
		return orientation;
	}

	const geo::vector_2d& AbstractCollisionShape::GetPosition() const
	{
		return position;
	}

}
