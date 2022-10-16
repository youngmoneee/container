#ifndef TRAITS_HPP
# define TRAITS_HPP

#include "iter.hpp"

namespace ft
{

/*
 *	remove const, volatile,
 */

template<typename T> struct	remove_cv { typedef T type; };
template<typename T> struct	remove_cv<const T> { typedef T type; };
template<typename T> struct	remove_cv<volatile T> { typedef T type; };
template<typename T> struct	remove_cv<const volatile T> { typedef T type; };

/*
 * 	Const Bool Type
 */

template <typename T, T v>
struct integral_constant {
	static const T value = v;
	typedef T value_type;
	typedef integral_constant<T, v> type;
	operator value_type() { return value; }
	value_type operator()() const ;
};

typedef integral_constant<bool,true> true_type;
typedef integral_constant<bool,false> false_type;

/*
 *	is_integral_type
 *	true
 *	char, char16_t, char32_t, wchar_t
 *	short, int, long, long long
 */
template <typename T>
struct	is_integral_base : public false_type {};

template <>	struct	is_integral_base<bool> : public true_type {};
template <>	struct	is_integral_base<char> : public true_type {};
template <>	struct	is_integral_base<signed char> : public true_type {};
template <>	struct	is_integral_base<unsigned char> : public true_type {};
template <>	struct	is_integral_base<char16_t> : public true_type {};
template <>	struct	is_integral_base<char32_t> : public true_type {};
template <>	struct	is_integral_base<wchar_t> : public true_type {};
template <>	struct	is_integral_base<short> : public true_type {};
template <>	struct	is_integral_base<unsigned short> : public true_type {};
template <>	struct	is_integral_base<int> : public true_type {};
template <>	struct	is_integral_base<unsigned int> : public true_type {};
template <>	struct	is_integral_base<long> : public true_type {};
template <>	struct	is_integral_base<unsigned long> : public true_type {};
template <>	struct	is_integral_base<long long> : public true_type {};
template <>	struct	is_integral_base<unsigned long long> : public true_type {};
template <>	struct	is_integral_base<__int128_t> : public true_type {};
template <>	struct	is_integral_base<__uint128_t> : public true_type {};


/*
 *	is_integral
 */

template<typename T>
struct is_integral : public is_integral_base<typename remove_cv<T>::type> {};

/*
 *	enable_if
 */
template <bool, typename = void>
struct	enable_if {};

template <typename T>
struct	enable_if<true, T> { typedef T	type; };

}		//	FT
#endif  //  TRAITS_HPP
