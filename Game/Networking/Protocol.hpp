#pragma once

#include "Packets.hpp"
#include "Socket.hpp"
#include "Connection.hpp"
#include "ClientRegistry.hpp"
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
		virtual int Tick(def::time) = 0; //Handle incoming packets, forward them via the specified exportstrategy.
		virtual void Respond() = 0; //Import packets via the specified importstrategy, Respond them to the peers (includes congestion avoidance).

	protected:

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
		virtual int Tick(def::time) override;
		virtual void Respond() override;

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
		virtual int Tick(def::time) override;
		virtual void Respond() override;

	private:

		ClientRegistry registry;
		uint32_t sequence_number;
		uint8_t buffer[def::max_packet_size];

	};

}
