#pragma once

#include "Packets.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <chrono>


//TODO: Add congestion avoidance.
namespace net
{

	class ClientsideProtocol
	{

		enum states { unconnected, connecting, connected };

	public:

		ClientsideProtocol(AbstractExportStrategy&);
		ClientsideProtocol() = delete;
		~ClientsideProtocol();

		void ReadAndExportPackets();
		void UpdateState(def::time);

	};

	class ServersideProtocol
	{
	public:

		ServersideProtocol(AbstractExportStrategy&);
		ServersideProtocol() = delete;
		~ServersideProtocol();

		void ReadAndExportPackets();
		void UpdateState(def::time);

	};

}
