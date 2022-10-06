#ifndef HELPER_HPP
#define HELPER_HPP

#include "iterator.hpp"

namespace ft
{
struct nullptr_t
{
private:
    void operator&(void) const;
public:
    template<typename T> operator T*(void) const { return 0; }
    template<typename T, typename U> operator U T::*(void) const { return 0; }
};

const nullptr_t    _nullptr = {};



}

#endif //HELPER_HPP
