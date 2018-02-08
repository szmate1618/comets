#include "GameServer.hpp"

#include <cassert>
#include <chrono>


namespace server
{

	//Stroustrup: "The constructors are called in the order in which the members are declared
	//in the class rather than the order in which the members appear in the initializer list.
	//To avoid confusion, it is best to specify the initializers in the member declaration order."
	GameServer::GameServer() :
		export_strategy{ client_input_payload_buffer },
		import_strategy{ server_state_payload_buffer },
		protocol{ def::server_port, export_strategy, import_strategy },
		running{ true },
		input_thread{ [=] { ReadPackets(); } }
	{
	}

	GameServer::~GameServer()
	{
		input_thread.join(); //TODO: Don't forget to stop this thread.
	}

	void GameServer::Tick(def::time duration)
	{
		ProcessPackets();
		UpdateState(duration);
		TestCollisions();
		SendPackets();
	}

	//This must be thread safe, because it's also called from ReadPackets.
	bool GameServer::Running() const //TODO: This basically returns a constant. Why don't we have a Stop method here?
	{
		return running.load();
	}

	void GameServer::ReadPackets() //Uses a totally ad hoc back-off strategy.
	{
		using namespace std::chrono_literals;
		def::time backoff = 0s;
		while (Running())
		{
			if (backoff > 0s)
			{
				std::this_thread::sleep_for(backoff);
			}
			backoff = 0s;
			for (int i = 0; i < 10; i++)
			{
				if (protocol.Tick() < 0) backoff += def::max_socket_read_backoff / 10;
				else backoff -= def::max_socket_read_backoff / 10;
			}
		}
	}

	//Read input, update entity orientation, acceleration, forces, etc.
	void GameServer::ProcessPackets()
	{
		ClientInputPayloadBuffer& cipb = client_input_payload_buffer;
		for (size_t i = 0; i < packet_buffer_length; ++i)
		{
			if (!cipb.is_free[i].load())
			{
				net::ClientInputPayload& cip = cipb.client_inputs[i];
				/*
				Do things with cip here.
				*/
				if (--cip.duration <= 0) cipb.is_free[i].store(true); //TODO: This assumes the method is being called at a constant pace.
			}
		}
	}

	void GameServer::UpdateState(def::time duration)
	{
	}

	void GameServer::TestCollisions()
	{
	}

	void GameServer::SendPackets()
	{
		protocol.Respond();
	}

	GameServer::ExportStrategy::ExportStrategy(ClientInputPayloadBuffer& cipb) : client_input_payload_buffer{ cipb } {}
	GameServer::ExportStrategy::~ExportStrategy() {}
	void GameServer::ExportStrategy::Export(const net::ServerStatePayload&) const  { assert(false && "Not actually implemented, not supposed to be called."); }
	void GameServer::ExportStrategy::Export(const net::ClientInputPayload& cip) const
	{
		ClientInputPayloadBuffer& cipb = client_input_payload_buffer;
		while (!cipb.is_free[cipb.current_index].load())
		{
			cipb.current_index++;
			cipb.current_index %= packet_buffer_length;
		}
		cipb.client_inputs[cipb.current_index].DeepCopyFrom(cip);
		cipb.is_free[cipb.current_index].store(false);
	}

	GameServer::ImportStrategy::ImportStrategy(ServerStatePayloadBuffer& sspb) : server_state_payload_buffer{ sspb } {}
	GameServer::ImportStrategy::~ImportStrategy() {}
	std::tuple<size_t, def::entity_id*, net::ServerStatePayload*> GameServer::ImportStrategy::ImportServerState() const
	{
		return { server_state_payload_buffer.count, server_state_payload_buffer.entity_ids, server_state_payload_buffer.server_states };
	}
	std::tuple<size_t, net::ClientInputPayload*> GameServer::ImportStrategy::ImportClientIntput() const
	{
		assert(false && "Not actually implemented, not supposed to be called.");
		return *reinterpret_cast<std::tuple<size_t, net::ClientInputPayload*>*>(0);
	}

}
