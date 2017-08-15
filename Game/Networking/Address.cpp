#include "Address.hpp"


namespace net {

	Address::Address
	(
		unsigned int a, //TODO: look into IPv6.
		unsigned int b,
		unsigned int c,
		unsigned int d,
		unsigned short port
	) : address{ (a << 24) | (b << 16) | (c << 8) | d }, port{ port } {} //TODO: Consistent spacing before and after : operators.

	Address::Address(unsigned int address, unsigned short port) : address{ address }, port{ port } {}

	unsigned int Address::GetAddress() const { return address; }

	unsigned char Address::GetA() const { return unsigned char((address & (255 << 24)) >> 24); }

	unsigned char Address::GetB() const { return unsigned char((address & (255 << 16)) >> 16); }

	unsigned char Address::GetC() const { return unsigned char((address & (255 << 8)) >> 8); }

	unsigned char Address::GetD() const { return unsigned char(address & 255); }

	unsigned short Address::GetPort() const { return port; }

}
