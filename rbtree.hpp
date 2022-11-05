#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "iter.hpp"
# include "utilities.hpp"

namespace ft
{
template<typename T>
struct tree_node
{
	static const bool	BLACK = false;
	static const bool	RED	= true;

	typedef T		value_type;
	typedef bool	color;

	tree_node*	parent;
	tree_node*	lchild;
	tree_node*	rchild;
	value_type	value;
	color		rbtype;

	tree_node(void)
	: parent(ft::nil), lchild(ft::nil), rchild(ft::nil), value(value_type()), rbtype(color()) {};
	tree_node(const tree_node& node)
	: parent(node.parent), lchild(node.lchild), rchild(node.rchild), value(node.value), rbtype(node.rbtype) {};
	tree_node(const value_type& value)
	: parent(ft::nil), lchild(ft::nil), rchild(ft::nil), value(value), rbtype(color()) {};
	~tree_node(void) {};

	tree_node& operator=(const tree_node& rhs) {
		if (this == &rhs) return *this;
		parent = rhs.parent;
		lchild = rhs.lchild;
		rchild = rhs.rchild;
		value = rhs.value;
		rbtype = rhs.rbtype;
		return *this;
	}

	bool	is_lchild(void) const { return this == &parent->lchild; }
	bool	is_rchild(void) const { return this == &parent->rchild; }
	bool	is_black(void) const { return BLACK == rbtype; }
	bool	is_red(void) const { return RED == rbtype; }

	tree_node*	get_min(void) {
		tree_node*	ret = this;
		while (ret->left != ft::nil) ret = &ret->lchild;
		return ret;
	}
	tree_node*	get_max(void) {
		tree_node*	ret = this;
		while (ret->rchild != ft::nil) ret = &ret->rchild;
		return ret;
	}
	tree_node*	next(void) {
		if (rchild != ft::nil) return rchild->get_min();
		tree_node*	ret = this;
		while (ret->is_lchild()) ret = &ret->parent;
		return &ret->parent;
	}
	tree_node*	prev(void) {
		if (lchild != ft::nil) return &lchild->get_max();
		tree_node*	ret = this;
		while (ret->is_rchild()) ret = &ret->parent;
		return &ret->parent;
	}

/*
	template<typename Other, typename Another, typename Comp>
	bool is_equal(const Other& other, const Another& another, Comp comp) {
		return !comp(other, another) && !comp(another, other);
	}
	*/
};

template<typename T, typename K, typename Comp, typename _Alloc>
class rbtree
{
public:
    typedef T		value_type;
    typedef K		key_type;
    typedef Comp	comp_type;

	typedef tree_node<value_type>	node_type;
	typedef tree_node<value_type>*	node_pointer;
	typedef tree_node<value_type>&	node_reference;

	typedef tree_iterator<value_type, node_type>
};
}   //  FT

#endif