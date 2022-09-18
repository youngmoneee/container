#ifndef NULLPTR_HPP
#define NULLPTR_HPP

namespace ft
{
struct nullptr_t
{
private:
    void operator&() const;
public:
    template<typename T> inline operator T*() const { return 0; }
    template<typename T, typename U> inline operator T U::*() const { return 0; }
};

static nullptr_t    _nullptr = {};

}

#endif //NULLPTR_HPP