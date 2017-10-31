#include "Protocol.hpp"


namespace net
{

	AbstractProtocol::AbstractProtocol(unsigned short port, const AbstractExportStrategy& exportstrategy, const AbstractImportStrategy&)
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

	int ClientsideProtocol::Tick(def::time duration)
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
			connection.Update(duration);

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
		: AbstractProtocol{ port, exportstrategy, importstrategy }
	{
	}

	ServersideProtocol::ServersideProtocol(const AbstractExportStrategy& exportstrategy, const AbstractImportStrategy& importstrategy)
		: AbstractProtocol{ 0, exportstrategy, importstrategy }
	{
	}

	ServersideProtocol::~ServersideProtocol()
	{
	}

	int ServersideProtocol::Tick(def::time duration) //TODO: Error handling.
	{
		net::Address from;
		int bytes_read = socket.Receive(from);

		Header header;
		size_t header_size = header.IO<net::Read>(buffer);

		switch (header.packet_type)
		{
		case client_input:
			ClientIntputPayload payload;
			payload.IO<net::Read>(buffer + header_size);
			exportstrategy.Export(payload.entity_id, payload); //TODO: If entity_id is contained in the payload there's no need for a separate array for it.
			registry.Touch(payload.entity_id, from);
			break;
		default:
			//TODO: Some kind of errorlogging here.
			break;
		}

		return bytes_read;
	}

	void ServersideProtocol::Respond()
	{
		PointeredPacket<ServerHeader, ServerStatePayload> packet;
		ServerHeader header = { def::protocol_id, sequence_number, server_state, 0, 0 }; //TODO: Implement acking mechanism.
		packet.header = &header;
		auto[count, entities, payloads] = importstrategy.ImportServerState();
		for (auto i = 0; i < count; i++)
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
