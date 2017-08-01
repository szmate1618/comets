#pragma once
//TODO: Figure out what #pragma once is.
#ifndef SZM_STATIC_LINKED_LIST
#define SZM_STATIC_LINKED_LIST

#include <vector>


namespace utils
{
	
	//Kind of a linked list, but with one, statically allocated contiguous block of memory.
	//First 2 and last 2 elements are used as guards.
	//This means we cannot insert at an arbitrary position, but fortunately we don't need to.
	template <typename T>
	class StaticLinkedList
	{

		template <typename T>
		struct ListElement { T element; __int32 previndex; __int32 nextindex; }; //We don't want to use too much memory here, so we require a fixed 32 bit int.

	public:

		StaticLinkedList();
		StaticLinkedList(__int32);
		~StaticLinkedList();
		__int32 InsertAtFirstGap(T);
		__int32 RemoveAt(__int32);
		__int32 Defragment();

		//Could use a static assert here to ensure its big enough to contain the guards.
		//Or just dynamic assert in the constructor.
		static const __int32 default_size = 1'000'000; //Yay for decimal separator apostrophe! C++11!
		std::vector<ListElement<T>> elements;

	private:

		__int32 instart, inend;
		__int32 outstart, outend;

	};

}

#endif
