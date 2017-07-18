#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Entities\SimplePartition.hpp"

#include <assert.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(TestSimplePartition) //TODO: Add more testcases here, mainly for testing Iterator methods separately.
	{

		typedef entity::StaticEntity* const pointer;
		typedef entity::Iterator<pointer> iterator;

		entity::SimplePartition InitPartition(long input_array[], long count)
		{
			entity::SimplePartition partition;
			assert(count <= partition.getCapacity());
			for(long i = 0; i < count; ++i)
			{
				partition.Add((pointer)input_array[i]);
			}
			return partition;
		}

	public:

		TEST_METHOD(TestFill)
		{
			const long n = 10000;
			assert(n >= entity::SimplePartition::getCapacity()); //Make sure we generate enough elements to fill the full capacity.
			long numbers[n];
			for (long i = 0; i < n; i++)
			{
				numbers[i] = i + 1;
			}
			entity::SimplePartition partition = InitPartition(numbers, entity::SimplePartition::getCapacity()); //Fill up to full capacity.


			long j = 1;
			for (iterator i = partition.begin(); i != partition.end(); i++)
			{
				Assert::AreEqual(j, (long)(*i), L"Failed to retrieve an inserted element.");
				j++;
			}
		}

		TEST_METHOD(TestNestedLoops)
		{
			long numbers[] = {1, 2};
			entity::SimplePartition partition = InitPartition(numbers, sizeof(numbers) / sizeof(long));
			long accumulator = 0;
			for(iterator i: partition)
			{
				for(iterator j: partition)
				{
					(accumulator *= 100) += 10 * (long)(*i) + (long)(*j);
				}
			}
			Assert::AreEqual(11122122L, accumulator, L"Apparently things got tangled up in this nested iteration.");
		}

		TEST_METHOD(TestNestedLoopsWithContinue)
		{
			long numbers[] = {1, 2, 3};
			entity::SimplePartition partition = InitPartition(numbers, sizeof(numbers) / sizeof(long));
			long accumulator = 0;
			for(iterator i: partition)
			{
				if ((long)(*i) == 1) continue;
				for(iterator j: partition)
				{
					if ((long)(*j) == 2) continue;
					(accumulator *= 100) += 10 * (long)(*i) + (long)(*j);
				}
			}
			Assert::AreEqual(21233133L, accumulator, L"Apparently things got tangled up in this continued nested iteration.");
		}
	};
}
