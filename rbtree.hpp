#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "iter.hpp"
# include "utilities.hpp"
# include "iter.hpp"
# include "iterator.hpp"
# include "pair.hpp"

# include <memory>

namespace ft
{
enum eColor {
	RED,
	BLACK
};

struct tree_node
{
	typedef tree_node* 			node_ptr;
	typedef const tree_node*	const_node_ptr;

	eColor		color;
	node_ptr	parent;
	node_ptr	left;
	node_ptr	right;

	static node_ptr	minimum(node_ptr ptr)
	{
		while(ptr->left != 0) ptr = ptr->left;
		return ptr;
	}
	static node_ptr	maximum(node_ptr ptr)
	{
		while(ptr->right != 0) ptr = ptr->right;
		return ptr;
	}
	static const_node_ptr minimum(const_node_ptr ptr)
	{
		while(ptr->left != 0) ptr = ptr->left;
		return ptr;
	}
	static const_node_ptr maximum(const_node_ptr ptr)
	{
		while(ptr->right != 0) ptr = ptr->right;
		return ptr;
	}
};

template<typename T>
struct rb_node : public tree_node
{
	typedef rb_node<T>*		link_type;
	T						value;
};

tree_node*
tree_increment(tree_node* ptr)
{
	if (ptr->right != 0)
	{
		ptr = ptr->right;
		while (ptr->left != 0) ptr = ptr->left;
	}
	else
	{
		tree_node*	tmp = ptr->parent;
		while (ptr == tmp->right)
		{
			ptr = tmp;
			tmp = tmp->parent;
		}
		if (ptr->right != tmp)
			ptr = tmp;
	}
	return ptr;
}

const tree_node*
tree_increment(const tree_node* ptr)
{
	return tree_increment(const_cast<tree_node*>(ptr));
}

tree_node*
tree_decrement(tree_node* ptr)
{
	if (ptr->color == RED && ptr->parent->parent == ptr)
		ptr = ptr->right;
	else if (ptr->left != 0)
	{
		tree_node* tmp = ptr->left;
		while(tmp->right != 0) tmp = tmp->right;
		ptr = tmp;
	}
	else
	{
		tree_node*	tmp = ptr->parent;
		while (ptr == tmp->left)
		{
			ptr = tmp;
			tmp = tmp->parent;
		}
		ptr = tmp;
	}
	return ptr;
}

const tree_node*
tree_decrement(const tree_node* ptr)
{
	return tree_decrement(const_cast<tree_node*>(ptr));
}

template<typename T>
class rb_iterator
{
public:
	typedef T								value_type;
	typedef value_type*						pointer;
	typedef	value_type&						reference;
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef ptrdiff_t						difference_type;

	typedef rb_iterator<T>					self;
	typedef	tree_node::node_ptr				node_ptr;
	typedef rb_node<T>*						link_type;

	link_type								node;

	rb_iterator() : node() {};
	explicit rb_iterator(link_type tp) : node(tp) {};
	~rb_iterator() {};

	reference operator*() const { return static_cast<link_type>(node)->value; }
	pointer	operator->() const { return &static_cast<link_type>(node)->value; }

	rb_iterator& operator++() {
		node = tree_increment(node);
		return *this;
	}
	rb_iterator operator++(int) {
		rb_iterator tmp = *this;
		operator++();
		return tmp;
	}
	rb_iterator& operator--() {
		node = tree_decrement(node);
		return *this;
	}
	rb_iterator operator--(int) {
		rb_iterator tmp = *this;
		operator--();
		return tmp;
	}

	bool operator==(const rb_iterator& rhs) {
		return node == rhs.node;
	}
	bool operator!=(const rb_iterator& rhs) {
		return node != rhs.node;
	}
};

template<typename T>
class const_rb_iterator
{
public:
	typedef T								value_type;
	typedef const value_type*				pointer;
	typedef	const value_type&				reference;
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef ptrdiff_t						difference_type;

	typedef	tree_node::const_node_ptr		node_ptr;
	typedef const rb_node<T>*				link_type;

	link_type								node;

