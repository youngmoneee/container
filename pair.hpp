#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{

template <typename T, typename U>
struct pair
{
    typedef T	type1;
	typedef U	type2;

	type1		first;
	type2		second;

	pair() {}
	pair(const type1& value1, const type2& value2)
	: first(value1), second(value2) {};
	pair(const pair& rhs) : first(rhs.first), second(rhs.second) {};

	template<typename Other1, typename Other2>
	pair(const pair<Other1, Other2>& rhs)
	: first(rhs.first), second(rhs.second) {};
	~pair() {};
	
	pair& operator=(const pair& rhs) {
		if (this == &rhs)
			return *this;
		first = rhs.first;
		second = rhs.second;
		return *this;
	};

	bool operator==(const pair<T, U>& rhs) {
		return this->first == rhs.first && this->second == rhs.second;
	}
	bool operator!=(const pair<T, U>& rhs) {
		return !(operator==(rhs));
	}
	bool operator<(const pair<T, U>& rhs) {
		if (this->first == rhs.first)
			return this->second < rhs.second;
		return this->first < rhs.first;
	}
	bool operator>(const pair<T, U>& rhs) {
		if (this->first == rhs.first)
			return this->second > rhs.second;
		return this->first > rhs.first;
	}
	bool operator<=(const pair<T, U>& rhs) {
		return !operator>(rhs);
	}
	bool operator>=(const pair<T, U>& rhs) {
		return !operator<(rhs);
	}
};

template<typename T, typename U>
pair<T, U> make_pair(T first, U second) { return pair<T, U>(first, second); }

	/*
	bool operator==(const pair<T, U>& lhs, const pair<T, U>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.first;
	}
	bool operator!=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
		return !(operator==(lhs, rhs));
	}
	bool operator<(const pair<T, U>& lhs, const pair<T, U>& rhs) {
		if (lhs.first == rhs.first)
			return lhs.second < rhs.second;
		return lhs.first < rhs.first;
	}
	bool operator>(const pair<T, U>& lhs, const pair<T, U>& rhs) {
		return operator<(rhs < lhs);
	}
	bool operator<=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
		return !operator>(lhs, rhs);
	}
	bool operator>=(const pair<T, U>& lhs, const pair<T, U>& rhs) {
		return !operator<(rhs, lhs);
	}
	*/

}   //  ft

#endif  //PAIR_H
