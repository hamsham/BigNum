/* 
 * File:   compress_test.cpp
 * Author: Miles Lacey
 *
 * Created on Jun 30, 2014, 10:44:41 AM
 */

#include <climits> // CHAR_BIT
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "bignum/bignum.h"

#ifndef BN_TEST_FILE
    #define BN_TEST_FILE nullptr
#endif

struct fileInfo {
    uint64_t numCompressions = {0};
    bignum fileData = {BN_POS, {0}};
};

enum class test_err_t : int {
    ERR_INVALID_FILE,
    ERR_OPENING_FILE,
    ERR_CLOSING_FILE,
    
    NO_FILE_ERR
};

BN_DECLARE_CLASS(BNIntType, bn_base256_single, BN_UINT16, 256);
BN_DECLARE_CLASS(BNIntType, bn_base256_double, BN_UINT32, 256);

BN_DEFINE_CLASS(BNIntType, BN_UINT16, 256);
BN_DEFINE_CLASS(BNIntType, BN_UINT32, 256);

template <>
constexpr bn_u64_t bn_min_limit<bn_base256_single>() {return 0;}
template <>
constexpr bn_u64_t bn_max_limit<bn_base256_single>() {return 255;}

template <>
constexpr bn_u64_t bn_min_limit<bn_base256_double>() {return 0;}
template <>
constexpr bn_u64_t bn_max_limit<bn_base256_double>() {return 511;}

BN_DECLARE_STRUCT(BNLimitsType, bn_limits_base256, bn_base256_single, bn_base256_single);
BN_DEFINE_STRUCT(BNLimitsType,                     bn_base256_single, bn_base256_single);

BN_DECLARE_CLASS(Bignum, bignum_base256, bn_limits_base256, bn_default_container_t<bn_limits_base256::base_single>);
BN_DEFINE_CLASS(Bignum,                  bn_limits_base256, bn_default_container_t<bn_limits_base256::base_single>);

///////////////////////////////////////////////////////////////////////////////
// Read a file
///////////////////////////////////////////////////////////////////////////////
test_err_t read_file(const std::string filename, std::string& outData)
{
    std::ifstream fin{filename, std::ifstream::binary | std::ifstream::in | std::ifstream::ate};

    if (!fin.good()) {
        return test_err_t::ERR_OPENING_FILE;
    }
    else {
        const std::size_t size = fin.tellg();
        fin.seekg(0, std::ios_base::beg);

        outData.resize(size, 0);

        fin.read(&outData[0], size);
    }


    fin.close();

    return test_err_t::NO_FILE_ERR;
}

///////////////////////////////////////////////////////////////////////////////
// compress the data within a file using bignums
///////////////////////////////////////////////////////////////////////////////
test_err_t compress(const std::string& filename, bignum_base256& outNum, std::size_t& inSize, uint16_t& numLastBits)
{
    std::cout << "Compressing: " << filename << '.' << std::endl;
    std::cout << "Original size: " << filename.size() << std::endl;

    inSize = filename.size();
    bignum_base256 inNum = bignum_base256{BN_POS, {}};

    for (typename std::string::const_iterator i = filename.cbegin(); i != filename.cend(); ++i)
    {
        const char c = *i;
        inNum.push_back((uint16_t)c);
    }
    inNum.push_back('\0');

    const bignum_base256 divisor{BN_POS, {2}};
    uint16_t digit = 0;
    std::size_t numBitsUsed = 0;

    while (inNum.size() != 1 || inNum.numData[0] > bn_base256_single{1})
    {
        uint16_t remainder = (inNum.numData[0] % bn_base256_single{2}) ? 1 : 0;
        digit = digit | (remainder << numBitsUsed);

        if (++numBitsUsed == sizeof(uint16_t) * CHAR_BIT)
        {
            numBitsUsed = 0;
            outNum.push_back(digit);
            digit = 0;
        }

        inNum /= divisor;
    }

    // input number has a single digit left
    {
        uint16_t remainder = (inNum.numData[0] % bn_base256_single{2}) ? 1 : 0;
        digit = digit | (remainder << numBitsUsed);
        ++numBitsUsed;
        outNum.push_back(digit);

    }

    numLastBits = numBitsUsed;

    std::cout << "Compressed size: " << outNum.size() << std::endl;
    std::cout << "Compressed Num: " << outNum << '\n' << std::endl;
    
    return test_err_t::NO_FILE_ERR;
}

