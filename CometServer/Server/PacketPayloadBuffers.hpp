#pragma once

#include "..\Networking\Packets.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <atomic>


namespace server
{

	static constexpr int oversize_factor = 5;
	static constexpr size_t packet_buffer_length = oversize_factor *  def::max_sessions;

	class ClientInputPayloadBuffer
	{
	public:

		ClientInputPayloadBuffer();
		~ClientInputPayloadBuffer();

		//It would be cleaner to make these private and provide a minimal necessary public interface
		//but it's simpler this way.
		size_t current_index;
		std::atomic_bool is_free[packet_buffer_length];
		net::ClientInputPayload client_inputs[packet_buffer_length];

	private:

	};

	class ServerStatePayloadBuffer
	{
	public:

		ServerStatePayloadBuffer();
		~ServerStatePayloadBuffer();

		//It would be cleaner to make these private and provide a minimal necessary public interface
		//but it's simpler this way.
		size_t count;
		def::entity_id entity_ids[packet_buffer_length];
		net::ServerStatePayload server_states[packet_buffer_length];

	private:

	};

}
