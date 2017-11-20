#pragma once

#include <vector>


namespace utils
{

	//A thin wrapper around a normal vector.
	//Automatically resizes itself on overindexing to accomodate the indexed element.
	template<typename T>
	class AutoExtendingVector
	{
	public:

		AutoExtendingVector();
		AutoExtendingVector(size_t);
		~AutoExtendingVector();
		T& operator[](size_t);

		static constexpr size_t default_size = 100;
		static constexpr double growth_factor = 1.5;

	private:

		std::vector<T> elements;

	};

}
