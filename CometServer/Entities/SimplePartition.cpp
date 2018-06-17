#include "SimplePartition.hpp"

#include <cassert>

namespace entity 
{

	SimplePartition::SimplePartition()
	{
	}

	SimplePartition::~SimplePartition()
	{
	}

    void SimplePartition::Add(StaticEntity* entity)
	{
		elements.emplace_back(entity);
	}

    void SimplePartition::Reset()
	{
		elements.clear();
	}

	std::vector<StaticEntity*>::const_iterator SimplePartition::begin() const
	{
		return elements.begin();
	}

	std::vector<StaticEntity*>::const_iterator SimplePartition::end() const
	{
		return elements.end();
	}

}
