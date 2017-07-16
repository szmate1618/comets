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
		virtual void Add(StaticEntity* entity) override;
		virtual Iterator<StaticEntity*> begin() override;
		virtual Iterator<StaticEntity*> end() override;

	private:

		static const long capacity = 1000;
		long count;
		StaticEntity* elements[capacity];

	};

}

#endif
