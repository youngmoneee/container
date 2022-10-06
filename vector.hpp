#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "iter.hpp"
#include "iterator.hpp"
#include "helper.hpp"
#include "traits.hpp"
#include <memory>
#include <stdexcept>
#include <limits>
//#include <iterator>
#include "algorithm.hpp"
#include <typeinfo>
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
		size_type n = v.size();	// size 구현
		_init(v.capacity());	// capacity 구현
		_construct(n);
		std::copy(v._begin_, v._end_, _begin_);
	}

	template <typename InputIterator>
	vector(InputIterator first,
		InputIterator last,
		const allocator_type& alloc = allocator_type(),
		typename enable_if<!ft::is_integral<InputIterator>::value>::type* = ft::_nullptr)
		: _alloc_(alloc) {
			difference_type n = ft::difference(random_access_iterator<InputIterator>(first), random_access_iterator<InputIterator>(last));
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
	bool empty(void) const {			return begin() == end(); }
	size_type max_size(void) const {return _alloc_.max_size(); }
	size_type size(void) const {	return _end_ - _begin_; }
	size_type capacity(void) const {return _cap_ - _begin_; }

	void reserve(size_type new_cap) {
		if (new_cap > max_size()) throw std::out_of_range("Too much allocation");
		if (new_cap <= capacity()) return ;
		if (new_cap < capacity() * 2) new_cap <<= 2;

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
		if (n > max_size()) throw std::length_error("Too much allocation");
		if (size() > n) {
			_destruct(size() - n);
      		return;
    	}
    	//this->insert(end(), n - size(), value);
		_construct(n - size(), value);
	}

	void assign( size_type count, const T& value )
	{
		clear();
		if (capacity() < count)
			reserve(count);
		_construct(count, value);
	}

	template<typename Iter>
	void assign(Iter first, Iter last, typename ft::enable_if<!ft::is_integral<Iter>::value>::type* = NULL) {
    	size_type n = ft::difference(first, last);
		clear();
		if (capacity() < n) reserve(n);
		for ( ; &*first != &*last; ++first) push_back(*first);
	}

	void clear(void) {
		_destruct(_begin_);
	}

	void swap(vector& v) {
		ft::swap(_begin_, v._begin_);
		ft::swap(_end_, v._end_);
		ft::swap(_cap_, v._cap_);
		ft::swap(_alloc_, v._alloc_);
	}

	iterator insert(iterator pos, const value_type& value) {
		size_type idx = &*pos - _begin_;

		insert(pos, 1, value);		
		return _begin_ + idx;
	}

	void insert(iterator pos, size_type n , const value_type& value) {
		size_type idx = &*pos - _begin_;
		
		if (capacity() - size() >= n) {
			for (size_type i = 0; i < size() - idx; ++i) {
				_alloc_.construct(_end_ + n - i, *(_end_ - i));
				_alloc_.destroy(_end_ - i);
			}
			_end_ = _begin_ + size() + n;
			for (size_type i = 0; i < n; ++i)
				_alloc_.construct(_begin_ + idx + i, value);
			return ;
		}

		pointer pbegin = _begin_;
		pointer pend = _end_;
		size_type psz = size();
		size_type pcap = capacity();

		_begin_ = _alloc_.allocate(psz + n);
		_end_ = _begin_ + psz + n;
		_cap_ = _end_;

		for (size_type i = 0; i < idx; ++i) {
			_alloc_.construct(_begin_ + i, *(pbegin + i));
			_alloc_.destroy(pbegin + i);
		}

		for (size_type i = 0; i < psz - idx; ++i) {
			_alloc_.construct(_end_ - i - 1, *(pend - i - 1));
			_alloc_.destroy(pend - i - 1);
		}

		for (size_type i = 0; i < n; ++i)
			_alloc_.construct(_begin_ + idx + i, value);

		_alloc_.deallocate(pbegin, pcap);
	}

	template<typename Iter>
	void insert(iterator pos, Iter first, Iter last, typename enable_if<!is_integral<Iter>::value>::type* = NULL) {
		size_type idx = &*pos - _begin_;
		size_type n = &*last - &*first;

		if (capacity() >= size() + n) {
			for (size_type i = 0; i < size() - idx; ++i) {
				_alloc_.construct(_end_ + n - i, *(_end_ - i));
				_alloc_.destroy(_end_ - i);
			}
			_end_ = _begin_ + size() + n;
			for (size_type i = 0; i < n; ++i, ++first)
				_alloc_.construct(_begin_ + idx + i, *first);
			return ;
		}

		pointer pbegin = _begin_;
		pointer pend = _end_;
		size_type psz = size();
		size_type pcap = capacity();

		_begin_ = _alloc_.allocate(psz + n);
		_end_ = _begin_ + psz + n;
		_cap_ = _end_;

		for (size_type i = 0; i < idx; ++i) {
			_alloc_.construct(_begin_ + i, *(pbegin + i));
			_alloc_.destroy(pbegin + i);
		}

		for (size_type i = 0; i < psz - idx; ++i) {
			_alloc_.construct(_end_ - i - 1, *(pend - i - 1));
			_alloc_.destroy(pend - i - 1);
		}

		for (size_type i = 0; i < n; ++i, ++first)
			_alloc_.construct(_begin_ + idx + i, *first);
		_alloc_.deallocate(pbegin, pcap);
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
		if (size() + 1 > capacity())
			reserve(size() + 1);
		_construct(1, value);
		//*(_end_ - 1) = value;
	}
	void pop_back(void) {
		_destruct(1);
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

}	// FT
#endif