#include "PacketBuffers.hpp"


namespace server
{

	ClientInputPayloadBuffer::ClientInputPayloadBuffer()
	{
		for (auto payload : client_inputs)
		{
			payload.inputs = new uint8_t[def::max_packet_size];
		}
	}

	ClientInputPayloadBuffer::~ClientInputPayloadBuffer()
	{
		for (auto payload = client_inputs.rbegin(); payload != client_inputs.rend(); ++payload)
		{
			delete[] payload->inputs;
		}
	}

	ServerStatePayloadBuffer::ServerStatePayloadBuffer()
	{
		for (auto payload : server_states)
		{
			payload.objects = new net::ServerObject[def::max_packet_size];
		}
	}

	ServerStatePayloadBuffer::~ServerStatePayloadBuffer()
	{
		for (auto payload = server_states.rbegin(); payload != server_states.rend(); ++payload)
		{
			delete[] payload->objects;
		}
	}

}
