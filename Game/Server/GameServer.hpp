#ifndef SZM_GAME_SERVER
#define SZM_GAME_SERVER

#include "AbstractServer.hpp"


namespace server
{

	class GameServer: public AbstractServer
	{
	public:

		GameServer();
		virtual ~GameServer() override;
		virtual void MainLoop() override;
		virtual bool Running() override;

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
