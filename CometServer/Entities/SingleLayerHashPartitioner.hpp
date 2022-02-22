#pragma once

#include "Entities.hpp"
#include "SimplePartition.hpp"

#include <unordered_map>
#include <utility>
#include <list>


namespace entity
{

	class SingleLayerHashPartitioner
	{
	public:

		SingleLayerHashPartitioner();
		~SingleLayerHashPartitioner();
		void Reset();
		void Insert(StaticEntity*);
		std::list<SimplePartition>::const_iterator begin() const;
		std::list<SimplePartition>::const_iterator end() const;

		//A rudimentary hash implementation for std::pair based on this
		//https://en.cppreference.com/w/cpp/utility/hash
		//At this point it is not known if it really suits our needs.
		struct pair_hash {
			template <class T1, class T2>
			size_t operator () (const std::pair<T1, T2> &p) const {
				size_t h1 = std::hash<T1>{}(p.first);
				size_t h2 = std::hash<T2>{}(p.second);
				return h1 ^ h2;
			}
		};

	protected:

		// TODO: Consider using a geo::vector_2d.
		std::unordered_map<std::pair<int64_t, int64_t>, SimplePartition*, pair_hash> partitions_map;
		std::list<SimplePartition> partitions;

	private:
	};

}
