/*
This implementation is based on Glenn Fiedler's excellent articles on game networking.
Particularly this one: https://gafferongames.com/post/sending_and_receiving_packets/
*/
#include "Socket.hpp"

#if PLATFORM == PLATFORM_WINDOWS
#pragma comment( lib, "wsock32.lib" )
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

		#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		int nonBlocking = 1;
		bool blocking = (fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
		#elif PLATFORM == PLATFORM_WINDOWS
		DWORD nonBlocking = 1;
		bool blocking = ioctlsocket(handle, FIONBIO, &nonBlocking);
		#endif
		assert(!blocking && "Faied to set non-blocking mode.");
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

	void Socket::Close()
	{
        #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		close(handle);
        #elif PLATFORM == PLATFORM_WINDOWS
		closesocket(handle);
        #endif
		is_open = false;
	}

	bool Socket::IsOpen() const { return is_open; }

	bool Socket::Send(const Address& destination, const void* packet_data, int packet_size) const
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

	int Socket::Receive(Address& sender, void* buffer, int buffer_size) const
	{
		sockaddr_in from;
		socklen_t fromLength = sizeof(from);

		int bytes = recvfrom(handle,
						(char*)buffer,
						buffer_size,
						0,
						(sockaddr*)&from,
						&fromLength);

		unsigned int from_address = ntohl(from.sin_addr.s_addr);
		unsigned int from_port = ntohs(from.sin_port);
		sender = Address(from_address, from_port);

		return bytes;
	}

	int Socket::Receive(Address& sender) const
	{
		return Receive(sender, (void*)recv_buffer, max_packet_size); //TODO: Use static cast?
	}

	void Socket::MaybeInitializeSockets()
	{
		assert(sockets_in_scope >= 0 && "Number of socket objects is less than 0. A concurreny error, maybe?");
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
