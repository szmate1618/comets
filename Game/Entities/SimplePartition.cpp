#include "SimplePartition.hpp"


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
		elements[count] = entity;
		++count;
	}

	Iterator<StaticEntity*> SimplePartition::begin()
	{
		return Iterator<StaticEntity*>(elements[0]);
	}

    Iterator<StaticEntity*> SimplePartition::end()
	{
		return Iterator<StaticEntity*>(elements[count]);
	}

}
