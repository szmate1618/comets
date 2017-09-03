#pragma once

#include "AbstractServer.hpp"
#include "..\Networking\Protocol.hpp"

#include <chrono>
#include <thread>


namespace server
{

	using tick = std::chrono::duration<double, std::ratio<1, 90>>;

	class GameServer : public AbstractServer
	{
	public:

		GameServer();
		virtual ~GameServer() override;
		virtual void Tick(def::time) override;
		virtual bool Running() override;

	private:

		bool running;
		std::thread input_thread;

		void ReadPackets();
		void ProcessPackets();
		void TestCollisions();
		void UpdateState(def::time);
		void SendPackets();
	};

}
