/* 
 * File:   bignum.h
 * Author: Miles Lacey
 *
 * Created on July 18, 2014, 12:43 PM
 */

#ifndef __BIGNUM_H__
#define	__BIGNUM_H__

#include <vector>

#include "bignum/bn_setup.h"
#include "bignum/bn_limits.h"
#include "bignum/bn_except.h"
#include "bignum/bn_int_type.h"
#include "bignum/bn_type.h"



///////////////////////////////////////////////////////////////////////////////
//          Typedefs Requiring Class Definitions
///////////////////////////////////////////////////////////////////////////////
template <typename data_t, class allocator = std::allocator<data_t>>
using bn_default_container_t = std::vector<data_t, allocator>;

///////////////////////////////////////////////////////////////////////////////
// Extern template declarations and typedefs
// 
// These are defined in the source file "bn_type.cpp"
///////////////////////////////////////////////////////////////////////////////
BN_DECLARE_CLASS(Bignum, bignum_lowp, bn_limits_lowp, bn_default_container_t<bn_limits_lowp::base_single>);
BN_DECLARE_CLASS(Bignum, bignum_medp, bn_limits_medp, bn_default_container_t<bn_limits_medp::base_single>);
BN_DECLARE_CLASS(Bignum, bignum_highp, bn_limits_highp, bn_default_container_t<bn_limits_highp::base_single>);

BN_DECLARE_CLASS(Bignum, bignum_base2, bn_limits_base2, bn_default_container_t<bn_limits_base2::base_single>);
BN_DECLARE_CLASS(Bignum, bignum_base8, bn_limits_base8, bn_default_container_t<bn_limits_base8::base_single>);
BN_DECLARE_CLASS(Bignum, bignum_base10, bn_limits_base10, bn_default_container_t<bn_limits_base10::base_single>);
BN_DECLARE_CLASS(Bignum, bignum_base16, bn_limits_base16, bn_default_container_t<bn_limits_base16::base_single>);

/**
 * Default-precision bignum
 */
typedef bignum_highp bignum;



#endif	/* __BIGNUM_H__ */

