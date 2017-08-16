#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Networking\Socket.hpp"

#include <chrono>
#include <thread>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std::chrono_literals;

namespace Test
{

	TEST_CLASS(Socket)
	{
	public:

		TEST_METHOD(SendAndReceive)
		{
			net::Address a1{ 127, 0, 0, 1, 11111 }, a2{ 127, 0, 0, 1, 22222 };
			net::Socket sender, responder;
			const char hello[] = "heLlo";
			const char world[] = "woRld";

			sender.Open(a1.GetPort());
			responder.Open(a2.GetPort());

			sender.Send(a2, hello, sizeof(hello));

			std::this_thread::sleep_for(10ms);
			net::Address from;
			int bytes_read = responder.Receive(from);
			Assert::AreNotEqual(0, bytes_read, L"Received zero bytes.");
			Assert::IsFalse(bytes_read < 0, L"Receive failed.");
			Assert::AreEqual(sizeof(hello), static_cast<size_t>(bytes_read), L"Sent and recevied size do not match.");
			for (int i = 0; i < bytes_read; i++)
			{
				Assert::AreEqual(hello[i], responder.recv_buffer[i], L"This character does not much, which quite likely means that none of them does.");
			}

			responder.Send(a1, world, sizeof(world));

			std::this_thread::sleep_for(10ms);
			bytes_read = sender.Receive(from);
			Assert::AreNotEqual(0, bytes_read, L"Received zero bytes.");
			Assert::IsFalse(bytes_read < 0, L"Receive failed.");
			Assert::AreEqual(sizeof(world), static_cast<size_t>(bytes_read), L"Sent and recevied size do not match.");
			for (int i = 0; i < bytes_read; i++)
			{
				Assert::AreEqual(world[i], sender.recv_buffer[i], L"This character does not much, which quite likely means that none of them does.");
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

			std::this_thread::sleep_for(10ms);
			net::Address from;
			int bytes_read = receiver.Receive(from);
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

			std::this_thread::sleep_for(10ms);
			net::Address from;
			int bytes_read = receiver.Receive(from);
			Assert::AreNotEqual(0, static_cast<int>(from.GetPort()), L"Ports do not match.");
		}

	};

}
