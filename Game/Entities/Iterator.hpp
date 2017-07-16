#ifndef SZM_ITERATOR
#define SZM_ITERATOR

#include "Entities.hpp"
#include "..\Geometry\Geometry.hpp"


namespace entity
{

	template <typename T>
	class Iterator: public std::iterator
	                <
	                	std::forward_iterator_tag,
	                	T,
	                	long,
	                	const T*,
	                	T&
                    >
	{
    public:

		Iterator<T>(T& element): element(element) {}
		virtual ~Iterator<T>() {}
        virtual Iterator<T>& operator++() {++element; return *this;}
        virtual Iterator<T> operator++(int) {++element; return *this;} //We break the usual C/C++ convention here, on purpose. We never intend to use a copy, so we don't create it.
        virtual bool operator==(Iterator<T> other) const {return this == &other;}
        virtual bool operator!=(Iterator<T> other) const {return !(this == &other);}
        virtual T& operator*() const {return *T;}

	private:

		T* element;
    };

}

#endif
