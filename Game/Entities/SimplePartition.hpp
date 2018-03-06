#pragma once

#include "Entities.hpp"

#include <vector>


namespace entity
{

	class SimplePartition
	{
	public:

		SimplePartition();
		~SimplePartition();
		void Reset();
		void Add(StaticEntity*);
		std::vector<StaticEntity*>::const_iterator begin() const;
		std::vector<StaticEntity*>::const_iterator end() const;

	private:

		std::vector<StaticEntity*> elements;

	};

}
