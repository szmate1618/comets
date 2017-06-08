#include <iostream>

#include "Socket.h"


Address::Address(){}
Address::Address(unsigned char a, 
             unsigned char b, 
             unsigned char c, 
             unsigned char d, 
			 unsigned short port)
{
	this->address = ( a << 24 ) | 
			( b << 16 ) | 
            ( c << 8  ) | 
			d;
	this->port = port;
}

Address::Address(unsigned int address, 
				 unsigned short port)
{
	this->address = address;
	this->port = port;
}

unsigned int Address::GetAddress() const {return address;}

unsigned char Address::GetA() const {return unsigned char(address | 255 << 24);}

unsigned char Address::GetB() const {return unsigned char(address | 255 << 16);}

unsigned char Address::GetC() const {return unsigned char(address | 255 << 8);}

unsigned char Address::GetD() const {return unsigned char(address | 255);}

unsigned short Address::GetPort() const {return port;}

bool Socket::is_initialized = false;

Socket::Socket()
{
	Initialize();

	handle = socket( AF_INET, 
                     SOCK_DGRAM, 
                     IPPROTO_UDP );

	DWORD nonBlocking = 1;
	ioctlsocket( handle, 
                  FIONBIO, 
                  &nonBlocking );
}

Socket::~Socket()
{
	Close();
	WSACleanup();
}

void Socket::Initialize()
{
	if (is_initialized) return;
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2,2), 
				&WsaData );
	is_initialized = true;
}

bool Socket::Open(unsigned short port)
{
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = 
    htons((unsigned short)port);

	if (bind(handle, 
           (const sockaddr*) &address, 
           sizeof(sockaddr_in) ) < 0)
	{
		std::cerr << ( "failed to bind socket\n" );
		return false;
	}
	return true;
}

void Socket::Close(){closesocket(handle);}

bool Socket::IsOpen(){return true;/*TODO actually implement this*/}

bool Socket::Send( const Address & destination, 
               const void * packet_data, 
			   int packet_size )
{
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(destination.GetAddress());
	address.sin_port = htons(destination.GetPort());

	int sent_bytes = 
    sendto( handle, 
            (const char*)packet_data, 
            packet_size,
            0, 
            (sockaddr*)&address, 
            sizeof(sockaddr_in) );

	if ( sent_bytes != packet_size )
	{
		std::cerr << ( "failed to send packet\n" );
		return false;
	}
	return true;
}

int Socket::Receive( Address& sender, 
                 void* packet_data, 
				 int packet_size )
{
    sockaddr_in from;
    socklen_t fromLength = sizeof( from );

    int bytes = recvfrom( handle, 
                          (char*)packet_data, 
                          max_packet_size,
                          0, 
                          (sockaddr*)&from, 
                          &fromLength );

    unsigned int from_address = 
        ntohl( from.sin_addr.s_addr );

    unsigned int from_port = 
        ntohs( from.sin_port );

	return bytes;
}