#pragma once

#include "Address.hpp"

#include <chrono>


namespace net
{


	class Connection
	{

	public:

		Connection(Address, std::chrono::duration<double>);
		Connection() = delete;
		~Connection();
		bool Update(std::chrono::duration<double>);


		const Address address;

	private:

		std::chrono::duration<double> countdown;

	};

}