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
		virtual void Add(StaticEntity* const entity) = 0;
		virtual Iterator<StaticEntity* const> begin() = 0;
		virtual Iterator<StaticEntity* const> end() = 0;

	};

}

#endif
