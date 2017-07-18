#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Entities\SimplePartitioner.hpp"

#include <assert.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	//This test class assumes that the partition itself is already tested, only need to test the partitioner logic.
	TEST_CLASS(TestSimplePartitioner)
	{
		
		typedef geo::Frame<entity::StaticEntity>& reference;
		typedef entity::Iterator<entity::AbstractPartition* const> iterator;

		entity::SimplePartitioner InitPartitioner(long input_array[], long count)
		{
			entity::SimplePartitioner partitioner;
			//assert(count <= (*(partitioner.begin())).getCapacity());
			for(long i = 0; i < count; ++i)
			{
				partitioner.Insert((reference)input_array[i]);
			}
			return partitioner;
		}

	public:
		
		TEST_METHOD(TestInsertAndRetrieve)
		{
			entity::SimplePartitioner partitioner;

			geo::EmptyFrame frame1 = {0, 1, 0, 1};
		}

	};
}