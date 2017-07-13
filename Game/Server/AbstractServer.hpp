#ifndef SZM_ABSTRACT_SERVER
#define SZM_ABSTRACT_SERVER

class AbstractServer
{
public:

	AbstractServer();
	virtual ~AbstractServer();
	virtual void MainLoop() = 0;
	virtual bool Running() = 0;

private:

	virtual void ReadPackets() = 0;
	virtual void ProcessPackets() = 0;
	virtual void TestCollisions() = 0;
	virtual void UpdateState() = 0;
	virtual void SendPackets() = 0;
};

#endif