/* 
 * File:   compress_test.cpp
 * Author: Miles Lacey
 *
 * Created on Jun 30, 2014, 10:44:41 AM
 */

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

///////////////////////////////////////////////////////////////////////////////
// Get the number of bytes in a file
///////////////////////////////////////////////////////////////////////////////
std::ifstream::pos_type getNumBytes(std::ifstream& fin) {
    if (fin.fail() || fin.bad()) {
        std::cout << "File read error" << std::endl;
        return 0;
    }
    
    std::ifstream::pos_type currentPos = fin.tellg();
    fin.seekg(0, std::ifstream::end);
    std::ifstream::pos_type totalSize = fin.tellg();
    fin.seekg(currentPos, std::ifstream::beg);
    fin.clear();
    return totalSize;
}

///////////////////////////////////////////////////////////////////////////////
// Get a bignum that can compress (subtract) another bignum in a reasonable
// amount of time.
///////////////////////////////////////////////////////////////////////////////
bignum& setOptimalSubtractor(bignum::double_t numSubtracteeDigis, bignum& subtractor) {
    const bignum::double_t optimalSize = numSubtracteeDigis-1;
    subtractor.resize(optimalSize, bn_max_limit<bignum::single_t>());
    return subtractor;
}

///////////////////////////////////////////////////////////////////////////////
// Get a bignum that can compress (subtract) another bignum in a reasonable
// amount of time using the data from a file.
///////////////////////////////////////////////////////////////////////////////
const bignum getSubtractor(std::ifstream& fin) {
    bignum ret = {BN_POS, {bn_max_limit<bignum::single_t>()}};
    bignum::double_t fileSize = getNumBytes(fin);
    
    if (fileSize == 0) {
        ret.pop_back();
        return ret;
    }
    setOptimalSubtractor(fileSize, ret);
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
// compress the data within a file using bignums
///////////////////////////////////////////////////////////////////////////////
test_err_t compress(const std::string& filename, bignum& outNum, bignum::double_t& compressionSize) {
    bignum compressor;
    std::ifstream fin{filename, std::ifstream::binary | std::ifstream::in};
    
    if (!fin.good()) {
        return test_err_t::ERR_OPENING_FILE;
    }
    else {
        outNum = std::move(bignum{BN_POS, {0}});
    }
    
    while (fin.good()) {
        uint32_t c1 = (uint32_t)(fin.good() ? fin.get() : 0);
        c1 <<= 0;
        uint32_t c2 = (uint32_t)(fin.good() ? fin.get() : 0);
        c2 <<= 8;
        uint32_t c3 = (uint32_t)(fin.good() ? fin.get() : 0);
        c3 <<= 16;
        uint32_t c4 = (uint32_t)(fin.good() ? fin.get() : 0);
        c4 <<= 24;
        
        uint32_t digit = c1 | c2 | c3 | c4;
        outNum.push_back(digit);
    }
    
    fin.close();
    
    std::cout << "Compressing: " << filename << '.' << std::endl;
    std::cout << "Original size: " << outNum.size() << std::endl;
    
    std::cout << outNum << '\n' << std::endl;
    compressionSize = outNum.size();
    outNum -= setOptimalSubtractor(compressionSize, compressor);
    
    std::cout << "Compressed size: " << outNum.size() << std::endl;
    std::cout << outNum << '\n' << std::endl;
    
    return test_err_t::NO_FILE_ERR;
}

///////////////////////////////////////////////////////////////////////////////
// decompress (add) a bignum so that it returns the original data from a file.
///////////////////////////////////////////////////////////////////////////////
test_err_t decompress(const std::string& filename, bignum& inNum, bignum::double_t compressionSize) {
    (void)filename;
    bignum compressor = {};
    
    std::cout << "Decompressing: " << filename << ".\n";
    std::cout << "Compressed Size: " << inNum.size() << std::endl;
    
    std::cout << inNum << '\n' << std::endl;
    inNum += setOptimalSubtractor(compressionSize, compressor);
    
    std::cout << "Decompressed Size: " << inNum.size() << std::endl;
    std::cout << inNum << '\n' << std::endl;
    
    for (typename bignum::container_type::size_type i = 0; i < inNum.size(); ++i) {
        uint32_t digit = inNum[i];
        std::cout
            << (char)(digit >> 0)
            << (char)(digit >> 8)
            << (char)(digit >> 16)
            << (char)(digit >> 24);
    }
    
    std::cout << '\n' << std::endl;
    
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
    std::vector<std::string> argList = std::move(parseArgs(argc, argv));
    
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
    
    for (const std::string& arg : argList) {
        bignum num = {};
        bignum::double_t compressionSize = 0;
        
        compress(arg, num, compressionSize);
        decompress(arg, num, compressionSize);
    }
    
    return 0;
}

