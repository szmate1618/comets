#pragma once

#include <cstdint>
#include <climits>


//We don't actually want to enforce most these, it's just a check, because it's important to know these sizes.
static_assert(sizeof(char) == 1, "sizeof(char) != 1, non standard compliant architecture.");
static_assert(CHAR_BIT == 8, "CHAR_BIT != 8");
static_assert(sizeof(int) >= 4, "sizeof(int) < 4");
static_assert(sizeof(long) >= 4, "sizeof(long) < 4");
static_assert(sizeof(float) == 4, "sizeof(float) != 4, non standard compliant floating-point implementation.");
static_assert(sizeof(double) == 8, "sizeof(double) != 8, non standard compliant floating-point implementation.");
static_assert(sizeof(uint8_t) == 1, "sizeof(uint8_t) != 1");
static_assert(sizeof(uint16_t) == 2, "sizeof(uint16_t) != 2");
static_assert(sizeof(uint32_t) == 4, "sizeof(uint32_t) != 4");
static_assert(sizeof(uint64_t) == 8, "sizeof(uint64_t) != 8");
