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

	Iterator<StaticEntity*> SimplePartition::begin()
	{
		return Iterator<StaticEntity*>(elements[0]);
	}

    Iterator<StaticEntity*> SimplePartition::end()
	{
		return Iterator<StaticEntity*>(elements[count + 1]);
	}

}
