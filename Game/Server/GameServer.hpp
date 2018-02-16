#pragma once

#include "AbstractServer.hpp"
#include "PacketPayloadBuffers.hpp"
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

	private:

		class ExportStrategy : public net::AbstractExportStrategy
		{
		public:

			ExportStrategy(ClientInputPayloadBuffer&);
			virtual ~ExportStrategy() override;
			virtual void Export(const net::ServerStatePayload&) const override;
			virtual void Export(const net::ClientInputPayload&) const override;

		private:

			ClientInputPayloadBuffer& client_input_payload_buffer;

		};

		class ImportStrategy : public net::AbstractImportStrategy
		{
		public:

			ImportStrategy(ServerStatePayloadBuffer&);
			virtual ~ImportStrategy() override;
			virtual std::tuple<size_t, def::entity_id*, net::ServerStatePayload*> ImportServerState() const override;
			virtual std::tuple<size_t, net::ClientInputPayload*> ImportClientIntput() const override;

		private:

			ServerStatePayloadBuffer& server_state_payload_buffer;

		};

		ClientInputPayloadBuffer client_input_payload_buffer;
		ServerStatePayloadBuffer server_state_payload_buffer;
		ExportStrategy export_strategy;
		ImportStrategy import_strategy;
		net::ServersideProtocol protocol;
		std::atomic<bool> running;
		std::thread input_thread;

		void ReadPackets();
		void ProcessPackets(def::time);
		void UpdateState(def::time);
		void TestCollisions();
		void SendPackets();

	};

}
