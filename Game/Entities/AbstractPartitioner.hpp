#ifndef SZM_ABSTRACT_PARTITIONER
#define SZM_ABSTRACT_PARTITIONER

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
		virtual Iterator<AbstractPartition> begin() = 0;
		virtual Iterator<AbstractPartition> end() = 0;

	private:
	};

}

#endif
