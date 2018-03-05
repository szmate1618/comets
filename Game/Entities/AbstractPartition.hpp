#pragma once

#include "Entities.hpp"


namespace entity
{

	class AbstractPartition
	{

	public:

		class AbstractIterator
		{
		public:

			virtual ~AbstractIterator() = 0;
			virtual AbstractIterator& operator++() = 0;
			virtual bool operator==(const AbstractIterator&) const = 0;
			virtual bool operator!=(const AbstractIterator&) const = 0;
			virtual const StaticEntity*& operator*() const = 0;
		};

		virtual ~AbstractPartition();
		virtual void Reset() = 0;
		virtual void Add(StaticEntity* const) = 0;
		
		//These consts are of utmost importance, see here: https://herbsutter.com/2008/01/01/gotw-88-a-candidate-for-the-most-important-const/
		virtual const AbstractIterator& begin() = 0;
		virtual const AbstractIterator& end() = 0;

	private:
	};

}
