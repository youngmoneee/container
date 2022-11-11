#ifndef MAP_HPP
# define MAP_HPP

#include <memory>

#include "algorithm.hpp"
#include "pair.hpp"
#include "iter.hpp"
#include "rbtree.hpp"

namespace ft
{
template<typename K, typename T, typename Comp = std::less<K>, typename _Alloc = std::allocator<pair<const K, T> > >
class map
{
private:
public:
//  Type
    typedef K											key_type;
    typedef T                                           mapped_type;
    typedef pair<const K, T>							value_type;		// Key : Value
    typedef Comp										key_compare;
    typedef _Alloc										allocator_type;

private:
	typedef typename allocator_type::value_type			alloc_value_type;

public:
	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		friend class map<K, T, Comp, _Alloc>;

	protected:
		Comp	comp;
		value_compare(Comp c) : comp(c) {};
	public:
		bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
	};

private:
	typedef typename _Alloc::template rebind<value_type>::other									pair_alloc_type;
	typedef RbTree<key_type, value_type, Select1st<value_type>, key_compare, pair_alloc_type>	rep_type;

	rep_type	rep;

public:
	typedef typename pair_alloc_type::pointer			pointer;
	typedef typename pair_alloc_type::const_pointer		const_pointer;
	typedef typename pair_alloc_type::reference			reference;
	typedef typename pair_alloc_type::const_reference	const_reference;
	typedef typename rep_type::iterator					iterator;
	typedef typename rep_type::const_iterator			const_iterator;
	typedef typename rep_type::size_type				size_type;
	typedef typename rep_type::difference_type			difference_type;
	typedef typename rep_type::reverse_iterator			reverse_iterator;
	typedef typename rep_type::const_reverse_iterator	const_reverse_iterator;

	map() : rep(Comp(), allocator_type()) {}
	explicit map(const Comp& comp, const allocator_type& alloc = allocator_type()) : rep(comp, alloc) {}
	map(const map& ref) : rep(ref.rep) {}
	template <typename Iter>
	map(Iter first, Iter last) : rep(Comp(), allocator_type()) { rep.insert_unique(first, last); }
	template <typename Iter>
	map(Iter first, Iter last, const Comp& comp, const allocator_type& alloc = allocator_type())
	: rep(comp, alloc) { rep.insert_unique(first, last); }

	map& operator=(const map& rhs) { rep = rhs.rep; return *this; }

	allocator_type get_allocator() const { return rep.get_alloc(); }

	iterator begin() { return rep.begin(); }
	const_iterator begin() const { return rep.begin(); }
	iterator end() { return rep.end(); }
	const_iterator end() const { return rep.end(); }
	reverse_iterator rbegin() { return rep.rbegin(); }
	const_reverse_iterator rbegin() const { return rep.rbegin(); }
	reverse_iterator rend() { return rep.rend(); }
	const_reverse_iterator rend() const { return rep.rend(); }

	bool empty() const { return rep.empty(); }
	size_type size() const { return rep.size(); }
	size_type max_size() const { return rep.max_size(); }

	mapped_type& operator[](const key_type& key)
	{
		iterator	it = lower_bound(key);

		if (it == end() || key_comp()(key, it->first))
			it = insert(it, value_type(key, mapped_type()));
		return it->second;
	}
	mapped_type& at(const key_type& key)
	{
		iterator	it = lower_bound(key);

		if (it == end() || key_comp()(key, it->first))
			throw std::out_of_range("Range Exception");
		return it->second;
	}
	const mapped_type& at(const key_type& key) const
	{
		const_iterator	it = lower_bound(key);

		if (it == end() || key_comp()(key, it->first))
			throw std::out_of_range("Range Exception");
		return it->second;
	}

	pair<iterator, bool> insert(const value_type& v) { return rep.insert_unique(v); }
	iterator insert(iterator pos, const value_type& v) { return rep.insert_unique(pos, v); }
	template<typename Iter>
	void insert(Iter first, Iter last) { return rep.insert_unique(first, last); }

	void erase(iterator pos) { rep.erase(pos); }
	size_type erase(const key_type& key) { return rep.erase(key); }
	void erase(iterator first, iterator last) { rep.erase(first, last); }

	void swap(map& rhs) { rep.swap(rhs.rep); }
	void clear() { rep.clear(); }

	key_compare key_comp() const { return rep.key_comp(); }
	value_compare value_comp() const { return value_compare(rep.key_comp()); }

	iterator find(const key_type& x) { return rep.find(x); }
	const_iterator find(const key_type& x) const { return rep.find(x); }
	size_type count(const key_type& x) const { return rep.find(x) == end() ? 0 : 1; }

	iterator lower_bound(const key_type& key) { return rep.lower_bound(key); }
	const_iterator lower_bound(const key_type& key) const { return rep.lower_bound(key); }
	iterator upper_bound(const key_type& key) { return rep.upper_bound(key); }
	const_iterator upper_bound(const key_type& key) const { return rep.upper_bound(key); }

	pair<iterator, iterator> equal_range(const key_type& key) { return rep.equal_range(key); }
	pair<const_iterator, const_iterator> equal_range(const key_type& key) const { return rep.equal_range(key); }

	template<typename FK, typename FT, typename FComp, typename FAlloc>
	friend bool operator==(const map<FK, FT, FComp, FAlloc>&, const map<FK, FT, FComp, FAlloc>&);
	template<typename FK, typename FT, typename FComp, typename FAlloc>
	friend bool operator<(const map<FK, FT, FComp, FAlloc>&, const map<FK, FT, FComp, FAlloc>&);
};

//	global rel operator

template<typename FK, typename FT, typename FComp, typename FAlloc>
bool operator==(const map<FK, FT, FComp, FAlloc>& lhs, const map<FK, FT, FComp, FAlloc>& rhs)
{ return lhs.rep == rhs.rep; }

template<typename FK, typename FT, typename FComp, typename FAlloc>
bool operator<(const map<FK, FT, FComp, FAlloc>& lhs, const map<FK, FT, FComp, FAlloc>& rhs)
{ return lhs.rep < rhs.rep; }

template<typename FK, typename FT, typename FComp, typename FAlloc>
bool operator!=(const map<FK, FT, FComp, FAlloc>& lhs, const map<FK, FT, FComp, FAlloc>& rhs)
{ return !(lhs == rhs); }

template<typename FK, typename FT, typename FComp, typename FAlloc>
bool operator<=(const map<FK, FT, FComp, FAlloc>& lhs, const map<FK, FT, FComp, FAlloc>& rhs)
{ return !(rhs < lhs); }

template<typename FK, typename FT, typename FComp, typename FAlloc>
bool operator>(const map<FK, FT, FComp, FAlloc>& lhs, const map<FK, FT, FComp, FAlloc>& rhs)
{ return !(lhs <= rhs); }

template<typename FK, typename FT, typename FComp, typename FAlloc>
bool operator>=(const map<FK, FT, FComp, FAlloc>& lhs, const map<FK, FT, FComp, FAlloc>& rhs)
{ return !(lhs < rhs); }

template<typename FK, typename FT, typename FComp, typename FAlloc>
void swap(const map<FK, FT, FComp, FAlloc>& lhs, const map<FK, FT, FComp, FAlloc>& rhs)
{ lhs.swap(rhs); }

}



#endif