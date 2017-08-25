#include "AbstractServer.hpp"
#include "GameServer.hpp"


int main()
{
	server::AbstractServer* gameserver = &server::GameServer{};
	
	volatile bool running = true;

	while (running && gameserver->Running())
	{
		gameserver->MainLoop();
	}

	return 0;
}
