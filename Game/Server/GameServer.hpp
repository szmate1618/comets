#pragma once

#include "AbstractServer.hpp"
#include "..\Networking\Protocol.hpp"
#include "..\Networking\Packets.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <chrono>
#include <thread>
#include <vector>
#include <atomic>


namespace server
{

	using tick = def::server_tick;

	class GameServer : public AbstractServer
	{
	public:

		GameServer();
		virtual ~GameServer() override;
		virtual void Tick(def::time) override;
		virtual bool Running() const override;

	protected:

		virtual void ReadPackets();
		virtual void ProcessPackets();
		virtual void UpdateState(def::time);
		virtual void TestCollisions();
		virtual void SendPackets();

	private:

		class ExportStrategy : public net::AbstractExportStrategy
		{
		public:

			ExportStrategy(std::vector<def::entity_id>&, std::vector<net::ClientIntputPayload>&);
			virtual ~ExportStrategy() override;
			virtual void Export(const net::ServerStatePayload&) const override;
			virtual void Export(def::entity_id, const net::ClientIntputPayload&) const override;

		};

		class ImportStrategy : public net::AbstractImportStrategy
		{
		public:

			ImportStrategy(std::vector<net::ServerStatePayload>&);
			virtual ~ImportStrategy() override;
			virtual std::tuple<size_t, def::entity_id*, net::ServerStatePayload*> ImportServerState() const override;
			virtual std::tuple<size_t, net::ClientIntputPayload*> ImportClientIntput() const override;

		};

		std::vector<def::entity_id> entity_buffer;
		std::vector<net::ClientIntputPayload> client_input_buffer;
		std::vector<net::ServerStatePayload> server_state_buffer;
		ExportStrategy export_strategy;
		ImportStrategy import_strategy;
		net::ServersideProtocol protocol;
		std::atomic<bool> running;
		std::thread input_thread;

	};

}
