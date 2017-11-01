#include "AbstractServer.hpp"
#include "GameServer.hpp"

#include <thread>
#include <chrono>


int main() //TODO: Maybe factor this out into a class for better testability.
{
	server::AbstractServer* gameserver = &server::GameServer{};
	
	volatile bool running = true;

	while (running && gameserver->Running())
	{
		auto start = std::chrono::steady_clock::now();
		gameserver->Tick(server::tick{ 1 });
		auto end = std::chrono::steady_clock::now();
		std::this_thread::sleep_for(server::tick{ 1 } - (end - start)); //TODO: What happens if this is negative?
	}

	return 0;
}
