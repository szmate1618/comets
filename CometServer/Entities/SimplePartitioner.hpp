#pragma once

#include "Entities.hpp"
#include "SimplePartition.hpp"


namespace entity
{

	class SimplePartitioner
	{
	public:

		SimplePartitioner();
		~SimplePartitioner();
		void Reset();
		void Insert(StaticEntity*);
		const SimplePartition* begin() const;
		const SimplePartition* end() const;

	protected:

		SimplePartition the_partition;

	private:
	};

}
