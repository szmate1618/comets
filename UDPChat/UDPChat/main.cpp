/*#include <winsock2.h>
#pragma comment( lib, "wsock32.lib" )*/
#include <iostream>

#include "Socket.h"
/*
bool InitializeSockets()
{
    WSADATA WsaData;
    return WSAStartup( MAKEWORD(2,2), 
                       &WsaData ) 
        == NO_ERROR;
}

void ShutdownSockets()
{
    WSACleanup();
}

sockaddr_in Bind(int handle,
			unsigned int a, unsigned int b, unsigned int c, unsigned int d,
			unsigned short port)
{
	unsigned int address = ( a << 24 ) | 
                       ( b << 16 ) | 
                       ( c << 8  ) | 
                         d;
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = 
		htons( (unsigned short) port );

	if ( bind( handle, 
			   (const sockaddr*) &addr, 
			   sizeof(sockaddr_in) ) < 0 )
	{
		printf( "failed to bind socket\n" );
	}
	return addr;
}	

void SetNonBlocking(int handle)
{
	DWORD nonBlocking = 1;
	if ( ioctlsocket( handle, 
					  FIONBIO, 
					  &nonBlocking ) != 0 )
	{
		printf( "failed to set non-blocking\n" );
	}
}*/

int main()
{
	/*InitializeSockets();
	int handle = socket( AF_INET, 
                     SOCK_DGRAM, 
                     IPPROTO_UDP );
	
	int handle2 = socket( AF_INET, 
                     SOCK_DGRAM, 
                     IPPROTO_UDP );

	SetNonBlocking(handle);
	SetNonBlocking(handle2);
	sockaddr_in source = Bind(handle, 127, 0, 0, 1, 2200);
	sockaddr_in target  = Bind(handle2, 127, 0, 0, 1, 2201);

	char packet_data[] = "Zitaegyribanc";

	for (int i = 0; i < 10; i++)
	{
		    sendto( handle, 
            (const char*)packet_data, 
            13,
            0, 
            (sockaddr*)&target, 
            sizeof(sockaddr_in) );

			char buff[1000];
			int len = 13;
			recvfrom(handle2,
					buff,
					13,
					0,
					(sockaddr*)&source,
					&len);
			std::cout << buff << std::endl;
			getchar();
	}
	getchar();

	ShutdownSockets();*/
	/*Address a1(127, 0, 0, 1, 6400);
	Address a2(127, 0, 0, 1, 6401);
	Socket sender;
	sender.Open(a1.GetPort());
	Socket receiver;
	receiver.Open(a2.GetPort());
	char data[]  = "mofomofomofo";
	sender.Send(a2, data, 12);*/
	const int port = 30000;
	Socket receiver;
	receiver.Open(6407);
	Socket socket;
	socket.Open(0);
	const char data2[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	socket.Send( Address(127,0,0,1,6401), data2, sizeof(data2) );
	const char data[] = "hello world!";
	socket.Send( Address(127,0,0,1,6401), data, sizeof(data) );
	const char data3[] = "..........................................................123456789";
	socket.Send(Address(127, 0, 0, 1, 6401), data3, sizeof(data3));


	while ( true )
	{
		Address sender;
		unsigned char buffer[max_packet_size];
		//buffer[0] = 0;
		memset(buffer, 100, sizeof(buffer));
		buffer[max_packet_size - 1] = 0;
		int bytes_read = 
			receiver.Receive(sender, 
							buffer, 
							sizeof(buffer));
		if (bytes_read <= 0)
			break;

		std::cout << bytes_read;
		std::cout << buffer << std::endl;
		getchar();
	}

	return 0;
}