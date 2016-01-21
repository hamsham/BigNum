
/* 
 * File:   bn_compare.h
 * Author: miles
 *
 * Created on January 20, 2016, 8:36 PM
 */

#ifndef __BN_COMPARE_H__
#define __BN_COMPARE_H__



/**
 * Compare the raw numerical data contained within a bignum.
 * This function is not designed to compare a bignum's descriptors.
 * 
 * @param const container_type&
 * 
 * @param const container_type&
 * 
 * @return TRUE if the two parameters are equal in numerical value,
 * FALSE if otherwise.
 */
template <class container_type>
bool abs_val_is_eq(const container_type&, const container_type&);

/**
 * Determine if the first bignum container is greater than the second in
 * terms of numerical value.
 * This function is not designed to compare a bignum's descriptors.
 * 
 * @param const container_type&
 * 
 * @param const container_type&
 * 
 * @return TRUE if the first parameter is greater, in numerical value,
 * than the second parameter;
 * FALSE if otherwise.
 */
template <class container_type>
bool abs_val_is_gt(const container_type&, const container_type&);

/**
 * Determine if the first bignum container is greater than or equal to
 * the second in terms of numerical value.
 * This function is not designed to compare a bignum's descriptors.
 * 
 * @param const container_type&
 * 
 * @param const container_type&
 * 
 * @return TRUE if the first parameter is greater, in numerical value,
 * than or equal to the second parameter;
 * FALSE if otherwise.
 */
template <class container_type>
bool abs_val_is_ge(const container_type&, const container_type&);

/**
 * Determine if the first bignum container is less than the second in
 * terms of numerical value.
 * This function is not designed to compare a bignum's descriptors.
 * 
 * @param const container_type&
 * 
 * @param const container_type&
 * 
 * @return TRUE if the first parameter is less, in numerical value,
 * than the second parameter;
 * FALSE if otherwise.
 */
template <class container_type>
bool abs_val_is_lt(const container_type&, const container_type&);

/**
 * Determine if the first bignum container is less than or equal to
 * the second in terms of numerical value.
 * This function is not designed to compare a bignum's descriptors.
 * 
 * @param const container_type&
 * 
 * @param const container_type&
 * 
 * @return TRUE if the first parameter is less, in numerical value,
 * than or equal to the second parameter;
 * FALSE if otherwise.
 */
template <class container_type>
bool abs_val_is_le(const container_type&, const container_type&);



#include "bignum/impl/bn_compare_impl.h"



#endif /* __BN_COMPARE_H__ */
