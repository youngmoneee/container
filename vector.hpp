#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iter.hpp"
#include "nullptr.hpp"
#include "traits.hpp"
#include <memory>
#include <stdexcept>
#include <algorithm>

namespace ft {

template <typename T, typename _Alloc = std::allocator<T> >
class vector
{
public:
	//	Type
    typedef T													value_type;
    typedef const T												const_value_type;
	
	//	Allocator
    typedef _Alloc												allocator_type;
    typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;

	//	Iterator
	typedef random_access_iterator_tag<value_type>				iterator;
	typedef random_access_iterator_tag<const_value_type>		const_iterator;
	typedef reverse_iterator<iterator>							reverse_iterator;	
	typedef reverse_iterator<const_iterator>					const_reverse_iterator;

	//	Size
	typedef typename iterator_traits<iterator>::difference_type	difference_type;
	typedef typename allocator_type::size_type					size_type;
	
private:	//	Variable
	allocator_type	_alloc_;
	pointer			_begin_;
	pointer			_end_;
	pointer			_cap_;

private:	//	Function
	void	_init(size_type n) {
		_begin_ = _alloc_.allocate(n);
		_end_ = _begin_;
		_cap_ = _begin_ + n;
	}

	void	_construct(size_type n) {
		while (n--) _alloc_.construct(_end_++);
	}
	void	_construct(size_type n, T v) {
		while (n--) _alloc_.construct(_end_++, v);
	}

	void	_destruct(size_type n) {
		while (n-- && _end_) _alloc_.destroy(--_end_);
	}
	void	_destruct(pointer until) {
		while (_end_ != until && _end_) _alloc_.destroy(--_end_);
	}



public:		//	Cannonical
	explicit vector(const allocator_type& alloc = allocator_type())
		: _alloc_(alloc),
		_begin_(_nullptr),
		_end_(_nullptr),
		_cap_(_nullptr) {};

	explicit vector(size_type n,
				const value_type& type = value_type(),
				const allocator_type& alloc = allocator_type())
		: _alloc_(alloc) {
			_init(n)
			_construct(n, type);
		};


	vector(const vector& v) : _alloc_(v.alloc) {
		size_type n = v.size();	// size 구현
		_init(v.capacity());	// capacity 구현
		_construct(n);
		std::copy(v._begin_, v._end_, _begin_);
	}

	template <typename InputIterator>
	vector(InputIterator first,
		InputIterator last,
		const allocator_type& alloc = allocator_type(),
		typename enable_if<!is_integral<InputIterator>::value>::type* = _nullptr)
		: _alloc_(alloc) {
			size_type n = std::distance(first, last);
			_init(n);
			_construct(n);
			std::copy(first, last, _begin_);
		}

	~vector(void) {
		if (_begin_ == _nullptr) return ;
		size_type pre_cap = capacity();
		_destruct(_begin_);
		_alloc_.deallocate(_begin_, pre_cap);
	}

	vector& operator=(const vector& v) {
		if (this == &v)
			return *this;
		assign(v._begin_, v._end_);
		return *this;
	}
};

    
}
#endif