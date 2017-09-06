#include "Protocol.hpp"


namespace net
{

	AbstractProtocol::AbstractProtocol(unsigned int port, AbstractExportStrategy& exportstrategy) : socket{ port }, exportstrategy{ exportstrategy }
	{
	}

	AbstractProtocol::~AbstractProtocol()
	{
	}

	ClientsideProtocol::ClientsideProtocol(unsigned int port, AbstractExportStrategy& exportstrategy) : AbstractProtocol{ port, exportstrategy }
	{
	}

	ClientsideProtocol::ClientsideProtocol(AbstractExportStrategy& exportstrategy) : ClientsideProtocol{ 0, exportstrategy }
	{
	}

	ClientsideProtocol::~ClientsideProtocol()
	{
	}

	void ClientsideProtocol::Tick(def::time duration)
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
	}

	ServersideProtocol::ServersideProtocol(unsigned int port, AbstractExportStrategy& exportstrategy) : AbstractProtocol{ port, exportstrategy }
	{
	}

	ServersideProtocol::ServersideProtocol(AbstractExportStrategy& exportstrategy) : AbstractProtocol{ 0, exportstrategy }
	{
	}

	ServersideProtocol::~ServersideProtocol()
	{
	}

	void ServersideProtocol::Tick(def::time duration)
	{
	}

}
