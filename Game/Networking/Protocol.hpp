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

		AbstractProtocol(unsigned short, const AbstractExportStrategy&, const AbstractImportStrategy&);
		virtual ~AbstractProtocol();
		virtual void Tick(def::time) = 0; //Handle incoming packets, forward them via the specified exportstrategy.
		virtual void Broadcast() = 0; //Import packets via the specified importstrategy, broadcast them to the peers (includes congestion avoidance).

	private:

		Socket socket;
		const AbstractExportStrategy& exportstrategy;
		const AbstractImportStrategy& importstrategy;

	};

	class ClientsideProtocol: public AbstractProtocol
	{

		enum state { unconnected, connecting, connected };

	public:

		ClientsideProtocol(unsigned short, const AbstractExportStrategy&, const AbstractImportStrategy&);
		ClientsideProtocol(const AbstractExportStrategy&, const AbstractImportStrategy&);
		ClientsideProtocol() = delete;
		virtual ~ClientsideProtocol() override;
		virtual void Tick(def::time) override;
		virtual void Broadcast() override;

	private:

		state current_state;
		Connection connection;

	};

	class ServersideProtocol : public AbstractProtocol
	{
	public:

		ServersideProtocol(unsigned short, const AbstractExportStrategy&, const AbstractImportStrategy&);
		ServersideProtocol(const AbstractExportStrategy&, const AbstractImportStrategy&);
		ServersideProtocol() = delete;
		virtual ~ServersideProtocol() override;
		virtual void Tick(def::time) override;
		virtual void Broadcast() override;

	};

}
