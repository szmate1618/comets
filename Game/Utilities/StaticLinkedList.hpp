#pragma once

#include <vector>


namespace utils
{
	
	//Kind of a linked list, but with one, statically allocated contiguous block of memory.
	//This means we cannot insert at an arbitrary position, but fortunately we don't need to.
	//First 2 and last 2 elements are used as guards.
	template<typename T>
	class StaticLinkedList
	{

		template<typename T>
		struct ListElement { T element; __int32 previndex; __int32 nextindex; }; //We don't want to use too much memory here, so we require a fixed 32 bit int. //TODO: Use int32_t.

	public:

		StaticLinkedList();
		StaticLinkedList(__int32);
		~StaticLinkedList();
		__int32 InsertAtFirstGap(T); //TODO: Add methods for compile-time polymorphism with STL LinkedList.
		__int32 RemoveAt(__int32);
		__int32 Defragment();

		//Could use a static assert here to ensure its big enough to contain the guards.
		//Or just dynamic assert in the constructor.
		static constexpr __int32 default_size = 1'000'000; //Yay for decimal separator apostrophe! C++11!
		std::vector<ListElement<T>> elements;

	private:

		//TODO: These could be constexprs, too.
		__int32 instart, inend;
		__int32 outstart, outend;

	};

}
