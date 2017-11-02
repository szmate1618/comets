#include "GameServer.hpp"

#include <cassert>
#include <chrono>


namespace server
{

	//Stroustrup: "The constructors are called in the order in which the members are declared
	//in the class rather than the order in which the members appear in the initializer list.
	//To avoid confusion, it is best to specify the initializers in the member declaration order."
	GameServer::GameServer() :
		export_strategy{ client_input_buffer },
		import_strategy{ server_state_buffer },
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
		auto start = std::chrono::steady_clock::now();
		while (Running())
		{
			if (backoff > 0s)
			{
				std::this_thread::sleep_for(backoff);
			}
			backoff = 0s;
			for (int i = 0; i < 10; i++)
			{
				auto elapsed_time = std::chrono::steady_clock::now() - start;
				start = std::chrono::steady_clock::now();
				if (protocol.Tick(elapsed_time) < 0) backoff += def::max_socket_read_backoff / 10;
				else backoff -= def::max_socket_read_backoff / 10;
			}
		}
	}

	//Read input, update entity orientation, acceleration, forces, etc.
	void GameServer::ProcessPackets()
	{
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

	GameServer::ExportStrategy::ExportStrategy(std::vector<net::ClientIntputPayload>& cib) {};
	GameServer::ExportStrategy::~ExportStrategy() {};
	void GameServer::ExportStrategy::Export(const net::ServerStatePayload&) const  { assert(false && "Not actually implemented, not supposed to be called."); };
	void GameServer::ExportStrategy::Export(const net::ClientIntputPayload&) const {}; //TODO: Actually implement this.

	GameServer::ImportStrategy::ImportStrategy(std::vector<net::ServerStatePayload>& ssb) {};
	GameServer::ImportStrategy::~ImportStrategy() {};
	std::tuple<size_t, def::entity_id*, net::ServerStatePayload*> GameServer::ImportStrategy::ImportServerState() const
	{
		std::tuple<size_t, def::entity_id*, net::ServerStatePayload*> dummy_return;
		return dummy_return;
	}; //TODO: Actually implement this.
	std::tuple<size_t, net::ClientIntputPayload*> GameServer::ImportStrategy::ImportClientIntput() const
	{
		assert(false && "Not actually implemented, not supposed to be called.");
		std::tuple<size_t, net::ClientIntputPayload*> dummy_return;
		return dummy_return;
	};

}
