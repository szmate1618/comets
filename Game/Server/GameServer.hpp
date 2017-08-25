#pragma once

#include "AbstractServer.hpp"

#include <chrono>


namespace server
{

	using tick = std::chrono::duration<double, std::ratio<1, 90>>;

	class GameServer: public AbstractServer
	{
	public:

		GameServer();
		virtual ~GameServer() override;
		virtual void Tick(std::chrono::duration<double>) override;
		virtual bool Running() override;

	private:

		bool running;

		void ReadPackets();
		void ProcessPackets();
		void TestCollisions();
		void UpdateState(std::chrono::duration<double>);
		void SendPackets();
	};

}
