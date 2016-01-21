/* 
 * File:   bn_subtraction.h
 * Author: elacey
 *
 * Created on January 15, 2016, 9:25 AM
 */

#ifndef __BN_SUBTRACTION_H__
#define	__BN_SUBTRACTION_H__



/**
 * Subtract a number from the first parameter.
 * The output parameter MUST be greater than the input, in both size and
 * numerical value.
 * This function is not designed to compare a bignum's descriptors.
 * 
 * @param The bignum_type where all numerical values will be
 * accumulated. This value MUST have an absolute value that is greater
 * than or equal to the second parameter.
 * 
 * @param A number to subtract from the first. This value MUST have an
 * absolute value that is less than or equal to the first parameter.
 */
template <typename limits_t, typename container_t>
void absValSub(container_t& largerNum, const container_t& smallerNum);



#include "bignum/impl/bn_subtraction_impl.h"



#endif	/* __BN_SUBTRACTION_H__ */

