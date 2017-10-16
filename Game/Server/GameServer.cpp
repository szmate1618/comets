#include "GameServer.hpp"


namespace server
{

	GameServer::GameServer() : running{ true }, input_thread{ [=] { ReadPackets(); } }
	{
	}

	GameServer::~GameServer()
	{
		input_thread.join(); //TODO: Don't forget to stop this thread.
	}

	void GameServer::Tick(def::time duration)
	{
		ProcessPackets();
		TestCollisions(); //TODO: Why not UpdateState first?
		UpdateState(duration);
		SendPackets();
	}

	bool GameServer::Running()
	{
		return running;
	}

	void GameServer::ReadPackets()
	{
		using namespace std::chrono_literals;
		def::time backoff = 0s;
	}

	void GameServer::ProcessPackets()
	{
		while (Running())
		{

		}
	}

	void GameServer::TestCollisions()
	{
	}

	void GameServer::UpdateState(def::time duration)
	{
	}

	void GameServer::SendPackets()
	{
	}

}
