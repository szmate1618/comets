#pragma once


namespace net
{

	class Address
	{
	public:

		Address();
		Address
		(
			unsigned int,
			unsigned int,
			unsigned int,
			unsigned int,
			unsigned short
		);
		Address(unsigned int, unsigned short);
		unsigned int GetAddress() const;
		unsigned char GetA() const;
		unsigned char GetB() const;
		unsigned char GetC() const;
		unsigned char GetD() const;
		unsigned short GetPort() const;

	private:

		unsigned int address;
		unsigned short port;

	};
}
