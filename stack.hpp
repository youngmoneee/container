#ifndef STACK_H
# define STACK_H

#include "vector.hpp"

namespace ft
{
template<typename T, typename Container = vector<T> >
class stack
{
public:
	typedef Container									container_type;
	typedef typename container_type::value_type			value_type;
	typedef typename container_type::size_type			size_type;
	typedef typename container_type::reference			reference;
	typedef typename container_type::const_reference	const_reference;
	typedef typename container_type::pointer			pointer;
	typedef typename container_type::const_pointer		const_pointer;

	explicit stack(const container_type& container = container_type()) : con(container) {};
	stack(const stack& rhs) : con(rhs.con) {};
	virtual ~stack(void) {};

	stack& operator=(const stack& rhs) {
		if (this == rhs) return *this;
		con = rhs.con;
		return *this;
	}

	reference top(void) { return con.back(); }
	const_reference top(void) const { return con.back(); }
	void push(const value_type& value) { con.push_back(value); }
	void pop(const value_type& value) { con.pop_back(); }

	bool empty(void) const { return con.empty(); }
	size_type size(void) const { return con.size(); }
protected:
	container_type	con;

private:
	const container_type get_container(void) const { return con; }

friend bool operator==(const stack& lhs, const stack& rhs) { return lhs.get_container() == rhs.get_container(); }
friend bool operator!=(const stack& lhs, const stack& rhs) { return lhs.con != rhs.con; }
friend bool operator<(const stack& lhs, const stack& rhs) { return lhs.con < rhs.con; }
friend bool operator<=(const stack& lhs, const stack& rhs) { return lhs.con <= rhs.con; }
friend bool operator>(const stack& lhs, const stack& rhs) { return lhs.con > rhs.con; }
friend bool operator>=(const stack& lhs, const stack& rhs) { return lhs.con >= rhs.con; }

};

}

#endif