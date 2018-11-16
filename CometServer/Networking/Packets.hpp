#pragma once

#include "BinarySerialization.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"
#include "..\Utilities\AssertTypeSizes.hpp"

#include <cstdint>
#include <tuple>


namespace net
{

	enum packet_type { client_input, server_state, shape_request, shape_description };

	class Header
	{
	public:

		uint8_t protocol_id;
		uint32_t sequence_number;
		uint8_t packet_type;

		Header() = default;
		Header(const Header&) = default;
		Header& operator=(const Header&) = default;
		bool operator==(const Header&) const;
		template<typename io_mode> size_t IO(uint8_t*);

	};

	class ServerHeader
	{
	public:

		Header common_header;
		uint32_t ack;
		uint32_t ack_bitfield;

		ServerHeader() = default;
		ServerHeader(const ServerHeader&) = default;
		ServerHeader& operator=(const ServerHeader&) = default;
		bool operator==(const ServerHeader&) const;
		template<typename io_mode> size_t IO(uint8_t*);

	};

	class ClientInputPayload
	{
	public:

		def::entity_id entity_id;
		uint8_t duration;
		uint16_t count; //count=0 will be used as client heartbeat.
		uint8_t* inputs;

		ClientInputPayload() = default;
		ClientInputPayload(const ClientInputPayload&) = default;
		ClientInputPayload& operator=(const ClientInputPayload&) = default;
		void DeepCopyFrom(const ClientInputPayload&); //TODO: Add tests. //TODO: But really, it just bit me and I wasted hours.
		bool operator==(const ClientInputPayload&) const;
		template<typename io_mode> size_t IO(uint8_t*);

	};

	class ServerObject
	{
	public:

		def::entity_id entity_id; //TODO: Originally this was called 'type'. Find out why.
		double phi;
		double x;
		double y;

		ServerObject() = default;
		ServerObject(const ServerObject&) = default;
		ServerObject& operator=(const ServerObject&) = default;
		bool operator==(const ServerObject&) const;
		template<typename io_mode>	size_t IO(uint8_t*);

	};

	class ServerStatePayload
	{
	public:

		uint16_t count;
		ServerObject* objects;

		ServerStatePayload() = default;
		ServerStatePayload(const ServerStatePayload&) = default;
		ServerStatePayload& operator=(const ServerStatePayload&) = default;
		void DeepCopyFrom(const ServerStatePayload&); //TODO: Add tests.
		bool operator==(const ServerStatePayload&) const;
		template<typename io_mode>	size_t IO(uint8_t*);

	};

	class ShapeRequest
	{
	public:

		def::entity_id entity_id;

		ShapeRequest() = default;
		ShapeRequest(const ShapeRequest&) = default;
		ShapeRequest& operator=(const ShapeRequest&) = default;
		bool operator==(const ShapeRequest&) const;
		template<typename io_mode> size_t IO(uint8_t*);

	};

	class ShapeDescription
	{
	public:

		def::entity_id entity_id;
		uint16_t vertex_count;
		uint16_t triangle_count;
		float* vertices;
		float* uvs;
		uint16_t* triangles;

		ShapeDescription() = default;
		ShapeDescription(const ShapeDescription&) = default;
		ShapeDescription& operator=(const ShapeDescription&) = default;
		void DeepCopyFrom(const ShapeDescription&); //TODO: Add tests.
		bool operator==(const ShapeDescription&) const;
		template<typename io_mode> size_t IO(uint8_t*);

	};

	template<typename H, typename P>
	class Packet
	{
	public:

		H header;
		P payload;

		Packet() = default;
		Packet(const Packet<H, P>&) = default;
		Packet<H, P>& operator=(const Packet<H, P>&) = default;
		bool operator==(const Packet<H, P>&) const;
		template<typename io_mode>	size_t IO(uint8_t*);

	};

	template<typename H, typename P>
	class PointeredPacket //This will help to avoid some unnecessary copies. //TODO: Write tests for this.
	{
	public:

		H* header;
		P* payload;

		PointeredPacket() = default;
		PointeredPacket(const PointeredPacket<H, P>&) = default;
		PointeredPacket<H, P>& operator=(const PointeredPacket<H, P>&) = default;
		bool operator==(const PointeredPacket<H, P>&) const;
		template<typename io_mode>	size_t IO(uint8_t*);

	};

	using ClientInputPacket = Packet<Header, ClientInputPayload>;
	using ServerStatePacket = Packet<ServerHeader, ServerStatePayload>;
	using ShapeRequestPacket = Packet<Header, ShapeRequest>;
	using ShapeDescriptionPacket = Packet<ServerHeader, ShapeDescription>;

	class AbstractExportStrategy
	{
	public:

		AbstractExportStrategy();
		virtual ~AbstractExportStrategy();
		virtual void Export(const ClientInputPayload&) const = 0;
		virtual void Export(const ServerStatePayload&) const = 0;

	};

	class AbstractImportStrategy
	{
	public:

		AbstractImportStrategy();
		virtual ~AbstractImportStrategy();
		virtual std::tuple<size_t, ClientInputPayload*> ImportClientIntput() const = 0;
		virtual std::tuple<size_t, def::entity_id*, ServerStatePayload*> ImportServerState() const = 0;

	};

}
