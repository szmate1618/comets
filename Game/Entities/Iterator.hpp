#pragma once

#include "Entities.hpp"
#include "..\Geometry\Geometry.hpp"


namespace entity
{

	template<typename T>
	class Iterator: public std::iterator //TODO: Actually we don't need this STL boilerplate. This iterator is not currently used with any STL algorithm.
	                <
	                	std::forward_iterator_tag, //TODO: This should be ptrdiff_t, also there is a deprecation warning.
	                	T,
	                	long,
	                	const T*,
	                	T&
                    >
	{
    public:

		//TODO: disable the default constructor here.
		Iterator<T>(const T& element): element(&element) {}
		virtual ~Iterator<T>() {}
        virtual Iterator<T>& operator++() {++element; return *this;}
        virtual Iterator<T> operator++(int) {++element; return *this;} //We break the usual C/C++ convention here, on purpose. We never intend to use a copy, so we don't create it.
		virtual bool operator==(const Iterator<T> other) const {return element == other.element;}
        virtual bool operator!=(const Iterator<T> other) const {return element != other.element;}
		virtual T& operator*() const {return *element;}

	private:

		T* element;

    };

}
