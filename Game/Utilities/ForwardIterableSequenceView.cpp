#include "ForwardIterableSequenceView.hpp"


namespace utils
{

	template<typename T>
	ForwardIterableSequenceView<T>::Iterator::Iterator(ForwardIterableSequenceView<T>& view, typename T::iterator& current_position)
		: view{ view }, current_position{ current_position } {}

	template<typename T>
	ForwardIterableSequenceView<T>::Iterator::Iterator(ForwardIterableSequenceView<T>& view)
		: view{ view }, current_position{ view.sequence[0].begin() } {}

	template<typename T>
	typename ForwardIterableSequenceView<T>::Iterator& ForwardIterableSequenceView<T>::Iterator::operator++()
	{
		++current_position;
		if (current_position == view.sequence[current_container].end())
		{
			++current_container;
			current_position = view.sequence[current_container].begin()
		}
		return *this;
	}

	template<typename T>
	//We break the usual C/C++ convention here, on purpose. We never intend to use a copy, so we don't create it.
	typename ForwardIterableSequenceView<T>::Iterator ForwardIterableSequenceView<T>::Iterator::operator++(int)
	{
		return ++*this;
	}

	template<typename T>
	bool ForwardIterableSequenceView<T>::Iterator::operator==(const Iterator& that) const
	{
		return current_position == that.current_position;
	}

	template<typename T>
	bool ForwardIterableSequenceView<T>::Iterator::operator!=(const Iterator& that) const
	{
		return !(*this == that);
	}

	template<typename T>
	T& ForwardIterableSequenceView<T>::Iterator::operator*() const
	{
		return *current_position;
	}

	template<typename T>
	ForwardIterableSequenceView<T>::ForwardIterableSequenceView(const T& container) : sequence{ container }
	{
	}

	template<typename T>
	ForwardIterableSequenceView<T>::~ForwardIterableSequenceView()
	{
	}

	template<typename T>
	void Append(const T&)
	{

	}

	template<typename T>
	typename ForwardIterableSequenceView<T>::Iterator ForwardIterableSequenceView<T>::begin() const
	{
		return Iterator(*this);
	}

	template<typename T>
	typename ForwardIterableSequenceView<T>::Iterator ForwardIterableSequenceView<T>::end() const
	{
		return Iterator(*this, sequence[sequence.count() - 1].end());
	}

}
