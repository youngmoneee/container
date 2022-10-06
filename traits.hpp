#ifndef TRAITS_HPP
# define TRAITS_HPP

#include "iter.hpp"

namespace ft
{

/*
 *	remove const, volatile,
 */

template<typename T> struct	remove_const { typedef T	type; };
template<typename T> struct	remove_const<const T> { typedef T	type; };

template<typename T> struct	remove_volatile { typedef T	type; };
template<typename T> struct	remove_volatile<volatile T> { typedef T		type; };

template<typename T> struct	remove_cv {
	typedef typename remove_const<typename remove_volatile<T>::type>::type		type;
};

/*
 *	integral_base
 */
template <bool B, typename T>
struct	integral_base
{
	typedef	T					type;
	const static bool value		= B;
};

/*
 *	is_integral_type
 *	true
 *	char, char16_t, char32_t, wchar_t
 *	short, int, long, long long
 */
template <typename T>
struct	is_integral_type : public integral_base<false, T> {};

template <>	struct	is_integral_type<bool> : public integral_base<true, bool> {};
template <>	struct	is_integral_type<signed char> : public integral_base<true, signed char> {};
template <>	struct	is_integral_type<unsigned char> : public integral_base<true, unsigned char> {};
template <>	struct	is_integral_type<wchar_t> : public integral_base<true, wchar_t> {};
template <>	struct	is_integral_type<short> : public integral_base<true, short> {};
template <>	struct	is_integral_type<unsigned short> : public integral_base<true, unsigned short> {};
template <>	struct	is_integral_type<int> : public integral_base<true, int> {};
template <>	struct	is_integral_type<unsigned int> : public integral_base<true, unsigned int> {};
template <>	struct	is_integral_type<long> : public integral_base<true, long> {};
template <>	struct	is_integral_type<unsigned long> : public integral_base<true, unsigned long> {};
template <>	struct	is_integral_type<long long> : public integral_base<true, long long> {};
template <>	struct	is_integral_type<unsigned long long> : public integral_base<true, unsigned long long> {};
template <>	struct	is_integral_type<__int128_t> : public integral_base<true, __int128_t> {};
template <>	struct	is_integral_type<__uint128_t> : public integral_base<true, __uint128_t> {};

/*
 *	is_integral
 */

template<typename T>
struct is_integral : public is_integral_type<typename remove_cv<T>::type> {};

/*
 *	enable_if
 */
template <bool B, typename T = void>
struct	enable_if {};

template <typename T>
struct	enable_if<true, T> { typedef T	type; };



}		//	FT
#endif  //  TRAITS_HPP
