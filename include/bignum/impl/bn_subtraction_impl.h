/* 
 * File:   bn_subtraction_impl.h
 * Author: elacey
 *
 * Created on January 15, 2016, 9:25 AM
 */



///////////////////////////////////////////////////////////////////////////////
// Subtraction implementation
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
void abs_val_sub(
    container_t& largerNum,
    const container_t& smallerNum
) {
    #ifdef BN_DEBUG
        if (largerNum.size() < smallerNum.size()
        || abs_val_is_lt(largerNum, smallerNum)
        ) {
            throw BNUnderflow{};
        }
    #endif

    typedef typename limits_t::base_single bn_single;
    typedef typename limits_t::base_double bn_double;
    
    // numerical iterators
    typename container_t::size_type outIter = 0;
    typename container_t::size_type inIter = 0;

    constexpr bn_double SINGLE_BASE_MAX = bn_max_limit<bn_single>();
    
    // borrow/carry counter
    bn_double numBorrowed = 0;
    
    while (true) {
        // get the single digits that are to be added
        const bn_double inDigit = (inIter < smallerNum.size()) ? smallerNum[inIter] : bn_double{0};
        const bn_double outDigit = (largerNum[outIter]-numBorrowed)-inDigit;
        
        if (SINGLE_BASE_MAX < outDigit) {
            largerNum[outIter] = (bn_single)(outDigit+SINGLE_BASE_MAX+bn_double{1});
            numBorrowed = 1;
        }
        else {
            largerNum[outIter] = (bn_single)outDigit;
            numBorrowed = 0;
        }
        
        // onto the next number
        ++outIter;
        ++inIter;
        
        // determine when to stop counting
        if (outIter == largerNum.size() && inIter >= smallerNum.size()) {
            break;
        }
    }
    
    // pop off any remaining zeroes
    typename container_t::size_type iter = largerNum.size();
    while (iter--) {
        if (0 ==largerNum[iter]) {
            largerNum.pop_back();
        }
        else {
            break;
        }
    }
}

