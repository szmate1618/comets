#include "Protocol.hpp"

#include <cassert>


namespace net
{

	AbstractProtocol::AbstractProtocol(unsigned short port, const AbstractExportStrategy& exportstrategy, const AbstractImportStrategy& importstrategy)
		: socket{ port }, exportstrategy{ exportstrategy }, importstrategy{ importstrategy }
	{
	}

	AbstractProtocol::~AbstractProtocol()
	{
	}

	ClientsideProtocol::ClientsideProtocol(unsigned short port, const AbstractExportStrategy& exportstrategy, const AbstractImportStrategy& importstrategy)
		: AbstractProtocol{ port, exportstrategy, importstrategy }
	{
	}

	ClientsideProtocol::ClientsideProtocol(const AbstractExportStrategy& exportstrategy, const AbstractImportStrategy& importstrategy)
		: ClientsideProtocol{ 0, exportstrategy, importstrategy}
	{
	}

	ClientsideProtocol::~ClientsideProtocol()
	{
	}

	int ClientsideProtocol::Tick()
	{
		switch (current_state)
		{
		case unconnected:
		{
			break;
		}
		case connecting:
		{
			break;
		}
		case connected:
		{
			//connection.Update(duration); //TODO: Decide if we want to use duration or not.

			if (connection.TimedOut()) { current_state = unconnected; } //TODO: Warnlog server timeout.
			break;
		}
		default: { break; } //TODO: Errorlog undefined state.
		}
		return -1; //TODO: Implement this.
	}

	void ClientsideProtocol::Respond()
	{
	}

	ServersideProtocol::ServersideProtocol(unsigned short port, const AbstractExportStrategy& exportstrategy, const AbstractImportStrategy& importstrategy)
		: AbstractProtocol{ port, exportstrategy, importstrategy }, sequence_number{ 0 }
	{
	}

	ServersideProtocol::ServersideProtocol(const AbstractExportStrategy& exportstrategy, const AbstractImportStrategy& importstrategy)
		: AbstractProtocol{ 0, exportstrategy, importstrategy }
	{
	}

	ServersideProtocol::~ServersideProtocol()
	{
	}

	int ServersideProtocol::Tick() //TODO: Error handling. //TODO: duration is unused at the moment. //TODO: Tick is a bit misleading, it really only consumes one packet.
	{
		net::Address from;
		int bytes_read = socket.Receive(from);

		if (bytes_read > 0)
		{
			Header header;
			size_t header_size = header.IO<net::Read>(socket.recv_buffer);

			if (header.protocol_id == def::protocol_id)
			{
				switch (header.packet_type)
				{
					case client_input:
					{
						ClientInputPayload client_input_payload;
						client_input_payload.inputs = buffer;
						client_input_payload.IO<net::Read>(socket.recv_buffer + header_size);
						exportstrategy.Export(client_input_payload);
						registry.Touch(client_input_payload.entity_id, from);
						break;
					}
					case shape_request:
					{
						ShapeRequestPayload shape_request_payload;
						shape_request_payload.IO<net::Read>(socket.recv_buffer + header_size);
						ShapeDescriptionPacket shape_description_packet;
						shape_description_packet.header = { def::protocol_id, sequence_number, shape_description, 0, 0 }; //TODO: Use sequence_number correctly.
						shape_description_packet.payload = exportstrategy.ExportImport(shape_request_payload);
						size_t bytes_written = shape_description_packet.IO<net::Write>(socket.send_buffer);
						socket.Send(from, bytes_written);
						break;
					}
					default:
					{
						//TODO: Some kind of errorlogging here.
						break;
					}
				}
			}
			else
			{
				//TODO: Some kind of warnlogging here.
			}
		}
		return bytes_read;
	}

	void ServersideProtocol::Respond()
	{
		PointeredPacket<ServerHeader, ServerStatePayload> packet;
		ServerHeader header = { def::protocol_id, sequence_number, server_state, 0, 0 }; //TODO: Implement acking mechanism.
		packet.header = &header;
		auto[count, entities, payloads] = importstrategy.ImportServerState();
		for (size_t i = 0; i < count; i++)
		{
			//TODO: Why write the buffer for entities we don't send anyway?
			packet.payload = &(payloads[i]);

			//TODO: This code makes assumptions about the internals of packets.
			//Factor this into a separate method or class somehow, preferably somewhere around the packets, add tests.
			uint16_t remaining_count = packet.payload->count;
			uint16_t max_per_packet_count = static_cast<uint16_t>((sizeof(buffer) - sizeof(ServerHeader) - sizeof(packet.payload->count)) / sizeof(ServerObject));
			ServerObject* first_object = packet.payload->objects;

			do
			{
				uint16_t current_per_packet_count = __min(max_per_packet_count, remaining_count);
				packet.payload->count = current_per_packet_count;
				remaining_count -= current_per_packet_count;

				size_t bytes_written = packet.IO<Write>(buffer); //TODO: Handle overflow.
				assert(bytes_written < def::max_packet_size && "Buffer overflow error.");

				//TODO: Consider making these operation non-destructive.
				packet.payload->objects += packet.payload->count;

				if (registry.Contains(entities[i]))
				{
					socket.Send(registry.GetAddress(entities[i]), buffer, static_cast<int>(bytes_written)); //TODO: Maybe tracelog sent bytes.
					sequence_number++;
				}
				else
				{
					//TODO: Errorlog this.
				}
			} while (remaining_count > 0); //TODO: Maybe a for loop with be more obviously finite.

			packet.payload->objects = first_object;
		}
	}

}
