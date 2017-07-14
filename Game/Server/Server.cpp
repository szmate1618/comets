#include "Server.hpp"


namespace server
{

	Server::Server()
	{
	}

	Server::~Server()
	{
	}

	void Server::MainLoop()
	{
		ReadPackets();
		ProcessPackets();
		TestCollisions();
		UpdateState();
		SendPackets();
	}

	void Server::ReadPackets()
	{
	}

	void Server::ProcessPackets()
	{
	}

	void Server::TestCollisions()
	{
	}

	void Server::UpdateState()
	{
	}

	void Server::SendPackets()
	{
	}

}