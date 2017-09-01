#pragma once

#include "BinarySerialization.hpp"

#include <cstdint>


//TODO: Refactor this into hpp+cpp.
namespace net
{

	enum packet_types { user_input, server_state };

	class Header
	{
	public:

		uint8_t protocol_id;
		uint32_t sequence_number;
		uint8_t packet_type;

		bool operator==(const Header& other) const
		{
			return protocol_id == other.protocol_id && sequence_number == other.sequence_number && packet_type == other.packet_type;
		}

		template<typename io_mode>
		size_t IO(uint8_t* packet_data_start) const
		{
			uint8_t* packet_data_current = packet_data_start;
			packet_data_current += io_mode.Process(packet_data_current, protocol_id);
			packet_data_current += Write(packet_data_current, sequence_number);
			return packet_data_current - packet_data_start;
		}
	};

	class ServerHeader
	{
	public:

		Header common_header;
		uint32_t ack;
		uint32_t ack_bitfield;

		bool operator==(const ServerHeader& other) const
		{
			return common_header == other.common_header && ack == other.ack && ack_bitfield == other.ack_bitfield;
		}

		template<typename io_mode>
		size_t IO(uint8_t* packet_data_start) const
		{
			uint8_t* packet_data_current = packet_data_start;
			packet_data_current += common_header.IO<io_mode>(packet_data_current);
			packet_data_current += io_mode.Process(packet_data_current, ack);
			packet_data_current += io_mode.Process(packet_data_current, ack_bitfield);
			return packet_data_current - packet_data_start;
		}
	};

	class UserInputPacket
	{
	public:

		Header common_header;
		uint8_t count;
		uint8_t* inputs;

		bool operator==(const UserInputPacket& other) const
		{
			if (!(common_header == other.common_header) || !(count == other.count)) return false;
			for (int i = 0; i < count; ++i)
			{
				if (inputs[i] != other.inputs[i]) return false;
			}
			return true;
		}

		template<typename io_mode>
		size_t IO(uint8_t* packet_data_start) const
		{
			uint8_t* packet_data_current = packet_data_start;
			packet_data_current += common_header.IO<io_mode>(packet_data_current);
			packet_data_current += io_mode.Process(packet_data_current, count);
			for (uint8_t* i = inputs; i - inputs < count; ++i)
			{
				packet_data_current += io_mode.Process(packet_data_current, *i);
			}
			return packet_data_current - packet_data_start;
		}
	};

	class ServerObject
	{
	public:

		uint32_t type;
		double radian; //TODO: User defined literals for degree and radian.
		double x;
		double y;

		bool operator==(const ServerObject& other) const
		{
			return type == other.type && radian == other.radian && x == other.x && y == other.y;
		}

		template<typename io_mode>
		size_t IO(uint8_t* packet_data_start) const
		{
			uint8_t* packet_data_current = packet_data_start;
			packet_data_current += io_mode.Process(packet_data_current, type);
			packet_data_current += io_mode.Process(packet_data_current, radian);
			packet_data_current += io_mode.Process(packet_data_current, x);
			packet_data_current += io_mode.Process(packet_data_current, y);
			return packet_data_current - packet_data_start;
		}

	};

	class ServerStatePacket
	{
	public:

		Header server_header;
		uint8_t count;
		ServerObject* objects;

		bool operator==(const ServerStatePacket& other) const
		{
			if (!(server_header == other.server_header) || !(count == other.count)) return false;
			for (int i = 0; i < count; ++i)
			{
				if (!(objects[i] == other.objects[i])) return false;
			}
			return true;
		}

		template<typename io_mode>
		size_t IO(uint8_t* packet_data_start) const
		{
			uint8_t* packet_data_current = packet_data_start;
			packet_data_current += server_header.IO<io_mode>(packet_data_current);
			packet_data_current += io_mode.Process(packet_data_current, count);
			for (ServerObject* i = objects; i - inputs < count; ++i)
			{
				packet_data_current += i->IO<io_mode>(packet_data_current, *i);
			}
			return packet_data_current - packet_data_start;
		}
	};

	class AbstractExportStrategy
	{
	public:

		AbstractExportStrategy() {};
		virtual ~AbstractExportStrategy() {};

		virtual void Export(ServerStatePacket) = 0;
		virtual void Export(def::user_id, UserInputPacket) = 0;
	};

}
