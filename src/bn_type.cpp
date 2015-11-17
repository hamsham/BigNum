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
BN_DEFINE_CLASS(bn_type, BN_UINT8, BN_UINT16);
BN_DEFINE_CLASS(bn_type, BN_UINT16, BN_UINT32);
BN_DEFINE_CLASS(bn_type, BN_UINT32, BN_UINT64);

BN_DEFINE_CLASS(bn_type, bn_base2_single, bn_base2_single);
BN_DEFINE_CLASS(bn_type, bn_base8_single, bn_base8_single);
BN_DEFINE_CLASS(bn_type, bn_base10_single, bn_base10_single);
BN_DEFINE_CLASS(bn_type, bn_base16_single, bn_base16_single);

