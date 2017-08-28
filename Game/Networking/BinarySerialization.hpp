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

	template<typename T> inline T hton(T t) { static_assert(false, "Template hton is not defined for this type of argument."); }
	template<> inline float hton<float>(float t) { return t; }
	template<> inline double hton<double>(double t) { return t; }
	template<> inline uint8_t hton<uint8_t>(uint8_t t) { return t; }
	template<> inline uint16_t hton<uint16_t>(uint16_t t) { return htons(t); }
	template<> inline uint32_t hton<uint32_t>(uint32_t t) { return htonl(t); }

	template<typename T>
	struct Write
	{
		inline size_t Process(uint8_t* packet_data, T t)
		{
			*reinterpret_cast<T*>(packet_data) = hton(t);
			return sizeof(T);
		}
	};

	template<typename T> inline T ntoh(T& t) { static_assert(false, "Template ntoh is not defined for this type of argument."); }
	template<> inline float ntoh<float>(float& t) { return t; }
	template<> inline double ntoh<double>(double& t) { return t; }
	template<> inline uint8_t ntoh<uint8_t>(uint8_t& t) { return t; }
	template<> inline uint16_t ntoh<uint16_t>(uint16_t& t) { return ntohs(t); }
	template<> inline uint32_t ntoh<uint32_t>(uint32_t& t) { return ntohl(t); }

	template<typename T>
	struct Read
	{
		inline size_t Process(uint8_t* packet_data, T t)
		{
			t = ntoh(*reinterpret_cast<T*>(packet_data));
			return sizeof(T);
		}
	};

}
