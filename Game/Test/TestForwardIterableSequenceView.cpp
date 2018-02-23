#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Utilities\ForwardIterableSequenceView.hpp"
#include "..\Entities\Entities.hpp"

#include <vector>
#include <algorithm> 


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(TestForwardIterableSequenceView)
	{

		using pointer = entity::StaticEntity*;
		using container = std::vector<pointer>;

	public:

		TEST_METHOD(Constructor)
		{
			std::vector<int> v1{ 1,2,3 };
			container v2(v1.size());
			std::transform(v1.begin(), v1.end(), v2.begin(), [](int i) { return reinterpret_cast<pointer>(i); });
			utils::ForwardIterableSequenceView<container> view(v2);
			int i = 0;
			for (auto p_entity : view)
			{
				Assert::AreEqual(v1[i], reinterpret_cast<int>(p_entity), L"Iterating through the sequence yielded unexpected value.");
				i++;
			}
		}

	};

}
