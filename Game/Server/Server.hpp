#ifndef SZM_SERVER
#define SZM_SERVER

#include "AbstractServer.hpp"


namespace server
{

	class Server: public AbstractServer
	{
	public:

		Server();
		~Server();
		void MainLoop();

	private:

		void ReadPackets();
		void ProcessPackets();
		void TestCollisions();
		void UpdateState();
		void SendPackets();
	};

}

#endif