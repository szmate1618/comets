#pragma once


namespace net
{

	static const char* const unregistered_error = "Sorry, this errorcode is not registered. Maybe look it up in the manual. Its numerical value is ";

	static const char* const blocking_mode_fail = "Failed to set non-blocking mode.";
	static const char* const packet_send_fail = "Failed to send packet.";
	static const char* const socket_bind_fail = "Failed to bind socket. See the details below then consult the manual of your socket library.";

	static const char* const WSANOTINITIALISED_text = "WSANOTINITIALISED: A successful WSAStartup call must occur before using this function.";
	static const char* const WSAENETDOWN_text = "WSAENETDOWN: The network subsystem has failed.";
	static const char* const WSAEACCES_text = "WSAEACCES: An attempt was made to access a socket in a way forbidden by its access permissions.";
	static const char* const WSAEADDRINUSE_text = "WSAEADDRINUSE: Only one usage of each socket address (protocol/network address/port) is normally permitted.";
	static const char* const WSAEADDRNOTAVAIL_text = "WSAEADDRNOTAVAIL: The requested address is not valid in its context.";
	static const char* const WSAEFAULT_text = "WSAEFAULT: The system detected an invalid pointer address in attempting to use a pointer argument in a call.";
	static const char* const WSAEINPROGRESS_text = "WSAEINPROGRESS: A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.";
	static const char* const WSAEINVAL_text = "WSAEINVAL: An invalid argument was supplied. This error is returned of the socket s is already bound to an address.";
	static const char* const WSAENOBUFS_text = "WSAENOBUFS: An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.";
	static const char* const WSAENOTSOCK_text = "WSAENOTSOCK: An operation was attempted on something that is not a socket. Are you trying to bind a closed one?";

}
