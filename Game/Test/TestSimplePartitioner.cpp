#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Entities\SimplePartitioner.hpp"

#include <cassert>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	//This test class assumes that the partition itself is already tested, only need to test the partitioner logic.
	TEST_CLASS(TestSimplePartitioner)
	{

		void InitPartitioner(entity::SimplePartitioner& partitioner, const long input_array[], const long count)
		{
			for(long i = 0; i < count; ++i)
			{
				#pragma warning( suppress : 4312 )
				partitioner.Insert((entity::StaticEntity*)input_array[i]);
			}
		}

	public:
		
		TEST_METHOD(InsertAndRetrieve)
		{
			entity::SimplePartitioner partitioner;
			partitioner.Insert(reinterpret_cast<entity::StaticEntity*>(1337));

			int count = 0;
			for(const auto& i: partitioner)
			{
				for(const auto& j: i)
				{
					#pragma warning( suppress : 4302 4311 )
					Assert::AreEqual(1337, reinterpret_cast<int>(j), L"Failed to retrieve correct entity pointer.");
				}
			}
		}

	};

}
