
/* 
 * File:   bn_limits_impl.h
 * Author: Miles Lacey
 *
 * Created on July 18, 2014, 9:28 PM
 */

#define _BN_DEFINE_LIMITS(numType) \
    template<> \
    constexpr bn_u64_t bn_min_limit<numType>() { \
        return std::numeric_limits<numType>::min(); \
    } \
    \
    template<> \
    constexpr bn_u64_t bn_max_limit<numType>() { \
        return std::numeric_limits<numType>::max(); \
    }

_BN_DEFINE_LIMITS(BN_UINT8)
_BN_DEFINE_LIMITS(BN_UINT16)
_BN_DEFINE_LIMITS(BN_UINT32)
_BN_DEFINE_LIMITS(BN_UINT64)

#undef _BN_DEFINE_LIMITS



///////////////////////////////////////////////////////////////////////////////
// Numeric max and min for specialized numbers
///////////////////////////////////////////////////////////////////////////////
/*
 * Binary precision min/max
 */
template <>
constexpr bn_u64_t bn_min_limit<bn_base2_single>() {return 0;}
template <>
constexpr bn_u64_t bn_max_limit<bn_base2_single>() {return 1;}

template <>
constexpr bn_u64_t bn_min_limit<bn_base2_double>() {return 0;}
template <>
constexpr bn_u64_t bn_max_limit<bn_base2_double>() {return 3;}

/*
 * Octal precision min/max
 */
template <>
constexpr bn_u64_t bn_min_limit<bn_base8_single>() {return 0;}
template <>
constexpr bn_u64_t bn_max_limit<bn_base8_single>() {return 7;}

template <>
constexpr bn_u64_t bn_min_limit<bn_base8_double>() {return 0;}
template <>
constexpr bn_u64_t bn_max_limit<bn_base8_double>() {return 63;}

/*
 * decimal precision min/max
 */
template <>
constexpr bn_u64_t bn_min_limit<bn_base10_single>() {return 0;}
template <>
constexpr bn_u64_t bn_max_limit<bn_base10_single>() {return 9;}

template <>
constexpr bn_u64_t bn_min_limit<bn_base10_double>() {return 0;}
template <>
constexpr bn_u64_t bn_max_limit<bn_base10_double>() {return 99;}

/*
 * hexadecimal precision min/max
 */
template <>
constexpr bn_u64_t bn_min_limit<bn_base16_single>() {return 0;}
template <>
constexpr bn_u64_t bn_max_limit<bn_base16_single>() {return 15;}

template <>
constexpr bn_u64_t bn_min_limit<bn_base16_double>() {return 0;}
template <>
constexpr bn_u64_t bn_max_limit<bn_base16_double>() {return 255;}
