#pragma once

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

			Iterator(ForwardIterableSequenceView<T>&, typename T::iterator&);
			Iterator(ForwardIterableSequenceView<T>&);
			Iterator& operator++();
			Iterator operator++(int);
			bool operator==(const Iterator&) const;
			bool operator!=(const Iterator&) const;
			T& operator*() const;

		private:

			ForwardIterableSequenceView<T>& view;
			size_t current_container;
			typename T::iterator current_position;

		};

		ForwardIterableSequenceView() = delete;
		ForwardIterableSequenceView(const T&);
		~ForwardIterableSequenceView();
		void Append(const T&);
		Iterator begin() const;
		Iterator end() const;

	private:

		std::vector<std::reference_wrapper<T>> sequence;

	};

}
