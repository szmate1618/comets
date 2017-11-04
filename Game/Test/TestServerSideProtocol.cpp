#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Networking\Protocol.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	static std::vector<def::entity_id> entity_buffer;
	static std::vector<net::ClientIntputPayload> client_input_buffer;
	static std::vector<net::ServerStatePayload> server_state_buffer;

	TEST_CLASS(TestServerSideProtocol)
	{

		class DummyExportStrategy : public net::AbstractExportStrategy
		{
		public:

			DummyExportStrategy() {}
			virtual ~DummyExportStrategy() {}
			virtual void Export(const net::ServerStatePayload& ss) const override { Assert::Fail(L"Not actually implemented, not supposed to be called."); }
			virtual void Export(const net::ClientIntputPayload& ci) const override
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
			virtual std::tuple<size_t, net::ClientIntputPayload*> ImportClientIntput() const override
			{
				Assert::Fail(L"Not actually implemented, not supposed to be called.");
				return *reinterpret_cast<std::tuple<size_t, net::ClientIntputPayload*>*>(0);
			}
		};

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
			protocol = new net::ServersideProtocol{ def::server_port, *export_strategy, *import_strategy };
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

		TEST_METHOD(Test01)
		{
		}

	};

}
