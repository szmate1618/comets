#pragma once

#include <vector>
#include <functional>


namespace utils
{

	template<class T>
	class ForwardIterableSequenceView
	{

	public:

		class Iterator
		{
		public:

			Iterator(ForwardIterableSequenceView<T>&, typename T::iterator&);
			Iterator(ForwardIterableSequenceView<T>&);
			Iterator& operator++();
			Iterator operator++(int);
			bool operator==(const Iterator&) const;
			bool operator!=(const Iterator&) const;
			typename T::value_type& operator*() const;

		private:

			ForwardIterableSequenceView<T>& view;
			size_t current_container;
			typename T::iterator& current_position;

		};

		ForwardIterableSequenceView() = delete;
		ForwardIterableSequenceView(T&);
		~ForwardIterableSequenceView();
		void Append(T&);
		Iterator begin();
		Iterator end();

	private:

		std::vector<std::reference_wrapper<T>> sequence;

	};

}
