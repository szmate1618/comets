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
		virtual void Add(AbstractEntity entity) = 0;
		virtual Iterator<AbstractEntity> begin() = 0;
		virtual Iterator<AbstractEntity> end() = 0;

	private:
	};

}

#endif
