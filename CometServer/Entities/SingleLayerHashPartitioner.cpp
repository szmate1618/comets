#include "SingleLayerHashPartitioner.hpp"


namespace entity 
{

	SingleLayerHashPartitioner::SingleLayerHashPartitioner()
	{
	}

	SingleLayerHashPartitioner::~SingleLayerHashPartitioner()
	{
	}

	void SingleLayerHashPartitioner::Reset()
	{
		partitions_map.clear();
		partitions.clear();
	}

	void SingleLayerHashPartitioner::Insert(StaticEntity* entity)
	{
		//TODO: Insert into all containing partitions based on bounding box.
		std::pair<double, double> position{ entity->position.x, entity->position.y };
		if (partitions_map.count(position) == 0)
		{
			partitions.emplace_back();
			partitions_map[position] = &(partitions[partitions.size() - 1]);
		}
		partitions_map[position]->Add(entity);
	}

	std::vector<SimplePartition>::const_iterator SingleLayerHashPartitioner::begin() const
	{
		return partitions.begin();
	}

	std::vector<SimplePartition>::const_iterator SingleLayerHashPartitioner::end() const
	{
		return partitions.end();
	}

}
