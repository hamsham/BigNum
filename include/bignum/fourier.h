/* 
 * File:   fourier.h
 * Author: elacey
 *
 * Created on January 15, 2016, 11:29 AM
 */

#ifndef __BN_FOURIER_H__
#define	__BN_FOURIER_H__

#include <complex>
#include <vector>

#include "bignum/bn_setup.h"



template <typename flt_t>
using cmplx_list_t = std::vector<std::complex<flt_t>>;

template <typename flt_t>
using cmplx_size_t = typename cmplx_list_t<flt_t>::size_type;

template <typename flt_t>
using cmplx_value_t = typename cmplx_list_t<flt_t>::value_type;



template <typename flt_t>
void fft(cmplx_list_t<flt_t>& x);

template <typename flt_t>
void ifft(cmplx_list_t<flt_t>& x);

template <typename container_t, typename flt_t>
cmplx_list_t<flt_t> create_fft_table(const container_t& a, const container_t& b);

template <typename flt_t>
void convolute_fft(cmplx_list_t<flt_t>& fftTable);



#include "bignum/impl/fourier_impl.h"

#endif	/* __BN_FOURIER_H__ */

