#pragma once

#include "Entities.hpp"
#include "..\Geometry\Geometry.hpp"
#include "Iterator.hpp"
#include "AbstractPartition.hpp"


namespace entity
{

	class AbstractPartitioner
	{
	public:

		AbstractPartitioner();
		virtual ~AbstractPartitioner();
		virtual void Insert(geo::Frame<StaticEntity>&) = 0;
		virtual Iterator<AbstractPartition* const> begin() = 0;
		virtual Iterator<AbstractPartition* const> end() = 0;

	private:
	};

}
