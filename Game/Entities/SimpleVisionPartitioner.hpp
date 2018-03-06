#pragma once

#include "SimplePartitioner.hpp"


namespace entity
{

	class SimpleVisionPartitioner : SimplePartitioner
	{
	public:

		SimpleVisionPartitioner();
		~SimpleVisionPartitioner();
		SimplePartition& GetPartition(StaticEntity*);

	private:

	};

}
