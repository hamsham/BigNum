


///////////////////////////////////////////////////////////////////////////////
// Addition implementation to two numbers with the same sign.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
void abs_val_add(
    container_t& outNum,
    const container_t& inNum
) {
    typedef typename limits_t::base_single bn_single;
    typedef typename limits_t::base_double bn_double;
    
    // numerical iterators
    typename container_t::size_type outIter = 0;
    typename container_t::size_type inIter = 0;
    
    static constexpr bn_double SINGLE_BASE_MAX = bn_max_limit<bn_single>();
    
    // arithmetic remainder
    bn_single remainder = 0;
    
    while (true) {
        // add a number to this object's container if necessary
        if (outIter == outNum.size()) {
            outNum.push_back(0);
        }

        // get the single digits that are to be added
        const bn_double inDigit = (inIter < inNum.size()) ? inNum[inIter] : bn_double{0};
        const bn_double outDigit = outNum[outIter] + inDigit + remainder;

        // allow integer overflow to handle the resulting value.
        if (SINGLE_BASE_MAX < outDigit) {
            const bn_single overflow = (bn_single)(outDigit % (SINGLE_BASE_MAX+bn_double{1}));
            outNum[outIter] = overflow;
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
        if (outIter == outNum.size() && inIter >= inNum.size() && !remainder) {
            break;
        }
    }
}
