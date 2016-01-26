


///////////////////////////////////////////////////////////////////////////////
// Addition implementation to two numbers with the same sign.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
void abs_val_add(
    container_t& outNum,
    const container_t& inNum
) {
    typedef typename limits_t::base_single single_t;
    typedef typename limits_t::base_double double_t;
    
    // numerical iterators
    typename container_t::size_type outIter = 0;
    typename container_t::size_type inIter = 0;
    
    static constexpr double_t SINGLE_BASE_MAX = bn_max_limit<single_t>();
    
    // arithmetic remainder
    single_t remainder = 0;
    
    while (true) {
        // add a number to this object's container if necessary
        if (outIter == outNum.size()) {
            outNum.push_back(0);
        }
        
        // get the single digits that are to be added
        const double_t inDigit = (inIter < inNum.size()) ? inNum[inIter] : double_t{0};
        const double_t outDigit = outNum[outIter] + inDigit + remainder;
        
        // allow integer overflow to handle the resulting value.
        if (SINGLE_BASE_MAX < outDigit) {
            const single_t overflow = SINGLE_BASE_MAX-double_t{1};
            outNum[outIter] = outDigit-overflow;
            remainder = 1;
        }
        else {
            outNum[outIter] = outDigit;
            remainder = 0;
        }
        
        // onto the next number
        ++outIter;
        ++inIter;
        
        // determine when to stop counting
        if (outIter == outNum.size() && inIter >= inNum.size() && 0 == remainder) {
            break;
        }
    }
}
