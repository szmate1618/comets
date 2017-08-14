#pragma once

#include "Address.hpp"


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
		~Socket();
		bool Open(unsigned short);
		void Close();
		bool IsOpen() const;
		bool Send(const Address&, const void*, int) const;
		int Receive(Address&, void*, int) const;
		int Receive(Address&) const;

		char recv_buffer[max_packet_size];

	private:

		int handle;
		bool is_open;

		static void MaybeInitializeSockets(); //Only call this from constructors.
		static void MaybeCleanupSockets(); //Only call this from destructors.
		static int sockets_in_scope;

	};

}
