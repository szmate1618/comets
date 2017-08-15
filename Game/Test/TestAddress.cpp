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
			net::Address address(0xAA, 0xBB, 0xCC, 0xDD, 11213);
			Assert::AreEqual(0xAABBCCDD, address.GetAddress(), L"Icorrect address.");
			Assert::AreEqual(0xAA, static_cast<int>(address.GetA()), L"Incorrect A value.");
			Assert::AreEqual(0xBB, static_cast<int>(address.GetB()), L"Incorrect B value.");
			Assert::AreEqual(0xCC, static_cast<int>(address.GetC()), L"Incorrect C value.");
			Assert::AreEqual(0xDD, static_cast<int>(address.GetD()), L"Incorrect D value.");
			Assert::AreEqual(11213, static_cast<int>(address.GetPort()), L"Incorrect port.");
		}		

		TEST_METHOD(TestConstructor02)
		{
			net::Address address(0xAABBCCDD, 44444);
			Assert::AreEqual(0xAABBCCDD, address.GetAddress(), L"Icorrect address.");
			Assert::AreEqual(0xAA, static_cast<int>(address.GetA()), L"Incorrect A value.");
			Assert::AreEqual(0xBB, static_cast<int>(address.GetB()), L"Incorrect B value.");
			Assert::AreEqual(0xCC, static_cast<int>(address.GetC()), L"Incorrect C value.");
			Assert::AreEqual(0xDD, static_cast<int>(address.GetD()), L"Incorrect D value.");
			Assert::AreEqual(44444, static_cast<int>(address.GetPort()), L"Incorrect port.");
		}
	};

}
