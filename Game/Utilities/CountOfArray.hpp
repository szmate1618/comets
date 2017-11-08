#pragma once


namespace util
{

	template<typename T, size_t N>
	constexpr size_t countof(const T (&array)[N]) { return N; } //TODO: Add test.

}