	const_rb_iterator() : node() {};
	const_rb_iterator(const rb_iterator<T>& iter) : node(iter.node) {};
	explicit const_rb_iterator(link_type tp) : node(tp) {};
	~const_rb_iterator() {};

	reference operator*() const { return static_cast<link_type>(node)->value; }
	pointer	operator->() const { return &static_cast<link_type>(node)->value; }

	const_rb_iterator& operator++() {
		node = tree_increment(node);
		return *this;
	}
	const_rb_iterator operator++(int) {
		rb_iterator tmp = *this;
		operator++();
		return tmp;
	}
	rb_iterator& operator--() {
		node = tree_decrement(node);
		return *this;
	}
	rb_iterator operator--(int) {
		rb_iterator tmp = *this;
		operator--();
		return tmp;
	}

	bool operator==(const const_rb_iterator& rhs) {
		return node == rhs.node;
	}
	bool operator!=(const const_rb_iterator& rhs) {
		return node != rhs.node;
	}
};

template<typename T>
bool operator==(const rb_iterator<T>& lhs, const const_rb_iterator<T>& rhs)
{ return lhs.node == rhs.node; }
template<typename T>
bool operator!=(const rb_iterator<T>& lhs, const const_rb_iterator<T>& rhs)
{ return lhs.node != rhs.node; }

void tree_rotate_left(const tree_node* target, tree_node* root)
{
	const tree_node* tmp = target->right;

	target->right = tmp->left;
	if (tmp->left != 0)
		tmp->left->parent = target;
	tmp->parent = target->parent;

	if (target == root)
		root = tmp;
	else if (target == target->parent->left)
		target->parent->left = y;
	else
		target->parent->right = tmp;
	tmp->left = target;
	target->parent = tmp;
}

void tree_rotate_right(const tree_node* target, tree_node* root)
{
	const tree_node*	tmp = target->left;

	target->left = tmp->right;
	if (tmp->right != 0)
		tmp->right->parent = target;
	tmp->parent = target->parent;

	if (target == root)
		root = tmp;
	else if (target == target->parent->right)
		target->parent->right = tmp;
	else
		target->parent->left = tmp;
	tmp->right = target;
	target->parent = tmp;
}

void insert_rebalance(const bool insert_left, tree_node* target, tree_node* parent, tree_node& header)
{
	const tree_node*& root = header.parent;

	target->parent = parent;
	target->left = 0;
	target->right = 0;
	target = RED;

	/**
	 * @brief : Insert, First node should be Left node
	 */
	if (insert_left)
	{
		parent->left = target;
		if (parent == &header)
		{
			header.parent = target;
			header.right = target;
		} else if (parent == header.left)
			header.left = target;
	} else {
		parent->right = target;
		if (parent == header.right)
			header.right = target;
	}

	/**
	 * @brief : Rebalance
	 */
	 while (target != root && target->parent->color == RED) {
		 const tree_node* parpar = target->parent->parent;

		 if (target->parent == parpar->left) {
			 const tree_node*	tmp = parpar->right;

			 if (tmp && tmp->color == RED) {//	#Case 1
				target->parent->color = BLACK;
				tmp->color = BLACK;
				parpar->color = RED;
				target = parpar;
			 } else {						//	#Case 2
				 if (target == target->parent->right) {
					 target = target->parent;
					 tree_rotate_left(target, root);
				 }
				 target->parent->color = BLACK;
				 parpar->color = RED;
				 tree_rotate_right(parpar, root);
			 }
		 }
		 else {
			 const tree_node*	tmp = parpar->left;

			 if (tmp && tmp->color = RED) {	//	#Case 1
				 target->parent->color = BLACK;
				 tmp->color = BLACK;
				 parpar->color = RED;
				 target = parpar;
			 } else {						//	#Case 2
				 if (target == target->parent->left) {
					 target = target->parent;
					 tree_rotate_right(target, root);
				 }
				 target->parent->color = BLACK;
				 parpar->color = RED;
				 tree_rotate_left(parpar, root);
			 }
		 }
	 }
	 root->color = BLACK;
}

tree_node*	rebalance_erase(const tree_node* z, tree_node& header)
{
	tree_node*&		root = header.parent;
	tree_node*&		leftest = header.left;
	tree_node*&		rightest = header.right;
	tree_node*		x = 0;
	tree_node*		y = z;
	tree_node*		x_par = 0;

	if (y->left == 0)
		x = y->right;
	else
	{
		if (y->right == 0)
			x = y->left;
		else
		{
			//	z has one or more non-null, y == z
			y = y->right;
			while (y->left != 0)
				y = y->left;
			x = y->right;
		}
	}

	if (y != z)
	{
		//	relink y in place of z. y is z's successor
		z->left->parent = y;
		y->left = z->left;
		if (y != z->right)
		{
			x_par = y->parent;
			if (x) x->parent = y->parent;
			y->parent->left = x;
			y->right = z->right;
			z->right->parent = y;
		}
		else
			x_par = y;

		if (root == z) root = y;
		else if (z->parent->left == z) z->parent->left = y;
		else z->parent->right = y;
		y->parent = z->parent;
		std::swap(y->color, z->color);
		y = z;
	}
	else
	{
		//	y == z
		x_par = y->parent;
		if (x) x->parent = y->parent;
		if (root == z) root = x;
		else {
			if(z->parent->left == z) z->parent->left = x;
			else z->parent->right = x;
		}

		if (leftest == z) {
			if (z->right == 0) leftest = z->parent;
			else leftest = tree_node::minimum(x);
		}
		if (rightest == z) {
			if (z->left == 0) rightest = z->parent;
			else rightest = tree_node::maximum(x);
		}
	}

	if (y->color != RED)
	{
		while (x != root && (x == 0 || x->color == BLACK))
		{
			if (x == x_par->left) {
				tree_node* cur = x_par->right;
				if (cur->color == RED) {	//	#CASE 1
					cur->color = BLACK;
					x_par->color = RED;
					tree_rotate_left(x_par, root);
					cur = x_par->right;
				}

				if ((cur->left == 0 || cur->left->color == BLACK) && (cur->right == 0 || cur->right->color == BLACK)) {
					cur->color = RED;
					x = x_par;
					x_par = x_par->parent;
				}
				else
				{
					if (cur->right == 0 || cur->right->color == BLACK) {	//	#CASE 3
						cur->left->color = BLACK;
						cur->color = RED;
						tree_rotate_right(cur, root);
						cur = x_par->right;
					}
					cur->color = x_par->color;								//	#CASE 4
					x_par->color = BLACK;
					if (cur->right) cur->right->color = BLACK;
					tree_rotate_left(x_par, root);
					break ;
				}
			}
			else
			{
				//	same as above, with right <-> left
				tree_node*	cur = x_par->left;
				if (cur->color == RED) {                                    //	#CASE 1
					cur->color = BLACK;
					x_par->color = RED;
					tree_rotate_right(x_par, root);
					cur = x_par->left;
				}

				if ((cur->right == 0  || cur->right->color == BLACK) && (cur->left == 0 || cur->left->color == BLACK))	{//	#CASE 2
					cur->color = RED;
					x = x_par;
					x_par = x_par->parent;
				}
				else
				{
					if (cur->left == 0 || cur->left->color == BLACK) {	//	#CASE 3
						cur->right->color = BLACK;
						cur->color = RED;
						tree_rotate_left(cur, root);
						cur = x_par->left;
					}
					cur->color = x_par->color;								//	#CASE 4
					x_par->color = BLACK;
					if (cur->left) cur->left->color = BLACK;
					tree_rotate_right(x_par, root);
					break ;
				}
			}
		}
		if (x) x->color = BLACK;
	}
	return y;
};

template<typename K, typename V, typename KV, typename Comp, typename Alloc = std::allocator<V> >
class RbTree
{
	typedef typename Alloc::template rebind<rb_node<V> >::other		node_allocator;

protected:
	typedef tree_node*			node_ptr;
	typedef const tree_node*	const_node_ptr;
	typedef rb_node<V>			rb_node;

public:
	typedef	K					key_type;
	typedef V					value_type;
	typedef value_type*			pointer;
	typedef const value_type*	const_pointer;
	typedef value_type&			reference;
	typedef const value_type&	const_reference;
	typedef rb_node*			link_type;
	typedef const rb_node*		const_link_type;
	typedef std::size_t			size_type;
	typedef std:;ptrdiff_t		difference_type;
	typedef Alloc				allocator_type;

