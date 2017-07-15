#include "AbstractServer.hpp"
#include "GameServer.hpp"


int main()
{
	server::GameServer concretegameserver;
	server::AbstractServer* gameserver = &concretegameserver;
	
	volatile bool running = true;

	while (running && gameserver->Running())
	{
		gameserver->MainLoop();
	}

	return 0;
}
