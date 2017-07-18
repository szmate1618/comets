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
		virtual void Reset() override;
		virtual void Add(StaticEntity* const entity) override;
		virtual Iterator<StaticEntity* const> begin() override;
		virtual Iterator<StaticEntity* const> end() override;
		static long getCapacity();

	private:

		static const long capacity = 1000;
		long count;
		StaticEntity* elements[capacity];

	};

}

#endif
