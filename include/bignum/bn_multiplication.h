/* 
 * File:   bn_multiplication.h
 * Author: elacey
 *
 * Created on January 15, 2016, 10:02 AM
 */

#ifndef __BN_MULTIPLICATION_H__
#define	__BN_MULTIPLICATION_H__



/**
 * Perform multiplication on two numbers using an FFT and return their product.
 * 
 * @param A container, managed by a container_t_t class, which will be multiplied.
 * 
 * @param A container, managed by a container_t_t class, which will be multiplied.
 * 
 * @return The product of both input numbers.
 */
template <typename limits_t, typename container_t>
container_t mul_strassen(const container_t& a, const container_t& b);



/**
 * Perform multiplication on two numbers and return their product.
 * 
 * @param A container, managed by a container_t_t class, which will be multiplied.
 * 
 * @param A container, managed by a container_t_t class, which will be multiplied.
 * 
 * @return The product of both input numbers.
 */
template <typename limits_t, typename container_t>
container_t mul_naive(const container_t& a, const container_t& b);



#include "bignum/impl/bn_multiplication_impl.h"



#endif	/* __BN_MULTIPLICATION_H__ */