	node_allocator& get_node_alloc() { return *static_cast<node_allocator*>(&this->impl); }
	const node_allocator& get_node_alloc() const { return *static_cast<node_allocator*>(&this->impl); }

	allocator_type get_alloc() const { return allocator_type(get_node_alloc()); }

protected:
	rb_node* get_node() { return impl.node_allocator::allocate(1); }
	void put_node(rb_node* ptr) { impl.node_allocator::deallocate(ptr, 1); }
	link_type create_node(const value_type& v) {
		link_type ret = get_node();
		try {
			get_alloc().construct(&ret->value, v);
		}
		catch (...) {
			put_node(ret);
			throw ;
		}
		return ret;
	}

	link_type copy_node(const_link_type target) {
		link_type dest = create_node(target->value);
		dest->color = target->color;
		dest->left = 0;
		dest->right = 0;
		return dest;
	}

	void destroy_node(link_type target) {
		get_alloc().destroy(&target->value);
		put_node(target);
	}

	template<typename KeyComp, bool is_pod = std::is_pod<KeyComp>::value>
	struct RbTreeImpl : public node_allocator
	{
		KeyComp		keyCompare;
		tree_node	header;
		size_type	size;

		RbTreeImpl(const node_allocator& alloc = node_allocator(), const KeyComp& comp = KeyComp())
		: node_allocator(alloc), keyCompare(comp), header(), size(0)
		{
			this->header.color = RED;
			this->header.parent = 0;
			this->header.left = &this->header;
			this->header.right = &this->header;
		}
	};

