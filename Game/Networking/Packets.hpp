#pragma once

#include "BinarySerialization.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

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

		Header() = default;

		Header(const Header& other) = default;

		Header& operator=(const Header& other) = default;

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

		ServerHeader() = default;

		ServerHeader(const ServerHeader& other) = default;

		ServerHeader& operator=(const ServerHeader& other) = default;

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

	class UserInputPayload
	{
	public:

		uint8_t count;
		uint8_t* inputs;

		UserInputPayload() = default;

		UserInputPayload(const UserInputPayload& other) = default;

		UserInputPayload& operator=(const UserInputPayload& other) = default;

		bool operator==(const UserInputPayload& other) const
		{
			if (!(count == other.count)) return false;
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

		ServerObject() = default;

		ServerObject(const ServerObject& other) = default;

		ServerObject& operator=(const ServerObject& other) = default;

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

	class ServerStatePayload
	{
	public:

		uint8_t count;
		ServerObject* objects;

		ServerStatePayload() = default;

		ServerStatePayload(const ServerStatePayload& other) = default;

		ServerStatePayload& operator=(const ServerStatePayload& other) = default;

		bool operator==(const ServerStatePayload& other) const
		{
			if (!(count == other.count)) return false;
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
			packet_data_current += io_mode.Process(packet_data_current, count);
			for (ServerObject* i = objects; i - inputs < count; ++i)
			{
				packet_data_current += i->IO<io_mode>(packet_data_current, *i);
			}
			return packet_data_current - packet_data_start;
		}
	};

	template<typename H, typename P>
	class Packet
	{
		H header;
		P payload;

		Packet() = default;

		Packet(const Packet<H, P>& other) = default;

		Packet<H, P>& operator=(const Packet<H, P>& other) = default;

		bool operator==(const Packet<H, P>& other) const
		{
			return header == other.header && payload == other.payload;
		}

		template<typename io_mode>
		size_t IO(uint8_t* packet_data_start) const
		{
			uint8_t* packet_data_current = packet_data_start;
			packet_data_current += header.IO<io_mode>(packet_data_current);
			packet_data_current += payload.IO<io_mode>(packet_data_current);
			return packet_data_current - packet_data_start;
		}

	};

	using UserInputPacket = Packet<Header, UserInputPayload>;
	using ServerStatePacket = Packet<ServerHeader, ServerStatePayload>;

	class AbstractExportStrategy
	{
	public:

		AbstractExportStrategy() {};
		virtual ~AbstractExportStrategy() {};

		virtual void Export(ServerStatePayload) = 0;
		virtual void Export(def::user_id, UserInputPayload) = 0;
	};

}
