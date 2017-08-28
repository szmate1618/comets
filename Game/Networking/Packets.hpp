#pragma once

#include "BinarySerialization.hpp"

#include <cstdint>


namespace net
{

	enum packet_types { user_input, server_state };

	struct Header
	{
		uint8_t protocol_id;
		uint32_t sequence_number;
		uint8_t packet_type;

		template<typename io_mode>
		size_t IO(uint8_t* packet_data_start)
		{
			uint8_t* packet_data_current = packet_data_start;
			packet_data_current += io_mode.Process(packet_data_current, protocol_id);
			packet_data_current += Write(packet_data_current, sequence_number);
			return packet_data_current - packet_data_start;
		}
	};

	struct ServerHeader
	{
		Header common_header;
		uint32_t ack;
		uint32_t ack_bitfield;

		template<typename io_mode>
		size_t IO(uint8_t* packet_data_start)
		{
			uint8_t* packet_data_current = packet_data_start;
			packet_data_current += common_header.IO<io_mode>(packet_data_current);
			packet_data_current += io_mode.Process(packet_data_current, ack);
			packet_data_current += io_mode.Process(packet_data_current, ack_bitfield);
			return packet_data_current - packet_data_start;
		}
	};

	struct UserInputPacket
	{
		Header common_header;
		uint8_t count;
		uint8_t* inputs;

		template<typename io_mode>
		size_t IO(uint8_t* packet_data_start)
		{
			uint8_t* packet_data_current = packet_data_start;
			packet_data_current += common_header.IO<io_mode>(packet_data_current);
			packet_data_current += io_mode.Process(packet_data_current, count);
			for (uint8_t* i = inputs; i - inputs < count; i++)
			{
				packet_data_current += io_mode.Process(packet_data_current, *i);
			}
			return packet_data_current - packet_data_start;
		}
	};

	struct ServerObject
	{
		uint32_t type;
		double radian; //TODO: User defined literals for degree and radian.
		double x;
		double y;

		template<typename io_mode>
		size_t IO(uint8_t* packet_data_start)
		{
			uint8_t* packet_data_current = packet_data_start;
			packet_data_current += io_mode.Process(packet_data_current, type);
			packet_data_current += io_mode.Process(packet_data_current, radian);
			packet_data_current += io_mode.Process(packet_data_current, x);
			packet_data_current += io_mode.Process(packet_data_current, y);
			return packet_data_current - packet_data_start;
		}

	};

	struct ServerStatePacket
	{
		Header server_header;
		uint8_t count;
		ServerObject* objects;

		template<typename io_mode>
		size_t IO(uint8_t* packet_data_start)
		{
			uint8_t* packet_data_current = packet_data_start;
			packet_data_current += server_header.IO<io_mode>(packet_data_current);
			packet_data_current += io_mode.Process(packet_data_current, count);
			for (ServerObject* i = objects; i - inputs < count; i++)
			{
				packet_data_current += i->IO<io_mode>(packet_data_current, *i);
			}
			return packet_data_current - packet_data_start;
		}
	};

}
