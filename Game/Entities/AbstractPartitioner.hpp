#ifndef SZM_ABSTRACT_PARTITIONER
#define SZM_ABSTRACT_PARTITIONER

#include "Entities.hpp"
#include "..\Geometry\Geometry.hpp"


namespace entity
{

	class AbstractPartitioner
	{
	public:

		AbstractPartitioner();
		virtual ~AbstractPartitioner();
		virtual void Insert(geo::Frame<AbstractEntity> entity) = 0;

	private:
	};

}

#endif
