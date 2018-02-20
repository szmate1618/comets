#pragma once

#include <initializer_list>
#include <vector>
#include <functional>


namespace utils
{

	template<typename T>
	class ForwardIterableSequenceView
	{

	public:

		class Iterator
		{
		public:

			Iterator(ForwardIterableSequenceView<T>&);
			Iterator& operator++();
			Iterator operator++(int);
			bool operator==(const Iterator) const;
			bool operator!=(const Iterator) const;
			T& operator*() const;

		private:

			ForwardIterableSequenceView<T>& view;
			size_t current_container;
			T::iterator current_position;

		};

		ForwardIterableSequenceView(std::initializer_list<T>);
		~ForwardIterableSequenceView();
		Iterator begin();
		Iterator end();

	private:

		std::vector<reference_wrapper<T>> sequence;

	};

}
