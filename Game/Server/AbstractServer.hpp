#pragma once

namespace server
{

	class AbstractServer
	{
	public:

		AbstractServer();
		virtual ~AbstractServer();
		virtual void MainLoop() = 0;
		virtual bool Running() = 0;

	private:

	};

}
