
# -------------------------------------
# Test Setup
# -------------------------------------
project(bignum_tests CXX)



# -------------------------------------
# Header/Include Paths
# -------------------------------------
include_directories(".")



# -------------------------------------
# Dependency setup
# -------------------------------------
set(BN_TEST_DEPS
    bignum
)



# -------------------------------------
# Test Definitions
# -------------------------------------
set(BN_TEST_FILE "${PROJECT_SOURCE_DIR}/test_file.cpp" CACHE STRING "Sample file to test for use as a bignum.")
add_definitions(-DBN_TEST_FILE="${BN_TEST_FILE}")



# -------------------------------------
# Building and Linkins Targets
# -------------------------------------
function(bn_add_test testname srcfile)
    add_executable(${testname} ${srcfile})
    add_dependencies(${testname} ${BN_TEST_DEPS})
    target_link_libraries(${testname} ${BN_TEST_DEPS})
    add_test(${testname} ${testname})
endfunction(bn_add_test)


bn_add_test(bn_integer_test integer_test.cpp)
bn_add_test(bn_arithmetic_test arithmetic_test.cpp)

bn_add_test(bn_compress_test compress_test.cpp)
configure_file(test_file.cpp test_file.cpp COPYONLY)
