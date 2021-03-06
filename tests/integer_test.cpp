/* 
 * File:   integer_test.cpp
 * Author: Miles Lacey
 *
 * Created on Jul 18, 2014, 7:22:08 PM
 */

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "bignum/bignum.h"

#define PRINT_TEST(x, op, y) \
    std::cout << x << BN_STRINGIFY(op) << y << "=" << (x op y) << std::endl

/*
 * Setup typedefs to make it easier to change test parameters
 */
typedef unsigned int_base_type;
typedef BNIntType<int_base_type, 0> int_type;

template class BNIntType<unsigned char, 0>;
template class BNIntType<unsigned short, 0>;
template class BNIntType<unsigned int, 0>;
template class BNIntType<unsigned long, 0>;
template class BNIntType<unsigned long long, 0>;

/**
 * Generate a random integral value based on the current test type
 */
int_base_type getRandInt() {
    return rand() % 101;
}

/*
 * Main()
 */
int main() {
    srand(time(nullptr));
    
    int_base_type basicInt = getRandInt();
    int_type testInt = getRandInt();
    
    PRINT_TEST(basicInt, +, testInt);
    PRINT_TEST(basicInt, -, testInt);
    PRINT_TEST(basicInt, *, testInt);
    PRINT_TEST(basicInt, /, testInt);
    PRINT_TEST(basicInt, %, testInt);
    PRINT_TEST(basicInt, &, testInt);
    PRINT_TEST(basicInt, |, testInt);
    PRINT_TEST(basicInt, ^, testInt);
    PRINT_TEST(basicInt, <<, testInt);
    PRINT_TEST(basicInt, >>, testInt);
    PRINT_TEST(basicInt, >, testInt);
    PRINT_TEST(basicInt, <, testInt);
    PRINT_TEST(basicInt, >=, testInt);
    PRINT_TEST(basicInt, <=, testInt);
    PRINT_TEST(basicInt, ==, testInt);
    PRINT_TEST(basicInt, !=, testInt);
    
    PRINT_TEST(testInt, +, basicInt);
    PRINT_TEST(testInt, -, basicInt);
    PRINT_TEST(testInt, *, basicInt);
    PRINT_TEST(testInt, /, basicInt);
    PRINT_TEST(testInt, %, basicInt);
    PRINT_TEST(testInt, &, basicInt);
    PRINT_TEST(testInt, |, basicInt);
    PRINT_TEST(testInt, ^, basicInt);
    PRINT_TEST(testInt, <<, basicInt);
    PRINT_TEST(testInt, >>, basicInt);
    PRINT_TEST(testInt, >, basicInt);
    PRINT_TEST(testInt, <, basicInt);
    PRINT_TEST(testInt, >=, basicInt);
    PRINT_TEST(testInt, <=, basicInt);
    PRINT_TEST(testInt, ==, basicInt);
    PRINT_TEST(testInt, !=, basicInt);
    
    return 0;
}

