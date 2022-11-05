#ifndef UTILITIES_HPP
# define UTILITIES_HPP

#include "iter.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include "traits.hpp"
#include "pair.hpp"

namespace ft {
	const class nullptr_t {
	private:
	void operator&(void) const;

	public:
	template <typename T>
	operator T*(void) const { return 0; }

	template <typename T, typename U>
	operator T U::*(void) const { return 0; }
	} nil = {};
}
# endif