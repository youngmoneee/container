#ifndef TREE_NODE_H
# define TREE_NODE_H

#include "nullptr.hpp"

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
	: parent(_nullptr), lchild(_nullptr), rchild(_nullptr), value(value_type()), rbtype(color()) {};
	tree_node(const tree_node& node)
	: parent(node.parent), lchild(node.lchild), rchild(node.rchild), value(node.value), rbtype(node.rbtype) {};
	tree_node(const value_type& value)
	: parent(_nullptr), lchild(_nullptr), rchild(_nullptr), value(value), rbtype(_nullptr) {};
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
		while (ret->left != _nullptr) ret = &ret->lchild;
		return ret;
	}
	tree_node*	get_max(void) {
		tree_node*	ret = this;
		while (ret->rchild != _nullptr) ret = &ret->rchild;
		return ret;
	}
	tree_node*	next(void) {
		if (rchild != _nullptr) return rchild->get_min();
		tree_node*	ret = this;
		while (ret->is_rchild()) ret = &ret->parent;
		return &ret->parent;
	}
	tree_node*	prev(void) {
		if (lchild != _nullptr) return &lchild->get_max();
		tree_node*	ret = this;
		while (ret->is_lchild()) ret = &ret->parent;
		return &ret->parent;
	}
};
}	//	FT

#endif	// TREE_NODE_H