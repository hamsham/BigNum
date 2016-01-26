/* 
 * File:   bn_type.cpp
 * Author: Miles Lacey
 * 
 * Created on July 24, 2014, 2:54 PM
 */

#include <iostream> // iostream operations

#include "bignum/bignum.h"

///////////////////////////////////////////////////////////////////////////////
// Bignum types
///////////////////////////////////////////////////////////////////////////////
BN_DEFINE_CLASS(Bignum, bn_limits_lowp, bn_default_container_t<bn_limits_lowp::base_single>);
BN_DEFINE_CLASS(Bignum, bn_limits_medp, bn_default_container_t<bn_limits_medp::base_single>);
BN_DEFINE_CLASS(Bignum, bn_limits_highp, bn_default_container_t<bn_limits_highp::base_single>);

BN_DEFINE_CLASS(Bignum, bn_limits_base2, bn_default_container_t<bn_limits_base2::base_single>);
BN_DEFINE_CLASS(Bignum, bn_limits_base8, bn_default_container_t<bn_limits_base8::base_single>);
BN_DEFINE_CLASS(Bignum, bn_limits_base10, bn_default_container_t<bn_limits_base10::base_single>);
BN_DEFINE_CLASS(Bignum, bn_limits_base16, bn_default_container_t<bn_limits_base16::base_single>);

