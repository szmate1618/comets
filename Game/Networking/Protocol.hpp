#pragma once

#include <chrono>


//TODO: Add congestion avoidance.
namespace net
{

	class ClientsideProtocol
	{

		enum states { unconnected, connecting, connected };

	public:

		ClientsideProtocol();
		~ClientsideProtocol();

	};

	class ServersideProtocol
	{
	public:

		ServersideProtocol();
		~ServersideProtocol();

	};

}