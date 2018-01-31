#include "StaticLinkedList.hpp"


namespace utils
{

	template<typename T>
	StaticLinkedList<T>::StaticLinkedList(): StaticLinkedList<T>{default_size} //Constructor delegation, C++11!
	{
	}

	template<typename T>
	StaticLinkedList<T>::StaticLinkedList(__int32 size): elements(size)
	{
		instart = 1; inend = elements.size() - 2;
		outstart = 0; outend = elements.size() - 1;

		//Chain up all the elements.
		for (__int32 i = 0; i < elements.size(); i++)
		{
			elements[i].previndex = i - 1;
			elements[i].nextindex = i + 1;
		}

		//Init inlist.
		elements[instart].nextindex = inend;
		elements[inend].previndex = instart;

		//Init outlist.
		elements[oustart].nextindex = outstart + 2;
		elements[outend].previndex = outend - 2;
	}

	template<typename T>
	StaticLinkedList<T>::~StaticLinkedList()
	{

	}

	//No error checking at all. Its the caller's responsibility to insert at previouly unoccupied positions.
	template<typename T>
	__int32 StaticLinkedList<T>::InsertAtFirstGap(T element)
	{
		__int32 firstgap = elements[outstart].nextindex;

		if (firstgap == outend)
		{
			//Resize.
		}
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
	__int32 StaticLinkedList<T>::RemoveAt(__int32 index)
	{
		//Remove from inlist, that's the easy part.
		elements[elements[index].previndex].nextindex = elements[index].nextindex;
		elements[elements[index].nextindex].previndex = elements[index].previndex;

		//Insert into outlist. A bit harder.
		__int32 borderindex = outstart;
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
	__int32 StaticLinkedList<T>::Defragment()
	{
		//TODO: Implement this.
	}

}