	template<typename KeyComp>
	struct RbTreeImpl<KeyComp, true> : public node_allocator
	{
		KeyComp		keyCompare;
		tree_node	header;
		size_type	size;

		RbTreeImpl(const node_allocator& alloc = node_allocator(), const KeyComp& comp = KeyComp())
		: node_allocator(alloc), keyCompare(comp), header(), size(0)
		{
			this->header.color = RED;
			this->header.parent = 0;
			this->header.left = &this->header;
			this->header.right = &this->header;
		}
	};
	RbTreeImpl<Comp>	impl;

protected:
	node_ptr& root() { return this->impl.header.parent; }
	const_node_ptr& root() const { return this->impl.header.parent; }
	node_ptr& get_leftest() { return this->impl.header.left; }
	const_node_ptr& get_leftest() const { return this->impl.header.left; }
	node_ptr& get_rightest() { return this->impl.header.right; }
	const_node_ptr& get_rightest() const { return this->impl.header.right; }

	link_type begin() { return static_cast<link_type>(this->impl.header.parent); }
	const_link_type begin() const { return static_cast<const_link_type>(this->impl.header.parent); }
	link_type end() { return static_cast<link_type>(&this->impl.header); }
	const_link_type end() const { return static_cast<const_link_type>(&this->impl.header); }

	static const_reference getValue(const_link_type target) { return target->value; }
	static const_reference getValue(const_node_ptr target) { return static_cast<const_link_type>(target)->value; }

	static const K& getKey(const_link_type target) { return KV()(getValue(target)); }
	static const K& getKey(const_node_ptr target) { return KV()(getValue(target)); }

	static link_type getLeft(node_ptr target) { return static_cast<link_type>(target->left); }
	static const_link_type getLeft(const_node_ptr target) { return static_cast<const_link_type>(target->left); }
	static link_type getRight(node_ptr target) { return static_cast<link_type>(target->right); }
	static const_link_type getRight(const_node_ptr target) { return static_cast<const_link_type>(target->right); }

