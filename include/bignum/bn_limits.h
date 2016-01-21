/* 
 * File:   bn_limits.h
 * Author: Miles Lacey
 *
 * Created on July 18, 2014, 9:23 PM
 */

#ifndef __BN_LIMITS_H__
#define	__BN_LIMITS_H__

#include "bignum/bn_setup.h"
#include "bignum/bn_int_type.h"



///////////////////////////////////////////////////////////////////////////////
// Maximum limit data type
///////////////////////////////////////////////////////////////////////////////
typedef BN_UINT64 bn_u64_t;



///////////////////////////////////////////////////////////////////////////////
// Custom implementation of std::numeric_limits<>
///////////////////////////////////////////////////////////////////////////////
/**
 * Empty numeric limit prototype.
 * 
 * @return a 64-bit integer, representing the minimum value allowable by the
 * input type.
 */
template<typename T>
constexpr bn_u64_t bn_min_limit();

/**
 * Empty numeric limit prototype.
 * 
 * @return a 64-bit integer, representing the maximum value allowable by the
 * input type.
 */
template<typename T>
constexpr bn_u64_t bn_max_limit();

///////////////////////////////////////////////////////////////////////////////
// 8-bit numerical limit specializations
///////////////////////////////////////////////////////////////////////////////
/**
 * Numeric minimum for an 8-bit integer
 * 
 * @return a 64-bit integer, representing the minimum value allowable by the
 * input type.
 */
template<>
constexpr bn_u64_t bn_min_limit<BN_UINT8>();

/**
 * Numeric maximum for an 8-bit integer
 * 
 * @return a 64-bit integer, representing the maximum value allowable by the
 * input type.
 */
template<>
constexpr bn_u64_t bn_max_limit<BN_UINT8>();

///////////////////////////////////////////////////////////////////////////////
// 16-bit numerical limit specializations
///////////////////////////////////////////////////////////////////////////////
/**
 * Numeric minimum for a 16-bit integer
 * 
 * @return a 64-bit integer, representing the minimum value allowable by the
 * input type.
 */
template<>
constexpr bn_u64_t bn_min_limit<BN_UINT16>();

/**
 * Numeric maximum for a 16-bit integer
 * 
 * @return a 64-bit integer, representing the maximum value allowable by the
 * input type.
 */
template<>
constexpr bn_u64_t bn_max_limit<BN_UINT16>();

///////////////////////////////////////////////////////////////////////////////
// 32-bit numerical limit specializations
///////////////////////////////////////////////////////////////////////////////
/**
 * Numeric minimum for a 32-bit integer
 * 
 * @return a 64-bit integer, representing the minimum value allowable by the
 * input type.
 */
template<>
constexpr bn_u64_t bn_min_limit<BN_UINT32>();

/**
 * Numeric maximum for a 32-bit integer
 * 
 * @return a 64-bit integer, representing the maximum value allowable by the
 * input type.
 */
template<>
constexpr bn_u64_t bn_max_limit<BN_UINT32>();

///////////////////////////////////////////////////////////////////////////////
// 64-bit numerical limit specializations
///////////////////////////////////////////////////////////////////////////////
/**
 * Numeric minimum for a 64-bit integer
 * 
 * @return a 64-bit integer, representing the minimum value allowable by the
 * input type.
 */
template<>
constexpr bn_u64_t bn_min_limit<BN_UINT64>();

/**
 * Numeric maximum for a 64-bit integer
 * 
 * @return a 64-bit integer, representing the maximum value allowable by the
 * input type.
 */
template<>
constexpr bn_u64_t bn_max_limit<BN_UINT64>();

#include "bignum/impl/bn_limits_impl.h"



///////////////////////////////////////////////////////////////////////////////
// Bignum limits structure for template instantiation
///////////////////////////////////////////////////////////////////////////////
/**
 * Numeric limits for the arithmetic values
 */
template <typename base_single_t, typename base_double_t>
struct bn_limits_t {
    
    /**
     * Exposed single-precision type
     */
    typedef base_single_t base_single;

    /**
     * Exposed double-precision type
     */
    typedef base_double_t base_double;
    
    /**
     * Internal enumeration to describe the min/max of the single and
     * double-precision data types.
     */
    enum : bn_u64_t {
        /**
         * Minimum value for the single-precision number
         */
        SINGLE_BASE_MIN = bn_min_limit<base_single>(),
        /**
         * Maximum value for the single-precision number
         */
        SINGLE_BASE_MAX = bn_max_limit<base_single>(),

        /**
         * Minimum value for the double-precision number
         */
        DOUBLE_BASE_MIN = bn_min_limit<base_double>(),
        /**
         * Maximum value for the double-precision number
         */
        DOUBLE_BASE_MAX = bn_max_limit<base_double>()
    };
    
    // There is nothing in this class to instatiate
    ~bn_limits_t() = delete;
    bn_limits_t() = delete;
    bn_limits_t(const bn_limits_t&) = delete;
    bn_limits_t(bn_limits_t&&) = delete;
    bn_limits_t& operator=(const bn_limits_t&) = delete;
    bn_limits_t& operator=(bn_limits_t&&) = delete;
};



///////////////////////////////////////////////////////////////////////////////
// Extern template declarations and typedefs
///////////////////////////////////////////////////////////////////////////////
BN_DECLARE_STRUCT(bn_limits_t, bn_limits_lowp, BN_UINT8, BN_UINT16);
BN_DECLARE_STRUCT(bn_limits_t, bn_limits_medp, BN_UINT16, BN_UINT32);
BN_DECLARE_STRUCT(bn_limits_t, bn_limits_highp, BN_UINT32, BN_UINT64);

BN_DECLARE_STRUCT(bn_limits_t, bn_limits_base2, bn_base2_single, bn_base2_single);
BN_DECLARE_STRUCT(bn_limits_t, bn_limits_base8, bn_base8_single, bn_base8_single);
BN_DECLARE_STRUCT(bn_limits_t, bn_limits_base10, bn_base10_single, bn_base10_single);
BN_DECLARE_STRUCT(bn_limits_t, bn_limits_base16, bn_base16_single, bn_base16_single);

#endif	/* __BN_LIMITS_H__ */

