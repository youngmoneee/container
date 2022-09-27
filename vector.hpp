#include <iostream>
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iter.hpp"
#include "nullptr.hpp"
#include "traits.hpp"
#include <memory>
#include <stdexcept>
#include "algorithm.hpp"
#include <limits>

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
	typedef random_access_iterator<value_type>				iterator;
	//typedef random_access_iterator<const value_type>		const_iterator;
	typedef reverse_iterator<iterator>						reverse_iterator;	
	//typedef reverse_iterator<const_iterator>				const_reverse_iterator;

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
		if (n > max_size())
			throw std::length_error("Too big");

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
			_init(n);
			_construct(n, type);
		};


	vector(const vector& v) : _alloc_(v._alloc_) {
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

	//	Size
	bool empty(void) {			return _begin_ == _end_; }
	size_type max_size() const {return std::numeric_limits<difference_type>::max() / sizeof(value_type);}
	size_type size() const {	return std::distance(_begin_, _end_); }
	size_type capacity(void) const {return static_cast<size_type>(_cap_ - _begin_); }

	void reserve(size_type new_cap) {
		if (new_cap > max_size())
			throw std::length_error("Too big");
		if (new_cap <= size() || new_cap <= capacity())
			return ;
		if (new_cap < capacity() * 2)
			new_cap = capacity() * 2;
		size_type pre_size = size();
		size_type pre_cap = capacity();
		pointer pbegin = _alloc_.allocate(new_cap);
		std::uninitialized_copy(_begin_, _end_, pbegin);
		_destruct(_begin_);
		_alloc_.deallocate(_begin_, pre_cap);
		_begin_ = pbegin;
		_end_ = _begin_ + pre_size;
		_cap_ = _begin_ + pre_cap;
	}

	template<typename iter>
	void assign(iter first, iter last, typename enable_if<!is_integral<iter>::value>::value = NULL) {
		size_type n = std::distance(first, last);
		if (capacity() < n) reserve(n);
		std::copy(first, last, _begin_);
		_end_ = _begin_ + n;
	}

	void clear(void) {
		_destruct(_begin_);
	}

	void swap(vector& v) {
		std::swap(_begin_, v._begin_);
		std::swap(_end_, v._end_);
		std::swap(_cap_, v._cap_);
		std::swap(_alloc_, v._alloc_);
	}

	iterator insert(iterator pos, const value_type& value) {
		difference_type diff = pos - begin();
		if (_cap_ < size() + 1) reserve(size() + 1);
		pointer ptr = _begin_ + diff;
		_construct(1);
		std::copy_backward(ptr, _end_ - 1, _end_);
		*ptr = value;
		return iterator(ptr);
	}

	void insert(iterator pos, size_type n , const value_type& value) {
		difference_type diff = pos - begin();
		if (capacity() < size() + n) reserve(size() + n);
		pointer ptr = _begin_ + diff;
		_construct(n);
		std::copy_backward(ptr, _end_ - n, _end_);
		while (n--) *(ptr + n) = value;
	}

	template<typename iter>
	void insert(iterator pos, iter first, iter last, typename enable_if<!is_integral<iter>::value>::value = NULL) {
		difference_type n = std::distance(first, last);
		difference_type diff = pos - begin();
		if (capacity() < size() + n) reserve(size() + n);
		pointer ptr = _begin_ + diff;
		_construct(n);
		std::copy_backward(ptr, _end_ - n, _end_);
		for (; first != last; first++, ptr++) *ptr = *first;
	}

	iterator erase(iterator pos) {
		difference_type diff = pos - begin();
		pointer ptr = _begin_ + diff;
		std::copy(ptr + 1, _end_, ptr);	// ptr + 1부터 end까지를 ptr에 입력
		_destruct(1);
		return iterator(ptr);
	}

	iterator erase(iterator first, iterator last) {
		difference_type n = std::distance(first, last);
		std::copy(last, end(), first);
		_destruct(n);
		return first;
	}

	allocator_type get_allocator(void) const {
		return _alloc_;
	}

	//	Iterator
	iterator begin(void) {	return iterator(_begin_); }
	const iterator begin(void) const { return iterator(_begin_); }
	iterator end(void) { return iterator(_end_); }
	const iterator end(void) const { return iterator(_end_); }
	reverse_iterator rbegin(void) { return reverse_iterator(end()); }
	const reverse_iterator rbegin(void) const { return reverse_iterator(end()); }
	reverse_iterator rend(void) { return reverse_iterator(begin()); }
	const reverse_iterator rend(void) const { return reverse_iterator(begin()); }

	//	Elem Access
	reference front(void) { return *_begin_; }
	const reference front(void) const { return *_begin_; }
	reference back(void) { return *(_end_ - 1); }
	const reference back(void) const { return  *(_end_ - 1); }
	value_type* data(void) throw() {
		return reinterpret_cast<value_type*>(_begin_);
	}
	const value_type* data(void) const throw() {
		return reinterpret_cast<const value_type*>(_begin_);
	}

	reference operator[](size_type n) { return _begin_[n]; }
	const reference operator[](size_type n) const { return _begin_[n]; }
	reference at(size_type n) {
		if (size() < n) throw std::out_of_range("index out of range");
		return _begin_[n];
	}
	const reference  at(size_type n) const {
		if (size() < n) throw std::out_of_range("index out of range");
		return _begin_[n];
	}
};

template<typename T, typename _Alloc>
bool operator==(const vector<T, _Alloc>& lhs, const vector<T, _Alloc>& rhs) {
	return lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, typename _Alloc>
bool operator!=(const vector<T, _Alloc>& lhs, const vector<T, _Alloc>& rhs) {
	return !(lhs == rhs);
}

template<typename T, typename _Alloc>
bool operator<(const vector<T, _Alloc>& lhs, const vector<T, _Alloc>& rhs) {
	return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, typename _Alloc>
bool operator<=(const vector<T, _Alloc>& lhs, const vector<T, _Alloc>& rhs) {
	return lhs == rhs || lhs < rhs;
}

template<typename T, typename _Alloc>
bool operator>(const vector<T, _Alloc>& lhs, const vector<T, _Alloc>& rhs) {
	return !(lhs <= rhs);
}

template<typename T, typename _Alloc>
bool operator>=(const vector<T, _Alloc>& lhs, const vector<T, _Alloc>& rhs) {
	return !(lhs < rhs);
}

template<typename T, typename _Alloc>
void swap(vector<T, _Alloc>& lhs, vector<T, _Alloc>& rhs) {
	return lhs.swap(rhs);
}

}
#endif