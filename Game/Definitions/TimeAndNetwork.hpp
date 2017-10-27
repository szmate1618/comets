#pragma once

#include <chrono>
#include <cstdint>


namespace def
{

	//Time type defnitions
	using namespace std::chrono_literals;
	using time = std::chrono::duration<double>;
	using server_tick = std::chrono::duration<double, std::ratio<1, 90>>;

	//Time constants
	static constexpr time connection_timeout = 5s;
	static constexpr time max_sleep = 1s; //TODO: Clean this up. Do we want to use this? Or we prefer max_socket_read_backoff?
	static constexpr time max_socket_read_backoff = 10ms;
	static constexpr time server_rate = server_tick(1);
	static constexpr time client_rate = server_tick(2);

	//Socket parameters
	static constexpr int max_packet_size = 1000; //TODO: Check recommended max MTU.

	//Protocol parameters
	using entity_id = long;
	static constexpr uint8_t protocol_id = 77;

	//Server configuration
	static constexpr unsigned short server_port = 7700; //TODO: This should be specified in a config file. Maybe the others, too.
	static constexpr int max_clients = 1000; //Yeah, this one, too. //TODO: Benchmark how many we can actually serve.

}
