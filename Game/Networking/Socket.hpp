#pragma once

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32) || defined(_WIN64)
#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM PLATFORM_MAC
#else
#define PLATFORM PLATFORM_UNIX
#endif

#if PLATFORM == PLATFORM_WINDOWS
#include <winsock2.h>
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#endif

#include "Address.hpp"
#include "LogMessages.hpp"


namespace net
{

	#if PLATFORM == PLATFORM_WINDOWS
	typedef int socklen_t;
	#endif

	constexpr int max_packet_size = 1000; //TODO: Check recommended max MTU.

	class Socket
	{
	public:

		Socket();
		Socket(unsigned short);
		~Socket();
		void Open(unsigned short);
		void Close();
		bool IsOpen() const;
		bool Send(const Address&, const void*, int) const;
		int Receive(Address&, void*, int) const;
		int Receive(Address&) const;

		char recv_buffer[max_packet_size];

	protected: //TODO: Maybe making the test class its friend would be a better solution.

		static void LogNetworkErrors(int);

	private:

		SOCKET handle;
		bool is_open;

		static void AssertAndLog(bool);
		static void AssertAndLog(bool, const char*);
		static void MaybeInitializeSockets(); //Only call this from constructors.
		static void MaybeCleanupSockets(); //Only call this from destructors.
		static int sockets_in_scope;

	};

}
