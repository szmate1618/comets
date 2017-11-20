#include "AutoExtendingVector.hpp"

namespace utils
{


	template<typename T>
	AutoExtendingVector<T>::AutoExtendingVector() : AutoExtendingVector<T>{ default_size } //Constructor delegation, C++11!
	{
	}

	template<typename T>
	AutoExtendingVector<T>::AutoExtendingVector(size_t size) : elements(size)
	{
	}

	template<typename T>
	AutoExtendingVector<T>::~AutoExtendingVector()
	{

	}

	template<typename T>
	T& AutoExtendingVector<T>::operator[](size_t index)
	{
		if (index >= elements.size())
		{
			elements.resize(index * growth_factor);
		}
		return elements[index];
	}
}
