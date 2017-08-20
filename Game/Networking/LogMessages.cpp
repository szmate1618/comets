#include "LogMessages.hpp"


namespace net
{

	const char* unknown_error = "Sorry, this errorcode is totally unknown. Its numerical value is ";


	const char* socket_bind_fail = "Failed to bind socket. See the details below then consult the manual of your socket library.";

	const char* WSANOTINITIALISED_text = "WSANOTINITIALISED: A successful WSAStartup call must occur before using this function.";
	const char* WSAENETDOWN_text = "WSAENETDOWN: The network subsystem has failed.";
	const char* WSAEACCES_text = " WSAEACCES: An attempt was made to access a socket in a way forbidden by its access permissions.";
	const char* WSAEADDRINUSE_text = "WSAEADDRINUSE: Only one usage of each socket address (protocol/network address/port) is normally permitted.";
	const char* WSAEADDRNOTAVAIL_text = "WSAEADDRNOTAVAIL: The requested address is not valid in its context.";
	const char* WSAEFAULT_text = "WSAEFAULT: The system detected an invalid pointer address in attempting to use a pointer argument in a call.";
	const char* WSAEINPROGRESS_text = "WSAEINPROGRESS: A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function.";
	const char* WSAEINVAL_text = "WSAEINVAL: An invalid argument was supplied. This error is returned of the socket s is already bound to an address.";
	const char* WSAENOBUFS_text = "WSAENOBUFS: An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.";
	const char* WSAENOTSOCK_text = "WSAENOTSOCK: An operation was attempted on something that is not a socket. Did you try to bind a closed one?";

}
