#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Networking\Packets.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(Packets)
	{
	public:

		TEST_METHOD(UserInputPacket)
		{
			net::UserInputPacket uip;
		}

	};

}
