
/* 
 * File:   bn_addition.h
 * Author: miles
 *
 * Created on January 7, 2016, 10:56 PM
 */

#ifndef __BN_ADDITION_H__
#define __BN_ADDITION_H__


        
/**
 * Add a number into the first parameter.
 * This function is not designed to compare a bignum's descriptors.
 * 
 * @param The bignum_type where all numerical values will be
 * accumulated.
 * 
 * @param A number to add into the first.
 */
template <typename container_type>
void absValAdd(container_type&, const container_type&);



#include "bignum/impl/bn_addition_impl.h"



#endif /* __BN_ADDITION_H__ */
