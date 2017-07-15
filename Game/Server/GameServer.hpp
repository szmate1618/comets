#ifndef SZM_GAME_SERVER
#define SZM_GAME_SERVER

#include "AbstractServer.hpp"


namespace server
{

	class GameServer: public AbstractServer
	{
	public:

		GameServer();
		~GameServer();
		void MainLoop();
		bool Running();

	private:

		bool running;

		void ReadPackets();
		void ProcessPackets();
		void TestCollisions();
		void UpdateState();
		void SendPackets();
	};

}

#endif
