#include "SimplePartition.hpp"

#include <assert.h>

namespace entity 
{

	SimplePartition::SimplePartition()
	{
		count = 0;
	}

	SimplePartition::~SimplePartition()
	{
	}

    void SimplePartition::Add(StaticEntity* entity)
	{
		assert(count < capacity);
		elements[count] = entity;
		++count;
	}

    void SimplePartition::Reset()
	{
		count = 0;
	}

	Iterator<StaticEntity> SimplePartition::begin()
	{
		return MyIterator<StaticEntity>(*elements[0], *this);
	}

    Iterator<StaticEntity> SimplePartition::end()
	{
		return MyIterator<StaticEntity>(*elements[count], *this);
	}

	long SimplePartition::getCapacity()
	{
		return capacity;
	}

}
