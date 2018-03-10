#pragma once

#include "Entities.hpp"
#include "..\Geometry\Geometry.hpp"


namespace entity
{

	//TODO: Find out if this is used somewhere, delete if not.
	template<typename T>
	class Iterator
	{
    public:

		//TODO: Disable the default constructor here.
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
