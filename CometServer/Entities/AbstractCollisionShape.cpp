#include "AbstractCollisionShape.hpp"


namespace entity 
{

	AbstractCollisionShape::AbstractCollisionShape(const geo::degree& orientation, const geo::vector_2d& position) :
		orientation{ orientation }, position{ position }
	{
	}

	AbstractCollisionShape::~AbstractCollisionShape()
	{
	}

}
