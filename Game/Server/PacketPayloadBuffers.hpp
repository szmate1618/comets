#pragma once

#include "..\Networking\Packets.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <array>
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
		std::array<std::atomic<bool>, packet_buffer_length> is_free; //TODO: Initialize this to all true.
		std::array<net::ClientInputPayload, packet_buffer_length> client_inputs;

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
		std::array<def::entity_id, packet_buffer_length> entity_ids;
		std::array<net::ServerStatePayload, packet_buffer_length> server_states;

	private:

	};
}
