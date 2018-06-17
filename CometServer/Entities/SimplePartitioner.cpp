#include "SimplePartitioner.hpp"


namespace entity 
{

	SimplePartitioner::SimplePartitioner()
	{
	}

	SimplePartitioner::~SimplePartitioner()
	{
	}

	void SimplePartitioner::Reset()
	{
		the_partition.Reset();
	}

	void SimplePartitioner::Insert(StaticEntity* entity)
	{
		the_partition.Add(entity);
	}

	const SimplePartition* SimplePartitioner::begin() const
	{
		return &the_partition;
	}

	const SimplePartition* SimplePartitioner::end() const
	{
		return begin() + 1;
	}

}
