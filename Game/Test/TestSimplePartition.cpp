#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Entities\SimplePartition.hpp"

#include <assert.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(TestSimplePartition)
	{
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
				partition.Add((entity::StaticEntity* const)numbers[i]);
			}

			long j = 1;
			for (entity::Iterator<entity::StaticEntity* const> i = partition.begin(); i != partition.end(); i++)
			{
				Assert::AreEqual(j, (long)(*i), L"Failed to retrieve an inserted element.");
				j++;
			}
			Assert::IsTrue(true);//If there's a Fail, why is there no Success?
		}

	};
}