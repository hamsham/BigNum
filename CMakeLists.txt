cmake_minimum_required(VERSION 3.0.2)

project("BigNum" CXX)
set(CMAKE_CXX_STANDARD 11)

set(BN_OUTPUT_NAME "bignum")



# -------------------------------------
# Compiler Options
# -------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_definitions(-Wall)
    add_definitions(-Werror)
    add_definitions(-Wextra)
    add_definitions(-pedantic)
    add_definitions(-pedantic-errors)

    # Tested on Linux, all static libraries need to be compiled with the -fPIC
    # flag in order to be linked into shared libs. This is going to destroy all
    # benchmarks due to extra assembly instructions being compiled in.
    if(NOT WIN32 AND NOT BUILD_SHARED_LIBS)
        add_definitions(-fPIC)
    endif()
      
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_definitions(/Zc:__cplusplus)
    add_definitions(/Wall)
    add_definitions(/sdl-)
    add_definitions(/W3)
    add_definitions(/WX)
    add_definitions(/permissive-) # enable conformance mode
    add_definitions(/Za)
    add_definitions(/Zc:rvalueCast)
    add_definitions(/Zc:strictStrings)
    add_definitions(/Zc:inline)
    
else()
    message(FATAL_ERROR "Your compiler is currently unsupported: ${CMAKE_CXX_COMPILER_ID}")

endif()



# -------------------------------------
# Header Files & Search Paths
# -------------------------------------
include_directories("include")



# -------------------------------------
# Source Files
# -------------------------------------
set(BN_SOURCES
    "include/bignum/bignum.h"
    "include/bignum/bn_addition.h"
    "include/bignum/bn_compare.h"
    "include/bignum/bn_except.h"
    "include/bignum/bn_int_type.h"
    "include/bignum/bn_limits.h"
    "include/bignum/bn_multiplication.h"
    "include/bignum/bn_setup.h"
    "include/bignum/bn_subtraction.h"
    "include/bignum/bn_type.h"
    "include/bignum/fourier.h"
    "include/bignum/impl/bn_addition_impl.h"
    "include/bignum/impl/bn_compare_impl.h"
    "include/bignum/impl/bn_int_type_impl.h"
    "include/bignum/impl/bn_limits_impl.h"
    "include/bignum/impl/bn_multiplication_impl.h"
    "include/bignum/impl/bn_subtraction_impl.h"
    "include/bignum/impl/bn_type_impl.h"
    "include/bignum/impl/fourier_impl.h"

    "src/bignum.cpp"
    "src/bn_except.cpp"
    "src/bn_int_type.cpp"
    "src/bn_limits.cpp"
    "src/bn_setup.cpp"
    "src/bn_type.cpp"
)



# -------------------------------------
# Library Setup
# -------------------------------------
add_library("${BN_OUTPUT_NAME}" "${BN_SOURCES}")
install(DIRECTORY "include/bignum" DESTINATION "include/bignum")
install(TARGETS "${BN_OUTPUT_NAME}"
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION bin
)



# -------------------------------------
# Tests
# -------------------------------------
set(BN_BUILD_TESTS TRUE CACHE BOOL "Build tests for the BigNum library.")

if(BN_BUILD_TESTS)
    enable_testing()
    add_subdirectory("tests")
endif()
