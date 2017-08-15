#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Networking\Socket.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(Socket)
	{
	public:

		TEST_METHOD(SendAndReceive)
		{
			net::Address a1{ 127, 0, 0, 1, 11111 }, a2{ 127, 0, 0, 1, 22222 };
			net::Socket sender, receiver;
			const char hello[] = "heLlo";
			const char world[] = "woRld";

			sender.Open(a1.GetPort());
			receiver.Open(a2.GetPort());

			sender.Send(a2, hello, sizeof(hello));

			// TODO: Add delay here.
			net::Address from;
			int bytes_read;
			while ((bytes_read = receiver.Receive(from)) <= 0) {} 
			Assert::AreEqual(sizeof(hello), static_cast<unsigned long long>(bytes_read), L"Sent and recevied size do not match.");
			for (int i = 0; i < bytes_read; i++)
			{
				Assert::AreEqual(hello[i], receiver.recv_buffer[i], L"This character does not much, which quite likely means that none of them does.");
			}
		}

		TEST_METHOD(GetAddress)
		{
			net::Address a1{ 127, 0, 0, 1, 11111 }, a2{ 127, 0, 0, 1, 22222 };
			net::Socket sender, receiver;
			const char hello[] = "heLlo";

			sender.Open(a1.GetPort());
			receiver.Open(a2.GetPort());

			sender.Send(a2, hello, sizeof(hello));

			// TODO: Add delay here.
			net::Address from;
			int bytes_read;
			while ((bytes_read = receiver.Receive(from)) <= 0) {}
			Assert::AreEqual(a1.GetAddress(), from.GetAddress(), L"Addresses do not match.");
			Assert::AreEqual(static_cast<int>(a1.GetPort()), static_cast<int>(from.GetPort()), L"Ports do not match."); //Why on Earth do I need this cast here?!
		}

		TEST_METHOD(UnspecifiedPort)
		{
			net::Address a2{ 127, 0, 0, 1, 11111 };
			net::Socket sender, receiver;
			const char hello[] = "heLlo";

			sender.Open(0);
			receiver.Open(a2.GetPort());

			sender.Send(a2, hello, sizeof(hello));

			// TODO: Add delay here.
			net::Address from;
			int bytes_read;
			while ((bytes_read = receiver.Receive(from)) <= 0) {}
			Assert::AreNotEqual(0, static_cast<int>(from.GetPort()), L"Ports do not match.");
		}

	};

}
