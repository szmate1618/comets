#ifndef SZM_CLIENT
#define SZM_CLIENT

class Client
{
public:

	Client();
	~Client();
	void MainLoop();

private:

	void ReadPackets();
	void ProcessPackets();
	void ReadUserInput();
	void SendPackets();
};

#endif
