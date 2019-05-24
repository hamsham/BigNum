
/* 
 * File:   bn_division.h
 * Author: miles
 *
 * Created on January 7, 2016, 10:56 PM
 */

#ifndef __BN_DIVISION_H__
#define __BN_DIVISION_H__


        
/**
 * Divide one number by the second parameter.
 * This function is not designed to compare a bignum's descriptors.
 * 
 * @param The bignum_type where all numerical values will be
 * divided.
 * 
 * @param The divisor.
 */
template <typename limits_t, typename container_t>
void abs_val_div(container_t& outNum, const container_t& inNum);



#include "bignum/impl/bn_division_impl.h"



#endif /* __BN_DIVISION_H__ */
