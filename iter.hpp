#ifndef ITER_HPP
# define ITER_HPP

#include "helper.hpp"
#include "traits.hpp"
#include "iterator.hpp"
#include <iterator>

namespace ft
{
//	Random Iterator
template <typename T>
class random_access_iterator
: public std::iterator<random_access_iterator_tag, T>
{
public:
	typedef T*															iterator_type;
	typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
	typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
	typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
	typedef typename ft::iterator_traits<iterator_type>::reference			reference;

	random_access_iterator(pointer ptr = ft::_nullptr) : cur(ptr) {};
	template<typename U>
	random_access_iterator(const random_access_iterator<U>& ref) : cur(ref.base()) {};
	~random_access_iterator(void) {};

	template<typename U>
	random_access_iterator& operator=(random_access_iterator<U>& rhs) {
		cur = rhs.base();
		return *this;
	}

	iterator_type base(void) const { return cur; }
	pointer operator->(void) const { return cur; }
	reference operator*(void) const { return *cur; }
	reference operator[](difference_type n) const { return cur[n]; }

	random_access_iterator& operator++(void) {
		++cur;
		return *this;
	}
	random_access_iterator operator++(int) {
		random_access_iterator tmp(*this);
		++cur;
		return tmp;
	}
	random_access_iterator& operator--(void) {
		--cur;
		return *this;
	}
	random_access_iterator operator--(int) {
		random_access_iterator tmp(*this);
		--cur;
		return tmp;
	}

	random_access_iterator operator+(difference_type n) const {
		return random_access_iterator(cur + n);
	}
	random_access_iterator operator-(difference_type n) const {
		return random_access_iterator(cur - n);
	}
	random_access_iterator& operator+=(difference_type n) {
		cur += n;
		return *this;
	}
	random_access_iterator& operator-=(difference_type n) {
		cur -= n;
		return *this;
	}

protected:
	pointer	cur;
};

	/*
	 * Random Access relational
	 */
	template <typename T, typename U>
	bool operator==(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <typename T, typename U>
	bool operator!=(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <typename T, typename U>
	bool operator<(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <typename T, typename U>
	bool operator>(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <typename T, typename U>
	bool operator<=(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template <typename T, typename U>
	bool operator>=(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template <typename T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n,
										const random_access_iterator<T>& rhs) {
		return random_access_iterator<T>(rhs.base() + n);
	}
	template <typename T, typename U>
	typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T>& lhs,
																  const random_access_iterator<U>& rhs) {
		return lhs.base() - rhs.base();
	}

/*
 * 	Reverse Iterator
 */
template <typename Iterator>
class reverse_iterator
{
public:
	typedef Iterator														iterator_type;
	typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
	typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
	typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
	typedef typename ft::iterator_traits<iterator_type>::reference			reference;
	typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;

public:
	reverse_iterator(void) : cur(iterator_type()){};
	explicit reverse_iterator(iterator_type iter) : cur(iter) {};
	template<typename U>
	reverse_iterator(const reverse_iterator<U>& rhs) : cur(rhs.base()) {};
	~reverse_iterator(void) {};

	iterator_type base(void) const { return cur; };

	template<typename U>
	reverse_iterator& operator=(const reverse_iterator<U>& rhs) {
		cur = rhs.base();
		return *this;
	}

	reverse_iterator operator+(difference_type n) const {
		return reverse_iterator(cur - n);
	}
	reverse_iterator operator-(difference_type n) const {
		return reverse_iterator(cur + n);
	}
	reverse_iterator& operator++(void) {
		--cur;
		return *this;
	}
	reverse_iterator operator++(int) {
		reverse_iterator tmp(*this);
		--cur;
		return tmp;
	}
	reverse_iterator& operator--(void) {
		++cur;
		return *this;
	}
	reverse_iterator operator--(int) {
		reverse_iterator tmp(*this);
		++cur;
		return tmp;
	}
	reverse_iterator& operator+=(difference_type n) {
		cur -= n;
		return *this;
	}
	reverse_iterator& operator-=(difference_type n) {
		cur += n;
		return *this;
	}

	//	Access
	reference operator*(void) const {
		//iterator_type	tmp(cur);
		return *(cur - 1);
	}
	pointer operator->(void) const { return &operator*(); }
	reference operator[](difference_type n) const { return *(*this + n); };
	
	private:
	iterator_type	cur;
};
/*
template<typename T, typename U>
class tree_iterator : public iterator<bidirectional_iterator_tag, T>
{
public:
	typedef T			value_type;
	typedef value_type*	pointer;
	typedef	value_type&	reference;
	typedef U*			iterator_type;

	typedef typename iterator_traits<iterator_type>::value_type			node_type;
	typedef typename iterator_traits<iterator_type>::pointer			node_pointer;
	typedef typename iterator_traits<iterator_type>::reference			node_reference;
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
	typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;

	tree_iterator(void) : cur(_nullptr) {};
	tree_iterator(node_pointer cur) : cur(cur) {};
	tree_iterator(const tree_iterator& ref) : cur(ref.base()) {};
	~tree_iterator(void) {};

	tree_iterator& operator=(const tree_iterator& rhs) {
		if (this == &rhs) return *this;
		this.cur = rhs.base();
		return *this;
	}

	node_pointer	base(void) const { return cur; }
	pointer			operator->(void) const { return &cur->value; }
	reference		operator*(void) const { return cur->value; }

	tree_iterator&	operator++(void) {
		cur = cur.
	}

protected:
	node_pointer		cur;
};
*/

	//	Reverse relational
	template <typename T, typename U>
	bool operator==(const ft::reverse_iterator<T>& lhs, const ft::reverse_iterator<U>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <typename T, typename U>
	bool operator!=(const ft::reverse_iterator<T>& lhs, const ft::reverse_iterator<U>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <typename T, typename U>
	bool operator<(const ft::reverse_iterator<T>& lhs, const ft::reverse_iterator<U>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <typename T, typename U>
	bool operator>(const ft::reverse_iterator<T>& lhs, const ft::reverse_iterator<U>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <typename T, typename U>
	bool operator<=(const ft::reverse_iterator<T>& lhs, const ft::reverse_iterator<U>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template <typename T, typename U>
	bool operator>=(const ft::reverse_iterator<T>& lhs, const ft::reverse_iterator<U>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template <typename Iter>
	reverse_iterator<Iter> operator+(typename ft::reverse_iterator<Iter>::difference_type n,
		const ft::reverse_iterator<Iter>& iter) {
			return ft::reverse_iterator<Iter>(iter.base() - n);
		}
	template <typename T, typename U>
	typename reverse_iterator<T>::difference_type operator-(const reverse_iterator<T>& lhs,
		const reverse_iterator<U>& rhs) {
			return rhs.base() - lhs.base();
		}
}	//	FT
#endif //   ITERATOR_HPP
