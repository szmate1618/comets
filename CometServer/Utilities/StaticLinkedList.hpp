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

		struct ListElement { T element; size_t previndex; size_t nextindex; }; //We don't want to use too much memory here, so we require a fixed 32 bit int.

	public:

		class Iterator
		{
		public:

			Iterator(StaticLinkedList<T>&, size_t);
			Iterator(StaticLinkedList<T>&);
			Iterator& operator++();
			Iterator operator++(int);
			bool operator==(const Iterator&) const;
			bool operator!=(const Iterator&) const;
			T& operator*() const;

		private:

			StaticLinkedList<T>& list;
			size_t index;

		};

		StaticLinkedList();
		StaticLinkedList(size_t);
		~StaticLinkedList();
		Iterator begin();
		Iterator end();
		size_t InsertAtFirstGap(const T&); //TODO: Add methods for compile-time polymorphism with STL LinkedList.
		size_t RemoveAt(size_t);
		size_t Defragment();

		//Could use a static assert here to ensure its big enough to contain the guards.
		//Or just dynamic assert in the constructor.
		#ifdef NDEBUG //This is to speed up the launches of debug builds.
		static constexpr size_t default_size = 1'000'000; //Yay for decimal separator apostrophe! C++11!
		#else
		static constexpr size_t default_size = 1'000;
		#endif
		std::vector<ListElement> elements;

	private:

		//TODO: These could be constexprs, too.
		size_t instart, inend;
		size_t outstart, outend;

	};

}
