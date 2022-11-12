#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include <iterator>

#include "traits.hpp"

namespace ft
{

/*
 *	Iter Category
 */
	struct  input_iterator_tag {};
	struct  output_iterator_tag {};
	struct  forward_iterator_tag : public input_iterator_tag {};
	struct  bidirectional_iterator_tag : public forward_iterator_tag {};
	struct  random_access_iterator_tag : public std::bidirectional_iterator_tag {};

/*
 *	Iterator
 */
	template<typename Category, typename T, typename Distance = ptrdiff_t,
			typename Pointer = T*, typename Reference = T&>
	struct  iterator
	{
		typedef	Category	iterator_category;
		typedef T			value_type;
		typedef	Distance	difference_type;
		typedef	Pointer		pointer;
		typedef	Reference	reference;
	};
}   //FT

#endif