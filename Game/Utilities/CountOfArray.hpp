#pragma once


namespace util
{

	//TODO: Or maybe just use std::array everywhere?
	template<typename T, size_t N>
	constexpr size_t countof(const T (&array)[N]) { return N; } //TODO: Add test.

}
