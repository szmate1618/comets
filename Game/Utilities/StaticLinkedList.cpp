#include "StaticLinkedList.hpp"

namespace utils
{

	template <typename T>
	StaticLinkedList<T>::StaticLinkedList()
	{
		elements.reserve(default_size);
		elements[0].nextindex = elements.capacity - 1;
		elements[elements.capacity - 1].previndex = 0;
	}

	template <typename T>
	StaticLinkedList<T>::~StaticLinkedList()
	{

	}

	//No error checking at all. Its the callers responsibility to insert at previouly unoccupied positions.
	template <typename T>
	__int32 StaticLinkedList<T>::InsertAt(T element, __int32 index, __int32 previndex, __int32 nextindex)
	{
		elements[index].element = element;
		elements[index].previndex = previndex;
		elements[index].nextindex = nextindex;

		elements[elements[index].previndex].nextindex = index;
		elements[elements[index].nextindex].previndex = index;
	}

	//No error checking at all. Its the callers responsibility to remove at previouly occupied positions.
	template <typename T>
	__int32 StaticLinkedList<T>::RemoveAt(__int32 index)
	{
		elements[elements[index].previndex].nextindex = elements[index].nextindex;
		elements[elements[index].nextindex].previndex = elements[index].previndex;
		return index;
	}

}
