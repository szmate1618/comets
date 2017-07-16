#ifndef SZM_SIMPLE_PARTITION
#define SZM_SIMPLE_PARTITION

#include "AbstractPartition.hpp"
#include "Entities.hpp"
#include "Iterator.hpp"
#include "..\Geometry\Geometry.hpp"


namespace entity
{

	class SimplePartition: AbstractPartition
	{
	public:

		SimplePartition();
		virtual ~SimplePartition() override;
		virtual void Add(AbstractEntity entity) override;
		virtual Iterator<AbstractEntity> begin() override;
		virtual Iterator<AbstractEntity> end() override;

	};

}

#endif
