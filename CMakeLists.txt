cmake_minimum_required(VERSION 3.0.2)

project("BigNum" CXX)
set(BN_OUTPUT_NAME "bignum")



# -------------------------------------
# Compiler Options
# -------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    set(BN_COMPILER_WARNINGS "-Wall -Werror -Wextra -pedantic -pedantic-errors")
    set(BN_COMMON_COMPILER_FLAGS "")
    set(BN_C_COMPILER_FLAGS "-std=c99 ${BN_COMMON_COMPILER_FLAGS} ${BN_COMPILER_WARNINGS}")
    set(BN_CXX_COMPILER_FLAGS "-std=c++11 ${BN_COMMON_COMPILER_FLAGS} ${BN_COMPILER_WARNINGS}")

    # Tested on Linux, all static libraries need to be compiled with the -fPIC
    # flag in order to be linked into shared libs. This is going to destroy all
    # benchmarks due to extra assembly instructions being compiled in.
    if(NOT WIN32 AND NOT BUILD_SHARED_LIBS)
        set(BN_C_COMPILER_FLAGS "${BN_C_COMPILER_FLAGS} -fPIC")
        set(BN_CXX_COMPILER_FLAGS "${BN_CXX_COMPILER_FLAGS} -fPIC")
    endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

    set(BN_COMPILER_WARNINGS "/Wall /sdl /W3 /WX")
    set(BN_COMMON_COMPILER_FLAGS "/Za /Zc:rvalueCast /Zc:strictStrings /Zc:inline")
    set(BN_C_COMPILER_FLAGS "${BN_COMMON_COMPILER_FLAGS} ${BN_COMPILER_WARNINGS}")
    set(BN_CXX_COMPILER_FLAGS "${BN_COMMON_COMPILER_FLAGS} ${BN_COMPILER_WARNINGS}")

else()

    message(FATAL_ERROR "Your compiler is currently unsupported: ${CMAKE_CXX_COMPILER_ID}")

endif()

#add_definitions(${BN_C_COMPILER_FLAGS})
add_definitions(${BN_CXX_COMPILER_FLAGS})



# -------------------------------------
# Header Files & Search Paths
# -------------------------------------
include_directories("include")



# -------------------------------------
# Source Files
# -------------------------------------
set(BN_SOURCES
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
