/* 
 * File:   bn_int_type_impl.h
 * Author: Miles Lacey
 *
 * Created on July 18, 2014, 1:01 PM
 */

///////////////////////////////////////////////////////////////////////////////
// Constructors
///////////////////////////////////////////////////////////////////////////////
template <typename numType, BN_UINT64 intId>
constexpr BNIntType<numType, intId>::BNIntType() :
    num{0}
{}

template <typename numType, BN_UINT64 intId>
constexpr BNIntType<numType, intId>::BNIntType(const BNIntType& bni) :
    num{bni.num}
{}

template <typename numType, BN_UINT64 intId>
constexpr BNIntType<numType, intId>::BNIntType(BNIntType&& bni) :
    num{bni.num}
{}

template <typename numType, BN_UINT64 intId>
constexpr BNIntType<numType, intId>::BNIntType(const numType& n) :
    num{n}
{}

template <typename numType, BN_UINT64 intId>
constexpr BNIntType<numType, intId>::BNIntType(numType&& n) :
    num{n}
{}

///////////////////////////////////////////////////////////////////////////////
// Assignment Operators
///////////////////////////////////////////////////////////////////////////////
template <typename numType, BN_UINT64 intId>
inline BNIntType<numType, intId>& BNIntType<numType, intId>::operator=(const BNIntType& bni) {
    num = bni.num;
    return *this;
}

template <typename numType, BN_UINT64 intId>
inline BNIntType<numType, intId>& BNIntType<numType, intId>::operator=(BNIntType&& bni) {
    num = bni.num;
    return *this;
}

template <typename numType, BN_UINT64 intId>
inline BNIntType<numType, intId>& BNIntType<numType, intId>::operator=(const numType& n) {
    num = n;
    return *this;
}

template <typename numType, BN_UINT64 intId>
inline BNIntType<numType, intId>& BNIntType<numType, intId>::operator=(numType&& n) {
    num = n;
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Type-Casting
///////////////////////////////////////////////////////////////////////////////
template <typename numType, BN_UINT64 intId>
constexpr BNIntType<numType, intId>::operator numType() const {
    return num;
}

///////////////////////////////////////////////////////////////////////////////
// Unary Arithmetic
///////////////////////////////////////////////////////////////////////////////
template <typename numType, BN_UINT64 intId>
inline BNIntType<numType, intId> BNIntType<numType, intId>::operator++(int) {
    BNIntType<numType, intId> ret{num};
    ++num;
    return ret;
}

template <typename numType, BN_UINT64 intId>
inline BNIntType<numType, intId> BNIntType<numType, intId>::operator--(int) {
    BNIntType<numType, intId> ret{num};
    --num;
    return ret;
}

template <typename numType, BN_UINT64 intId>
inline BNIntType<numType, intId>& BNIntType<numType, intId>::operator++() {
    ++num;
    return *this;
}

template <typename numType, BN_UINT64 intId>
inline BNIntType<numType, intId>& BNIntType<numType, intId>::operator--() {
    --num;
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Unary Sign/Bit Ops
///////////////////////////////////////////////////////////////////////////////
template <typename numType, BN_UINT64 intId>
constexpr BNIntType<numType, intId> BNIntType<numType, intId>::operator!() const {
    return BNIntType<numType, intId>{(numType)!num};
}

template <typename numType, BN_UINT64 intId>
constexpr BNIntType<numType, intId> BNIntType<numType, intId>::operator+() const {
    return BNIntType<numType, intId>{(numType)+num};
}

template <typename numType, BN_UINT64 intId>
constexpr BNIntType<numType, intId> BNIntType<numType, intId>::operator-() const {
    return BNIntType<numType, intId>{(numType)-num};
}

template <typename numType, BN_UINT64 intId>
constexpr BNIntType<numType, intId> BNIntType<numType, intId>::operator~() const {
    return BNIntType<numType, intId>{(numType)~num};
}

///////////////////////////////////////////////////////////////////////////////
// Binary operators returning a bn_int_type type
///////////////////////////////////////////////////////////////////////////////
#define BN_INT_TYPE_BINARY_OP(op) \
    template <typename numType, BN_UINT64 intId> \
    constexpr BNIntType<numType, intId> BNIntType<numType, intId>::operator op (const BNIntType<numType, intId>& bni) const { \
        return BNIntType<numType, intId>{(numType)(num op bni.num)}; \
    } \
    \
    template <typename numType, BN_UINT64 intId> \
    constexpr BNIntType<numType, intId> BNIntType<numType, intId>::operator op (const numType& n) const { \
        return BNIntType<numType, intId>{(numType)(num op n)}; \
    } \
    \
    template <typename numType, BN_UINT64 intId> \
    inline BNIntType<numType, intId>& BNIntType<numType, intId>::operator op##= (const BNIntType<numType, intId>& bni) { \
        num op##= bni.num; \
        return *this; \
    } \
    \
    template <typename numType, BN_UINT64 intId> \
    inline BNIntType<numType, intId>& BNIntType<numType, intId>::operator op##= (const numType& n) { \
        num op##= n; \
        return *this; \
    }
    

    // Non-Assigned arithmetic
    BN_INT_TYPE_BINARY_OP(+)
    BN_INT_TYPE_BINARY_OP(-)
    BN_INT_TYPE_BINARY_OP(*)
    BN_INT_TYPE_BINARY_OP(/)
    BN_INT_TYPE_BINARY_OP(%)
    BN_INT_TYPE_BINARY_OP(&)
    BN_INT_TYPE_BINARY_OP(|)
    BN_INT_TYPE_BINARY_OP(^)
    BN_INT_TYPE_BINARY_OP(>>)
    BN_INT_TYPE_BINARY_OP(<<)

