/* 
 * File:   bn_int_type.cpp
 * Author: A435534a
 * 
 * Created on July 18, 2014, 1:01 PM
 */

#include "bn_setup.h"
#include "bn_limits.h"
#include "bn_int_type.h"

///////////////////////////////////////////////////////////////////////////////
// Integral types for bignum specialization.
///////////////////////////////////////////////////////////////////////////////
BN_DEFINE_CLASS(bn_int_type, BN_UINT8, bn_max_limit<BN_UINT8>());
BN_DEFINE_CLASS(bn_int_type, BN_UINT16, bn_max_limit<BN_UINT16>());
BN_DEFINE_CLASS(bn_int_type, BN_UINT32, bn_max_limit<BN_UINT32>());

BN_DEFINE_CLASS(bn_int_type, BN_UINT8, 2);
BN_DEFINE_CLASS(bn_int_type, BN_UINT16, 2);

BN_DEFINE_CLASS(bn_int_type, BN_UINT16, 8);
BN_DEFINE_CLASS(bn_int_type, BN_UINT32, 8);

BN_DEFINE_CLASS(bn_int_type, BN_UINT32, 10);
BN_DEFINE_CLASS(bn_int_type, BN_UINT64, 10);

BN_DEFINE_CLASS(bn_int_type, BN_UINT32, 16);
BN_DEFINE_CLASS(bn_int_type, BN_UINT64, 16);
