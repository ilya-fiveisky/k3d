#ifndef CONSTEXPR_STRING_COSTRING_H
#define	CONSTEXPR_STRING_COSTRING_H

#include <stdexcept>
#include <string>

namespace constexpr_string
{
    
constexpr unsigned requires_in_range( unsigned i, unsigned len )
{
    return i >= len ? 
        throw std::out_of_range("i=" + std::to_string(i) + ", len=" + std::to_string(len)) 
        : i;
}

class costring
{
    const char * const begin_;
    unsigned size_;
 
public:
    template< unsigned N >
    constexpr costring( const char(&arr)[N] ) : begin_(arr), size_(N - 1) {
        static_assert( N >= 1, "not a string literal");
    }
 
    constexpr char operator[]( unsigned i ) { 
        return requires_in_range(i, size_), begin_[i]; 
    }
 
    constexpr operator const char *() { 
        return begin_; 
    }
 
    constexpr unsigned size() { 
        return size_; 
    }
};
}

#endif // !CONSTEXPR_STRING_COSTRING_H

