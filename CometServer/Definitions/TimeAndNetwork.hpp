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
	static constexpr time session_timeout = 5s;
	static constexpr time max_sleep = 1s; //TODO: Clean this up. Do we want to use this? Or we prefer max_socket_read_backoff?
	static constexpr time max_socket_read_backoff = 10ms;
	static constexpr time server_rate = server_tick(1);
	static constexpr time client_rate = server_tick(2);

	//Socket parameters
	static constexpr int max_packet_size = 1000; //TODO: Check recommended max MTU. //TODO: Why is this not size_t?

	//Protocol parameters
	using entity_id = uint32_t; //Used in ClientInputPayload and ServerObject. Changing it changes the protocol on the binary level.
	using owner_id = uint32_t; //TODO: This is not used at the moment.
	using shape_id = uint32_t;
	using texture_id = uint32_t;
	static constexpr uint8_t protocol_id = 77;
	enum user_input { turn_left, turn_right, thrust, brake, fire, warp }; //TODO: Maybe use strongly typed enum class (everywhere) instead?

	//Server configuration
	static constexpr unsigned short server_port = 7700; //TODO: This should be specified in a config file. Maybe the others, too.
	static constexpr int max_sessions = 1000; //Yeah, this one, too. //TODO: Benchmark how many we can actually serve. //TODO: Currently this is not enforced.

	//Weapon parameters
	static constexpr time default_weapon_cooldown = 0.3s; //TODO: Maybe move these to Gameplay.hpp.
	static constexpr time zero_seconds = 0s;

}