	static node_ptr minimum(node_ptr target) { return tree_node::minimum(target); }
	static const_node_ptr minimum(const_node_ptr target) { return tree_node::minimum(target); }
	static node_ptr maximum(node_ptr target) { return tree_node::maximum(target); }
	static const_node_ptr maximum(const_node_ptr target) { return tree_node::maximum(target); }

public:
	typedef rb_iterator<value_type>					iterator;
	typedef const_rb_iterator<value_type>			const_iterator;

	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

private:
	iterator insert(node_ptr target, node_ptr parent, const value_type& val)
	{
		bool insert_left = (target != 0 || parent == end() || impl.keyCompare(KV()(val), getKey(parent)));

		link_type	z = create_node(val);

		insert_rebalance(insert_left, z, parent, impl.header);
		++impl.size;
		return iterator(z);
	}
	const_iterator insert(const_node_ptr target, const_node_ptr parent, const value_type& val)
	{
		bool insert_left = (target != 0 || parent == end() || impl.keyCompare(KV()(val), getKey(parent)));

		link_type	z = create_node(val);

		insert_rebalance(insert_left, z, const_cast<node_ptr >(parent), impl.header);
		++impl.size;
		return const_iterator(z);
	}
	iterator insert_lower(node_ptr target, node_ptr parent, const value_type& val)
	{
		bool insert_left = (target != 0 || parent == end() || !impl.keyCompare(getKey(parent), KV()(val)));

		link_type	z = create_node(val);

		insert_rebalance(insert_left, z, parent, impl.header);
		++impl.size;
		return iterator(z);
	}
	link_type copy(const_link_type target, link_type parent)
	{
		link_type	top = copy_node(target);
		top->parent = parent;

		try {
			if (target->right) top->right = copy(getRight(target), top);
			parent = top;
			target = getLeft(target);

			while (target != 0)
			{
				link_type	y = copy_node(target);
				parent->left = y;
				y->parent = parent;
				if (target->right) y->right = copy(getRight(target), y);
				parent = y;
				target = getLeft(target);
			}
		}
		catch (...) {
			erase(top);
			throw ;
		}
		 return top;
	}

	void erase(link_type target)
	{
		while (target != 0) {
			erase(getRight(target));
			link_type tmp = getLeft(target);
			destroy_node(target);
			target = tmp;
		}
	}

public:
	RbTree(){};
	RbTree(const Compare& comp) : impl(allocator_type(), comp) {};
	RbTree(const Compare& comp, const allocator_type& alloc) : impl(alloc, comp) {};
	RbTree(const RbTree<K, V, KV, Comp, Alloc>& target) : impl(target.get_node_alloc(), target.impl.keyCompare) {
		if (target.root() != 0) {
			root() = copy(target.begin(), end());
			get_leftest() = minimum(root());
			get_rightest() = minimum(root());
			impl.size = target.impl.size;
		}
	}

	~RbTree() { erase(begin()); }

	RbTree<K, V, KV, Comp, Alloc>& operator=(const RbTree<K, V, KV, Comp, Alloc>& target)
	{
		if (this == &target) return *this;
		clear();
		impl.keyCompare = target.impl.keyCompare;
		if (target.root() != 0) {
			root() = copy(target.begin(), end());
			get_leftest() = minimum(root());
			get_rightest() = maximum(root());
			impl.size = target.impl.size;
		}
		return *this;
	}

	//	Access
	Comp key_comp() const { return impl.keyCompare; }

