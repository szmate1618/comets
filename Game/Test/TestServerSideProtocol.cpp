#include "stdafx.h"
#include "CppUnitTest.h"

#include "ToStringSpecializations.hpp"
#include "..\Networking\Protocol.hpp"
#include "..\Networking\Packets.hpp"
#include "..\Utilities\CountOfArray.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	static std::vector<def::entity_id> entity_buffer;
	static std::vector<net::ClientInputPayload> client_input_buffer;
	static std::vector<net::ServerStatePayload> server_state_buffer;

	TEST_CLASS(TestServerSideProtocol)
	{

		class DummyExportStrategy : public net::AbstractExportStrategy
		{
		public:

			DummyExportStrategy() {}
			virtual ~DummyExportStrategy() {}
			virtual void Export(const net::ServerStatePayload& ss) const override { Assert::Fail(L"Not actually implemented, not supposed to be called."); }
			virtual void Export(const net::ClientInputPayload& ci) const override
			{
				client_input_buffer.emplace_back(ci);
			}

		};

		class DummyImportStrategy : public net::AbstractImportStrategy
		{
		public:

			DummyImportStrategy() {};
			virtual ~DummyImportStrategy() {};
			virtual std::tuple<size_t, def::entity_id*, net::ServerStatePayload*> ImportServerState() const override
			{
				return { entity_buffer.size(), &entity_buffer.front(), &server_state_buffer.front() };
			};
			virtual std::tuple<size_t, net::ClientInputPayload*> ImportClientIntput() const override
			{
				Assert::Fail(L"Not actually implemented, not supposed to be called.");
				return *reinterpret_cast<std::tuple<size_t, net::ClientInputPayload*>*>(0);
			}
		};

		net::Address server_address{ 127,0,0,1,def::server_port };
		DummyExportStrategy* export_strategy;
		DummyImportStrategy* import_strategy;
		net::ServersideProtocol* protocol;

		TEST_METHOD_INITIALIZE(InitializeServerSideProtocolTests)
		{
			entity_buffer.clear();
			client_input_buffer.clear();
			server_state_buffer.clear();

			export_strategy = new DummyExportStrategy;
			import_strategy = new DummyImportStrategy;
			protocol = new net::ServersideProtocol{ server_address.GetPort(), *export_strategy, *import_strategy };
		}

		TEST_METHOD_CLEANUP(CleanupServerSideProtocolTests)
		{
			entity_buffer.clear();
			client_input_buffer.clear();
			server_state_buffer.clear();

			delete protocol;
			delete import_strategy;
			delete export_strategy;
		}

	public:

		TEST_METHOD(Receive)
		{
			net::Socket client_socket;
			uint8_t inputs[4] = { 1, 20, 77, 78 };
			//TODO: Aggregate initialization is convenient, but automatically filling these default params would be cool, too.
			//Add a packet factory, maybe?
			net::ClientInputPacket packet{ def::protocol_id, 0, net::client_input, 1337, 2, static_cast<uint16_t>(util::countof(inputs)), inputs };
			client_socket.Send(server_address, packet.IO<net::Write>(client_socket.send_buffer)); //Because packet.IO returns the size. How convenient!

			protocol->Tick();
			Assert::AreEqual(packet.payload, client_input_buffer[0], L"Failed to correctly receive client input payload.");
		}

	};

}
