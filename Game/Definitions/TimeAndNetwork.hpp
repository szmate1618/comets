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

	using user_id = int;
	static constexpr uint8_t protocol_id = 77;

}