	iterator begin() { return iterator(static_cast<link_type>(impl.header.left)); }
	const_iterator begin() const { return const_iterator(static_cast<const_link_type>(impl.header.left)); }
	iterator end() { return iterator(static_cast<link_type>(&impl.header)); }
	const_iterator end() const { return const_iterator(static_cast<const_link_type>(&impl.header)); }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(begin()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

	bool empty() const { return !impl.size; }
	size_type size() const { return impl.size; }
	size_type max_size() const { return get_alloc().max_size(); }
	void swap(RbTree<K, V, KV, Comp, Alloc>& other)
	{
		if (root() == 0)
		{
			if (other.root() != 0)
			{
				root() = other.root();
				other.root() = 0;

				get_leftest() = other.get_leftest();
				get_rightest() = other.get_rightest();
				other.get_leftest() = other.get_rightest() = other.end();
			}
		}
		else if (other.root() == 0)
		{
			other.root() = root();
			root() = 0;

			other.get_leftest() = get_leftest();
			other.get_rightest() = get_rightest();
			get_leftest() = get_rightest() = end();
		}
		else
		{
			std::swap(root(), other.root());
			std::swap(get_leftest(), other.get_leftest());
			std::swap(get_rightest(), other.get_rightest());

			root()->parent = end();
			other->parent = other.end();
		}

		std::swap(this->impl.size, other.impl.size);
		std::swap(this->impl.keyCompare, other.impl.keyCompare);
	}

	/**
	 * @brief Insert Erase Implementation
	 */

	ft::pair<iterator, bool> insert_unique(const value_type& v)
	{
		link_type	x = begin();
		link_type	y = end();
		bool		comp = true;

		while (x != 0)
		{
			y = x;
			comp = impl.keyCompare(KV()(v), getKey(x));
			x = comp ? getLeft(x) : getRight(x);
		}
		iterator	it = iterator(y);
		if (comp) {
			if (it == begin()) return pair<iterator, bool>(insert(x, y, v), true);
			else --it;
		}
		if (impl.keyCompare(getKey(it.node), KV()(v))) return pair<iterator, bool>(insert(x, y, v), true);
		return pair<iterator, bool>(it, false);
	}

	iterator insert_equal(const value_type& v)
	{
		link_type	x = begin();
		link_type	y = end();
		bool		comp = true;
		while (x != 0)
		{
			y = x;
			comp = impl.keyCompare(KV()(v), getKey(x));
			x = comp ? getLeft(x) : getRight(x);
		}
		return insert(x, y, v);
	}

	iterator insert_equal_lower(const value_type& v)
	{
		link_type	x = begin();
		link_type	y = end();
		bool 		comp = true;

		while (x != 0)
		{
			y = x;
			comp = impl.keyCompare(KV()(v), getKey(x));
			x = !comp ? getLeft(x) : getRight(x);
		}
		return insert_lower(x, y, v);
	}

	iterator insert_unique(iterator pos, const value_type& v)
	{
		if (pos.node == end())
		{
			if (!empty() && impl.keyCompare(getKey(get_rightest()), KV()(v))) return insert(0, get_rightest(), v);
			else return insert_unique(v).first;
		}
		else if (impl.keyCompare(KV()(v), getKey(pos.node)))
		{
			iterator	before = pos;

			if (pos.node == get_leftest()) return insert(get_leftest(), get_leftest(), v);
			else if (impl.keyCompare(getKey((--before).node), KV()(v)))
			{
				if (getRight(before.node) == 0) return insert(0, before.node, v);
				else return insert(pos.node, pos.node, v);
			}
			else return insert_unique(v).first;
		}
		else if (impl.keyCompare(getKey(pos.node), KV()(v)))
		{
			iterator	after = pos;

			if (pos.node == get_rightest()) return insert(0, get_rightest(), v);
			else if (impl.keyCompare(KV()(v), getKey((++after).node)))
			{
				if (getRight(pos.node) == 0) return insert(0, pos.node, v);
				else return insert(after.node, after.node, v);
			}
			else return insert_unique(v).first;
		}
		else return pos;
	}

	const_iterator insert_unique(const_iterator pos, const value_type& v)
	{
		if (pos.node ==end())
		{
			if (!empty() && impl.keyCompare(getKey(get_rightest()), KV()(v))) return insert(0, get_rightest(), v);
			else return const_iterator(insert_unique(v).first);
		}
		else if (impl.keyCompare(KV()(v), getKey(pos.node)))
		{
			const_iterator	before = pos;

			if (pos.node == get_leftest()) return insert(get_leftest(), get_leftest(), v);
			else if (impl.keyCompare(getKey((--before).node), KV()(v)))
			{
				if (getRight(before.node) == 0) return insert(0, before.node, v);
				else return insert(pos.node, pos.node, v);
			}
			else return const_iterator(insert_unique(v).first);
		}
		else if (impl.keyCompare(getKey(pos.node), KV()(v)))
		{
			const_iterator	after = pos;

			if (pos.node == get_rightest()) return insert(0, get_rightest(), v);
			else if (impl.keyCompare(KV()(v), getKey((++after).node)))
			{
				if (getRight(pos.node) == 0) return insert(0, pos.node, v);
				else return insert(after.node, after.node, v);
			}
			else return const_iterator(insert_unique(v).first);
		}
		else return pos;
	}

	iterator insert_equal(iterator pos, const value_type& v)
	{
		if (pos.node == end())
		{
			if (!empty() && impl.keyCompare(KV()(v)), getKey(get_rightest())) return insert(0, get_rightest(), v);
			else return insert_unique(v);
		}
		else if (!impl.keyCompare(getKey(pos.node), KV()(v)))
		{
			iterator	before = pos;

			if (pos.node == get_leftest()) return insert(get_leftest(), get_leftest(), v);
			else if (!impl.keyCompare(KV()(v), getKey((--before).node)))
			{
				if (getRight(before.node) == 0) return insert(0, before.node, v);
				else return insert(pos.node, pos.node, v);
			}
			else return insert_unique(v);
		}
		else
		{
			iterator	after = pos;
			if (pos.node == get_rightest()) return insert(0, get_rightest(), v);
			else if (!impl.keyCompare(getKey((++after).node)), KV()(v))
			{
				if (getRight(pos.node) == 0) return insert(0, pos.node, v);
				else return insert(after.node, after.node, v);
			}
			else return insert_equal_lower(v);
		}
	}

	const_iterator insert_equal(const_iterator pos, const value_type& v)
	{
		if (pos.node == end())
		{
			if (!empty() && !impl.keyCompare(KV()(v)), getKey(get_rightest())) return insert(0, get_rightest(), v);
			else return const_iterator(insert_unique(v));
		}
		else if (!impl.keyCompare(getKey(pos.node), KV()(v)))
		{
			const_iterator	before = pos;
			if (pos.node == get_leftest()) return insert(get_leftest(), get_leftest(), v);
			else if (!impl.keyCompare(KV()(v), getKey((--before).node)))
			{
				if (getRight(before.node) == 0) return insert(0, before.node, v);
				else return insert(pos.node, pos.node, v);
			}
			else return const_iterator(insert_unique(v));
		}
		else
		{
			const_iterator	after = pos;
			if (pos.node == get_rightest()) return insert(0, get_rightest(), v);
			else if (!impl.keyCompare(getKey((++after).node)), KV()(v))
			{
				if (getRight(pos.node) == 0) return insert(0, pos.node, v);
				else return insert(after.node, after.node, v);
			}
			else return const_iterator(insert_equal_lower(v));
		}
	}

	template<typename Iter>
	void insert_unique(Iter first, Iter last)
	{
		for (; first != last; ++first) insert_unique(end(), *first);
	}

	template<typename Iter>
	void insert_equal(Iter first, Iter last)
	{
		for (; first != last; ++first) insert_equal(end(), *first);
	}

	void erase(iterator pos)
	{
		link_type	y = static_cast<link_type>(rebalance_erase(pos.node, impl.header));
		destroy_node(y);
		--impl.size;
	}

	void erase(const_iterator pos)
	{
		link_type	y = static_cast<link_type>(rebalance_erase(const_cast<node_ptr>(pos.node), impl.header));
		destroy_node(y);
		--impl.size;
	}

	size_type erase(const key_type& x)
	{
		pair<iterator, iterator>	pitit = equal_range(x);
		const size_type	presize = size();
		erase(pitit.first, pitit.second);
		return presize - size();
	}

	void erase(iterator first, iterator last)
	{
		if (first == begin() && last == end()) clear();
		else for (; first != last; ++first) erase(*first);
	}

	void erase(const_iterator first, const_iterator last)
	{
		if (first == begin() && last == end()) clear();
		else for (; first != last; ++first) erase(*first);
	}

	void erase(const key_type* first, const key_type* last)
	{
		for (; first != last; ++first) erase(*first);
	}

	void clear()
	{
		erase(begin());
		root() = 0;
		get_leftest() = get_rightest() = end();
		impl.size = 0;
	}

	iterator find(const key_type& k)
	{
		link_type	x = begin();
		link_type	y = end();

		for (; x != 0;)
		{
			if (!impl.keyCompare(getKey(x), k))
			{
				y = x;
				x = getLeft(x);
			}
			else x = getRight(x);
		}
		iterator	it = iterator(y);
		return it == end() || impl.keyCompare(k, getKey(it.node)) ? end() : it;
	}

	const_iterator find(const key_type& k) const
	{
		const_link_type	x = begin();
		const_link_type	y = begin();

		for (; x != 0;)
		{
			if (!impl.keyCompare(getKey(x), k))
			{
				y = x;
				x = getLeft(x);
			}
			else x = getRight(x);
		}
		const_iterator	it = const_iterator(y);
		return it == end() || impl.keyCompare(k, getKey(it.node)) ? end() : it;
	}

	size_type count(const key_type& k) const
	{
		pair<const_iterator, const_iterator> pitit = equal_range(k);
		return std::distance(pitit.first, pitit.second);
	}

	iterator lower_bound(const key_type& k)
	{
		link_type	x = begin();
		link_type	y = end();

		for (; x != 0;)
		{
			if (!impl.keyCompare(getKey(x), k))
			{
				y = x;
				x = getLeft(x);
			}
			else x = getRight(x);
		}
		return iterator(y);
	}

	const_iterator lower_bound(const key_type& k)
	{
		link_type	x = begin();
		link_type	y = end();

		for (; x != 0;)
		{
			if (impl.keyCompare(getKey(x), k))
			{
				y = x;
				x = getLeft(x);
			}
			else x = getRight(x);
		}
		return const_iterator(y);
	}

	iterator upper_bound(const key_type& k)
	{
		link_type	x = begin();
		link_type	y = end();

		for (; x != 0;)
		{
			if (impl.keyCompare(k, getKey(x)))
			{
				y = x;
				x = getLeft(x);
			}
			else x = getRight(x);
		}
		return iterator(y);
	}

	const_iterator upper_bound(const key_type& k) const
	{
		const_link_type	x = begin();
		const_link_type	y = end();

		for (; x != 0;)
		{
			if (impl.keyCompare(k, getKey(x)))
			{
				y = x;
				x = getLeft(x);
			}
			else x = getRight(x);
		}
		return const_iterator(y);
	}

	pair<iterator, iterator> equal_range(const key_type& k)
	{ return pair<iterator, iterator>(lower_bound(k), upper_bound(k)); }
	pair<const_iterator, const_iterator> equal_range(const key_type& k)
	{ return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)); }
};

