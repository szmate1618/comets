#include "Packets.hpp"
#include "BinarySerialization.hpp"


namespace net
{

	bool Header::operator==(const Header& other) const
	{
		return protocol_id == other.protocol_id && sequence_number == other.sequence_number && packet_type == other.packet_type;
	}

	template<typename io_mode>
	size_t Header::IO(uint8_t* packet_data_start)
	{
		uint8_t* packet_data_current = packet_data_start;
		packet_data_current += io_mode::Process(packet_data_current, protocol_id);
		packet_data_current += io_mode::Process(packet_data_current, sequence_number);
		packet_data_current += io_mode::Process(packet_data_current, packet_type);
		return packet_data_current - packet_data_start;
	}

	bool ServerHeader::operator==(const ServerHeader& other) const
	{
		return common_header == other.common_header && ack == other.ack && ack_bitfield == other.ack_bitfield;
	}

	template<typename io_mode>
	size_t ServerHeader::IO(uint8_t* packet_data_start)
	{
		uint8_t* packet_data_current = packet_data_start;
		packet_data_current += common_header.IO<io_mode>(packet_data_current);
		packet_data_current += io_mode::Process(packet_data_current, ack);
		packet_data_current += io_mode::Process(packet_data_current, ack_bitfield);
		return packet_data_current - packet_data_start;
	}

	void ClientInputPayload::DeepCopyFrom(const ClientInputPayload& that)
	{
		uint8_t* these_inputs = this->inputs;
		*this = that;
		this->inputs = these_inputs;
		std::memcpy(this->inputs, that.inputs, that.count);
	}

	bool ClientInputPayload::operator==(const ClientInputPayload& other) const
	{
		if (entity_id != other.entity_id) return false;
		if (duration != other.duration) return false;
		if (count != other.count) return false;
		for (int i = 0; i < count; ++i)
		{
			if (inputs[i] != other.inputs[i]) return false;
		}
		return true;
	}

	template<typename io_mode>
	size_t ClientInputPayload::IO(uint8_t* packet_data_start)
	{
		uint8_t* packet_data_current = packet_data_start;
		packet_data_current += io_mode::Process(packet_data_current, entity_id);
		packet_data_current += io_mode::Process(packet_data_current, duration);
		packet_data_current += io_mode::Process(packet_data_current, count);
		for (uint8_t* i = inputs; i - inputs < count; ++i)
		{
			packet_data_current += io_mode::Process(packet_data_current, *i);
		}
		return packet_data_current - packet_data_start;
	}

	bool ServerObject::operator==(const ServerObject& other) const
	{
		return entity_id == other.entity_id && phi == other.phi && x == other.x && y == other.y;
	}

	template<typename io_mode>
	size_t ServerObject::IO(uint8_t* packet_data_start)
	{
		uint8_t* packet_data_current = packet_data_start;
		packet_data_current += io_mode::Process(packet_data_current, entity_id);
		packet_data_current += io_mode::Process(packet_data_current, phi);
		packet_data_current += io_mode::Process(packet_data_current, x);
		packet_data_current += io_mode::Process(packet_data_current, y);
		return packet_data_current - packet_data_start;
	}

	void ServerStatePayload::DeepCopyFrom(const ServerStatePayload& that)
	{
		ServerObject* these_objects = this->objects;
		*this = that;
		this->objects = these_objects;
		std::memcpy(this->objects, that.objects, that.count);
	}

	bool ServerStatePayload::operator==(const ServerStatePayload& other) const
	{
		if (!(count == other.count)) return false;
		for (int i = 0; i < count; ++i)
		{
			if (!(objects[i] == other.objects[i])) return false;
		}
		return true;
	}

	template<typename io_mode>
	size_t ServerStatePayload::IO(uint8_t* packet_data_start)
	{
		uint8_t* packet_data_current = packet_data_start;
		packet_data_current += io_mode::Process(packet_data_current, count);
		for (ServerObject* i = objects; i - objects < count; ++i) //TODO: Somehow handle overindexing.
		{
			packet_data_current += i->IO<io_mode>(packet_data_current);
		}
		return packet_data_current - packet_data_start;
	}

	bool ShapeRequestPayload::operator==(const ShapeRequestPayload& other) const
	{
		return entity_id == other.entity_id;
	}

	template<typename io_mode>
	size_t ShapeRequestPayload::IO(uint8_t* packet_data_start)
	{
		uint8_t* packet_data_current = packet_data_start;
		packet_data_current += io_mode::Process(packet_data_current, entity_id);
		return packet_data_current - packet_data_start;
	}

	void ShapeDescriptionPayload::DeepCopyFrom(const ShapeDescriptionPayload& that)
	{
		this->entity_id = that.entity_id;
		this->vertex_count = that.vertex_count;
		this->triangle_count = that.triangle_count;
		std::memcpy(this->vertices, that.vertices, that.vertex_count);
		std::memcpy(this->uvs, that.uvs, that.vertex_count);
		std::memcpy(this->triangles, that.triangles, that.triangle_count);
	}

	bool ShapeDescriptionPayload::operator==(const ShapeDescriptionPayload& other) const
	{
		if (!(entity_id == other.entity_id)) return false;
		if (!(vertex_count == other.vertex_count)) return false;
		if (!(triangle_count == other.triangle_count)) return false;
		for (int i = 0; i < vertex_count * 2; ++i)
		{
			if (!(vertices[i] == other.vertices[i])) return false;
		}
		for (int i = 0; i < vertex_count * 2; ++i)
		{
			if (!(uvs[i] == other.uvs[i])) return false;
		}
		for (int i = 0; i < triangle_count * 3; ++i)
		{
			if (!(triangles[i] == other.triangles[i])) return false;
		}
		return true;
	}

