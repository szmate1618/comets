#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Networking\Socket.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(Socket)
	{
	public:

		TEST_METHOD(TestSendAndReceive)
		{
			net::Address a1{ 127, 0, 0, 1, 11111 }, a2{ 127, 0, 0, 1, 22222 };
			net::Socket s1, s2;
			const char hello[] = "heLlo";
			const char world[] = "woRld";

			s1.Open(a1.GetPort());
			s2.Open(a2.GetPort());

			s1.Send(a2, hello, sizeof(hello));

			// TODO: Add delay here.
			net::Address from;
			int bytes_read;
			while ((bytes_read = s2.Receive(from)) <= 0) {} 
			Assert::AreEqual(sizeof(hello), static_cast<unsigned long long>(bytes_read), L"Sent and recevied size do not match.");
			for (int i = 0; i < bytes_read; i++)
			{
				Assert::AreEqual(hello[i], s2.recv_buffer[i], L"This character does not much, which quite likely means that none of them does.");
			}
		}

		TEST_METHOD(TestGetAddress)
		{
			net::Address a1{ 127, 0, 0, 1, 11111 }, a2{ 127, 0, 0, 1, 22222 };
			net::Socket s1, s2;
			const char hello[] = "heLlo";

			s1.Open(a1.GetPort());
			s2.Open(a2.GetPort());

			s1.Send(a2, hello, sizeof(hello));

			// TODO: Add delay here.
			net::Address from;
			int bytes_read;
			while ((bytes_read = s2.Receive(from)) <= 0) {}
			Assert::AreEqual(a1.GetAddress(), from.GetAddress(), L"Addresses do not match.");
			Assert::AreEqual(static_cast<int>(a1.GetPort()), static_cast<int>(from.GetPort()), L"Ports do not match."); //Why on Earth do I need this cast here?!
		}

	};

}
