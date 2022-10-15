#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include "iter.hpp"
#include "iterator.hpp"
#include "helper.hpp"
#include "traits.hpp"
#include "algorithm.hpp"
#include <memory>
#include <algorithm>
#include <stdexcept>
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
	typedef typename allocator_type::template rebind<value_type>::other		type_allocator;

	typedef std::allocator_traits<type_allocator>				type_traits;
	typedef typename type_traits::pointer						pointer;
	typedef typename type_traits::const_pointer					const_pointer;
    typedef value_type&											reference;
	typedef const value_type&									const_reference;

	//	Size
	typedef typename std::ptrdiff_t								difference_type;
	typedef typename std::size_t								size_type;
	
	//	Iterator
	typedef random_access_iterator<value_type>					iterator;
	typedef random_access_iterator<const_value_type>			const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;	
	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

private:	//	Variable
	allocator_type	_alloc_;
	pointer			_begin_;
	pointer			_end_;
	pointer			_cap_;

private:	//	Function
	void	_init(size_type n) {
		if (n > max_size()) throw std::length_error("Too big");

		_begin_ = _alloc_.allocate(n);
		_end_ = _begin_;
		_cap_ = _begin_ + n;
	}

	void	_construct(size_type n) {
		for (; n; ++_end_, --n) _alloc_.construct(_end_);
	}
	void	_construct(size_type n, T v) {
		for (; n; ++_end_, --n) _alloc_.construct(_end_, v);
	}

	void	_destruct(size_type n) {
		for (; n && _end_; --_end_, --n) _alloc_.destroy(_end_);
	}
	void	_destruct(pointer until) {
		for (; _end_ != until && _end_; --_end_) _alloc_.destroy(_end_);
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
		size_type n = v.size();
		_begin_ = _alloc_.allocate(n);
		_end_ = _begin_;
		_cap_ = _begin_ + n;

		for (pointer p = v._begin_; p != v._end_; ++p, ++_end_) _alloc_.construct(_end_, *p);
	}

	template <typename InputIterator>
	vector(InputIterator first,
		InputIterator last,
		const allocator_type& alloc = allocator_type(),
		typename enable_if<!ft::is_integral<InputIterator>::value>::type* = ft::_nullptr)
		: _alloc_(alloc) {
			size_type n = ft::difference(first, last);
			_init(n);
			_construct(n);
			ft::copy(first, last, _begin_);
		}

	~vector(void) {
		if (_begin_ == ft::_nullptr) return ;
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
	bool empty(void) const {			return begin() == end(); }
	size_type max_size(void) const {return _alloc_.max_size(); }
	size_type size(void) const {	return _end_ - _begin_; }
	size_type capacity(void) const {return _cap_ - _begin_; }

	void reserve(size_type new_cap) {
		if (new_cap > max_size()) throw std::out_of_range("Too much allocation");
		if (new_cap <= capacity()) return ;
		if (new_cap < capacity() * 2) new_cap = capacity() << 1;

		pointer prebegin = _begin_;
		pointer preend = _end_;
		size_type precap = capacity();

		_begin_ = _alloc_.allocate(new_cap);
		_end_ = _begin_;
		_cap_ = _begin_ + new_cap;

		for (pointer cur = prebegin; cur != preend; ++cur)
			_construct(1, *cur);
		for (pointer cur = preend; cur != prebegin; )
			_alloc_.destroy(--cur);
		_alloc_.deallocate(prebegin, precap);
	}

	void resize(size_type n, value_type value = value_type()) {
		if (n > max_size()) throw std::out_of_range("Too much allocation");
		if (size() > n) _destruct(size() - n);
		else insert(_end_, n - size(), value);
	}

	void assign( size_type count, const T& value )
	{
		clear();
		if (capacity() < count)
			reserve(count);
		_construct(count, value);
	}

	template<typename Iter>
	void assign(Iter first, Iter last, typename enable_if<!ft::is_integral<Iter>::value>::type* = ft::_nullptr) {
    	size_type n = ft::difference(first, last);
		//size_type n = last - first;
		if (capacity() < n) reserve(n);
		ft::copy(first, last, _begin_);
		_end_ = _begin_ + n;
	}

	void clear(void) {
		_destruct(_begin_);
	}

	void swap(vector& v) {
		if (this == &v) return ;
		std::swap(_begin_, v._begin_);
		std::swap(_end_, v._end_);
		std::swap(_cap_, v._cap_);
		std::swap(_alloc_, v._alloc_);
	}

	iterator insert(iterator pos, const value_type& value) {
		size_type len = ft::difference(begin(), pos);
		insert(pos, 1, value);
		return begin() + len;
	}

	void insert(iterator pos, size_type n , const value_type& value) {
		size_type len = pos - begin();
		if (capacity() < size() + n) reserve(size() + n);

		pointer ptr = _begin_ + len;
		_construct(n);
		ft::copy_backward(ptr, _end_ - n, _end_);
		for (size_type i = 0; i < n; ++i) ptr[i] = value;
	}

	template<typename Iter>
	void insert(iterator pos, Iter first, Iter last, typename enable_if<!ft::is_integral<Iter>::value>::type* = ft::_nullptr) {
		size_type iter_diff = ft::difference(first, last);
		size_type len = ft::difference(begin(), pos);

		if (capacity() < size() + iter_diff) reserve(size() + iter_diff);

		pointer ptr = _begin_ + len;
		_construct(iter_diff);
		ft::copy_backward(ptr, _end_ - iter_diff, _end_);
		ft::copy(first, last, begin() + len);
	}

	iterator erase(iterator pos) {
		size_type len = pos - begin();
		pointer ptr = _begin_ + len;

		ft::copy(ptr + 1, _end_, ptr);
		_destruct(1);
		return iterator(ptr);
	}

	iterator erase(iterator first, iterator last) {
		size_type iter_diff = ft::difference(first, last);
		ft::copy(last, end(), first);
		_destruct(iter_diff);
		return first;
	}

	allocator_type get_allocator(void) const {
		return _alloc_;
	}

	//	Iterator
	iterator begin(void) {	return iterator(_begin_); }
	const_iterator begin(void) const { return iterator(_begin_); }
	iterator end(void) { return iterator(_end_); }
	const_iterator end(void) const { return iterator(_end_); }
	reverse_iterator rbegin(void) { return reverse_iterator(end()); }
	const_reverse_iterator rbegin(void) const { return reverse_iterator(end()); }
	reverse_iterator rend(void) { return reverse_iterator(begin()); }
	const_reverse_iterator rend(void) const { return reverse_iterator(begin()); }

	//	Elem Access
	reference front(void) { return *_begin_; }
	const_reference front(void) const { return *_begin_; }
	reference back(void) { return *(_end_ - 1); }
	const_reference back(void) const { return  *(_end_ - 1); }
	value_type* data(void) throw() {
		return reinterpret_cast<value_type*>(_begin_);
	}
	const value_type* data(void) const throw() {
		return reinterpret_cast<const value_type*>(_begin_);
	}

	reference operator[](size_type n) { return _begin_[n]; }
	const_reference operator[](size_type n) const { return _begin_[n]; }
	reference at(size_type n) {
		if (size() < n) throw std::out_of_range("index out of range");
		return _begin_[n];
	}
	const_reference  at(size_type n) const {
		if (size() < n) throw std::out_of_range("index out of range");
		return _begin_[n];
	}
	void push_back(const T& value) {
		if (_end_ == _cap_)
			reserve(empty() ? 1 : capacity() * 2);
		//if (_cap_ == _end_)
		//	reserve(size() + 1);
		_construct(1, value);
	}
	void pop_back(void) {
		_destruct(1);
	}
};

template<typename T, typename _Alloc>
bool operator==(const ft::vector<T, _Alloc>& lhs, const ft::vector<T, _Alloc>& rhs) {
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, typename _Alloc>
bool operator!=(const ft::vector<T, _Alloc>& lhs, const ft::vector<T, _Alloc>& rhs) {
	return !(lhs == rhs);
}

template<typename T, typename _Alloc>
bool operator<(const ft::vector<T, _Alloc>& lhs, const ft::vector<T, _Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, typename _Alloc>
bool operator<=(const ft::vector<T, _Alloc>& lhs, const ft::vector<T, _Alloc>& rhs) {
	return lhs == rhs || lhs < rhs;
}

template<typename T, typename _Alloc>
bool operator>(const ft::vector<T, _Alloc>& lhs, const ft::vector<T, _Alloc>& rhs) {
	return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template<typename T, typename _Alloc>
bool operator>=(const ft::vector<T, _Alloc>& lhs, const ft::vector<T, _Alloc>& rhs) {
	return lhs == rhs || lhs > rhs;
}

template<typename T, typename _Alloc>
void swap(vector<T, _Alloc>& lhs, vector<T, _Alloc>& rhs) {
	lhs.swap(rhs);
}


}	// FT
#endif