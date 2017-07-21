#ifndef SZM_SIMPLE_PARTITIONER
#define SZM_SIMPLE_PARTITIONER

#include "Entities.hpp"
#include "..\Geometry\Geometry.hpp"
#include "Iterator.hpp"
#include "AbstractPartitioner.hpp"
#include "SimplePartition.hpp"


namespace entity
{

	class SimplePartitioner: public AbstractPartitioner
	{
	public:

		SimplePartitioner();
		virtual ~SimplePartitioner() override;
		virtual void Insert(geo::Frame<StaticEntity>&) override;
		virtual Iterator<AbstractPartition> begin() override;
		virtual Iterator<AbstractPartition> end() override;

	private:

		SimplePartition the_partition;
	};

}

#endif
