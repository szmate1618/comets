#include "GameServer.hpp"

#include <cassert>
#include <chrono>


namespace server
{

	//Stroustrup: "The constructors are called in the order in which the members are declared
	//in the class rather than the order in which the members appear in the initializer list.
	//To avoid confusion, it is best to specify the initializers in the member declaration order."
	GameServer::GameServer() :
		universe{R"(universe_initial_state.ssv)"},
		export_strategy{ client_input_payload_buffer },
		import_strategy{ server_state_payload_buffer },
		protocol{ def::server_port, export_strategy, import_strategy },
		running{ true },
		input_thread{ [=] { ReadPackets(); } },
		tick{ 0 }
	{
	}

	GameServer::~GameServer()
	{
		input_thread.join(); //TODO: Don't forget to stop this thread.
	}

	void GameServer::Tick(def::time duration)
	{
		ProcessPackets(duration);
		UpdateState(duration);
		TestCollisions();
		//TODO: Isn't this part of the logic supposed to be a part of the protocol? Maybe not, but think about it.
		//TODO: This should be calculated as the ratio of the server and client rate.
		if (tick % 2 == 1) SendPackets();
		tick++;
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
				if (protocol.Tick() <= 0) backoff += def::max_socket_read_backoff / 10;
				else backoff -= def::max_socket_read_backoff / 10;
			}
		}
	}

	//Read input, update entity orientation, acceleration, forces, etc.
	void GameServer::ProcessPackets(def::time duration)
	{
		ClientInputPayloadBuffer& cipb = client_input_payload_buffer;
		ServerStatePayloadBuffer& sspb = server_state_payload_buffer;
		sspb.count = 0;
		for (size_t i = 0; i < packet_buffer_length; ++i)
		{
			if (!cipb.is_free[i].load())
			{
				net::ClientInputPayload& cip = cipb.client_inputs[i];
				sspb.entity_ids[sspb.count++] = cip.entity_id;
				for (size_t j = 0; j < cip.count; ++j)
				{
					universe.EntityHandleInput(duration, cip.entity_id, static_cast<def::user_input>(cip.inputs[j]));
				}
				if (--cip.duration <= 0) cipb.is_free[i].store(true); //TODO: This assumes the method is being called at a constant pace.
			}
		}
	}

	//Update current speed and position.
	void GameServer::UpdateState(def::time duration)
	{
		universe.UpdateState(duration);
	}

	//Test for collision at the current position, create new entities (e.g. explosions), remove expired (e.g. destroyed) entities.
	void GameServer::TestCollisions()
	{
		universe.TestCollisions();
	}

	//Test for visibility at the current position, send response.
	void GameServer::SendPackets()
	{
		universe.TestVisibility();
		//Collect visible environment for all queried entities.
		ServerStatePayloadBuffer& sspb = server_state_payload_buffer;
		for (size_t i = 0; i < sspb.count; i++)
		{
			def::entity_id entity_id = sspb.entity_ids[i];
			sspb.server_states[i].count = 0;
			for (const auto& visible_entity : universe.GetVision(entity_id))
			{
				net::ServerObject& server_object = sspb.server_states[i].objects[sspb.server_states[i].count++];
				server_object.entity_id = visible_entity->id;
				server_object.phi = visible_entity->orientation;
				server_object.x = visible_entity->position.x;
				server_object.y = visible_entity->position.y;
			}
		}
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
