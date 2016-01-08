/* 
 * File:   arithmetic_basic.cpp
 * Author: Miles Lacey
 *
 * Created on June 18, 2014, 1:05 PM
 */

#include <iostream>

#include "bignum/bignum.h"

/*
 * Use with an std::ostream
 */
#define LOG_DEBUG_COMP(x, cmp, y)\
    x << BN_STRINGIFY(cmp) << y << ":\t" << (x cmp y)

#define CREATE_BN_TEST(bnType) \
void test_##bnType() { \
    std::cout \
        << "------------------------------------------------------------------\n" \
        << "\t\t\t" << BN_STRINGIFY(bnType) << '\n' \
        << "------------------------------------------------------------------\n" \
        << std::endl; \
    bnType testNum1 = {bn_desc_t::BN_NEG, {1, bn_max_limit<bnType::single_t>(), bn_max_limit<bnType::single_t>()}}; \
    bnType testNum2 = {bn_desc_t::BN_POS, {bn_min_limit<bnType::single_t>(), 1, bn_min_limit<bnType::single_t>()}}; \
    \
    std::cout << LOG_DEBUG_COMP(testNum1, >, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum1, >=, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum1, <, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum1, <=, testNum2) << std::endl; \
    std::cout << std::endl; \
    \
    std::cout << LOG_DEBUG_COMP(testNum1, +, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum1, -, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum1, *, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, +, testNum1) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, -, testNum1) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, *, testNum1) << std::endl; \
    std::cout << std::endl; \
     \
    testNum1.setDescriptor(BN_POS); \
    testNum2.setDescriptor(BN_NEG); \
     \
    std::cout << LOG_DEBUG_COMP(testNum1, >, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum1, >=, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum1, <, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum1, <=, testNum2) << std::endl; \
    std::cout << std::endl; \
     \
    std::cout << LOG_DEBUG_COMP(testNum1, +, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum1, -, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum1, *, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, +, testNum1) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, -, testNum1) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, *, testNum1) << std::endl; \
    std::cout << "\n\n" << std::endl; \
}

CREATE_BN_TEST(bignum_base2)
CREATE_BN_TEST(bignum_base8)
CREATE_BN_TEST(bignum_base10)
CREATE_BN_TEST(bignum_base16)

int main() {
    try {
        test_bignum_base2();
        test_bignum_base8();
        test_bignum_base10();
        test_bignum_base16();
    }
    catch(const std::exception& e) {
       std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
    return 0;
}

