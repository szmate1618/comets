#include "AbstractServer.hpp"
#include "GameServer.hpp"

int main()
{
	server::GameServer concretegameserver = server::GameServer();
	server::AbstractServer* gameserver = &concretegameserver;
	
	volatile bool running = true;

	while (running && gameserver->Running())
	{
		gameserver->MainLoop();
	}
	gameserver->Finish(); //Should Finish() be called automatically only, from the destructor?

	return 0;
}
