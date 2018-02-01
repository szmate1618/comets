#pragma once

#include "..\Networking\Packets.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <vector>
#include <atomic>


namespace server
{

	class ClientInputPayloadBuffer
	{
	public:

		ClientInputPayloadBuffer();
		virtual ~ClientInputPayloadBuffer();

		//It would be cleaner to make these private and provide a minimal necessary public interface
		//but it's simpler this way.
		std::vector<std::atomic<bool>> is_free;
		std::vector<net::ClientInputPayload> client_inputs;

	private:

	};

	class ServerStatePayloadBuffer
	{
	public:

		ServerStatePayloadBuffer();
		virtual ~ServerStatePayloadBuffer();

		//It would be cleaner to make these private and provide a minimal necessary public interface
		//but it's simpler this way.
		std::vector<def::entity_id> entity_ids;
		std::vector<net::ServerStatePayload> server_states;

	private:

	};
}
