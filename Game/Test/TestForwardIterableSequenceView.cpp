#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Utilities\ForwardIterableSequenceView.hpp"
#include "..\Entities\Entities.hpp"

#include <vector>
#include <algorithm>
#include <list>


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
			#pragma warning( suppress : 4312 )
			std::transform(v1.begin(), v1.end(), v2.begin(), [](int i) { return reinterpret_cast<pointer>(i); });
			utils::ForwardIterableSequenceView<container> view{ v2 };
			#pragma warning( suppress : 4302 4311 )
			Assert::AreEqual(v1.front(), reinterpret_cast<int>(*view.begin()), L"Failed to correctly retrieve first element of a single container.");

			std::vector<int> v3{ 4, 5, 6 };
			container v4(v3.size());
			#pragma warning( suppress : 4312 )
			std::transform(v3.begin(), v3.end(), v4.begin(), [](int i) { return reinterpret_cast<pointer>(i); });
			view.Append(v4);
			#pragma warning( suppress : 4302 4311 )
			Assert::AreEqual(v1.front(), reinterpret_cast<int>(*view.begin()), L"Failed to correctly retrieve first element of a sequence of containers.");
		}

		TEST_METHOD(IterateThroughAContainer)
		{
			std::vector<int> v1{ 1, 2, 3 };
			container v2(v1.size());
			#pragma warning( suppress : 4312 )
			std::transform(v1.begin(), v1.end(), v2.begin(), [](int i) { return reinterpret_cast<pointer>(i); });
			utils::ForwardIterableSequenceView<container> view{ v2 };
			size_t i = 0;
			for (auto& entity : view)
			{
				#pragma warning( suppress : 4302 4311 )
				Assert::AreEqual(v1[i], reinterpret_cast<int>(entity), L"Iterating through the sequence of one container yielded unexpected value.");
				i++;
			}
			Assert::AreEqual(v1.size(), i, L"Failed to enumerate all of the elements of a container.");
		}

		TEST_METHOD(IterateThroughMultipleContainers)
		{
			std::vector<int> v1{ 1, 2, 3 };
			container v2(v1.size());
			#pragma warning( suppress : 4312 )
			std::transform(v1.begin(), v1.end(), v2.begin(), [](int i) { return reinterpret_cast<pointer>(i); });
			std::vector<int> v3{ 4, 5, 6, 7 };
			container v4(v3.size());
			#pragma warning( suppress : 4312 )
			std::transform(v3.begin(), v3.end(), v4.begin(), [](int i) { return reinterpret_cast<pointer>(i); });
			std::vector<int> v5{ 8, 9, 10 };
			container v6(v5.size());
			#pragma warning( suppress : 4312 )
			std::transform(v5.begin(), v5.end(), v6.begin(), [](int i) { return reinterpret_cast<pointer>(i); });
			utils::ForwardIterableSequenceView<container> view{ v2 };
			view.Append(v4);
			view.Append(v6);
			v1.insert(v1.end(), v3.begin(), v3.end());
			v1.insert(v1.end(), v5.begin(), v5.end());
			size_t i = 0;
			for (auto& entity : view)
			{
				#pragma warning( suppress : 4302 4311 )
				Assert::AreEqual(v1[i], reinterpret_cast<int>(entity), L"Iterating through the sequence of multiple containers yielded unexpected value.");
				i++;
			}
			Assert::AreEqual(v1.size(), i, L"Failed to enumerate all of the elements of a sequence of containers.");
		}

		TEST_METHOD(PassByReference)
		{
			std::vector<int> v1{ 1, 2, 3 };
			std::vector<int> v2{ v1 };
			utils::ForwardIterableSequenceView<std::vector<int>> view{ v2 };
			for (auto& entity : view)
			{
				entity *= 2;
			}
			for (size_t i = 0; i < v1.size(); i++)
			{
				Assert::AreEqual(v1[i] * 2, v2[i], L"Failed to change one of the values in the original container. Maybe it is not passed by reference?");
			}
		}

		TEST_METHOD(IterateThroughLists)
		{
			std::list<int> l1{ 5, 2, -4 };
			std::list<int> l2{ 6, 23, 0, 144, 5, 5 };
			std::vector<int> v;
			v.insert(v.end(), l1.begin(), l1.end());
			v.insert(v.end(), l2.begin(), l2.end());
			utils::ForwardIterableSequenceView<std::list<int>> view{ l1 };
			view.Append(l2);
			size_t i = 0;
			for (auto& entity : view)
			{
				Assert::AreEqual(v[i], entity, L"Iterating through the sequence of multiple lists yielded unexpected value.");
				i++;
			}
			Assert::AreEqual(v.size(), i, L"Failed to enumerate all of the elements of a sequence of lists.");
		}

	};

}