template <typename K, typename V, typename KV, typename Comp, typename Alloc>
bool operator==(const RbTree<K, V, KV, Comp, Alloc>& lhs,
				const RbTree<K, V, KV, Comp, Alloc>& rhs)
{ return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

template <typename K, typename V, typename KV, typename Comp, typename Alloc>
bool operator!=(const RbTree<K, V, KV, Comp, Alloc>& lhs,
				const RbTree<K, V, KV, Comp, Alloc>& rhs)
{ return !(lhs == rhs); }

template <typename K, typename V, typename KV, typename Comp, typename Alloc>
bool operator<(const RbTree<K, V, KV, Comp, Alloc>& lhs,
				const RbTree<K, V, KV, Comp, Alloc>& rhs)
{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

template <typename K, typename V, typename KV, typename Comp, typename Alloc>
bool operator<=(const RbTree<K, V, KV, Comp, Alloc>& lhs,
			   const RbTree<K, V, KV, Comp, Alloc>& rhs)
{ return !(rhs < lhs); }

template <typename K, typename V, typename KV, typename Comp, typename Alloc>
bool operator>(const RbTree<K, V, KV, Comp, Alloc>& lhs,
				const RbTree<K, V, KV, Comp, Alloc>& rhs)
{ return rhs < lhs; }

template <typename K, typename V, typename KV, typename Comp, typename Alloc>
bool operator>=(const RbTree<K, V, KV, Comp, Alloc>& lhs,
				const RbTree<K, V, KV, Comp, Alloc>& rhs)
{ return !(lhs < rhs); }

template <typename K, typename V, typename KV, typename Comp, typename Alloc>
void swap(const RbTree<K, V, KV, Comp, Alloc>& lhs,
		  const RbTree<K, V, KV, Comp, Alloc>& rhs)
{ return lhs.swap(rhs); }

}   //  FT

#endif