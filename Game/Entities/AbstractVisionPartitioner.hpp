#pragma once


#include "AbstractPartitioner.hpp"
#include "Entities.hpp"
#include "Iterator.hpp"
#include "AbstractPartition.hpp"


namespace entity
{

	class AbstractVisionPartitioner : public AbstractPartitioner
	{

	public:

		class AbstractIterator : public AbstractPartitioner::AbstractIterator
		{
		public:

			virtual ~AbstractIterator() = 0;
			virtual AbstractIterator& operator++() = 0;
			virtual bool operator==(const AbstractIterator&) const = 0;
			virtual bool operator!=(const AbstractIterator&) const = 0;
			virtual AbstractPartition& operator*() const = 0;
		};

		virtual ~AbstractVisionPartitioner();
		virtual const AbstractPartition& GetPartition(StaticEntity* const) const = 0;

	private:
	};

}
