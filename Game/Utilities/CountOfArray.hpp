#pragma once


namespace util
{

	template<typename T, size_t N>
	size_t countof(T (&array)[N]) { return N; }

}
