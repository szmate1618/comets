#pragma once

#include <vector>


namespace utils
{

	//A thin wrapper around a normal vector.
	//Automatically resizes itself on overindexing to accomodate the indexed element.
	//TODO: Add tests.
	template<typename T>
	class AutoExtendingVector
	{
	public:

		AutoExtendingVector() : AutoExtendingVector<T>{ default_size } {}
		AutoExtendingVector(size_t size) : elements(size) {}
		~AutoExtendingVector() {}
		T& operator[](size_t index)
		{
			if (index >= elements.size())
			{
				elements.resize(index * growth_factor);
			}
			return elements[index];
		}

		static constexpr size_t default_size = 100;
		static constexpr double growth_factor = 1.5;

	private:

		std::vector<T> elements;

	};

}
