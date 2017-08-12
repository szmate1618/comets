/*
This implementation is based on Glenn Fiedler's excellent articles on game networking.
Particularly this one: https://gafferongames.com/post/sending_and_receiving_packets/
*/
#include "Socket.hpp"

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
	#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
	#define PLATFORM PLATFORM_MAC
#else
	#define PLATFORM PLATFORM_UNIX
#endif

#if PLATFORM == PLATFORM_WINDOWS
	#include <winsock2.h>
	#pragma comment( lib, "wsock32.lib" )
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <fcntl.h>
#endif

#include <iostream>
#include <cassert>


namespace net
{

	int Socket::sockets_in_scope = 0;

	Socket::Socket() : is_open{ false }
	{
		MaybeInitializeSockets();
		handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		DWORD nonBlocking = 1;
		ioctlsocket(handle, FIONBIO, &nonBlocking);
	}

	Socket::~Socket()
	{
		Close();
		MaybeCleanupSockets();
	}

	bool Socket::Open(unsigned short port)
	{
		sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(port);

		if (bind(handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
		{
			std::cerr << ("Failed to bind socket.\n"); //TODO: Logging?
			return false;
		}
		is_open = true;
		return true;
	}

	void Socket::Close() { closesocket(handle); is_open = false; }

	bool Socket::IsOpen() const { return is_open; }

	bool Socket::Send(const Address & destination, const void * packet_data, int packet_size) const
	{
		sockaddr_in address;
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = htonl(destination.GetAddress());
		address.sin_port = htons(destination.GetPort());

		int sent_bytes = sendto(handle,
							(const char*)packet_data,
							packet_size,
							0,
							(sockaddr*)&address,
							sizeof(sockaddr_in));

		if (sent_bytes != packet_size)
		{
			std::cerr << ("Failed to send packet.\n"); //TODO: Logging?
			return false;
		}
		return true;
	}

	int Socket::Receive(Address& sender, void* packet_data, int packet_size) const
	{
		sockaddr_in from;
		socklen_t fromLength = sizeof(from);

		int bytes = recvfrom(handle,
						(char*)packet_data,
						max_packet_size,
						0,
						(sockaddr*)&from,
						&fromLength);

		unsigned int from_address = ntohl(from.sin_addr.s_addr);
		unsigned int from_port = ntohs(from.sin_port);
		return bytes;
	}

	void Socket::MaybeInitializeSockets()
	{
		assert(sockets_in_scope >= 0, "Number of scope objects is less than 0. A concurreny error, maybe?");
		if (sockets_in_scope++ != 0) return;

		#if PLATFORM == PLATFORM_WINDOWS
		WSADATA WsaData;
		WSAStartup(MAKEWORD(2, 2), &WsaData);
		#endif
	}

	void Socket::MaybeCleanupSockets()
	{
		if (--sockets_in_scope != 0) return;

		#if PLATFORM == PLATFORM_WINDOWS
		WSACleanup();
		#endif
	}

}
