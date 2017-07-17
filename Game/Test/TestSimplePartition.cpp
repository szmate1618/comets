#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Entities\SimplePartition.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(TestSimplePartition)
	{
	public:
		
		TEST_METHOD(TestAdd)
		{
			entity::SimplePartition partition;
			entity::StaticEntity entity;
			for(long i = 0; i < partition.getCapacity(); ++i)
			{
				partition.Add(&entity);
			}
		}

	};
}