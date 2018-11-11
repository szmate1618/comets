#include "Protocol.hpp"
#include "..\Utilities\CountOfArray.hpp"

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
						ClientInputPayload payload;
						payload.inputs = buffer;
						payload.IO<net::Read>(socket.recv_buffer + header_size);
						exportstrategy.Export(payload);
						registry.Touch(payload.entity_id, from);
						break;
					}
					case shape_request:
					{
						ShapeRequest request;
						request.IO<net::Read>(socket.recv_buffer + header_size);
						ShapeDescriptionPacket description;
						description.header = { def::protocol_id, sequence_number, shape_description, 0, 0 };
						float vertices[] = { 0.5, 0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5 };
						float uvs[] = { 1, 0, 0, 0, -0, 1, 1, 1 };
						uint16_t triangles[] = { 0, 1, 3, 2, 3, 1 };
						description.payload = { request.entity_id, static_cast<uint16_t>(util::countof(vertices) / 2), static_cast<uint16_t>(util::countof(triangles) / 3), vertices, uvs, triangles };
						size_t bytes_written = description.IO<net::Write>(socket.send_buffer);
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
			packet.payload = &(payloads[i]);
			size_t bytes_written = packet.IO<Write>(buffer); //TODO: Handle overflow.
			if (registry.Contains(entities[i]))
			{
				socket.Send(registry.GetAddress(entities[i]), buffer, static_cast<int>(bytes_written)); //TODO: Maybe tracelog sent bytes.
				sequence_number++;
			}
			else
			{
				//TODO: Errorlog this.
			}
		}
	}

}
