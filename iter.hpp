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

//	Random Iterator
template <typename T>
class random_access_iterator : public std::iterator<random_access_iterator_tag, T> {
public:
	typedef T*	iterator_type;
	typedef typename iterator_traits<iterator_type>::value_type			value_type;
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
	typedef typename iterator_traits<iterator_type>::pointer			pointer;
	typedef typename iterator_traits<iterator_type>::reference			reference;

	random_access_iterator(void) : cur(NULL) {};
	random_access_iterator(T* ptr) : cur(ptr) {};
	template<typename U>
	random_access_iterator(const random_access_iterator<U>& ref) : cur(ref.base()) {};
	~random_access_iterator(void) {};

	template<typename U>
	random_access_iterator& operator=(random_access_iterator<U>& rhs) {
		if (this == &rhs)
			return *this;
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
	random_access_iterator& operator++(int) {
		random_access_iterator tmp = *this;
		++cur;
		return tmp;
	}
	random_access_iterator& operator--(void) {
		--cur;
		return *this;
	}
	random_access_iterator& operator--(int) {
		random_access_iterator tmp = *this;
		cur--;
		return tmp;
	}

	random_access_iterator operator+(difference_type n) {
		return random_access_iterator(cur + n);
	}
	random_access_iterator operator-(difference_type n) {
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

private:
	pointer	cur;
};

//	Reverse Iterator
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
	typedef Iterator											iterator_type;
	typedef typename iterator_traits<Iterator>::difference_type	difference_type;
	typedef typename iterator_traits<Iterator>::pointer			pointer;
	typedef typename iterator_traits<Iterator>::reference		reference;

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
		return *--tmp;
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

	//	Random Access relational
	template <typename T, typename U>
	bool operator==(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <typename T, typename U>
	bool operator!=(const random_access_iterator<T>& lhs, const random_access_iterator<U>& rhs) {
		return !(lhs == rhs);
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

	//	Reverse relational
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
			return rhs - lhs;
		}
	template <typename T, typename U>
	typename reverse_iterator<T>::difference_type operator-(const reverse_iterator<T>& lhs,
		const reverse_iterator<U>& rhs) {
			return rhs.base() - lhs.base();
		}
}	//	FT
#endif //   ITERATOR_HPP
