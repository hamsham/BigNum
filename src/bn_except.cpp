/* 
 * File:   bn_except.cpp
 * Author: Miles Lacey
 * 
 * Created on June 24, 2014, 12:43 PM
 */

#include <iostream>

#include "bignum/bn_except.h"

///////////////////////////////////////////////////////////////////////////////
// BigNum Runtime Assertions.
///////////////////////////////////////////////////////////////////////////////
void bn_runtime_assert(bool condition, bn_error_t type, const char* const msg) {
	if (condition) {
        return;
    }

	const char* const errorString[] = {"ALERT: ", "WARNING: ", "ERROR: "};
    
	std::ostream& stream = (type > BN_ALERT) ? std::cerr : std::cout;

	stream << errorString[type] << msg << std::endl;

	if (type == BN_ERROR) {
        throw BN_ERROR;
    }
}

///////////////////////////////////////////////////////////////////////////////
// BigNum Exception types.
///////////////////////////////////////////////////////////////////////////////
/*
 * NaN Exception
 */
const char* bnNaN::what() const noexcept {
    return "Bignum NaN state reached.";
}

/*
 * NaN Exception
 */
const char* bnUnderflow::what() const noexcept {
    return "Attempted to subtract a larger bignum number from a smaller one.";
}

