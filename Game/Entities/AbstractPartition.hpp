#pragma once

#include "Entities.hpp"
#include "Iterator.hpp"


namespace entity
{

	class AbstractPartition
	{
	public:

		AbstractPartition();
		virtual ~AbstractPartition();
		virtual void Reset() = 0;
		virtual void Add(StaticEntity* const) = 0;
		virtual Iterator<StaticEntity* const> begin() = 0;
		virtual Iterator<StaticEntity* const> end() = 0;

	};

}
