#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Networking\Address.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(Address)
	{
	public:

		TEST_METHOD(TestConstructor01)
		{
			net::Address address(123, 456, 789, 101, 11213);
			Assert::AreEqual(static_cast<unsigned char>(123), address.GetA(), L"Incorrect A value.");
			Assert::AreEqual(static_cast<unsigned char>(456), address.GetB(), L"Incorrect D value.");
			Assert::AreEqual(static_cast<unsigned char>(789), address.GetC(), L"Incorrect C value.");
			Assert::AreEqual(static_cast<unsigned char>(101), address.GetD(), L"Incorrect D value.");
			Assert::AreEqual(static_cast<unsigned short>(11213), address.GetPort(), L"Incorrect port.");
		}		

		TEST_METHOD(TestConstructor02)
		{
			net::Address address(0xAABBCCDD, 44444);
			Assert::AreEqual(static_cast<unsigned char>(0xAA), address.GetA(), L"Incorrect A value.");
			Assert::AreEqual(static_cast<unsigned char>(0xBB), address.GetB(), L"Incorrect D value.");
			Assert::AreEqual(static_cast<unsigned char>(0xCC), address.GetC(), L"Incorrect C value.");
			Assert::AreEqual(static_cast<unsigned char>(0xDD), address.GetD(), L"Incorrect D value.");
			Assert::AreEqual(static_cast<unsigned short>(44444), address.GetPort(), L"Incorrect port.");
		}
	};

}
