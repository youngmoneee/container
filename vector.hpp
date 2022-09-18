#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iter/iter.hpp"
#include "nullptr.hpp"
#include <memory>

namespace ft {

template <typename T, typename _Alloc = std::allocator<T> >
class vector
{
public:
    typedef T													value_type;
    typedef const T												const_value_type;
    typedef _Alloc												allocator_type;
    typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;

	typedef random_access_iterator_tag<value_type>				iterator;
	typedef random_access_iterator_tag<const_value_type>		const_iterator;
	typedef reverse_iterator<value_type>						reverse_iterator;	
	typedef reverse_iterator<const_value_type>					const_reverse_iterator;

	typedef iterator_traits<iterator>::difference_type		difference_type;
	typedef allocator_type::size_type							size_type;
	
private:
	allocator_type	_alloc;
	pointer			_begin;
	pointer			_end;
	pointer			_end_cap;

public:
	explicit vector(const allocator_type& alloc = allocator_type())
		: _alloc(alloc),
		_begin(_nullptr),
		_end(_nullptr),
		_end_cap(_nullptr) {};
	explicit vector(size_type n, const value_type& type = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc) {
			_begin = _alloc.allocate(n);
			_end = _begin;
			_end_cap = _start + n;
			while (n--) alloc.construct(_end++, val);
		}

	template <typename InputIterator>
	vector(InputIterator first, InputIterator second, const allocator_type& alloc = allocator_type(),
		typename enable_if<!is_integral<InputIterator>::value>::type* = _nullptr)
		: _alloc(alloc) {
		
		}
};

    
}
#endif