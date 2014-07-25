/* 
 * File:   bn_limits.h
 * Author: Miles Lacey
 *
 * Created on July 18, 2014, 9:23 PM
 */

#ifndef __BN_LIMITS_H__
#define	__BN_LIMITS_H__

#include <limits>

#include "bn_setup.h"

///////////////////////////////////////////////////////////////////////////////
// Custom implementation of std::numeric_limits<>
///////////////////////////////////////////////////////////////////////////////

typedef BN_UINT64 bn_limit_t;

/**
 * Empty numeric limit prototype.
 * 
 * @return a 64-bit integer, representing the minimum value allowable by the
 * input type.
 */
template<typename T>
constexpr bn_limit_t bn_min_limit();

/**
 * Empty numeric limit prototype.
 * 
 * @return a 64-bit integer, representing the maximum value allowable by the
 * input type.
 */
template<typename T>
constexpr bn_limit_t bn_max_limit();

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
constexpr bn_limit_t bn_min_limit<BN_UINT8>();

/**
 * Numeric maximum for an 8-bit integer
 * 
 * @return a 64-bit integer, representing the maximum value allowable by the
 * input type.
 */
template<>
constexpr bn_limit_t bn_max_limit<BN_UINT8>();

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
constexpr bn_limit_t bn_min_limit<BN_UINT16>();

/**
 * Numeric maximum for a 16-bit integer
 * 
 * @return a 64-bit integer, representing the maximum value allowable by the
 * input type.
 */
template<>
constexpr bn_limit_t bn_max_limit<BN_UINT16>();

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
constexpr bn_limit_t bn_min_limit<BN_UINT32>();

/**
 * Numeric maximum for a 32-bit integer
 * 
 * @return a 64-bit integer, representing the maximum value allowable by the
 * input type.
 */
template<>
constexpr bn_limit_t bn_max_limit<BN_UINT32>();

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
constexpr bn_limit_t bn_min_limit<BN_UINT64>();

/**
 * Numeric maximum for a 64-bit integer
 * 
 * @return a 64-bit integer, representing the maximum value allowable by the
 * input type.
 */
template<>
constexpr bn_limit_t bn_max_limit<BN_UINT64>();

#include "impl/bn_limits_impl.h"

#endif	/* __BN_LIMITS_H__ */

