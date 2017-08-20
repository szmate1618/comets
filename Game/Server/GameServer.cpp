#include "GameServer.hpp"


namespace server
{

	GameServer::GameServer() : running{ true }
	{
	}

	GameServer::~GameServer()
	{
	}

	void GameServer::MainLoop()
	{
		ReadPackets();
		ProcessPackets();
		TestCollisions();
		UpdateState();
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

	void GameServer::UpdateState()
	{
	}

	void GameServer::SendPackets()
	{
	}

}
