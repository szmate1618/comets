#pragma once

#include <chrono>
#include <cstdint>


namespace def
{

	using namespace std::chrono_literals;
	using time = std::chrono::duration<double>;
	using server_tick = std::chrono::duration<double, std::ratio<1, 90>>;

	static constexpr time connection_timeout = 5s;
	static constexpr time max_sleep = 1s;
	static constexpr time server_rate = server_tick(1);
	static constexpr time client_rate = server_tick(2);

	static constexpr int max_packet_size = 1000; //TODO: Check recommended max MTU.

	using entity_id = long;
	static constexpr uint8_t protocol_id = 77;

	static constexpr unsigned short server_port = 7700; //TODO: This should be specified in a config file. Maybe the others, too.

}
