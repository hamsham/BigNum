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
class bn_int_type {
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
        constexpr bn_int_type();
        constexpr bn_int_type(const bn_int_type&);
        constexpr bn_int_type(bn_int_type&&);
        constexpr bn_int_type(const numType&);
        constexpr bn_int_type(numType&&);
        
        ~bn_int_type() = default;
        
        // assignment
        inline bn_int_type& operator=(const bn_int_type&);
        inline bn_int_type& operator=(bn_int_type&&);
        inline bn_int_type& operator=(const numType&);
        inline bn_int_type& operator=(numType&&);
        
        // type-casting
        constexpr operator numType() const;
        
        // unary arithmetic
        inline bn_int_type operator++(int);
        inline bn_int_type operator--(int);
        inline bn_int_type& operator++();
        inline bn_int_type& operator--();
        
        // unary sign/bit ops
        constexpr bn_int_type operator ! () const;
        constexpr bn_int_type operator + () const;
        constexpr bn_int_type operator - () const;
        constexpr bn_int_type operator ~ () const;
        
        //---------------------------------------------------------------------
        // Operations with another arbitrary number
        //---------------------------------------------------------------------
        // basic/binary arithmetic
        constexpr bn_int_type operator + (const bn_int_type&) const;
        constexpr bn_int_type operator - (const bn_int_type&) const;
        constexpr bn_int_type operator * (const bn_int_type&) const;
        constexpr bn_int_type operator / (const bn_int_type&) const;
        constexpr bn_int_type operator % (const bn_int_type&) const;
        constexpr bn_int_type operator & (const bn_int_type&) const;
        constexpr bn_int_type operator | (const bn_int_type&) const;
        constexpr bn_int_type operator ^ (const bn_int_type&) const;
        constexpr bn_int_type operator >> (const bn_int_type&) const;
        constexpr bn_int_type operator << (const bn_int_type&) const;
        
        // arithmetic with assignment
        inline bn_int_type& operator += (const bn_int_type&);
        inline bn_int_type& operator -= (const bn_int_type&);
        inline bn_int_type& operator *= (const bn_int_type&);
        inline bn_int_type& operator /= (const bn_int_type&);
        inline bn_int_type& operator %= (const bn_int_type&);
        inline bn_int_type& operator &= (const bn_int_type&);
        inline bn_int_type& operator |= (const bn_int_type&);
        inline bn_int_type& operator ^= (const bn_int_type&);
        inline bn_int_type& operator >>= (const bn_int_type&);
        inline bn_int_type& operator <<= (const bn_int_type&);
        
        // boolean comparison
        constexpr bool operator==(const bn_int_type&) const;
        constexpr bool operator!=(const bn_int_type&) const;
        constexpr bool operator>(const bn_int_type&) const;
        constexpr bool operator>=(const bn_int_type&) const;
        constexpr bool operator<(const bn_int_type&) const;
        constexpr bool operator<=(const bn_int_type&) const;
        
        //---------------------------------------------------------------------
        // Operations with POD types
        //---------------------------------------------------------------------
        // basic/binary arithmetic
        constexpr bn_int_type operator + (const numType&) const;
        constexpr bn_int_type operator - (const numType&) const;
        constexpr bn_int_type operator * (const numType&) const;
        constexpr bn_int_type operator / (const numType&) const;
        constexpr bn_int_type operator % (const numType&) const;
        constexpr bn_int_type operator & (const numType&) const;
        constexpr bn_int_type operator | (const numType&) const;
        constexpr bn_int_type operator ^ (const numType&) const;
        constexpr bn_int_type operator >> (const numType&) const;
        constexpr bn_int_type operator << (const numType&) const;
        
        // arithmetic with assignment
        inline bn_int_type& operator += (const numType&);
        inline bn_int_type& operator -= (const numType&);
        inline bn_int_type& operator *= (const numType&);
        inline bn_int_type& operator /= (const numType&);
        inline bn_int_type& operator %= (const numType&);
        inline bn_int_type& operator &= (const numType&);
        inline bn_int_type& operator |= (const numType&);
        inline bn_int_type& operator ^= (const numType&);
        inline bn_int_type& operator >>= (const numType&);
        inline bn_int_type& operator <<= (const numType&);
        
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
BN_DECLARE_CLASS(bn_int_type, bn_uint8, BN_UINT8, std::numeric_limits<BN_UINT8>::max());
BN_DECLARE_CLASS(bn_int_type, bn_uint16, BN_UINT16, std::numeric_limits<BN_UINT16>::max());
BN_DECLARE_CLASS(bn_int_type, bn_uint32, BN_UINT32, std::numeric_limits<BN_UINT32>::max());

BN_DECLARE_CLASS(bn_int_type, bn_base2_single, BN_UINT8, 2);
BN_DECLARE_CLASS(bn_int_type, bn_base2_double, BN_UINT16, 2);

BN_DECLARE_CLASS(bn_int_type, bn_base8_single, BN_UINT16, 8);
BN_DECLARE_CLASS(bn_int_type, bn_base8_double, BN_UINT32, 8);

BN_DECLARE_CLASS(bn_int_type, bn_base10_single, BN_UINT32, 10);
BN_DECLARE_CLASS(bn_int_type, bn_base10_double, BN_UINT64, 10);

BN_DECLARE_CLASS(bn_int_type, bn_base16_single, BN_UINT32, 16);
BN_DECLARE_CLASS(bn_int_type, bn_base16_double, BN_UINT64, 16);



///////////////////////////////////////////////////////////////////////////////
// std::iostream
///////////////////////////////////////////////////////////////////////////////
template <typename numType, BN_UINT64 intId>
inline std::ostream& operator << (std::ostream&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline std::istream& operator >> (std::istream&, bn_int_type<numType, intId>&);

///////////////////////////////////////////////////////////////////////////////
// R-Value Operations with POD types
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// basic/binary arithmetic
//-----------------------------------------------------------------------------
template <typename numType, BN_UINT64 intId>
constexpr numType operator + (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator - (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator * (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator / (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator % (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator & (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator | (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator ^ (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator >> (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr numType operator << (const numType&, const bn_int_type<numType, intId>&);


//-----------------------------------------------------------------------------
// arithmetic with assignment
//-----------------------------------------------------------------------------
template <typename numType, BN_UINT64 intId>
inline numType& operator += (numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator -= (numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator *= (numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator /= (numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator %= (numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator &= (numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator |= (numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator ^= (numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator >>= (numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
inline numType& operator <<= (numType&, const bn_int_type<numType, intId>&);

//-----------------------------------------------------------------------------
// boolean comparison
//-----------------------------------------------------------------------------
template <typename numType, BN_UINT64 intId>
constexpr bool operator == (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr bool operator != (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr bool operator > (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr bool operator >= (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr bool operator < (const numType&, const bn_int_type<numType, intId>&);

template <typename numType, BN_UINT64 intId>
constexpr bool operator <= (const numType&, const bn_int_type<numType, intId>&);

///////////////////////////////////////////////////////////////////////////////
// Implementation Header
///////////////////////////////////////////////////////////////////////////////
#include "bignum/impl/bn_int_type_impl.h"

#endif	/* __BN_INT_TYPE_H__ */

