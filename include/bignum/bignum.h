/* 
 * File:   bignum.h
 * Author: Miles Lacey
 *
 * Created on July 18, 2014, 12:43 PM
 */

#ifndef __BIGNUM_H__
#define	__BIGNUM_H__

#include "bignum/bn_setup.h"
#include "bignum/bn_limits.h"
#include "bignum/bn_except.h"
#include "bignum/bn_int_type.h"
#include "bignum/bn_type.h"

///////////////////////////////////////////////////////////////////////////////
//          Typedefs Requiring Class Definitions
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Integral types for bignum specialization.
// 
// These are defined in the source file "bn_int_type.cpp"
///////////////////////////////////////////////////////////////////////////////
BN_DECLARE_CLASS(bn_int_type, bn_uint8, BN_UINT8, bn_max_limit<BN_UINT8>());
BN_DECLARE_CLASS(bn_int_type, bn_uint16, BN_UINT16, bn_max_limit<BN_UINT16>());
BN_DECLARE_CLASS(bn_int_type, bn_uint32, BN_UINT32, bn_max_limit<BN_UINT32>());

BN_DECLARE_CLASS(bn_int_type, bn_base2_single, BN_UINT8, 2);
BN_DECLARE_CLASS(bn_int_type, bn_base2_double, BN_UINT16, 2);

BN_DECLARE_CLASS(bn_int_type, bn_base8_single, BN_UINT16, 8);
BN_DECLARE_CLASS(bn_int_type, bn_base8_double, BN_UINT32, 8);

BN_DECLARE_CLASS(bn_int_type, bn_base10_single, BN_UINT32, 10);
BN_DECLARE_CLASS(bn_int_type, bn_base10_double, BN_UINT64, 10);

BN_DECLARE_CLASS(bn_int_type, bn_base16_single, BN_UINT32, 16);
BN_DECLARE_CLASS(bn_int_type, bn_base16_double, BN_UINT64, 16);

///////////////////////////////////////////////////////////////////////////////
// Numeric max and min for specialized numbers
///////////////////////////////////////////////////////////////////////////////
/*
 * Binary precision min/max
 */
template <>
constexpr bn_limit_t bn_min_limit<bn_base2_single>() {return 0;}
template <>
constexpr bn_limit_t bn_max_limit<bn_base2_single>() {return 1;}

template <>
constexpr bn_limit_t bn_min_limit<bn_base2_double>() {return 0;}
template <>
constexpr bn_limit_t bn_max_limit<bn_base2_double>() {return 3;}

/*
 * Octal precision min/max
 */
template <>
constexpr bn_limit_t bn_min_limit<bn_base8_single>() {return 0;}
template <>
constexpr bn_limit_t bn_max_limit<bn_base8_single>() {return 7;}

template <>
constexpr bn_limit_t bn_min_limit<bn_base8_double>() {return 0;}
template <>
constexpr bn_limit_t bn_max_limit<bn_base8_double>() {return 63;}

/*
 * decimal precision min/max
 */
template <>
constexpr bn_limit_t bn_min_limit<bn_base10_single>() {return 0;}
template <>
constexpr bn_limit_t bn_max_limit<bn_base10_single>() {return 9;}

template <>
constexpr bn_limit_t bn_min_limit<bn_base10_double>() {return 0;}
template <>
constexpr bn_limit_t bn_max_limit<bn_base10_double>() {return 99;}

/*
 * hexadecimal precision min/max
 */
template <>
constexpr bn_limit_t bn_min_limit<bn_base16_single>() {return 0;}
template <>
constexpr bn_limit_t bn_max_limit<bn_base16_single>() {return 15;}

template <>
constexpr bn_limit_t bn_min_limit<bn_base16_double>() {return 0;}
template <>
constexpr bn_limit_t bn_max_limit<bn_base16_double>() {return 255;}

///////////////////////////////////////////////////////////////////////////////
// Extern template declarations and typedefs
// 
// These are defined in the source file "bn_type.cpp"
///////////////////////////////////////////////////////////////////////////////
BN_DECLARE_CLASS(bn_type, bignum_lowp, BN_UINT8, BN_UINT16);
BN_DECLARE_CLASS(bn_type, bignum_medp, BN_UINT16, BN_UINT32);
BN_DECLARE_CLASS(bn_type, bignum_highp, BN_UINT32, BN_UINT64);

BN_DECLARE_CLASS(bn_type, bignum_base2, bn_base2_single, bn_base2_single);
BN_DECLARE_CLASS(bn_type, bignum_base8, bn_base8_single, bn_base8_single);
BN_DECLARE_CLASS(bn_type, bignum_base10, bn_base10_single, bn_base10_single);
BN_DECLARE_CLASS(bn_type, bignum_base16, bn_base16_single, bn_base16_single);

/**
 * Default-precision bignum
 */
typedef bignum_highp bignum;

#endif	/* __BIGNUM_H__ */

