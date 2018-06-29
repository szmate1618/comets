#include "StaticLinkedList.hpp"
#include "..\Entities\Entities.hpp"


namespace utils
{

	template<typename T>
	StaticLinkedList<T>::Iterator::Iterator(StaticLinkedList<T>& list, size_t index) : list{ list }, index{ index } {}

	template<typename T>
	StaticLinkedList<T>::Iterator::Iterator(StaticLinkedList<T>& list) : Iterator{ list, list.elements[list.instart].nextindex } {}

	template<typename T>
	typename StaticLinkedList<T>::Iterator& StaticLinkedList<T>::Iterator::operator++() { index = list.elements[index].nextindex; return *this; }

	template<typename T>
	//We break the usual C/C++ convention here, on purpose. We never intend to use a copy, so we don't create it.
	//TODO: Then maybe just delegate to the prefix increment operator.
	typename StaticLinkedList<T>::Iterator StaticLinkedList<T>::Iterator::operator++(int) { index = list.elements[index].nextindex; return *this; }

	template<typename T>
	bool StaticLinkedList<T>::Iterator::operator==(const Iterator& other) const { return index == other.index; }

	template<typename T>
	bool StaticLinkedList<T>::Iterator::operator!=(const Iterator& other) const { return index != other.index; } //TODO: Delegate to ==.

	template<typename T>
	T& StaticLinkedList<T>::Iterator::operator*() const { return list.elements[index].element; }

	template<typename T>
	StaticLinkedList<T>::StaticLinkedList() : StaticLinkedList<T>{ default_size } //Constructor delegation, C++11!
	{
	}

	template<typename T>
	StaticLinkedList<T>::StaticLinkedList(size_t size) : elements(size)
	{
		instart = 1; inend = elements.size() - 2;
		outstart = 0; outend = elements.size() - 1;

		//Chain up all the elements.
		for (size_t i = 0; i < elements.size(); i++)
		{
			elements[i].previndex = i - 1;
			elements[i].nextindex = i + 1;
		}

		//Init inlist.
		elements[instart].nextindex = inend;
		elements[inend].previndex = instart;
		elements[instart + 1].previndex = outstart;
		elements[inend - 1].nextindex = outend;

		//Init outlist.
		elements[outstart].nextindex = outstart + 2;
		elements[outend].previndex = outend - 2;
	}

	template<typename T>
	StaticLinkedList<T>::~StaticLinkedList()
	{
	}

	template<typename T>
	typename StaticLinkedList<T>::Iterator StaticLinkedList<T>::begin()
	{
		return { *this };
	}

	template<typename T>
	typename StaticLinkedList<T>::Iterator StaticLinkedList<T>::end()
	{
		return { *this, inend };
	}

	//No error checking at all. It's the caller's responsibility to insert at previouly unoccupied positions.
	template<typename T>
	size_t StaticLinkedList<T>::InsertAtFirstGap(const T& element)
	{
		size_t firstgap = elements[outstart].nextindex;

		if (firstgap == outend)
		{
			//Resize.
		}
		elements[firstgap].element = element;
		//Remove from outlist.
		elements[elements[firstgap].previndex].nextindex = elements[firstgap].nextindex;
		elements[elements[firstgap].nextindex].previndex = elements[firstgap].previndex;
		//Insert into inlist.
		//firstgap - 1 is in inlist, by definition.
		elements[firstgap].previndex = firstgap - 1;
		elements[firstgap].nextindex = elements[firstgap - 1].nextindex;
		elements[elements[firstgap - 1].nextindex].previndex = firstgap;
		elements[firstgap - 1].nextindex = firstgap;

		return firstgap;
	}

	//No error checking at all. Its the caller's responsibility to remove at previouly occupied positions.
	template<typename T>
	size_t StaticLinkedList<T>::RemoveAt(size_t index)
	{
		//Remove from inlist, that's the easy part.
		elements[elements[index].previndex].nextindex = elements[index].nextindex;
		elements[elements[index].nextindex].previndex = elements[index].previndex;

		//Insert into outlist. A bit harder.
		size_t borderindex = outstart;
		while (borderindex < index)
		{
			borderindex = elements[borderindex].nextindex;
		}
		elements[index].previndex = elements[borderindex].previndex;
		elements[index].nextindex = borderindex;
		elements[elements[borderindex].nextindex].nextindex = index;
		elements[borderindex].previndex = index;

		return index;
	}

	//TODO: Do some measurements to see when to use this.
	template<typename T>
	size_t StaticLinkedList<T>::Defragment()
	{
		return -1; //TODO: Implement this.
	}

	//Explicit instantiations.
	template class StaticLinkedList<entity::StaticEntity>;
	template class StaticLinkedList<entity::DynamicEntity>;

}
