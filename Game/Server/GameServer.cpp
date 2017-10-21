#include "GameServer.hpp"

#include <cassert>


namespace server
{

	//Stroustrup: "The constructors are called in the order in which the members are declared
	//in the class rather than the order in which the members appear in the initializer list.
	//To avoid confusion, it is best to specify the initializers in the member declaration order."
	GameServer::GameServer() :
		export_strategy{ entity_buffer, client_input_buffer },
		import_strategy{ server_state_buffer },
		protocol{ 0, export_strategy, import_strategy },
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

	bool GameServer::Running() //TODO: This basically returns a constant. Why don't we have a Stop method here?
	{
		return running;
	}

	void GameServer::ReadPackets()
	{
		using namespace std::chrono_literals;
		def::time backoff = 0s;
	}

	//Read input, update entity orientation, acceleration, forces, etc.
	void GameServer::ProcessPackets()
	{
		while (Running())
		{

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
	}

	GameServer::ExportStrategy::ExportStrategy(std::vector<def::entity_id>& eb, std::vector<net::ClientIntputPayload>& cib) {};
	GameServer::ExportStrategy::~ExportStrategy() {};
	void GameServer::ExportStrategy::Export(const net::ServerStatePayload&) { assert(false && "Not actually implemented, not supposed to be called."); };
	void GameServer::ExportStrategy::Export(def::entity_id, const net::ClientIntputPayload&) {}; //TODO: Actually implement this.

	GameServer::ImportStrategy::ImportStrategy(std::vector<net::ServerStatePayload>& ssb) {};
	GameServer::ImportStrategy::~ImportStrategy() {};
	std::tuple<size_t, def::entity_id*, net::ServerStatePayload*> GameServer::ImportStrategy::ImportServerState()
	{
		std::tuple<size_t, def::entity_id*, net::ServerStatePayload*> dummy_return;
		return dummy_return;
	}; //TODO: Actually implement this.
	std::tuple<size_t, net::ClientIntputPayload*> GameServer::ImportStrategy::ImportClientIntput() 
	{
		assert(false && "Not actually implemented, not supposed to be called.");
		std::tuple<size_t, net::ClientIntputPayload*> dummy_return;
		return dummy_return;
	};

}
