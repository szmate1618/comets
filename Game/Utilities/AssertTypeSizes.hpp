#pragma once

#include <cstdint>


//We don't actually want to enforce most these, it's just a check, because it's important to know these sizes.
static_assert(sizeof(char) == 1, "Non standard-compliant architecture. Size of char should be 1 unit.");
#pragma warning( suppress : 4309 )
static_assert(static_cast<unsigned char>(256) != 256, "Size of char is more than 8 bits. Strange.");
static_assert(sizeof(int) >= 4, "Size of int is less than 4 units.");
static_assert(sizeof(long) >= 4, "Size of long is less than 4 units.");
static_assert(sizeof(uint8_t) == 1, "Size of uint8_t isn't 1 unit.");
static_assert(sizeof(uint16_t) == 2, "Size of uint16_t isn't 2 units.");
static_assert(sizeof(uint32_t) == 4, "Size of uint32_t isn't 4 units.");
static_assert(sizeof(uint64_t) == 8, "Size of uint64_t isn't 8 units.");
