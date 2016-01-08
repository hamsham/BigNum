/* 
 * File:   bn_limits.cpp
 * Author: Miles Lacey
 * 
 * Created on July 18, 2014, 9:23 PM
 */

#include "bignum/bn_limits.h"

///////////////////////////////////////////////////////////////////////////////
// Bignum types
///////////////////////////////////////////////////////////////////////////////
BN_DEFINE_CLASS(bn_limits_t, BN_UINT8, BN_UINT16);
BN_DEFINE_CLASS(bn_limits_t, BN_UINT16, BN_UINT32);
BN_DEFINE_CLASS(bn_limits_t, BN_UINT32, BN_UINT64);

BN_DEFINE_CLASS(bn_limits_t, bn_base2_single, bn_base2_single);
BN_DEFINE_CLASS(bn_limits_t, bn_base8_single, bn_base8_single);
BN_DEFINE_CLASS(bn_limits_t, bn_base10_single, bn_base10_single);
BN_DEFINE_CLASS(bn_limits_t, bn_base16_single, bn_base16_single);
