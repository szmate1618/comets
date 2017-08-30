#pragma once

#include "Address.hpp"
#include "..\Definitions\TimeAndNetwork.hpp"

#include <chrono>


namespace net
{


	class Connection
	{

	public:

		Connection(Address, def::time);
		Connection();
		~Connection();
		bool Update(def::time);

		const Address address;

	private:

		def::time countdown;

	};

}