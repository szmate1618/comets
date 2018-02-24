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

		TEST_METHOD(BeginEnd)
		{
			std::vector<int> v1{ 1, 2, 3 };
			container v2(v1.size());
			std::transform(v1.begin(), v1.end(), v2.begin(), [](int i) { return reinterpret_cast<pointer>(i); });
			utils::ForwardIterableSequenceView<container> view{ v2 };
			Assert::AreEqual(v1.front(), reinterpret_cast<int>(*view.begin()), L"Failed to correctly retrieve first element of a single container.");

			std::vector<int> v3{ 4, 5, 6 };
			container v4(v3.size());
			std::transform(v3.begin(), v3.end(), v4.begin(), [](int i) { return reinterpret_cast<pointer>(i); });
			view.Append(v4);
			Assert::AreEqual(v1.front(), reinterpret_cast<int>(*view.begin()), L"Failed to correctly retrieve first element of a sequence of containers.");
		}

		TEST_METHOD(IterateThroughAContainer)
		{
			std::vector<int> v1{ 1, 2, 3 };
			container v2(v1.size());
			std::transform(v1.begin(), v1.end(), v2.begin(), [](int i) { return reinterpret_cast<pointer>(i); });
			utils::ForwardIterableSequenceView<container> view(v2);
			size_t i = 0;
			for (auto p_entity : view)
			{
				Assert::AreEqual(v1[i], reinterpret_cast<int>(p_entity), L"Iterating through the sequence of one container yielded unexpected value.");
				i++;
			}
			Assert::AreEqual(v1.size(), i, L"Failed to enumerate all of the elements of a container.");
		}

	};

}
