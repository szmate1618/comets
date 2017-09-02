#include "GameServer.hpp"


namespace server
{

	GameServer::GameServer() : running{ true }
	{
	}

	GameServer::~GameServer()
	{
	}

	void GameServer::Tick(def::time duration)
	{
		ReadPackets(); //TODO: This should run in a separate thread.
		ProcessPackets();
		TestCollisions();
		UpdateState(duration);
		SendPackets();
	}

	bool GameServer::Running()
	{
		return running;
	}

	void GameServer::ReadPackets()
	{
	}

	void GameServer::ProcessPackets()
	{
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
