#pragma once

#include "Entities.hpp"
#include "SimplePartition.hpp"

#include <unordered_map>
#include <tuple>
#include <vector>


namespace entity
{

	class SingleLayerHashPartitioner
	{
	public:

		SingleLayerHashPartitioner();
		~SingleLayerHashPartitioner();
		void Reset();
		void Insert(StaticEntity*);
		std::vector<SimplePartition>::const_iterator begin() const;
		std::vector<SimplePartition>::const_iterator end() const;

	protected:

		// TODO: Consider using a geo::vector_2d.
		std::unordered_map<std::tuple<double, double>, SimplePartition*> partitions_map;
		std::vector<SimplePartition> partitions;

	private:
	};

}
