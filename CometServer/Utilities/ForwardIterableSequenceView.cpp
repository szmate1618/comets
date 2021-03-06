#include "ForwardIterableSequenceView.hpp"
#include "..\Entities\Entities.hpp"

#include <list>


namespace utils
{

	template<class T>
	ForwardIterableSequenceView<T>::Iterator::Iterator(ForwardIterableSequenceView<T>& view, typename T::iterator current_position, size_t current_container)
		: view{ view }, current_position{ current_position }, current_container{ current_container } {}

	template<class T>
	ForwardIterableSequenceView<T>::Iterator::Iterator(ForwardIterableSequenceView<T>& view)
		: Iterator{ view, view.sequence.front().get().begin(), 0 } {}

	template<class T>
	typename ForwardIterableSequenceView<T>::Iterator& ForwardIterableSequenceView<T>::Iterator::operator++()
	{
		++current_position;
		if (current_position == view.sequence[current_container].get().end() && current_container < view.sequence.size() - 1)
		{
			++current_container;
			current_position = view.sequence[current_container].get().begin();
		}
		return *this;
	}

	template<class T>
	//We break the usual C/C++ convention here, on purpose. We never intend to use a copy, so we don't create it. //TODO: Don't do this.
	typename ForwardIterableSequenceView<T>::Iterator ForwardIterableSequenceView<T>::Iterator::operator++(int)
	{
		return ++*this;
	}

	template<class T>
	bool ForwardIterableSequenceView<T>::Iterator::operator==(const Iterator& that) const
	{
		return current_container == that.current_container && current_position == that.current_position;
	}

	template<class T>
	bool ForwardIterableSequenceView<T>::Iterator::operator!=(const Iterator& that) const
	{
		return !(*this == that);
	}

	template<class T>
	typename T::value_type& ForwardIterableSequenceView<T>::Iterator::operator*() const
	{
		return *current_position;
	}

	template<class T>
	ForwardIterableSequenceView<T>::ForwardIterableSequenceView(T& container) : sequence{ container }
	{
	}

	template<class T>
	ForwardIterableSequenceView<T>::~ForwardIterableSequenceView()
	{
	}

	template<class T>
	void ForwardIterableSequenceView<T>::Append(T& container)
	{
		sequence.push_back(container);
	}

	template<class T>
	typename ForwardIterableSequenceView<T>::Iterator ForwardIterableSequenceView<T>::begin()
	{
		return { *this };
	}

	template<class T>
	typename ForwardIterableSequenceView<T>::Iterator ForwardIterableSequenceView<T>::end()
	{
		return { *this, sequence.back().get().end() , sequence.size() - 1 };
	}

	//Explicit instantiations.
	template class ForwardIterableSequenceView<std::vector<entity::StaticEntity*>>;
	//The following are just for easier and more thorough testing.
	template class ForwardIterableSequenceView<std::vector<int>>;
	template class ForwardIterableSequenceView<std::list<int>>;

}
