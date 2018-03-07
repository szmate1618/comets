#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Entities\SimplePartitioner.hpp"

#include <cassert>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	/*//This test class assumes that the partition itself is already tested, only need to test the partitioner logic.
	TEST_CLASS(TestSimplePartitioner)
	{
		
		typedef geo::Frame<entity::StaticEntity>& reference;
		typedef entity::Iterator<entity::AbstractPartition* const> iterator;

		void InitPartitioner(entity::SimplePartitioner& partitioner, const long input_array[], const long count)
		{
			assert(count <= ((entity::SimplePartition*)*partitioner.begin())->getCapacity()); //This is funky.
			for(long i = 0; i < count; ++i)
			{
				partitioner.Insert((reference)input_array[i]);
			}
		}

	public:
		
		TEST_METHOD(InsertAndRetrieve)
		{
			entity::SimplePartitioner partitioner;

			geo::Frame<entity::StaticEntity> frame;
			frame.minx = 0;
			frame.maxx = 1;
			frame.miny = 0;
			frame.maxy = 1;
			frame.entity = (entity::StaticEntity*)1;

			partitioner.Insert(frame);

			int count = 0;
			for(const iterator& i: partitioner)
			{
				for(const auto j: (**i))
				{
					#pragma warning( suppress : 4302 4311 )
					Assert::AreEqual(1, reinterpret_cast<int>(j), L"Failed to retrieve correct entity pointer.");
				}
			}
		}

	};*/

}
