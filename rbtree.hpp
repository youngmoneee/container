#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "iter.hpp"
# include "utilities.hpp"
# include "iter.hpp"
# include "iterator.hpp"

# include <memory>

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
	typedef const T	const_value_type;

    typedef K		key_type;
    typedef Comp	comp_type;

	typedef tree_node<value_type>						node_type;
	typedef tree_node<value_type>*						node_pointer;
	typedef tree_node<value_type>&						node_reference;

	typedef tree_iterator<value_type, node_type>		iterator;
	typedef tree_iterator<const_value_type, node_type>	const_iterator;

	typedef _Alloc	allocator_type;
	typedef typename allocator_type::template rebind<node_type>::other node_allocator;
	typedef std::allocator_traits<node_allocator> 		node_traits;

	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;

	rbtree(const comp_type& comp, const allocator_type& alloc) : _comp_(comp), _alloc_(alloc), _size_(size_type()) {
		_nil_ = _alloc_.allocate(1);
		_alloc_.construct(_nil_, value_type());
		_nil_->rbtype = tree_node::BLACK;
		_nil_->parent = _nil_->lchild = _nil_->rchild = _nil_;
		_end_ = _construct_(value_type());
		_end_->rbtype = tree_node::BLACK;
		_begin_ = _end_;
	}

	rbtree(const rbtree& rhs) : comp(rhs.comp), _alloc_(rhs._alloc_), size(size_type()) {
		_nil_ = _alloc_.allocate(1);
		_alloc_.construct(_nil_, value_type());
		_nil_->rbtype = tree_node::BLACK;
		_nil_->parent = _nil_->lchild = _nil_->rchild = _nil_;
		_end_ = _construct_(value_type());
		_end_->rbtype = tree_node::BLACK;
		_begin_ = _end_;
		insert(rhs._begin_, rhs._end_);
	}

	~rbtree() {
		_destruct_all(_end_);
		_destruct_(_nil_);
	}

	//	TODO	: swap
	rbtree& operator=(const rbtree& rhs) {
		if (this == &rhs) return *this;
		rbtree tmp(rhs);
		ft::swap(_nil_, tmp._nil_);
    	ft::swap(_begin_, tmp._begin_);
    	ft::swap(_end_, tmp._end_);
    	ft::swap(_comp_, tmp._comp_);
    	ft::swap(_alloc_, tmp._alloc_);
    	ft::swap(_size_, tmp._size_);
		return *this;
	}

	iterator begin(void) {
		return iterator(_begin_, _nil_);
	}
	const_iterator begin(void) const {
		return const_iterator(_begin_, _nil_);
	}
	iterator end(void) {
		return iterator(_end_, _nil_);
	}
	const_iterator end(void) const {
		return const_iterator(_end_, _nil_);
	}

	size_type size(void) const {
		return _size_;
	}
	size_type max_size(void) const {
		return _alloc_.max_size();
	}

	bool empty(void) const {
		return !size;
	}

	node_pointer get_root(void) const {
		return _end_->lchild;
	}
	void set_root(const node_pointer ptr) {
		ptr->parent = _end_;
		_end_->lchild = ptr;
	}
	node_pointer find_parent(const value_type& val, node_pointer pos = ft::nil) {
		if (pos && pos != _end_) {
			if (_comp_(val, pos->value) && pos->lchild == _nil_) {
				iterator prev = iterator(pos->prev(), _nil_);
				if (prev == begin() || _comp_(*--prev, val)) return pos;
			} else if (pos->rchild == _nil_) {
				iterator next = iterator(pos->next(), _nil_);
				if (next == end() || _comp_(val, *++next)) return pos;
			}
		}
		node_pointer cur = get_root();
		node_pointer last = end();
		for (; cur != _nil_;) {
			last = cur;
			if (_comp_(val, cur->value)) cur = cur->lchild;
			else if (_comp_(cur->value, val)) cur = cur->rchild;
			else return cur;
		}
		return last;
	}

private:
	node_pointer	_begin_;
	node_pointer	_end_;
	node_allocator	_alloc_;
	node_pointer	_nil_;
	comp_type		_comp_;
	
	size_type		_size_;

	node_pointer _construct_(const value_type& val) {
		node_pointer ret = _alloc_.allocate(1);
		_alloc_.construct(ret, val);
		ret->parent = ret->lchild = ret->rchild = _nil_;
		ret->rbtype = tree_node::RED;
		return ret;
	}
	void	_destruct_(node_pointer del) {
		_alloc_.destroy(del);
		_alloc_.deallocate(del, 1);
	}

	void	_destruct_all(node_pointer del) {
		if (del == _nil_) return ;
		_destruct_all(del->lchild);
		_destruct_all(del->rchild);
		_destruct_(del);
	}
};
}   //  FT

#endif