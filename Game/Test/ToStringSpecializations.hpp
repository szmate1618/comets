#pragma once

#include "CppUnitTest.h"

#include "..\Networking\Packets.hpp"


namespace unittest = Microsoft::VisualStudio::CppUnitTestFramework;
template<> inline std::wstring unittest::ToString<uint16_t>(const uint16_t& t) { RETURN_WIDE_STRING(t); }
template<> inline std::wstring unittest::ToString<net::Header>(const net::Header& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }
template<> inline std::wstring unittest::ToString<net::ServerHeader>(const net::ServerHeader& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }
template<> inline std::wstring unittest::ToString<net::ServerObject>(const net::ServerObject& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }
template<> inline std::wstring unittest::ToString<net::ClientInputPayload>(const net::ClientInputPayload& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }
template<> inline std::wstring unittest::ToString<net::ServerStatePayload>(const net::ServerStatePayload& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }
template<> inline std::wstring unittest::ToString<net::ClientInputPacket>(const net::ClientInputPacket& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }
template<> inline std::wstring unittest::ToString<net::ServerStatePacket>(const net::ServerStatePacket& t) { RETURN_WIDE_STRING("N/A - ToString not implemented, sorry."); }


