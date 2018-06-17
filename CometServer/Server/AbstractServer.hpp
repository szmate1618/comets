#pragma once

#include "..\Definitions\TimeAndNetwork.hpp"

#include <chrono>


namespace server
{

	class AbstractServer
	{
	public:

		AbstractServer();
		virtual ~AbstractServer();
		virtual void Tick(def::time) = 0;
		virtual bool Running() const = 0;

	private:

	};

}
