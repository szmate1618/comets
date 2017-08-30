#include "Connection.hpp"


namespace net
{

	Connection::Connection(Address address, def::time duration) : address{ address }, countdown{ duration }
	{

	}

	Connection::Connection()
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

}
