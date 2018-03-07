#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Entities\SimplePartition.hpp"
#include "..\Utilities\CountOfArray.hpp"

#include <cassert>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	/*TEST_CLASS(TestSimplePartition) //TODO: Add more testcases here, mainly for testing Iterator methods separately.
	{

		using pointer = entity::StaticEntity* const;
		using iterator = entity::Iterator<pointer>;

		void InitPartition(entity::SimplePartition& partition, const long input_array[], const long count)
		{
			assert(count <= partition.getCapacity());
			for(long i = 0; i < count; ++i)
			{
				#pragma warning( suppress : 4312 )
				partition.Add(reinterpret_cast<pointer>(input_array[i]));
			}
		}

	public:

		TEST_METHOD(Fill)
		{
			const long n = 10000;
			assert(n >= entity::SimplePartition::getCapacity()); //Make sure we generate enough elements to fill the full capacity.
			long numbers[n];
			for (long i = 0; i < n; i++)
			{
				numbers[i] = i + 1;
			}
			entity::SimplePartition partition;
			InitPartition(partition, numbers, entity::SimplePartition::getCapacity()); //Fill up to full capacity.


			long j = 1;
			for (iterator i = partition.begin(); i != partition.end(); i++)
			{
				#pragma warning( suppress : 4302 4311 )
				Assert::AreEqual(j, reinterpret_cast<long>(*i), L"Failed to retrieve an inserted element.");
				j++;
			}
		}

		TEST_METHOD(NestedLoops)
		{
			long numbers[] = {1, 2};
			entity::SimplePartition partition;
			InitPartition(partition, numbers, static_cast<long>(util::countof(numbers)));
			long accumulator = 0;
			for(const iterator& i: partition)
			{
				for(const iterator& j: partition)
				{
					#pragma warning( suppress : 4302 4311 )
					(accumulator *= 100) += 10 * reinterpret_cast<long>(*i) + reinterpret_cast<long>(*j);
				}
			}
			Assert::AreEqual(11122122L, accumulator, L"Apparently things got tangled up in this nested iteration.");
		}

		TEST_METHOD(NestedLoopsWithContinue)
		{
			long numbers[] = {1, 2, 3};
			entity::SimplePartition partition;
			InitPartition(partition, numbers, static_cast<long>(util::countof(numbers)));
			long accumulator = 0;
			for(const iterator& i: partition)
			{
				#pragma warning( suppress : 4302 4311 )
				if (reinterpret_cast<long>(*i) == 1) continue;
				for(const iterator& j: partition)
				{
					#pragma warning( suppress : 4302 4311 )
					if (reinterpret_cast<long>(*j) == 2) continue;
					#pragma warning( suppress : 4302 4311 )
					(accumulator *= 100) += 10 * reinterpret_cast<long>(*i) + reinterpret_cast<long>(*j);
				}
			}
			Assert::AreEqual(21233133L, accumulator, L"Apparently things got tangled up in this continued nested iteration.");
		}

	};*/

}
