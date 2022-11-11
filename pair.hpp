#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{

template <typename T, typename U>
struct pair
{
	typedef T first_type;
	typedef U second_type;

	first_type first;
	second_type second;

	pair() : first(), second() {}

	pair(const first_type & value1, const second_type & value2)
			: first(value1), second(value2) {};

	pair(const pair & rhs) : first(rhs.first), second(rhs.second) {};

	template<typename Other1, typename Other2>
	pair(const pair<Other1, Other2> & rhs)
			: first(rhs.first), second(rhs.second) {};

	~pair() {};
};

template<typename T, typename U>
pair<T, U> make_pair(T first, U second) { return pair<T, U>(first, second); }

template<typename T, typename U>
bool operator==(const pair<T, U>& lhs, const pair<T, U>& rhs)
{ return lhs.first == rhs.first && lhs.second == rhs.second; }

template<typename T, typename U>
bool operator!=(const pair<T, U>& lhs, const pair<T, U>& rhs)
{ return !(lhs == rhs); }

template<typename T, typename U>
bool operator<(const pair<T, U>& lhs, const pair<T, U>& rhs)
{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

template<typename T, typename U>
bool operator>(const pair<T, U>& lhs, const pair<T, U>& rhs)
{ return rhs < lhs; }

template<typename T, typename U>
bool operator<=(const pair<T, U>& lhs, const pair<T, U>& rhs)
{ return !(rhs < lhs); }

template<typename T, typename U>
bool operator>=(const pair<T, U>& lhs, const pair<T, U>& rhs)
{ return !(lhs < rhs); }
}   //  ft

#endif  //PAIR_H
