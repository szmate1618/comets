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

	void ClientsideProtocol::Broadcast()
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

	int ServersideProtocol::Tick(def::time duration)
	{
		net::Address from;
		int bytes_read = socket.Receive(from);

		return bytes_read;
	}

	void ServersideProtocol::Broadcast()
	{
	}

}
