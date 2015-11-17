/* 
 * File:   bignum_setup.h
 * Author: Miles Lacey
 *
 * Created on June 18, 2014, 1:42 PM
 */

#ifndef __BIGNUM_SETUP_H__
#define	__BIGNUM_SETUP_H__

#if __cplusplus < 201103L
    #error "This library requires a fully C++11-compliant compiler."
#endif

#include <cstdint>

/**
 * Preprocessor String Macro
 */
#ifndef BN_STRINGIFY
    #define BN_STRINGIFY(x) #x
#endif

/**
 * Macro to allow for templated classes to be declared in header files without
 * any instantiations.
 */
#define BN_DECLARE_CLASS(type, nickname, ...)\
    extern template class type<__VA_ARGS__>;\
    typedef type<__VA_ARGS__> nickname

/**
 * Macro to allow for templated classes to be defined/instantiated in a single
 * compilation unit.
 */
#define BN_DEFINE_CLASS(type, ...)\
    template class type<__VA_ARGS__>

/*
 * Fixed-sized types that are used for built-in bignum types
 */
typedef uint8_t BN_UINT8;
typedef uint16_t BN_UINT16;
typedef uint32_t BN_UINT32;
typedef uint64_t BN_UINT64;

// Default single-precision type
typedef BN_UINT32 BN_SINGLE;

// default double-precision type
typedef BN_UINT64 BN_DOUBLE;

#endif	/* __BIGNUM_SETUP_H__ */

