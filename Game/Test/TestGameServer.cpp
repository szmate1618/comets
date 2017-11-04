#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Networking\Protocol.hpp"
#include "..\Networking\Packets.hpp"
#include "..\Server\GameServer.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(TestGameServer)
	{

		class DummyExportStrategy : public net::AbstractExportStrategy
		{
		public:
			DummyExportStrategy(std::vector<net::ClientIntputPayload>&) {}
		};

		class DummyImportStrategy : public net::AbstractImportStrategy
		{
		public:
			DummyImportStrategy(std::vector<net::ServerStatePayload>& ssb) {}
		};

		/*class DummyGameServer
		{
		public:
			DummyGameServer() :
			export_strategy{ client_input_buffer },
			import_strategy{ server_state_buffer },
			protocol{ def::server_port, export_strategy, import_strategy },
			input_thread{ [=] { ReadPackets(); } } {}
			void DummyTick()
			{
			protocol.Respond();
			}
		private:
			void DummyGameServer::ReadPackets()
			{
			}
			std::vector<net::ClientIntputPayload> client_input_buffer;
			std::vector<net::ServerStatePayload> server_state_buffer;
			DummyExportStrategy export_strategy;
			DummyImportStrategy import_strategy;
			net::ServersideProtocol protocol;
			std::thread input_thread;
		};*/

	public:

		TEST_METHOD(Test01)
		{
		}

	};

}
