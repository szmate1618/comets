#include "SimpleVisionPartitioner.hpp"


namespace entity
{

	SimpleVisionPartitioner::SimpleVisionPartitioner()
	{
	}

	SimpleVisionPartitioner::~SimpleVisionPartitioner()
	{
	}

	SimplePartition& SimpleVisionPartitioner::GetPartition(StaticEntity* entity)
	{
		return the_partition;
	}

}
