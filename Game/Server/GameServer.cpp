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

}
