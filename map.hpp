#ifndef MAP_HPP
# define MAP_HPP

#include "algorithm.hpp"
#include <memory>
#include "pair.hpp"
#include "iter.hpp"

namespace ft
{
template<typename Key, typename T, typename Compare = less<Key>, typename _Alloc = std::allocator<pair<const Key, T> > >
class map
{
private:
public:
//  Type
    typedef Key                                         key_type;
    typedef T                                           mapped_type;
    typedef pair<const key_type, mapped_type>           value_type;
    typedef Compare                                     key_compare;
    typedef _Alloc                                      allocator_type;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
	typedef typename allocator_type::size_type			size_type;
	typedef typename allocator_type::difference_type	difference_type;

	typedef bidirectional_iterator<value_type>			iterator;
	typedef bidirectional_iterator<const value_type>	const_iterator;
	typedef reverse_iterator<iterator>					reverse_iterator;
	typedef reverse_iterator<const_iterator>			const_reverse_iterator;

	//typedef typename allocator_type::template rebind<value_type>::other type_allocator;
    class value_compare : std::binary_function<value_type, value_type, bool>
    {
        protected:
        Compare comp;

        value_type(key_compare c) : comp(c);
        value_type(void) {};
        
    }
};

}

#endif