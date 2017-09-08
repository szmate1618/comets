#pragma once

#include "Packets.hpp"
#include "Socket.hpp"
#include "Connection.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <chrono>


//TODO: Add congestion avoidance.
namespace net
{

	class AbstractProtocol
	{
	public:

		AbstractProtocol(unsigned int, AbstractExportStrategy&, AbstractImportStrategy&);
		virtual ~AbstractProtocol();
		virtual void Tick(def::time) = 0;

	private:

		Socket socket;
		AbstractExportStrategy& exportstrategy;
		AbstractImportStrategy& importstrategy;

	};

	class ClientsideProtocol: public AbstractProtocol
	{

		enum state { unconnected, connecting, connected };

	public:

		ClientsideProtocol(unsigned int, AbstractExportStrategy&, AbstractImportStrategy&);
		ClientsideProtocol(AbstractExportStrategy&, AbstractImportStrategy&);
		ClientsideProtocol() = delete;
		virtual ~ClientsideProtocol();
		virtual void Tick(def::time) override;

	private:

		state current_state;
		Connection connection;

	};

	class ServersideProtocol : public AbstractProtocol
	{
	public:

		ServersideProtocol(unsigned int, AbstractExportStrategy&, AbstractImportStrategy&);
		ServersideProtocol(AbstractExportStrategy&, AbstractImportStrategy&);
		ServersideProtocol() = delete;
		virtual ~ServersideProtocol();
		virtual void Tick(def::time) override;

	};

}
