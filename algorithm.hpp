#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

#include <functional>

namespace ft
{
template<typename Iter1, typename Iter2>
bool equal(Iter1 first1, Iter1 last1, Iter2 first2) {
	for (; first1 != last1; first1++, first2++)
		if (*first1 != *first2) return false;
	return true;
}
template<typename Iter1, typename Iter2, typename BinFunc>
bool equal(Iter1 first1, Iter1 last1, Iter2 first2, BinFunc pred) {
	for (; first1 != last1; first1++, first2++)
		if (!pred(*first1, *first2)) return false;
	return true;
}

template<typename T, typename U, typename Comp>
bool is_equal(const T& t, const U& u, Comp comp) { return !(comp(t, u) || comp(u, t)); }

template<typename Iter1, typename Iter2>
bool lexicographical_compare(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2) {
	for (; first1 != last1; first1++, first2++)
		if (first2 == last2 || *first2 < *first1) return false;
		else if (*first1 < *first2) return true;
	return first2 != last2;
}

template<typename Iter1, typename Iter2, typename Compare>
bool lexicographical_compare(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2, Compare cmp) {
	for (; first1 != last1; first1++, first2++)
		if (first2 == last2 || cmp(*first2, *first1)) return false;
		else if (cmp(*first1, *first2)) return true;
	return first2 != last2;
}
template<typename T>
struct less : std::binary_function<T, T, bool>
{
	bool operator()(const T& lhs, const T& rhs) const {
		return lhs < rhs;
	}
};

template<typename T>
struct greater : std::binary_function<T, T, bool>
{
	bool operator()(const T& lhs, const T& rhs) const {
		return lhs > rhs;
	}
};

template<typename InputIt, typename OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
	for (; first != last; ++first, ++d_first) *d_first = *first;
	return d_first;
}

template<typename InputIt, typename OutputIt>
OutputIt copy_backward(InputIt first, InputIt last, OutputIt d_last) {
	for (; first != last; ) *(--d_last) = *(--last);
	return d_last;
};

template<typename Pair>
struct Select1st : public std::unary_function<Pair, typename Pair::first_type>
{
	typename Pair::first_type& operator()(Pair& x) const { return x.first; }
	const typename Pair::first_type& operator()(const Pair& x) const { return x.first; }
};

template <typename T>
struct Identity : public std::unary_function<T, T>
{
	T& operator()(T& x) const { return x; }
	const T& operator()(const T& x) const { return x; }
};

template <typename T>
struct Identity <const T> : Identity<T> {};

}

#endif
