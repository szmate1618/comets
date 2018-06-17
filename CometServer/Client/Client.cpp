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
	ReadClientIntput();
	SendPackets();
}

void Client::ReadPackets()
{
}

void Client::ProcessPackets()
{
}

void Client::ReadClientIntput()
{
}

void Client::SendPackets()
{
}
