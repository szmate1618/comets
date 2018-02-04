#include "PacketPayloadBuffers.hpp"

#include <iterator>

namespace server
{

	ClientInputPayloadBuffer::ClientInputPayloadBuffer() : current_index{ 0 }
	{
		for (auto& flag : is_free)
		{
			flag.store(true);
		}
		for (auto& payload : client_inputs)
		{
			payload.inputs = new uint8_t[def::max_packet_size];
		}
	}

	ClientInputPayloadBuffer::~ClientInputPayloadBuffer()
	{
		for (auto& payload = std::rbegin(client_inputs); payload != std::rend(client_inputs); ++payload)
		{
			delete[] payload->inputs;
		}
	}

	ServerStatePayloadBuffer::ServerStatePayloadBuffer() : count{ 0 }
	{
		for (auto& payload : server_states)
		{
			payload.objects = new net::ServerObject[def::max_packet_size];
		}
	}

	ServerStatePayloadBuffer::~ServerStatePayloadBuffer()
	{
		for (auto& payload = std::rbegin(server_states); payload != std::rend(server_states); ++payload)
		{
			delete[] payload->objects;
		}
	}

}
