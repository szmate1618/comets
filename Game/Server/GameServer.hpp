#pragma once

#include "AbstractServer.hpp"

#include <chrono>


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