///////////////////////////////////////////////////////////////////////////////
// decompress (add) a bignum so that it returns the original data from a file.
///////////////////////////////////////////////////////////////////////////////
test_err_t decompress(const std::string& filename, const bignum_base256& inNum, std::size_t inSize, uint16_t numLastBits) {
    std::cout << "Decompressing: " << filename << ".\n";
    std::cout << "Compressed Size: " << inNum.size() << ' ' << numLastBits << std::endl;
    std::cout << inNum << '\n' << std::endl;

    bignum_base256 outNum = bignum_base256{BN_POS, {0}};
    const bignum_base256 divisor{BN_POS, {2}};
    std::size_t iter = inNum.size();
    std::size_t numBitsUsed = numLastBits;

    while (iter > 0 && numBitsUsed > 0)
    {
        --numBitsUsed;
        bignum_base256 digit{BN_POS, {(uint16_t)(((int)inNum.numData[iter-1] >> numBitsUsed) & 1)}};

        outNum = (outNum * divisor) + digit;

        if (!numBitsUsed)
        {
            numBitsUsed = (sizeof(uint16_t) * CHAR_BIT);
            --iter;
        }
    }

    std::cout << "Decompressed Size: " << outNum.size() << std::endl;
    std::cout << "Reference Size: " << inSize << std::endl;

    for (bn_base256_single c : outNum.numData)
    {
        std::cout << (char)c;
    }
    std::cout << std::endl;

    std::cout << outNum << std::endl;
    
    return test_err_t::NO_FILE_ERR;
}

///////////////////////////////////////////////////////////////////////////////
// parse the arguments passed into main()
///////////////////////////////////////////////////////////////////////////////
std::vector<std::string> parseArgs(int argc, char** argv) {
    std::vector<std::string> argList;
    
    for (int i = 1; i < argc; ++i) {
        std::string inArg = argv[i];
        
        argList.emplace_back(inArg);
    }
    
    return argList;
}

///////////////////////////////////////////////////////////////////////////////
// Main
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
    #if 1
    std::vector<std::string> argList = std::move(parseArgs(argc, argv));
    //argList.emplace_back(std::string{__FILE__});
    
    if (argList.empty()) {
        if (BN_TEST_FILE == nullptr) {
            std::cerr << "No sample file provided to the compression test." << std::endl;
            return -1;
        }
        else {
            argList.emplace_back(std::string{BN_TEST_FILE});
        }
    }
    
    std::cout << "Attempting to compress and decompress the following files:";
    for (const std::string& arg : argList) {
        std::cout << "\n\t" << arg;
    }
    std::cout << std::endl;


    for (const std::string& inFile : argList) {
        std::string fileData;

        if (read_file(inFile, fileData) != test_err_t::NO_FILE_ERR)
        {
            std::cerr << "Unable to open the file " << inFile << " for reading." << std::endl;
        }

        bignum_base256 num = {BN_POS, {}};
        num.numData.clear(); // insurance

        std::size_t compression = 0;
        uint16_t lastBits = 0;

        compress(fileData, num, compression, lastBits);
        decompress(inFile, num, compression, lastBits);
    }

    #else
    (void)argc;
    (void)argv;
    bignum_base256 num = {BN_POS, {0}};
    num.numData.clear(); // insurance

    std::size_t compression = 0;
    uint16_t lastBits = 0;

    std::string testString{"Hello World!"};

    compress(testString, num, compression, lastBits);
    decompress(testString, num, compression, lastBits);

    #endif
    
    return 0;
}

