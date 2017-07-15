#include "Client.hpp"

Client::Client()
{
}

Client::~Client()
{
}

void Client::MainLoop()
{
	ReadPackets();
	ProcessPackets();
	ReadUserInput();
	SendPackets();
}

void Client::ReadPackets()
{
}

void Client::ProcessPackets()
{
}

void Client::ReadUserInput()
{
}

void Client::SendPackets()
{
}
