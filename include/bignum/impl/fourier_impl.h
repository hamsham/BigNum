/* 
 * File:   fourier_impl.h
 * Author: elacey
 *
 * Created on January 15, 2016, 11:29 AM
 */



/*
 * 
 */
template <typename num_t>
constexpr bool isPow2(const num_t n) {
    return n && !(n & (n-1));
}



/*
 * 
 */
template <typename num_t>
num_t nextPow2(num_t n) {
    if (n == 0) {
        return 0;
    }

    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return ++n;
}



template <typename flt_t>
void fft(cmplx_list_t<flt_t>& x) {
    static constexpr flt_t pi = 3.1415926535897932384626433832795;
    
    // in the event that an array was passed in with a non-power-of-two length.
    const cmplx_size_t<flt_t> len = x.size();
    
    // base case
    if (len == 1) {
        x = cmplx_list_t<flt_t>{x[0]};
        return;
    }

    // Partition the input list into evenly-index and oddly-indexed elements.
    const cmplx_size_t<flt_t> halfLen = len / 2;
    
    cmplx_list_t<flt_t> evens;  evens.reserve(halfLen);
    cmplx_list_t<flt_t> odds;   odds.reserve(halfLen);

    for (cmplx_size_t<flt_t> i = 0; i < halfLen; ++i) {
        // zero-pad both partitions if the input array was not at the
        // required radix=2 capacity
        if (i < x.size()) {
            evens.push_back(x[2*i]);
            odds.push_back(x[2*i+1]);
        }
        else {
            evens[i] = odds[i] = std::complex<flt_t>{0};
        }
    }

    // TODO: Fix the recursion!
    fft<flt_t>(evens);
    fft<flt_t>(odds);

    // combine the even and odd partitions
    const cmplx_size_t<flt_t> nf = (flt_t)len;

    for (cmplx_size_t<flt_t> k = 0; k < halfLen; ++k) {
        const flt_t kf = (flt_t)k;
        const flt_t w = -2.0 * kf * pi / nf;
        const std::complex<flt_t> wk {std::cos(w), std::sin(w)};

        x[k] = evens[k] + (wk * odds[k]);
        x[k+halfLen] = evens[k] - (wk * odds[k]);
    }
}



template <typename flt_t>
void ifft(cmplx_list_t<flt_t>& x) {
    for (cmplx_value_t<flt_t>& e : x) {
        e = std::conj(e);
    }

    fft<flt_t>(x);

    const flt_t len = static_cast<flt_t>(x.size());

    for (cmplx_value_t<flt_t>& e : x) {
        e = std::conj(e) / len;
    }
}



template <typename container_t, typename flt_t>
cmplx_list_t<flt_t> create_fft_table(const container_t& a, const container_t& b) {
    typedef typename container_t::size_type big_size_type;
    typedef typename container_t::value_type big_value_type;
    
    // Create a list of complex numbers with interleaved values from the two
    // input numbers. The output list must have a length that's a power of 2.
    big_size_type aLen = a.size();
    big_size_type bLen = b.size();
    
    // Ensure the Cooley-Tukey algorithm has its radix=2 requirement fulfilled.
    // Add a few digits to the end so the algorithm has room for overflow.
    big_size_type size = aLen + bLen;
    
    if (!isPow2(size)) {
        size = nextPow2(size);
    }
    
    cmplx_list_t<flt_t> ret;
    ret.reserve(size);
    
    for (big_size_type i = 0; i < size; ++i) {
        // Add some zero-padding to the output list if necessary
        big_value_type aVal = 0;
        
        if (i < aLen) { aVal = a[i]; }
        
        big_value_type bVal = 0;
        
        if (i < bLen) { bVal = b[i]; }
        
        ret.push_back(std::complex<flt_t>{(flt_t)aVal, (flt_t)bVal});
    }
    
    return ret;
}



template <typename flt_t>
void convolute_fft(cmplx_list_t<flt_t>& fftTable) {
    const cmplx_size_t<flt_t> fftSize = fftTable.size();
    
	// transform.
    cmplx_list_t<flt_t> transforms{fftTable};
    fft<flt_t>(transforms);

    // point-wise multiplication in frequency domain.
    for (cmplx_size_t<flt_t> i = 0; i < fftSize; ++i) {
        // extract the individual transformed signals from the composed one.
        const cmplx_value_t<flt_t>& ti = transforms[i];
        const cmplx_value_t<flt_t>&& tc = std::conj(transforms[-i % fftSize]);
        
        // perform convolution
        const cmplx_value_t<flt_t> x1 = ti + tc;
        const cmplx_value_t<flt_t> x2 = ti - tc;
        const cmplx_value_t<flt_t> x3 = x1 * x2;

        // avoid pedantic compilers
        constexpr flt_t rotation = flt_t{0.25};
        
        fftTable[i] = std::complex<flt_t>{x3.imag(), -x3.real()} * rotation;
    }
}
