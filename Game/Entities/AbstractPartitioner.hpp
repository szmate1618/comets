#pragma once

#include "Entities.hpp"
#include "Iterator.hpp"
#include "AbstractPartition.hpp"


namespace entity
{

	class AbstractPartitioner
	{

	public:

		class AbstractIterator
		{
		public:

			virtual ~AbstractIterator() = 0;
			virtual AbstractIterator& operator++() = 0;
			virtual bool operator==(const AbstractIterator&) const = 0;
			virtual bool operator!=(const AbstractIterator&) const = 0;
			virtual AbstractPartition& operator*() const = 0;
		};

		AbstractPartitioner();
		virtual ~AbstractPartitioner();
		virtual void Insert(StaticEntity* const) = 0; //TODO: Include an EmptyFrame in AbstractCollisionShape.

		//These consts are of utmost importance, see here: https://herbsutter.com/2008/01/01/gotw-88-a-candidate-for-the-most-important-const/
		virtual const AbstractIterator& begin() = 0;
		virtual const AbstractIterator& end() = 0;

	private:
	};

}
