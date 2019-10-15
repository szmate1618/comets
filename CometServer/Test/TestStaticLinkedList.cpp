#include "stdafx.h"
#include "CppUnitTest.h"

#include "ToStringSpecializations.hpp"
#include "..\Utilities\StaticLinkedList.hpp"

#include <cassert>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(TestStaticLinkedList) //TODO: Add a lot more testcases here.
	{
	public:

		TEST_METHOD(ImplementationDetails)
		{
			utils::StaticLinkedList<int> list(20);
			Assert::AreEqual(2, static_cast<int>(list.InsertAtFirstGap(0)));
		}

		TEST_METHOD(Insert10)
		{
			utils::StaticLinkedList<int> list(20);

			for (int i = 0; i < 10; i++) { list.InsertAtFirstGap(i); }

			int i = 0;
			for (const auto& element : list)
			{
				Assert::AreEqual(i++, element);
			}
			Assert::AreEqual(10, i);
		}

		TEST_METHOD(Insert1000)
		{
			utils::StaticLinkedList<int> list(1010);

			for (int i = 0; i < 1000; i++) { list.InsertAtFirstGap(i); }

			int i = 0;
			for (const auto& element : list)
			{
				Assert::AreEqual(i++, element);
			}
			Assert::AreEqual(1000, i);
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(Insert1000000)
			TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()

		TEST_METHOD(Insert1000000)
		{
			utils::StaticLinkedList<int> list(1'000'020);

			for (int i = 0; i < 1'000'000; i++) { list.InsertAtFirstGap(i); }

			int i = 0;
			for (const auto& element : list)
			{
				Assert::AreEqual(i++, element);
			}
			Assert::AreEqual(1'000'000, i);
		}

		TEST_METHOD(RemoveAt8)
		{
			utils::StaticLinkedList<int> list(20);

			int element_at_7;
			for (int i = 0; i < 10; i++) { if (list.InsertAtFirstGap(i) == 7) element_at_7 = i; }
			list.RemoveAt(8);

			int i = 0;
			for (const auto& element : list)
			{
				Assert::AreEqual(i++, element);
				if (element == element_at_7) i++;
			}
			Assert::AreEqual(10, i);
		}

		TEST_METHOD(RemoveAt7And9And8)
		{
			utils::StaticLinkedList<int> list(20);

			int element_at_6;
			for (int i = 0; i < 10; i++) { if (list.InsertAtFirstGap(i) == 6) element_at_6 = i; }
			list.RemoveAt(7);
			list.RemoveAt(9);
			list.RemoveAt(8);

			int i = 0;
			for (const auto& element : list)
			{
				Assert::AreEqual(i++, element);
				if (element == element_at_6) i+= 3;
			}
			Assert::AreEqual(10, i);
		}

		TEST_METHOD(Remove1Repeatedly)
		{
			utils::StaticLinkedList<int> list(10);

			list.RemoveAt(list.InsertAtFirstGap(0));
			list.RemoveAt(list.InsertAtFirstGap(0));

			size_t index = list.InsertAtFirstGap(0);

			int i = 0;
			for (const auto& element : list)
			{
				Assert::AreEqual(i++, element);
			}
			Assert::AreEqual(1, i);

			list.RemoveAt(index);

			i = 0;
			for (const auto& element : list)
			{
				i++;
			}
			Assert::AreEqual(0, i);
		}


		TEST_METHOD(InsertIntoGap)
		{
			utils::StaticLinkedList<int> list(10);

			list.InsertAtFirstGap(0);
			size_t index  = list.InsertAtFirstGap(1);
			list.InsertAtFirstGap(2);

			list.RemoveAt(index);

			Assert::AreEqual(index, list.InsertAtFirstGap(1));
		}

	};

}
