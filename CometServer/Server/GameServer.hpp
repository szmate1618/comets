#pragma once

#include "AbstractServer.hpp"
#include "PacketPayloadBuffers.hpp"
#include "..\Entities\Universe.hpp"
#include "..\Networking\Protocol.hpp"
#include "..\Networking\Packets.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <chrono>
#include <thread>
#include <vector>
#include <atomic>


namespace server
{

	using tick = def::server_tick; //TODO: This is unused, and a bit strange anyway.

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

			ExportStrategy(GameServer&);
			virtual ~ExportStrategy() override;
			virtual void Export(const net::ClientInputPayload&) const override;
			virtual net::ShapeDescriptionPayload& ExportImport(const net::ShapeRequestPayload&) const override;

		private:

			GameServer& game_server;

		};

		class ImportStrategy : public net::AbstractImportStrategy
		{
		public:

			ImportStrategy(GameServer&);
			virtual ~ImportStrategy() override;
			virtual std::tuple<size_t, def::entity_id*, net::ServerStatePayload*> ImportServerState() const override;

		private:

			GameServer& game_server;

		};

		entity::Universe universe;
		ClientInputPayloadBuffer client_input_payload_buffer;
		ServerStatePayloadBuffer server_state_payload_buffer;
		net::ShapeDescriptionPayload shape_description_payload;
		ExportStrategy export_strategy;
		ImportStrategy import_strategy;
		net::ServersideProtocol protocol;
		std::atomic<bool> running;
		std::thread input_thread;
		int tick;

		void ReadPackets();
		void ProcessPackets(def::time);
		void UpdateState(def::time);
		void TestCollisions();
		void SendPackets();

	};

}
