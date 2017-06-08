#ifndef MYSOCKET
#define MYSOCKET

#include <winsock2.h>
#pragma comment( lib, "wsock32.lib" )


typedef int socklen_t;

const int max_packet_size = 100;

class Address
{
public:

    Address();
    Address( unsigned char, 
             unsigned char, 
             unsigned char, 
             unsigned char, 
             unsigned short) ;
    Address( unsigned int, 
             unsigned short);
    unsigned int GetAddress() const;
    unsigned char GetA() const;
    unsigned char GetB() const;
    unsigned char GetC() const;
    unsigned char GetD() const;
    unsigned short GetPort() const;

private:

    unsigned int address;
    unsigned short port;
};

class Socket
{
public:

    Socket();
    ~Socket();
    bool Open(unsigned short);
	static void Initialize();
    void Close();
    bool IsOpen();// const;
    bool Send( const Address&, 
               const void*,
               int);
    int Receive( Address&, 
                 void*, 
                 int);

private:
	static bool is_initialized;
    int handle;
};

#endif