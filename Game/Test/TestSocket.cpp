#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Networking\Socket.hpp"

#include <chrono>
#include <thread>
#include <map>
#include <iostream>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std::chrono_literals;

namespace Test
{

	TEST_CLASS(Socket)
	{
	public:

		TEST_METHOD(SendAndReceive)
		{
			net::Address address1{ 127, 0, 0, 1, 11111 }, address2{ 127, 0, 0, 1, 22222 };
			net::Socket sender, responder;
			const char hello[] = "heLlo";
			const char world[] = "woRld";

			sender.Open(address1.GetPort());
			responder.Open(address2.GetPort());

			sender.Send(address2, hello, sizeof(hello));

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

			responder.Send(address1, world, sizeof(world));

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
			net::Address address1{ 127, 0, 0, 1, 11111 }, address2{ 127, 0, 0, 1, 22222 };
			net::Socket sender, receiver;
			const char hello[] = "heLlo";

			sender.Open(address1.GetPort());
			receiver.Open(address2.GetPort());

			sender.Send(address2, hello, sizeof(hello));

			std::this_thread::sleep_for(10ms);
			net::Address from;
			int bytes_read = receiver.Receive(from);
			Assert::AreEqual(address1.GetAddress(), from.GetAddress(), L"Addresses do not match.");
			Assert::AreEqual(static_cast<int>(address1.GetPort()), static_cast<int>(from.GetPort()), L"Ports do not match."); //Why on Earth do I need this cast here?!
		}

		TEST_METHOD(UnspecifiedPort)
		{
			net::Address address{ 127, 0, 0, 1, 11111 };
			net::Socket sender, receiver;
			const char hello[] = "heLlo";

			sender.Open(0);
			receiver.Open(address.GetPort());

			sender.Send(address, hello, sizeof(hello));

			std::this_thread::sleep_for(10ms);
			net::Address from;
			int bytes_read = receiver.Receive(from);
			Assert::AreNotEqual(0, static_cast<int>(from.GetPort()), L"Ports do not match.");
		}

		TEST_METHOD(ExternalBuffer)
		{
			net::Address address1{ 127, 0, 0, 1, 11111 }, address2{ 127, 0, 0, 1, 22222 };
			net::Socket sender, responder;
			const char message[] = "Mortal Wombat III";

			sender.Open(address1.GetPort());
			responder.Open(address2.GetPort());

			sender.Send(address2, message, sizeof(message));

			std::this_thread::sleep_for(10ms);
			net::Address from;
			char buffer[sizeof(message)];
			int bytes_read = responder.Receive(from, buffer, sizeof(buffer));
			Assert::AreNotEqual(0, bytes_read, L"Received zero bytes.");
			Assert::IsFalse(bytes_read < 0, L"Receive failed.");
			Assert::AreEqual(sizeof(message), static_cast<size_t>(bytes_read), L"Sent and recevied size do not match.");
			for (int i = 0; i < bytes_read; i++)
			{
				Assert::AreEqual(message[i], buffer[i], L"This character does not much, which quite likely means that none of them does.");
			}
		}

		TEST_METHOD(TooSmallExternalBuffer)
		{
			net::Address address1{ 127, 0, 0, 1, 11111 }, address2{ 127, 0, 0, 1, 22222 };
			net::Socket sender, responder;
			const char message[] = "Mortal Wombat III";

			sender.Open(address1.GetPort());
			responder.Open(address2.GetPort());

			sender.Send(address2, message, sizeof(message));

			std::this_thread::sleep_for(10ms);
			net::Address from;
			char buffer[sizeof(message) - 1];
			int bytes_read = responder.Receive(from, buffer, sizeof(buffer));
			Assert::AreEqual(-1, bytes_read, L"Error: failed to fail.");

			sender.Send(address2, message, sizeof(message) - 1);

			std::this_thread::sleep_for(10ms);
			bytes_read = responder.Receive(from, buffer, sizeof(buffer));
			Assert::AreNotEqual(-1, bytes_read, L"Error: failed to succeed.");
		}

		//Apparently what I was trying here is simply not possible:
		//https://stackoverflow.com/questions/12714922/how-to-re-bind-a-udp-socket-in-linux
		/*TEST_METHOD(OpenClose)
		{
			net::Socket socket;
			Assert::IsFalse(socket.IsOpen(), L"Socket is open before opening.");
			socket.Open(0);
			Assert::IsTrue(socket.IsOpen(), L"Socket is closed after opening.");
			socket.Open(0);
			Assert::IsTrue(socket.IsOpen(), L"Socket is closed after opening again.");
			socket.Close();
			Assert::IsFalse(socket.IsOpen(), L"Socket is open after closing.");
		}*/

		TEST_METHOD(LogErrors)
		{
			class MySocket: net::Socket { public: void MyLogBindErrors(int e) { LogNetworkErrors(e); } } s;
			std::map<int, const char*> errortexts = 
			{
				{WSANOTINITIALISED, "WSANOTINITIALISED"},
				{WSAENETDOWN, "WSAENETDOWN"},
				{WSAEACCES, "WSAEACCES"},
				{WSAEADDRINUSE, "WSAEADDRINUSE"},
				{WSAEADDRNOTAVAIL, "WSAEADDRNOTAVAIL"},
				{WSAEFAULT, "WSAEFAULT"},
				{WSAEINPROGRESS, "WSAEINPROGRESS"},
				{WSAEINVAL, "WSAEINVAL"},
				{WSAENOBUFS, "WSAENOBUFS" },
				{WSAENOTSOCK, "WSAENOTSOCK"}
			};
			std::stringstream buffer; //We redirect cout into this buffer.
			std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
			for (auto entry : errortexts)
			{
				s.MyLogBindErrors(entry.first);
				Assert::AreEqual({ entry.second }, buffer.str().substr(buffer.str().find('\n') + 18, std::strlen(entry.second)));
				buffer.str("");
				buffer.clear();
			}
			std::cout.rdbuf(old); //Restore original stdout target.
		}

		TEST_METHOD(NonBlockingMode)
		{
			net::Socket socket{ 0 };

			net::Address from;
			char buffer[10];
			int bytes_read = socket.Receive(from, buffer, sizeof(buffer));
			//If this hangs indefinitely, the socket is still in blocking mode.
		}

	};

}
