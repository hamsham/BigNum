/* 
 * File:   bn_int_type.h
 * Author: Miles Lacey
 *
 * Created on July 18, 2014, 1:01 PM
 */

#ifndef __BN_INT_TYPE_H__
#define	__BN_INT_TYPE_H__

#include <iostream>
#include <limits>

#include "bignum/bn_setup.h"

/**
 * Specialization for a bignum to contain a number with an arbitrary minimum and
 * and maximum.
 */
template <typename numType, BN_UINT64 intId>
class BNIntType {
    /*
     * Public Members
     */
    public:
        numType num;
    
    /*
     * Public Methods
     */
    public:
        // constructors
        constexpr BNIntType();
        constexpr BNIntType(const BNIntType&);
        constexpr BNIntType(BNIntType&&);
        constexpr BNIntType(const numType&);
        constexpr BNIntType(numType&&);
        
        ~BNIntType() = default;
        
        // assignment
        inline BNIntType& operator=(const BNIntType&);
        inline BNIntType& operator=(BNIntType&&);
        inline BNIntType& operator=(const numType&);
        inline BNIntType& operator=(numType&&);
        
        // type-casting
        constexpr operator numType() const;
        
        // unary arithmetic
        inline BNIntType operator++(int);
        inline BNIntType operator--(int);
        inline BNIntType& operator++();
        inline BNIntType& operator--();
        
        // unary sign/bit ops
        constexpr BNIntType operator ! () const;
        constexpr BNIntType operator + () const;
        constexpr BNIntType operator - () const;
        constexpr BNIntType operator ~ () const;
        
        //---------------------------------------------------------------------
        // Operations with another arbitrary number
        //---------------------------------------------------------------------
        // basic/binary arithmetic
        constexpr BNIntType operator + (const BNIntType&) const;
        constexpr BNIntType operator - (const BNIntType&) const;
        constexpr BNIntType operator * (const BNIntType&) const;
        constexpr BNIntType operator / (const BNIntType&) const;
        constexpr BNIntType operator % (const BNIntType&) const;
        constexpr BNIntType operator & (const BNIntType&) const;
        constexpr BNIntType operator | (const BNIntType&) const;
        constexpr BNIntType operator ^ (const BNIntType&) const;
        constexpr BNIntType operator >> (const BNIntType&) const;
        constexpr BNIntType operator << (const BNIntType&) const;
        
        // arithmetic with assignment
        inline BNIntType& operator += (const BNIntType&);
        inline BNIntType& operator -= (const BNIntType&);
        inline BNIntType& operator *= (const BNIntType&);
        inline BNIntType& operator /= (const BNIntType&);
        inline BNIntType& operator %= (const BNIntType&);
        inline BNIntType& operator &= (const BNIntType&);
        inline BNIntType& operator |= (const BNIntType&);
        inline BNIntType& operator ^= (const BNIntType&);
        inline BNIntType& operator >>= (const BNIntType&);
        inline BNIntType& operator <<= (const BNIntType&);
        
        // boolean comparison
        constexpr bool operator==(const BNIntType&) const;
        constexpr bool operator!=(const BNIntType&) const;
        constexpr bool operator>(const BNIntType&) const;
        constexpr bool operator>=(const BNIntType&) const;
        constexpr bool operator<(const BNIntType&) const;
        constexpr bool operator<=(const BNIntType&) const;
        
        //---------------------------------------------------------------------
        // Operations with POD types
        //---------------------------------------------------------------------
        // basic/binary arithmetic
        constexpr BNIntType operator + (const numType&) const;
        constexpr BNIntType operator - (const numType&) const;
        constexpr BNIntType operator * (const numType&) const;
        constexpr BNIntType operator / (const numType&) const;
        constexpr BNIntType operator % (const numType&) const;
        constexpr BNIntType operator & (const numType&) const;
        constexpr BNIntType operator | (const numType&) const;
        constexpr BNIntType operator ^ (const numType&) const;
        constexpr BNIntType operator >> (const numType&) const;
        constexpr BNIntType operator << (const numType&) const;
        
