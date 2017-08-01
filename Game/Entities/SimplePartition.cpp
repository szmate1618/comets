#include "SimplePartition.hpp"

#include <cassert>

namespace entity 
{

	SimplePartition::SimplePartition()
	{
		count = 0;
	}

	SimplePartition::~SimplePartition()
	{
	}

    void SimplePartition::Add(StaticEntity* const entity)
	{
		assert(count < capacity);
		elements[count] = entity;
		++count;
	}

    void SimplePartition::Reset()
	{
		count = 0;
	}

	Iterator<StaticEntity* const> SimplePartition::begin()
	{
		return Iterator<StaticEntity* const>(elements[0]);
	}

    Iterator<StaticEntity* const> SimplePartition::end()
	{
		return Iterator<StaticEntity* const>(elements[count]);
	}

	long SimplePartition::getCapacity()
	{
		return capacity;
	}

}
