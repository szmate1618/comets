#pragma once

#include <chrono>

namespace net
{

	using namespace std::chrono_literals;
	using time = std::chrono::duration<double>;
	using server_tick = std::chrono::duration<double, std::ratio<1, 90>>;

	static constexpr time connection_timeout = 5s;
	static constexpr time max_sleep = 1s;
	static constexpr time server_rate = server_tick(1);
	static constexpr time client_rate = server_tick(2);
	static constexpr time client_rate_low = server_tick(6);

	class ClientsideProtocol
	{

		enum states { unconnected, connecting, connected }; //TODO: Add low packet-rate state for congestion avoidance.

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