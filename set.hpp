#ifndef SET_HPP
# define SET_HPP

#include "rbtree.hpp"

namespace ft
{

template<typename K, typename Comp = ft::less<K>, typename Alloc = std::allocator<K> >
class set
{
	typedef typename Alloc::value_type            alloc_value_type;

public:
	typedef K			key_type;
	typedef K			value_type;
	typedef Comp		key_compare;
	typedef Comp		value_compare;
	typedef Alloc		allocator_type;

private:
	typedef typename Alloc::template rebind<K>::other											key_alloc_type;
	typedef RbTree<key_type, value_type, Identity<value_type>, key_compare, key_alloc_type>		rep_type;
	rep_type	rep;

public:
	typedef typename key_alloc_type::pointer			pointer;
	typedef typename key_alloc_type::reference			reference;
	typedef typename key_alloc_type::const_pointer		const_pointer;
	typedef typename key_alloc_type::const_reference	const_reference;

	typedef typename rep_type::const_iterator			iterator;
	typedef typename rep_type::const_iterator			const_iterator;
	typedef typename rep_type::const_reverse_iterator	reverse_iterator;
	typedef typename rep_type::const_reverse_iterator	const_reverse_iterator;
	typedef typename rep_type::size_type				size_type;
	typedef typename rep_type::difference_type			difference_type;

	set() : rep(Comp(), Alloc()) {}
	explicit set(const Comp& comp, const allocator_type& alloc = allocator_type()) : rep(comp, alloc) {}
	template <typename Iter>
	set(Iter first, Iter last) : rep(Comp(), allocator_type())
	{ rep.insert_unique(first, last); }
	template <class Iter>
	set(Iter first, Iter last, const Comp& comp, const allocator_type& alloc = allocator_type()) : rep(comp, alloc)
	{ rep.insert_unique(first, last); }
	set(const set<K, Comp, Alloc>& rhs) : rep(rhs.rep) {}

	set<K, Comp, Alloc>& operator=(const set<K, Comp, Alloc>& rhs)
	{
		rep = rhs.rep;
		return *this;
	}
	key_compare key_comp() const { return rep.key_comp(); }
	value_compare value_comp() const { return rep.key_comp(); }
	allocator_type get_allocator() const { return rep.get_alloc(); }

	iterator begin() const { return rep.begin(); }
	iterator end() const { return rep.end(); }
	reverse_iterator rbegin() const { return rep.rbegin(); }
	reverse_iterator rend() const { return rep.rend(); }

	bool empty() const { return rep.empty(); };
	size_type size() const { return rep.size(); }
	size_type max_size() const { return rep.max_size(); }
	void swap(set<K, Comp, Alloc>& rhs) { rep.swap(rhs.rep); }

	ft::pair<iterator, bool> insert(const value_type& v)
	{
		ft::pair<typename rep_type::iterator, bool> ret = rep.insert_unique(v);
		return ft::pair<iterator, bool>(ret.first, ret.second);
	}
	iterator insert(iterator pos, const value_type& v) { return rep.insert_unique(pos, v); }
	template<typename Iter>
	void insert(Iter first, Iter last) { rep.insert_unique(first, last); }

	void erase(iterator pos) { rep.erase(pos); }
	size_type erase(const key_type& k) { return rep.erase(k); }
	void erase(iterator first, iterator last) { rep.erase(first, last); }
	void clear() { rep.clear(); }
	size_type count(const key_type& k) const { return rep.find(k) == rep.end() ? 0 : 1; }

	iterator find(const key_type& k) { return rep.find(k); }
	const_iterator find(const key_type& k) const { return rep.find(k); }

	iterator lower_bound(const key_type& k) { return rep.lower_bound(k); }
	const_iterator lower_bound(const key_type& k) const { return rep.lower_bound(k); }
	iterator upper_bound(const key_type& k) { return rep.upper_bound(k); }
	const_iterator upper_bound(const key_type& k) const { return rep.upper_bound(k); }

	ft::pair<iterator, iterator> equal_range(const key_type& k) { return rep.equal_range(k); }
	ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const { return rep.equal_range(k); }

	template <typename OtherK, typename OtherComp, typename OtherAlloc>
	friend bool operator==(const set<OtherK, OtherComp, OtherAlloc>&, const set<OtherK, OtherComp, OtherAlloc>&);
	template <typename OtherK, typename OtherComp, typename OtherAlloc>
	friend bool operator<(const set<OtherK, OtherComp, OtherAlloc>&, const set<OtherK, OtherComp, OtherAlloc>&);
};
template <typename K, typename Comp, typename Alloc>
bool operator==(const set<K, Comp, Alloc>& lhs, const set<K, Comp, Alloc>& rhs) { return lhs.rep == rhs.rep; }
template <typename K, typename Comp, typename Alloc>
bool operator<(const set<K, Comp, Alloc>& lhs, const set<K, Comp, Alloc>& rhs) { return lhs.rep < rhs.rep; }
template <typename K, typename Comp, typename Alloc>
bool operator!=(const set<K, Comp, Alloc>& lhs, const set<K, Comp, Alloc>& rhs) { return !(lhs == rhs); }
template <typename K, typename Comp, typename Alloc>
bool operator>(const set<K, Comp, Alloc>& lhs, const set<K, Comp, Alloc>& rhs) { return rhs < lhs; }
template <typename K, typename Comp, typename Alloc>
bool operator<=(const set<K, Comp, Alloc>& lhs, const set<K, Comp, Alloc>& rhs) { return !(rhs < lhs); }
template <typename K, typename Comp, typename Alloc>
bool operator>=(const set<K, Comp, Alloc>& lhs, const set<K, Comp, Alloc>& rhs) { return !(lhs < rhs); }

template <class K, class Comp, class Alloc>
void swap(set<K, Comp, Alloc>& lhs, set<K, Comp, Alloc>& rhs) { lhs.swap(rhs); }
}	//	FT
#endif