#ifndef SZM_SIMPLE_PARTITIONER
#define SZM_SIMPLE_PARTITIONER

#include "Entities.hpp"
#include "..\Geometry\Geometry.hpp"
#include "Iterator.hpp"
#include "AbstractPartitioner.hpp"
#include "SimplePartition.hpp"


namespace entity
{

	class SimplePartitioner: AbstractPartitioner
	{
	public:

		SimplePartitioner();
		virtual ~SimplePartitioner() override;
		virtual void Insert(geo::Frame<StaticEntity> entity) override;
		virtual Iterator<AbstractPartition* const> begin() override;
		virtual Iterator<AbstractPartition* const> end() override;

	private:
	};

}

#endif
