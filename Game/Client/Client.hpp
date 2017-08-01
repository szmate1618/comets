#pragma once

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
