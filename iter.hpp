#ifndef ITERATOR_HPP
#define ITERATOR_HPP

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
	typedef	T*			pointer;
	typedef	T&			reference;
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
	typedef	ptrdiff_t								difference_type;
	typedef	T*										pointer;
	typedef	T&										reference;
};

template <typename T>
struct	iterator_traits< const T* >
{
	typedef	random_access_iterator_tag				iterator_category;
	typedef	T										value_type;
	typedef	ptrdiff_t								difference_type;
	typedef	const T*								pointer;
	typedef	const T&								reference;
};

template <typename Iterator>
class reverse_iterator :
public iterator<typename iterator_traits<Iterator>::iterator_category,
				typename iterator_traits<Iterator>::value_type,
				typename iterator_traits<Iterator>::difference_type,
				typename iterator_traits<Iterator>::pointer,
				typename iterator_traits<Iterator>::reference>
{
protected:
	Iterator	current;
public:
	typedef Iterator										iterator_type;
	typedef typename iterator_traits<It>::difference_type	difference_type;
	typedef typename iterator_traits<It>::pointer			pointer;
	typedef typename iterator_traits<It>::reference			reference;

public:
	reverse_iterator(){};
	explicit reverse_iterator(Iterator iter) : current(iter) {};
	template<typename U>
	reverse_iterator(const reverse_iterator<U>& rhs) : current(rhs.base()) {};
	virtual ~reverse_iterator() {};

	Iterator base() const { return current; };

	template<typename U>
	reverse_iterator& operator=(const reverse_iterator<U>& rhs) {
		current = rhs.base();
		return *this;
	}
	reference operator*() const {
		iterator_type	tmp = current;
		return *--ret;
	}
	pointer operator->() const {
		return &(operator*());
	}
	reverse_iterator operator+(difference_type n) const {
		return reverse_iterator(current - n);
	}
	reverse_iterator operator-(difference_type n) const {
		return reverse_iterator(current + n);
	}
	reverse_iterator& operator++() {
		--current;
		return *this;
	}
	reverse_iterator operator++(int) {
		reverse_iterator tmp = *this;
		--current;
		return *this;
	}
	reverse_iterator& operator--() {
		++current;
		return *this;
	}
	reverse_iterator operator--(int) {
		reverse_iterator tmp = *this;
		++current;
		return *this;
	}
	reverse_iterator& operator+=(difference_type n) {
		current -= n;
		return *this;
	}
	reverse_iterator& operator-=(difference_type n) {
		current += n;
		return *this;
	}
	reference operator[](difference_type n) const { return current[-n - 1]; };
	
};
	template <typename T, typename U>
	bool operator==(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <typename T, typename U>
	bool operator!=(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) {
		return !(lhs == rhs);
	}
	template <typename T, typename U>
	bool operator<(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <typename T, typename U>
	bool operator>(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <typename T, typename U>
	bool operator<=(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template <typename T, typename U>
	bool operator>=(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template <typename Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type lhs,
		const reverse_iterator<Iter>& rhs) {
			return rhs + n;
		}
	template <typename T, typename U>
	typename reverse_iterator<T>::difference_type operator-(const reverse_iterator<T>& lhs,
		const reverse_iterator<U>& rhs) {
			return rhs.base() - lhs.base();
		}
}	//	FT
#endif //   ITERATOR_HPP