#pragma once

#include <chrono>


namespace server
{

	class AbstractServer
	{
	public:

		AbstractServer();
		virtual ~AbstractServer();
		virtual void Tick(std::chrono::duration<double>) = 0;
		virtual bool Running() = 0;

	private:

	};

}
