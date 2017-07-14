#include "GameServer.hpp"


namespace server
{

	GameServer::GameServer(): running(true)
	{
	}

	GameServer::~GameServer()
	{
		Finish();
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

	void GameServer::Finish()
	{
		running = false;
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