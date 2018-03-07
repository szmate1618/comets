#pragma once

#include "SimplePartitioner.hpp"


namespace entity
{

	class SimpleVisionPartitioner : public SimplePartitioner
	{
	public:

		SimpleVisionPartitioner();
		~SimpleVisionPartitioner();
		SimplePartition& GetPartition(StaticEntity*);

	private:

	};

}
