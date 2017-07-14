#ifndef SZM_ABSTRACT_SERVER
#define SZM_ABSTRACT_SERVER

namespace server
{

	class AbstractServer
	{
	public:

		AbstractServer();
		virtual ~AbstractServer();
		virtual void MainLoop() = 0;
		virtual bool Running() = 0;
		virtual void Finish() = 0;

	private:

	};

}

#endif
