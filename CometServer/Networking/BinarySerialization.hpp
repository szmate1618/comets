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
#pragma comment( lib, "wsock32.lib" )
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
#include <netinet/in.h>
#endif

#include <cstdint>


namespace net
{

	//TODO: Why not just use function overloading?
	template<typename T> inline T hton(T t) { static_assert(false, "Template hton is not defined for this type of argument."); }
	template<> inline float hton<float>(float t) { return t; } //TODO: Handle floating point endianness.
	template<> inline double hton<double>(double t) { return t; } //TODO: Handle floating point endianness.
	template<> inline uint8_t hton<uint8_t>(uint8_t t) { return t; }
	template<> inline uint16_t hton<uint16_t>(uint16_t t) { return htons(t); }
	template<> inline uint32_t hton<uint32_t>(uint32_t t) { return htonl(t); }

	struct Write
	{
		template<typename T>
		static inline size_t Process(uint8_t* packet_data, T t)
		{
			T nt = hton(t);
			std::memcpy(packet_data, &nt, sizeof(T)); //This is indeed the recommended way, see here: http://en.cppreference.com/w/cpp/language/reinterpret_cast
			return sizeof(T);
		}
	};

	template<typename T> inline T ntoh(T& t) { static_assert(false, "Template ntoh is not defined for this type of argument."); }
	template<> inline float ntoh<float>(float& t) { return t; }
	template<> inline double ntoh<double>(double& t) { return t; }
	template<> inline uint8_t ntoh<uint8_t>(uint8_t& t) { return t; }
	template<> inline uint16_t ntoh<uint16_t>(uint16_t& t) { return ntohs(t); }
	template<> inline uint32_t ntoh<uint32_t>(uint32_t& t) { return ntohl(t); }

	struct Read
	{
		template<typename T>
		static inline size_t Process(uint8_t* packet_data, T& t)
		{
			T ht;
			std::memcpy(&ht, packet_data, sizeof(T)); //This is indeed the recommended way, see here: http://en.cppreference.com/w/cpp/language/reinterpret_cast
			t = ntoh(ht);
			return sizeof(T);
		}
	};

}
