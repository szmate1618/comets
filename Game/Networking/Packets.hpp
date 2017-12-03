#pragma once

#include "BinarySerialization.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"
#include "..\Utilities\AssertTypeSizes.hpp"
#include "..\Utilities\AutoExtendingVector.hpp"

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

	class ClientInputPayload
	{
	public:

		uint32_t entity_id;
		uint8_t duration; //TODO: Also add entity_id.
		uint16_t count; //count=0 will be used as client heartbeat.
		mutable utils::AutoExtendingVector<uint8_t> inputs;

		ClientInputPayload() = default;
		ClientInputPayload(const ClientInputPayload& other) = default;
		ClientInputPayload& operator=(const ClientInputPayload& other) = default;
		bool operator==(const ClientInputPayload& other) const;
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

	template<typename H, typename P>
	class PointeredPacket //This will help to avoid some unnecessary copies. //TODO: Write tests for this.
	{
	public:

		H* header;
		P* payload;

		PointeredPacket() = default;
		PointeredPacket(const PointeredPacket<H, P>& other) = default;
		PointeredPacket<H, P>& operator=(const PointeredPacket<H, P>& other) = default;
		bool operator==(const PointeredPacket<H, P>& other) const;
		template<typename io_mode>	size_t IO(uint8_t* packet_data_start);

	};

	using ClientInputPacket = Packet<Header, ClientInputPayload>;
	using ServerStatePacket = Packet<ServerHeader, ServerStatePayload>;

	class AbstractExportStrategy
	{
	public:

		AbstractExportStrategy();
		virtual ~AbstractExportStrategy();
		virtual void Export(const ServerStatePayload&) const = 0;
		virtual void Export(const ClientInputPayload&) const = 0;

	};

	class AbstractImportStrategy
	{
	public:

		AbstractImportStrategy();
		virtual ~AbstractImportStrategy();
		virtual std::tuple<size_t, def::entity_id*, ServerStatePayload*> ImportServerState() const = 0;
		virtual std::tuple<size_t, ClientInputPayload*> ImportClientIntput() const = 0;

	};

}
