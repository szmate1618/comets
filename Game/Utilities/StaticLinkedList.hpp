#pragma once
//TODO: Figure out what #pragma once is.
#ifndef SZM_STATIC_LINKED_LIST
#define SZM_STATIC_LINKED_LIST


namespace utils
{
	
	//Kind of a linked list, but with one, statically allocated contigous block of memory.
	//First and last elements are used as guards.
	//This means we cannot insert at arbitrary position, but fortunately we don't need to.
	template <typename T>
	class StaticLinkedList
	{

		struct ListElement { T element; indextype previndex; __int32 nextindex; }; //We don't want to use too much memory here, so we require a fixed 32 bit int.

	public:

		StaticLinkedList();
		~StaticLinkedList();
		__int32 InsertAt(T, __int32, __int32, __int32);
		__int32 RemoveAt(__int32);

		const __int32 default_size = 1, 000, 000; //Yay for decimal separator comma! C++11!
		ListElement<T> elements[default_size];

	};

}

#endif
