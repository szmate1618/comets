#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Networking\Packets.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
			uint16_t count; //This is intentionally less than the actual length of the array, for testing.
			uint32_t elements[10];
			DummyPacket() = default;
			DummyPacket(bool)
			{
				F = 1.25;
				D = 2.03125;
				UI8 = 3;
				UI16 = 4;
				UI32 = 5;
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
			Assert::AreEqual(long{ dummy_with_data.UI16 }, long{ dummy_empty.UI16 }, L"Failed to write and/or to read back uint16_t.");
			Assert::AreEqual(dummy_with_data.UI32, dummy_empty.UI32, L"Failed to write and/or to read back uint32_t.");
			Assert::AreEqual(long{ dummy_with_data.count }, long{ dummy_empty.count }, L"Failed to write and/or to read back count.");
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

		TEST_METHOD(UserInputPacket)
		{
			net::UserInputPacket uip;
		}

	};

}
