#ifndef SZM_SIMPLE_PARTITION
#define SZM_SIMPLE_PARTITION

#include "AbstractPartition.hpp"
#include "Entities.hpp"
#include "Iterator.hpp"
#include "..\Geometry\Geometry.hpp"


namespace entity
{

	class SimplePartition: public AbstractPartition
	{

		template <typename T> //TODO: Apparently I can't specialize this class, because of the return type of operator++(int)
		class MyIterator: public Iterator<T>
		{
		public:

			MyIterator<T>(T& element, const SimplePartition& partition): Iterator(element), partition(partition), position(0) {}
			virtual ~MyIterator<T>() {}
			virtual MyIterator<T>& operator++() {++position; return partition.*elements[position];}
			virtual MyIterator<T> operator++(int) {++position; return partition.*elements[position];}

		private:

			const long position;
			const SimplePartition& partition;
		};

	public:

		SimplePartition();
		virtual ~SimplePartition() override;
		virtual void Reset() override;
		virtual void Add(StaticEntity*) override; //TODO: Why can't I pass a reference here?
		virtual Iterator<StaticEntity> begin() override;
		virtual Iterator<StaticEntity> end() override;
		static long getCapacity();

	private:

		static const long capacity = 1000;
		long count;
		StaticEntity* elements[capacity];

	};

}

#endif
