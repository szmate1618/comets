#include "Connection.hpp"


namespace net
{

	Connection::Connection(Address address, std::chrono::duration<double> duration) : address{ address }, countdown{ duration }
	{

	}

	Connection::~Connection()
	{

	}

	bool Connection::Update(std::chrono::duration<double> duration)
	{
		using namespace std::chrono_literals;
		countdown -= duration;
		return countdown <= 0.0s;
	}

}