	template<typename io_mode>
	size_t ShapeDescriptionPayload::IO(uint8_t* packet_data_start)
	{
		uint8_t* packet_data_current = packet_data_start;
		packet_data_current += io_mode::Process(packet_data_current, entity_id);
		packet_data_current += io_mode::Process(packet_data_current, vertex_count);
		packet_data_current += io_mode::Process(packet_data_current, triangle_count);
		for (float* i = vertices; i - vertices < vertex_count * 2; ++i) //TODO: Somehow handle overindexing.
		{
			packet_data_current += io_mode::Process(packet_data_current, *i);
		}
		for (float* i = uvs; i - uvs < vertex_count * 2; ++i) //TODO: Somehow handle overindexing.
		{
			packet_data_current += io_mode::Process(packet_data_current, *i);
		}
		for (uint16_t* i = triangles; i - triangles < triangle_count * 3; ++i) //TODO: Somehow handle overindexing.
		{
			packet_data_current += io_mode::Process(packet_data_current, *i);
		}
		return packet_data_current - packet_data_start;
	}

	template<typename H, typename P>
	bool Packet<H, P>::operator==(const Packet<H, P>& other) const
	{
		return header == other.header && payload == other.payload;
	}

	template<typename H, typename P>
	template<typename io_mode>
	size_t Packet<H, P>::IO(uint8_t* packet_data_start)
	{
		uint8_t* packet_data_current = packet_data_start;
		packet_data_current += header.IO<io_mode>(packet_data_current);
		packet_data_current += payload.IO<io_mode>(packet_data_current);
		return packet_data_current - packet_data_start;
	}

	template<typename H, typename P>
	bool PointeredPacket<H, P>::operator==(const PointeredPacket<H, P>& other) const
	{
		return *header == *(other.header) && *payload == *(other.payload);
	}

	template<typename H, typename P>
	template<typename io_mode>
	size_t PointeredPacket<H, P>::IO(uint8_t* packet_data_start)
	{
		uint8_t* packet_data_current = packet_data_start;
		packet_data_current += header->IO<io_mode>(packet_data_current);
		packet_data_current += payload->IO<io_mode>(packet_data_current);
		return packet_data_current - packet_data_start;
	}

	AbstractExportStrategy::AbstractExportStrategy() {};

	AbstractExportStrategy::~AbstractExportStrategy() {};

	AbstractImportStrategy::AbstractImportStrategy() {};

	AbstractImportStrategy::~AbstractImportStrategy() {};

	//Explicit instantiations.
	template size_t Header::IO<Read>(uint8_t*);
	template size_t Header::IO<Write>(uint8_t*);
	template size_t ServerHeader::IO<Read>(uint8_t*);
	template size_t ServerHeader::IO<Write>(uint8_t*);
	template size_t ClientInputPayload::IO<Read>(uint8_t*);
	template size_t ClientInputPayload::IO<Write>(uint8_t*);
	template size_t ServerObject::IO<Read>(uint8_t*);
	template size_t ServerObject::IO<Write>(uint8_t*);
	template size_t ServerStatePayload::IO<Read>(uint8_t*);
	template size_t ServerStatePayload::IO<Write>(uint8_t*);
	template size_t ShapeRequestPayload::IO<Read>(uint8_t*);
	template size_t ShapeRequestPayload::IO<Write>(uint8_t*);
	template size_t ShapeDescriptionPayload::IO<Read>(uint8_t*);
	template size_t ShapeDescriptionPayload::IO<Write>(uint8_t*);
	template class Packet<Header, ClientInputPacket>;
	template size_t Packet<Header, ClientInputPacket>::IO<Read>(uint8_t*);
	template size_t Packet<Header, ClientInputPacket>::IO<Write>(uint8_t*);
	template class Packet<ServerHeader, ServerStatePayload>;
	template size_t Packet<ServerHeader, ServerStatePayload>::IO<Read>(uint8_t*);
	template size_t Packet<ServerHeader, ServerStatePayload>::IO<Write>(uint8_t*);
	template class Packet<Header, ShapeRequestPayload>;
	template size_t Packet<Header, ShapeRequestPayload>::IO<Read>(uint8_t*);
	template size_t Packet<Header, ShapeRequestPayload>::IO<Write>(uint8_t*);
	template class Packet<ServerHeader, ShapeDescriptionPayload>;
	template size_t Packet<ServerHeader, ShapeDescriptionPayload>::IO<Read>(uint8_t*);
	template size_t Packet<ServerHeader, ShapeDescriptionPayload>::IO<Write>(uint8_t*);
	template class PointeredPacket<Header, ClientInputPacket>;
	template size_t PointeredPacket<Header, ClientInputPacket>::IO<Read>(uint8_t*);
	template size_t PointeredPacket<Header, ClientInputPacket>::IO<Write>(uint8_t*);
	template class PointeredPacket<ServerHeader, ServerStatePayload>;
	template size_t PointeredPacket<ServerHeader, ServerStatePayload>::IO<Read>(uint8_t*);
	template size_t PointeredPacket<ServerHeader, ServerStatePayload>::IO<Write>(uint8_t*);
	template class PointeredPacket<Header, ShapeRequestPayload>;
	template size_t PointeredPacket<Header, ShapeRequestPayload>::IO<Read>(uint8_t*);
	template size_t PointeredPacket<Header, ShapeRequestPayload>::IO<Write>(uint8_t*);
	template class PointeredPacket<ServerHeader, ShapeDescriptionPayload>;
	template size_t PointeredPacket<ServerHeader, ShapeDescriptionPayload>::IO<Read>(uint8_t*);
	template size_t PointeredPacket<ServerHeader, ShapeDescriptionPayload>::IO<Write>(uint8_t*);

}
