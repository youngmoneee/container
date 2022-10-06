#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft
{

/*
 *	Iter Category
 */
struct  input_iterator_tag {};
struct  output_iterator_tag {};
struct  forward_iterator_tag : public input_iterator_tag {};
struct  bidirectional_iterator_tag : public forward_iterator_tag {};
struct  random_access_iterator_tag : public bidirectional_iterator_tag {};

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

/*
 *	Iter Traits
 */
template<typename iterator>
struct	iterator_traits
{
	typedef	typename	iterator::iterator_category	iterator_category;
	typedef	typename	iterator::value_type		value_type;
	typedef	typename	iterator::difference_type	difference_type;
	typedef	typename	iterator::pointer			pointer;
	typedef	typename	iterator::reference			reference;
};

template<typename T>
struct	iterator_traits< T* >
{
	typedef	random_access_iterator_tag				iterator_category;
	typedef	T										value_type;
	typedef	ptrdiff_t	    						difference_type;
	typedef	T*										pointer;
	typedef	T&										reference;
};

template <typename T>
struct	iterator_traits< const T* >
{
	typedef	ft::random_access_iterator_tag			iterator_category;
	typedef	T										value_type;
	typedef	ptrdiff_t	    						difference_type;
	typedef	const T*								pointer;
	typedef	const T&								reference;
};

template < class InputIterator >
typename ft::iterator_traits< InputIterator >::difference_type difference(
    InputIterator first, InputIterator last) {
  typedef
      typename ft::iterator_traits<InputIterator>::difference_type size_type;
  size_type n = 0;
  for (; first != last; ++first) ++n;
  return n;
}

}   //FT

#endif