#include "SimplePartitioner.hpp"


namespace entity 
{

	SimplePartitioner::SimplePartitioner()
	{
	}

	SimplePartitioner::~SimplePartitioner()
	{
	}

	void SimplePartitioner::Insert(geo::Frame<StaticEntity>& entity_frame)
	{
		the_partition.Add(entity_frame.entity);
	}

	Iterator<AbstractPartition* const> SimplePartitioner::begin()
	{
		return Iterator<AbstractPartition* const>(&the_partition); //Wait? I'm passing an rvalue reference here?! C++11 FTW!
	}

	Iterator<AbstractPartition* const> SimplePartitioner::end()
	{
		return Iterator<AbstractPartition* const>(&the_partition + 1);
	}

}