#undef BN_INT_TYPE_BINARY_OP

///////////////////////////////////////////////////////////////////////////////
// Binary comparison operators
///////////////////////////////////////////////////////////////////////////////
#define BN_INT_TYPE_BOOL_OP(op) \
    template <typename numType, BN_UINT64 intId> \
    constexpr bool BNIntType<numType, intId>::operator op (const BNIntType<numType, intId>& bni) const { \
        return num op bni.num; \
    } \
    \
    template <typename numType, BN_UINT64 intId> \
    constexpr bool BNIntType<numType, intId>::operator op (const numType& n) const { \
        return num op n; \
    }
    
    BN_INT_TYPE_BOOL_OP(==)
    BN_INT_TYPE_BOOL_OP(!=)
    BN_INT_TYPE_BOOL_OP(>)
    BN_INT_TYPE_BOOL_OP(>=)
    BN_INT_TYPE_BOOL_OP(<)
    BN_INT_TYPE_BOOL_OP(<=)

#undef BN_INT_TYPE_BOOL_OP

///////////////////////////////////////////////////////////////////////////////
// R-Value Binary comparison operators
///////////////////////////////////////////////////////////////////////////////
#define BN_INT_TYPE_BINARY_OP_R(op) \
    template <typename numType, BN_UINT64 intId> \
    constexpr numType operator op (const numType& n, const BNIntType<numType, intId>& bni) { \
        return n op bni.num; \
    } \
    \
    template <typename numType, BN_UINT64 intId> \
    inline numType& operator op##= (numType& n, const BNIntType<numType, intId>& bni) { \
        return n op##= bni.num; \
    }

    // Non-Assigned arithmetic
    BN_INT_TYPE_BINARY_OP_R(+)
    BN_INT_TYPE_BINARY_OP_R(-)
    BN_INT_TYPE_BINARY_OP_R(*)
    BN_INT_TYPE_BINARY_OP_R(/)
    BN_INT_TYPE_BINARY_OP_R(%)
    BN_INT_TYPE_BINARY_OP_R(&)
    BN_INT_TYPE_BINARY_OP_R(|)
    BN_INT_TYPE_BINARY_OP_R(^)
    BN_INT_TYPE_BINARY_OP_R(>>)
    BN_INT_TYPE_BINARY_OP_R(<<)

#undef BN_INT_TYPE_BINARY_OP_R

///////////////////////////////////////////////////////////////////////////////
// R-Value Binary comparison operators
///////////////////////////////////////////////////////////////////////////////
#define BN_INT_TYPE_BOOL_OP_R(op) \
    template <typename numType, BN_UINT64 intId> \
    constexpr bool operator op (const numType& n, const BNIntType<numType, intId>& bni) { \
        return n op bni.num; \
    }
    
    BN_INT_TYPE_BOOL_OP_R(==)
    BN_INT_TYPE_BOOL_OP_R(!=)
    BN_INT_TYPE_BOOL_OP_R(>)
    BN_INT_TYPE_BOOL_OP_R(>=)
    BN_INT_TYPE_BOOL_OP_R(<)
    BN_INT_TYPE_BOOL_OP_R(<=)

#undef BN_INT_TYPE_BOOL_OP_R

///////////////////////////////////////////////////////////////////////////////
// std::iostream
///////////////////////////////////////////////////////////////////////////////
template <typename numType, BN_UINT64 intId>
inline std::ostream& operator << (std::ostream& outStr, const BNIntType<numType, intId>& bni) {
    return outStr << bni.num;
}

template <typename numType, BN_UINT64 intId>
inline std::istream& operator >> (std::istream& inStr, BNIntType<numType, intId>& bni) {
    return inStr >> bni.num;
}
