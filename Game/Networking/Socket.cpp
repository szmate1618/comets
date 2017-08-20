/*
This implementation is based on Glenn Fiedler's excellent articles on game networking.
Particularly this one: https://gafferongames.com/post/sending_and_receiving_packets/
*/
#include "Socket.hpp"

#include "../Utilities/Logger.hpp"

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

		int bind_return = bind(handle, (const sockaddr*)&address, sizeof(sockaddr_in));
		if (bind_return != 0)
		{
			util::Log(util::error, "Failed to bind socket. See the details below then consult the manual of your socket library.");
			#if PLATFORM == PLATFORM_WINDOWS //TODO: Also add Linux error logging/handling.
			int errorcode = WSAGetLastError();
			switch (errorcode)
			{
			case WSANOTINITIALISED: { util::Log(util::error, "WSANOTINITIALISED: A successful WSAStartup call must occur before using this function."); break; }
			case WSAENETDOWN: { util::Log(util::fatal, "WSAENETDOWN: The network subsystem has failed."); break; }
			case WSAEACCES: { util::Log(util::error, " WSAEACCES: An attempt was made to access a socket in a way forbidden by its access permissions."); break; }
			case WSAEADDRINUSE: { util::Log(util::error, "WSAEADDRINUSE: Only one usage of each socket address (protocol/network address/port) is normally permitted."); break; }
			case WSAEADDRNOTAVAIL: { util::Log(util::error, "WSAEADDRNOTAVAIL: The requested address is not valid in its context."); break; }
			case WSAEFAULT: { util::Log(util::error, "WSAEFAULT: The system detected an invalid pointer address in attempting to use a pointer argument in a call."); break; }
			case WSAEINPROGRESS: { util::Log(util::error, "WSAEINPROGRESS: A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."); break; }
			case WSAEINVAL: { util::Log(util::error, "WSAEINVAL: An invalid argument was supplied. This error is returned of the socket s is already bound to an address."); break; }
			case WSAENOBUFS: { util::Log(util::error, "WSAENOBUFS: An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full."); break; }
			case WSAENOTSOCK: { util::Log(util::error, "WSAENOTSOCK: An operation was attempted on something that is not a socket. Did you try to bind a closed one?"); break; }
			default: { util::Log(util::error, "Sorry, this errorcode is totally unknown. Its numerical value is " + std::to_string(errorcode) + "."); break; }
			}
			#endif
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
