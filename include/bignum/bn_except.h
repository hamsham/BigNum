/* 
 * File:   bn_except.h
 * Author: Miles Lacey
 *
 * Created on June 24, 2014, 12:43 PM
 */

#ifndef __BIGNUM_EXCEPT_H__
#define	__BIGNUM_EXCEPT_H__

#include <exception>

#include "bignum/bn_setup.h"

///////////////////////////////////////////////////////////////////////////////
// BigNum Runtime Assertions.
///////////////////////////////////////////////////////////////////////////////
/**
 * Runtime Assertion types that can be used to assist debugging.
 * These were borrowed with permission from:
 * 
 * http://githum.com/hamsham
 */
enum bn_error_t : int {
    BN_ALERT    = 0,
    BN_WARNING  = 1,
    BN_ERROR    = 2
};

/**
 * BigNum Assertion
 */
void bn_runtime_assert(bool eval, bn_error_t, const char* str);

/**
 * Basic Assertion Template
 */
#ifndef BN_ASSERT_BASIC
	#define BN_ASSERT_BASIC( x, fileName, lineNum, type )\
		bn_runtime_assert(\
			x, type,\
			"Assertion failed"\
            " on line " BN_STRINGIFY( lineNum )\
            " of " BN_STRINGIFY( fileName )\
            ": (" BN_STRINGIFY( x ) ")"\
		)
#endif /* BN_ASSERT_BASIC */

///////////////////////////////////////////////////////////////////////////////
// BigNum Assertion Macros.
///////////////////////////////////////////////////////////////////////////////
/**
 * Assertion Types
 */
#ifndef BN_ASSERT
	#define BN_ASSERT( x ) BN_ASSERT_BASIC( x, __FILE__, __LINE__, bn_error_t::BN_ERROR )
#endif /* ASSERT */

/**
 * Debug Assertion.
 * Prints an error to std::cerr and throws an exception.
 * Only used when the macro BN_DEBUG is enabled.
 */
#ifdef BN_DEBUG
    #ifndef BN_DEBUG_ASSERT
    	#define BN_DEBUG_ASSERT( x ) BN_ASSERT( x )
    #endif
#else
    #define BN_DEBUG_ASSERT
#endif /* DEBUG */

/**
 * Print a warning to std::cerr. Don't throw an exception
 */
#ifndef BN_WARN
	#define BN_WARN( x ) BN_ASSERT_BASIC( x, __FILE__, __LINE__, bn_error_t::BN_WARNING )
#endif /* ASSERT_WARN */

/**
 * Print an error message to std::cerr and throw an exception.
 */
#ifndef BN_ALERT
	#define BN_ALERT( x ) BN_ASSERT_BASIC( x, __FILE__, __LINE__, bn_error_t::BN_ALERT )
#endif /* ASSERT_ALERT */

///////////////////////////////////////////////////////////////////////////////
// BigNum Exception types.
///////////////////////////////////////////////////////////////////////////////
/**
 * BigNum NaN Exception.
 * 
 * This exception should be thrown when a number cannot reallocate or has run
 * out of memory.
 */
class BNNaN final : virtual public std::exception {
    public:
        BNNaN   ()                      noexcept = default;
        BNNaN   (const BNNaN&)          noexcept = default;
        BNNaN   (BNNaN&&)               noexcept = default;
        
        virtual ~BNNaN() = default;
        
        BNNaN&              operator=   (const BNNaN&)  noexcept = default;
        BNNaN&              operator=   (BNNaN&&)       noexcept = default;
        virtual const char* what        ()              const noexcept override;
};

/**
 * BigNum Subtraction underflow Exception.
 * 
 * This exception should be thrown internally only.
 * Throw this exception when subtracting a larger number from a smaller number.
 * 
 * The implementation only allows for smaller or equal numbers to be subtracted
 * from larger ones.
 */
class BNUnderflow final : virtual public std::exception {
    public:
        BNUnderflow         ()                      noexcept = default;
        BNUnderflow         (const BNUnderflow&)    noexcept = default;
        BNUnderflow         (BNUnderflow&&)         noexcept = default;
        
        virtual ~BNUnderflow() = default;
        
        BNUnderflow&        operator=   (const BNUnderflow&)    noexcept = default;
        BNUnderflow&        operator=   (BNUnderflow&&)         noexcept = default;
        virtual const char* what        ()                      const noexcept override;
};

#endif	/* __BIGNUM_EXCEPT_H__ */

