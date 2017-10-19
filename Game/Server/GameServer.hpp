#pragma once

#include "AbstractServer.hpp"
#include "..\Networking\Protocol.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <chrono>
#include <thread>


namespace server
{

	using tick = def::server_tick;

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
		void UpdateState(def::time);
		void TestCollisions();
		void SendPackets();
	};

}
