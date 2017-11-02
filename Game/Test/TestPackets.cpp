#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Networking\Packets.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittest = Microsoft::VisualStudio::CppUnitTestFramework;
template<> inline std::wstring unittest::ToString<uint16_t>(const uint16_t& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring unittest::ToString<net::Header>(const net::Header& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }
template<> inline std::wstring unittest::ToString<net::ServerHeader>(const net::ServerHeader& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }
template<> inline std::wstring unittest::ToString<net::ServerObject>(const net::ServerObject& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }
template<> inline std::wstring unittest::ToString<net::ClientIntputPayload>(const net::ClientIntputPayload& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }
template<> inline std::wstring unittest::ToString<net::ServerStatePayload>(const net::ServerStatePayload& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }
template<> inline std::wstring unittest::ToString<net::ClientIntputPacket>(const net::ClientIntputPacket& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }
template<> inline std::wstring unittest::ToString<net::ServerStatePacket>(const net::ServerStatePacket& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }

namespace Test
{

	TEST_CLASS(Packets)
	{

		class DummyPacket
		{
		public:
			float F;
			double D;
			uint8_t UI8;
			uint16_t UI16;
			uint32_t UI32;
			uint16_t count;
			uint32_t elements[10];
			DummyPacket() = default;
			DummyPacket(bool)
			{
				F = 1.25;
				D = 2.03125;
				UI8 = 250;
				UI16 = 65'000;
				UI32 = 4'000'000'000;
				count = 5; //This is intentionally less than the actual length of the array, for testing.
				elements[0] = 6;
				elements[1] = 7;
				elements[2] = 8;
				elements[3] = 9;
				elements[4] = 10;
			}
			template<typename io_mode>	size_t IO(uint8_t* packet_data_start)
			{
				uint8_t* packet_data_current = packet_data_start;
				packet_data_current += io_mode::Process(packet_data_current, F);
				packet_data_current += io_mode::Process(packet_data_current, D);
				packet_data_current += io_mode::Process(packet_data_current, UI8);
				packet_data_current += io_mode::Process(packet_data_current, UI16);
				packet_data_current += io_mode::Process(packet_data_current, UI32);
				packet_data_current += io_mode::Process(packet_data_current, count);
				for (uint32_t* i = elements; i - elements < count; ++i)
				{
					packet_data_current += io_mode::Process(packet_data_current, *i);
				}
				return packet_data_current - packet_data_start;
			}
		};

	public:

		TEST_METHOD(BinarySerialization)
		{
			DummyPacket dummy_empty;
			uint32_t original_tail[5] = { dummy_empty.elements[5], dummy_empty.elements[6], dummy_empty.elements[7], dummy_empty.elements[8], dummy_empty.elements[9] };
			DummyPacket dummy_with_data{ true };
			uint8_t buffer[def::max_packet_size];

			dummy_with_data.IO<net::Write>(buffer);
			dummy_empty.IO<net::Read>(buffer);

			Assert::AreEqual(dummy_with_data.F, dummy_empty.F, L"Failed to write and/or to read back float.");
			Assert::AreEqual(dummy_with_data.D, dummy_empty.D, L"Failed to write and/or to read back double.");
			Assert::AreEqual(dummy_with_data.UI8, dummy_empty.UI8, L"Failed to write and/or to read back uint8_t.");
			Assert::AreEqual(dummy_with_data.UI16, dummy_empty.UI16, L"Failed to write and/or to read back uint16_t.");
			Assert::AreEqual(dummy_with_data.UI32, dummy_empty.UI32, L"Failed to write and/or to read back uint32_t.");
			Assert::AreEqual(dummy_with_data.count, dummy_empty.count, L"Failed to write and/or to read back count.");
			Assert::AreEqual(dummy_with_data.elements[0], dummy_empty.elements[0], L"Failed to write and/or to read back elements[0].");
			Assert::AreEqual(dummy_with_data.elements[1], dummy_empty.elements[1], L"Failed to write and/or to read back elements[1].");
			Assert::AreEqual(dummy_with_data.elements[2], dummy_empty.elements[2], L"Failed to write and/or to read back elements[2].");
			Assert::AreEqual(dummy_with_data.elements[3], dummy_empty.elements[3], L"Failed to write and/or to read back elements[3].");
			Assert::AreEqual(dummy_with_data.elements[4], dummy_empty.elements[4], L"Failed to write and/or to read back elements[4].");
			Assert::AreEqual(original_tail[0], dummy_empty.elements[5], L"Accidentally overwrote elements[5].");
			Assert::AreEqual(original_tail[1], dummy_empty.elements[6], L"Accidentally overwrote elements[6].");
			Assert::AreEqual(original_tail[2], dummy_empty.elements[7], L"Accidentally overwrote elements[7].");
			Assert::AreEqual(original_tail[3], dummy_empty.elements[8], L"Accidentally overwrote elements[8].");
			Assert::AreEqual(original_tail[4], dummy_empty.elements[9], L"Accidentally overwrote elements[9].");
		}

		TEST_METHOD(Header)
		{
			net::Header header_empty{};
			net::Header header_with_data{ 1, 2, 3 };
			uint8_t buffer[def::max_packet_size];

			header_with_data.IO<net::Write>(buffer);
			header_empty.IO<net::Read>(buffer);

			Assert::AreEqual(header_with_data, header_empty, L"Failed to write and/or read back Header.");
		}

		TEST_METHOD(ServerHeader)
		{
			net::ServerHeader header_empty{};
			net::ServerHeader header_with_data{ 1, 2, 3, 4, 5 };
			uint8_t buffer[def::max_packet_size];

			header_with_data.IO<net::Write>(buffer);
			header_empty.IO<net::Read>(buffer);

			Assert::AreEqual(header_with_data, header_empty, L"Failed to write and/or read back ServerHeader.");
		}

		TEST_METHOD(ServerObject)
		{
			net::ServerObject serverobject_empty{};
			net::ServerObject serverobject_with_data{ 1, 2, 3, 4 };
			uint8_t buffer[def::max_packet_size];

			serverobject_with_data.IO<net::Write>(buffer);
			serverobject_empty.IO<net::Read>(buffer);

			Assert::AreEqual(serverobject_with_data, serverobject_empty, L"Failed to write and/or read back ServerObject.");
		}

		TEST_METHOD(ClientIntputPayload)
		{
			uint8_t empty_input_buffer[10];
			net::ClientIntputPayload ClientIntput_empty{};
			ClientIntput_empty.inputs = empty_input_buffer;
			uint8_t inputs[4] = { 5, 6, 7, 8 };
			net::ClientIntputPayload ClientIntput_with_data{ 334, 34, 4, inputs };
			uint8_t buffer[def::max_packet_size];

			ClientIntput_with_data.IO<net::Write>(buffer);
			ClientIntput_empty.IO<net::Read>(buffer);

			Assert::AreEqual(ClientIntput_with_data, ClientIntput_empty, L"Failed to write and/or read back ClientIntputPayload.");
		}

		TEST_METHOD(ServerStatePayload)
		{
			net::ServerObject empty_input_buffer[10];
			net::ServerStatePayload serverstate_empty{};
			serverstate_empty.objects = empty_input_buffer;
			net::ServerObject objects[6] = { { 5, 5.0, 5.1, 5.2 },{ 6, 6.1, 6.2, 6.3 },{ 7, 7.1, 7.2, 7.3 },{ 8, 8.1, 8.2, 8.3 },{ 9, 9.1, 9.2, 9.3 },{ 10, 10.1, 10.2, 10.3 } };
			net::ServerStatePayload serverstate_with_data{ 6, objects };
			uint8_t buffer[def::max_packet_size];

			serverstate_with_data.IO<net::Write>(buffer);
			serverstate_empty.IO<net::Read>(buffer);

			Assert::AreEqual(serverstate_with_data, serverstate_empty, L"Failed to write and/or read back ServerStatePayload.");
		}

		TEST_METHOD(ClientIntputPacketWithoutArray)
		{
			net::ClientIntputPacket clientintput_empty{};
			net::ClientIntputPacket clientintput_with_data{ 1, 2, 3, 334, 34, 0, nullptr };
			uint8_t buffer[def::max_packet_size];

			clientintput_with_data.IO<net::Write>(buffer);
			clientintput_empty.IO<net::Read>(buffer);

			Assert::AreEqual(clientintput_with_data, clientintput_empty, L"Failed to write and/or read back ClientIntputPacket without array.");
		}

		TEST_METHOD(ClientIntputPacket)
		{
			uint8_t empty_input_buffer[10];
			net::ClientIntputPacket ClientIntput_empty{};
			ClientIntput_empty.payload.inputs = empty_input_buffer;
			uint8_t inputs[4] = { 5, 6, 7, 8 };
			net::ClientIntputPacket ClientIntput_with_data{ 1, 2, 3, 334, 34, 4, inputs };
			uint8_t buffer[def::max_packet_size];

			ClientIntput_with_data.IO<net::Write>(buffer);
			ClientIntput_empty.IO<net::Read>(buffer);

			Assert::AreEqual(ClientIntput_with_data, ClientIntput_empty, L"Failed to write and/or read back ClientIntputPacket.");
		}

		TEST_METHOD(ServerStatePacketWithoutArray)
		{
			net::ServerStatePacket serverstate_empty{};
			net::ServerStatePacket serverstate_with_data{ 1, 2, 3, 4, 5, 0, nullptr };
			uint8_t buffer[def::max_packet_size];

			serverstate_with_data.IO<net::Write>(buffer);
			serverstate_empty.IO<net::Read>(buffer);

			Assert::AreEqual(serverstate_with_data, serverstate_empty, L"Failed to write and/or read back ServerStatePacket without array.");
		}

		TEST_METHOD(ServerStatePacket)
		{
			net::ServerObject empty_input_buffer[10];
			net::ServerStatePacket serverstate_empty{};
			serverstate_empty.payload.objects = empty_input_buffer;
			net::ServerObject objects[6] = { {5, 5.0, 5.1, 5.2}, {6, 6.1, 6.2, 6.3}, {7, 7.1, 7.2, 7.3}, {8, 8.1, 8.2, 8.3}, { 9, 9.1, 9.2, 9.3 }, { 10, 10.1, 10.2, 10.3 } };
			net::ServerStatePacket serverstate_with_data{ 1, 2, 3, 4, 5, 6, objects };
			uint8_t buffer[def::max_packet_size];

			serverstate_with_data.IO<net::Write>(buffer);
			serverstate_empty.IO<net::Read>(buffer);

			Assert::AreEqual(serverstate_with_data, serverstate_empty, L"Failed to write and/or read back ServerStatePacket.");
		}

	};

}
