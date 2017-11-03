#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Networking\Protocol.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(ServerSideProtocol)
	{

		static std::vector<def::entity_id> entity_buffer;
		static std::vector<net::ClientIntputPayload> client_input_buffer;
		static std::vector<net::ServerStatePayload> server_state_buffer;

		class DummyExportStrategy 
		{
			DummyExportStrategy(std::vector<net::ClientIntputPayload>& cib) {}
			~DummyExportStrategy() {}
			void Export(const net::ServerStatePayload& ss) const { Assert::Fail(L"Not actually implemented, not supposed to be called."); }
			void Export(const net::ClientIntputPayload& ci) const 
			{
				client_input_buffer.emplace_back(ci);
			}

		};

		class DummyImportStrategy
		{
			DummyImportStrategy(std::vector<net::ServerStatePayload>& ssb) {};
			~DummyImportStrategy() {};
			std::tuple<size_t, def::entity_id*, net::ServerStatePayload*> ImportServerState() const
			{
				return { entity_buffer.size(), &entity_buffer.front(), &server_state_buffer.front() };
			};
			std::tuple<size_t, net::ClientIntputPayload*> ImportClientIntput() const
			{
				Assert::Fail(L"Not actually implemented, not supposed to be called.");
				std::tuple<size_t, net::ClientIntputPayload*> dummy_return;
				return dummy_return;
			}
		};

		TEST_METHOD_INITIALIZE(InitializerLoggerTests)
		{
			entity_buffer.clear();
			client_input_buffer.clear();
			server_state_buffer.clear();
		}

	public:

		TEST_METHOD(Test01)
		{
		}

	};

}
