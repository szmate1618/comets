#include "Connection.hpp"


namespace net
{

	Connection::Connection(const Address& address, def::time duration) : address{ address }, countdown{ duration }
	{

	}

	Connection::Connection() : address{}
	{

	}

	Connection::~Connection()
	{

	}

	bool Connection::Update(def::time duration)
	{
		using namespace std::chrono_literals;
		countdown -= duration;
		return countdown <= 0.0s;
	}

	bool Connection::TimedOut()
	{
		using namespace std::chrono_literals;
		return countdown <= 0.0s;
	}

}
