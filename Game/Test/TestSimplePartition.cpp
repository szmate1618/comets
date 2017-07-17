#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Entities\SimplePartition.hpp"

#include <assert.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(TestSimplePartition)
	{

		typedef entity::StaticEntity* const pointer;
		typedef entity::Iterator<pointer> iterator;

	public:
		
		TEST_METHOD(TestAddNumbers)
		{
			entity::SimplePartition partition;

			const long n = 10000; //TODO: Refactor these into an initializer method.
			assert(n >= partition.getCapacity());
			long numbers[n];
			for (long i = 0; i < n; i++)
			{
				numbers[i] = i + 1;
			}

			for(long i = 0; i < partition.getCapacity(); ++i)
			{
				partition.Add((pointer)numbers[i]);
			}

			long j = 1;
			for (iterator i = partition.begin(); i != partition.end(); i++)
			{
				Assert::AreEqual(j, (long)(*i), L"Failed to retrieve an inserted element.");
				j++;
			}
		}

		TEST_METHOD(TestNestedLoops)
		{
		}

	};
}