        // arithmetic with assignment
        inline BNIntType& operator += (const numType&);
        inline BNIntType& operator -= (const numType&);
        inline BNIntType& operator *= (const numType&);
        inline BNIntType& operator /= (const numType&);
        inline BNIntType& operator %= (const numType&);
        inline BNIntType& operator &= (const numType&);
        inline BNIntType& operator |= (const numType&);
        inline BNIntType& operator ^= (const numType&);
        inline BNIntType& operator >>= (const numType&);
        inline BNIntType& operator <<= (const numType&);
        
        // boolean comparison
        constexpr bool operator==(const numType&) const;
        constexpr bool operator!=(const numType&) const;
        constexpr bool operator>(const numType&) const;
        constexpr bool operator>=(const numType&) const;
        constexpr bool operator<(const numType&) const;
        constexpr bool operator<=(const numType&) const;
};



///////////////////////////////////////////////////////////////////////////////
// Integral types for bignum specialization.
///////////////////////////////////////////////////////////////////////////////
// These top 3 specialization correlate with a limits definition to the values in impl/bn_limits_impl.h
BN_DECLARE_CLASS(BNIntType, bn_uint8, BN_UINT8, std::numeric_limits<BN_UINT8>::max());
BN_DECLARE_CLASS(BNIntType, bn_uint16, BN_UINT16, std::numeric_limits<BN_UINT16>::max());
BN_DECLARE_CLASS(BNIntType, bn_uint32, BN_UINT32, std::numeric_limits<BN_UINT32>::max());

BN_DECLARE_CLASS(BNIntType, bn_base2_single, BN_UINT8, 2);
BN_DECLARE_CLASS(BNIntType, bn_base2_double, BN_UINT16, 2);

BN_DECLARE_CLASS(BNIntType, bn_base8_single, BN_UINT16, 8);
BN_DECLARE_CLASS(BNIntType, bn_base8_double, BN_UINT32, 8);

BN_DECLARE_CLASS(BNIntType, bn_base10_single, BN_UINT32, 10);
BN_DECLARE_CLASS(BNIntType, bn_base10_double, BN_UINT64, 10);

BN_DECLARE_CLASS(BNIntType, bn_base16_single, BN_UINT32, 16);
BN_DECLARE_CLASS(BNIntType, bn_base16_double, BN_UINT64, 16);



///////////////////////////////////////////////////////////////////////////////
// std::iostream
///////////////////////////////////////////////////////////////////////////////
template <typename numType, BN_UINT64 intId>
inline std::ostream& operator << (std::ostream&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline std::istream& operator >> (std::istream&, BNIntType<numType, intId>&);

///////////////////////////////////////////////////////////////////////////////
// R-Value Operations with POD types
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// basic/binary arithmetic
//-----------------------------------------------------------------------------
template <typename numType, BN_UINT64 intId>
constexpr numType operator + (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator - (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator * (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator / (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator % (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator & (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator | (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator ^ (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator >> (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator << (const numType&, const BNIntType<numType, intId>&);


//-----------------------------------------------------------------------------
// arithmetic with assignment
//-----------------------------------------------------------------------------
template <typename numType, BN_UINT64 intId>
inline numType& operator += (numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator -= (numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator *= (numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator /= (numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator %= (numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator &= (numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator |= (numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator ^= (numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator >>= (numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator <<= (numType&, const BNIntType<numType, intId>&);

//-----------------------------------------------------------------------------
// boolean comparison
//-----------------------------------------------------------------------------
template <typename numType, BN_UINT64 intId>
constexpr bool operator == (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr bool operator != (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr bool operator > (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr bool operator >= (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr bool operator < (const numType&, const BNIntType<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr bool operator <= (const numType&, const BNIntType<numType, intId>&);

///////////////////////////////////////////////////////////////////////////////
// Implementation Header
///////////////////////////////////////////////////////////////////////////////
#include "bignum/impl/bn_int_type_impl.h"

#endif	/* __BN_INT_TYPE_H__ */

