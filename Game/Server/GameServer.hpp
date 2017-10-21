#pragma once

#include "AbstractServer.hpp"
#include "..\Networking\Protocol.hpp"
#include "..\Networking\Packets.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <chrono>
#include <thread>
#include <vector>


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

		class ExportStrategy : public net::AbstractExportStrategy
		{
		public:

			ExportStrategy(std::vector<def::entity_id>&, std::vector<net::ClientIntputPayload>&);
			virtual ~ExportStrategy() override;
			virtual void Export(const net::ServerStatePayload&) override;
			virtual void Export(def::entity_id, const net::ClientIntputPayload&) override;

		};

		class ImportStrategy : public net::AbstractImportStrategy
		{
		public:

			ImportStrategy(std::vector<net::ServerStatePayload>&);
			virtual ~ImportStrategy() override;
			virtual std::tuple<size_t, def::entity_id*, net::ServerStatePayload*> ImportServerState() override;
			virtual std::tuple<size_t, net::ClientIntputPayload*> ImportClientIntput() override;

		};

		std::vector<def::entity_id> entity_buffer;
		std::vector<net::ClientIntputPayload> client_input_buffer;
		std::vector<net::ServerStatePayload> server_state_buffer;
		ExportStrategy export_strategy;
		ImportStrategy import_strategy;
		net::ServersideProtocol protocol;
		bool running;
		std::thread input_thread;

		void ReadPackets();
		void ProcessPackets();
		void UpdateState(def::time);
		void TestCollisions();
		void SendPackets();

	};

}
