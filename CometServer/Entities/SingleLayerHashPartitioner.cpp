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
		std::pair<int64_t, int64_t> position{ static_cast<int64_t>(entity->position.x) / 128, static_cast<int64_t>(entity->position.y) / 128 };
		if (partitions_map.count(position) == 0)
		{
			partitions.emplace_back();
			partitions_map[position] = &(partitions.back());
		}
		partitions_map[position]->Add(entity);
	}

	std::list<SimplePartition>::const_iterator SingleLayerHashPartitioner::begin() const
	{
		return partitions.begin();
	}

	std::list<SimplePartition>::const_iterator SingleLayerHashPartitioner::end() const
	{
		return partitions.end();
	}

}
