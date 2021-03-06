/* 
 * File:   bn_multiplication_impl.h
 * Author: elacey
 *
 * Created on January 15, 2016, 10:02 AM
 */

#include "bignum/fourier.h"



///////////////////////////////////////////////////////////////////////////////
// FFT-based multiplication
///////////////////////////////////////////////////////////////////////////////
template <typename limits_t, typename container_t>
container_t mul_strassen(const container_t& a, const container_t& b) {
    // Default type is double. Use floats if they perform well enough.
    typedef double flt_t;
    typedef typename limits_t::base_double bn_double;
    typedef typename container_t::size_type big_size_type;
    static constexpr bn_double NUM_BASE = bn_double{limits_t::SINGLE_BASE_MAX+1};
    
	// building a complex signal with the information of both signals.
    cmplx_list_t<flt_t> fftTable = std::move(create_fft_table<container_t, flt_t>(a, b));
    
    convolute_fft<flt_t>(fftTable);
    ifft_complex<flt_t>(fftTable);
    
    const cmplx_list_t<flt_t>& inverses = fftTable;
    
    container_t ret;
    ret.reserve(inverses.size());

    for (cmplx_size_t<flt_t> i = 0, c = 0; i < inverses.size(); ++i) {
        // drop imaginary part of the number
        const flt_t x = inverses[i].real();
        
        // round to an integer
        const bn_double ci = (bn_double)(c + std::floor(x + 0.5));
        
        ret.push_back(ci % NUM_BASE);

        // carry propagation
        c = (ci / NUM_BASE);
    }
    
    // trim trailing zeroes from the most-significant digits
    big_size_type numZeroes = 0;
    
    for (big_size_type i = ret.size(); i --> 0;) {
        if (ret[i]) {
            break;
        }
        
        ++numZeroes;
    }
    
    ret.resize(ret.size() - numZeroes);

    return ret;
}



///////////////////////////////////////////////////////////////////////////////
// Naive Multiplication
///////////////////////////////////////////////////////////////////////////////
template <typename limits_t, typename container_t>
container_t mul_naive(const container_t& a, const container_t& b) {
    typedef typename limits_t::base_double bn_double;
    typedef typename container_t::size_type big_size_type;
    static constexpr bn_double NUM_BASE = (bn_double)limits_t::SINGLE_BASE_MAX+(bn_double)1;
    
    container_t ret{};
    
    const big_size_type totalLen = a.size() + b.size();
    
    if (!totalLen) {
        return ret;
    }
    
    ret.resize(totalLen);
    
    for (unsigned i = 0; i < b.size(); ++i) {
        unsigned remainder = 0;
        
        for (unsigned j = 0; j < a.size(); ++j) {
            const big_size_type index = i + j;
            ret[index] += remainder + a[j] * b[i];
            remainder = ret[index] / NUM_BASE;
            ret[index] = ret[index] % NUM_BASE;
        }
        
        ret[i+a.size()] += remainder;
    }
    
    return ret;
}

