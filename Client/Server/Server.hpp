#ifndef SZM_SERVER
#define SZM_SERVER

class Server
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

#endif