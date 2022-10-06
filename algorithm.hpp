#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

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
	bool operator()(const T& lhs, const T& rhs) {
		return lhs < rhs;
	}
};

template<typename T>
struct greater : std::binary_function<T, T, bool>
{
	bool operator()(const T& lhs, const T& rhs) {
		return lhs > rhs;
	}
};

template<typename T>
void	swap(T& lhs, T& rhs) {
	T	C = lhs;
	lhs = rhs;
	rhs = C;
}

}

#endif
