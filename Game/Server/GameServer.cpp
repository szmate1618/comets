#include "GameServer.hpp"


namespace server
{

	GameServer::GameServer() : running{ true }
	{
	}

	GameServer::~GameServer()
	{
	}

	void GameServer::Tick(std::chrono::duration<double> duration)
	{
		ReadPackets();
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

	void GameServer::UpdateState(std::chrono::duration<double> duration)
	{
	}

	void GameServer::SendPackets()
	{
	}

}
