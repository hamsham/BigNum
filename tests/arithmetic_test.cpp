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
    bnType testNum1 = {bn_desc_t::BN_NEG, {1, bn_max_limit<bnType::bn_single>(), bn_max_limit<bnType::bn_single>()}}; \
    bnType testNum2 = {bn_desc_t::BN_POS, {bn_min_limit<bnType::bn_single>(), 1, bn_min_limit<bnType::bn_single>()}}; \
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
    std::cout << LOG_DEBUG_COMP(testNum1, /, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, +, testNum1) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, -, testNum1) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, *, testNum1) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, /, testNum1) << std::endl; \
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
    std::cout << LOG_DEBUG_COMP(testNum1, /, testNum2) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, +, testNum1) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, -, testNum1) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, *, testNum1) << std::endl; \
    std::cout << LOG_DEBUG_COMP(testNum2, /, testNum1) << std::endl; \
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

        bignum_base10 a{BN_POS, {0, 1, 3, 4, 7, 9, 8, 4, 3, 1, 7, 6, 0, 9, 3, 7, 5, 6, 8, 3, 6, 1, 0, 9, 0, 6, 4, 2, 6, 3, 6, 7, 3, 6, 4, 2, 5}};
        std::cout << a << std::endl;
        bignum_base10 b{BN_POS, {2, 5, 8, 5, 9, 0, 0, 1, 6, 3, 8, 6, 7, 6, 7, 3, 4, 2, 7, 3, 8, 0, 9, 1, 2, 5}};
        std::cout << b << std::endl;

        a += b;
        std::cout << a << std::endl;
        a -= b;
        std::cout << a << std::endl;
        a *= b;
        std::cout << a << std::endl;
        a /= b;
        std::cout << a << std::endl;
    }
    catch(const std::exception& e) {
       std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
    return 0;
}

