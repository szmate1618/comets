#ifndef SZM_ABSTRACT_PARTITION
#define SZM_ABSTRACT_PARTITION

#include "Entities.hpp"
#include "Iterator.hpp"
#include "..\Geometry\Geometry.hpp"


namespace entity
{

	class AbstractPartition
	{
	public:

		AbstractPartition();
		virtual ~AbstractPartition();
		virtual void Reset() = 0;
		virtual void Add(StaticEntity*) = 0;
		virtual Iterator<StaticEntity> begin() = 0;
		virtual Iterator<StaticEntity> end() = 0;

	};

}

#endif
