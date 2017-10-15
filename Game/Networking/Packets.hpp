#pragma once

#include "BinarySerialization.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <cstdint>
#include <tuple>


namespace net
{

	enum packet_types { client_input, server_state };

	class Header
	{
	public:

		uint8_t protocol_id;
		uint32_t sequence_number;
		uint8_t packet_type;

		Header() = default;
		Header(const Header& other) = default;
		Header& operator=(const Header& other) = default;
		bool operator==(const Header& other) const;
		template<typename io_mode> size_t IO(uint8_t* packet_data_start);

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
		bool operator==(const ServerHeader& other) const;
		template<typename io_mode> size_t IO(uint8_t* packet_data_start);

	};

	class ClientIntputPayload
	{
	public:

		uint8_t duration;
		uint16_t count; //count=0 will be used as client heartbeat.
		uint8_t* inputs;

		ClientIntputPayload() = default;
		ClientIntputPayload(const ClientIntputPayload& other) = default;
		ClientIntputPayload& operator=(const ClientIntputPayload& other) = default;
		bool operator==(const ClientIntputPayload& other) const;
		template<typename io_mode> size_t IO(uint8_t* packet_data_start);

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
		bool operator==(const ServerObject& other) const;
		template<typename io_mode>	size_t IO(uint8_t* packet_data_start);

	};

	class ServerStatePayload
	{
	public:

		uint16_t count;
		ServerObject* objects;

		ServerStatePayload() = default;
		ServerStatePayload(const ServerStatePayload& other) = default;
		ServerStatePayload& operator=(const ServerStatePayload& other) = default;
		bool operator==(const ServerStatePayload& other) const;
		template<typename io_mode>	size_t IO(uint8_t* packet_data_start);

	};

	template<typename H, typename P>
	class Packet
	{
	public:

		H header;
		P payload;

		Packet() = default;
		Packet(const Packet<H, P>& other) = default;
		Packet<H, P>& operator=(const Packet<H, P>& other) = default;
		bool operator==(const Packet<H, P>& other) const;
		template<typename io_mode>	size_t IO(uint8_t* packet_data_start);

	};

	using ClientIntputPacket = Packet<Header, ClientIntputPayload>;
	using ServerStatePacket = Packet<ServerHeader, ServerStatePayload>;

	class AbstractExportStrategy
	{
	public:

		AbstractExportStrategy();
		virtual ~AbstractExportStrategy();
		virtual void Export(const ServerStatePayload&) = 0;
		virtual void Export(def::entity_id, const ClientIntputPayload&) = 0;

	};

	class AbstractImportStrategy
	{
	public:

		AbstractImportStrategy();
		virtual ~AbstractImportStrategy();
		virtual std::tuple<size_t, def::entity_id*, ServerStatePayload*> ImportServerState() = 0;
		virtual std::tuple<size_t, ClientIntputPayload*> ImportClientIntput() = 0;

	};

}
