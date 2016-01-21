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
void absValSub(
    container_t& largerNum,
    const container_t& smallerNum
) {
    #ifdef BN_DEBUG
        if (largerNum.size() < smallerNum.size()
        || absValIsLess(largerNum, smallerNum)
        ) {
            throw bnUnderflow{};
        }
    #endif

    typedef typename limits_t::base_single single_t;
    typedef typename limits_t::base_double double_t;
    
    // numerical iterators
    typename container_t::size_type outIter = 0;
    typename container_t::size_type inIter = 0;

    constexpr double_t SINGLE_BASE_MAX = bn_max_limit<single_t>();
    
    // borrow/carry counter
    double_t numBorrowed = 0;
    
    while (true) {
        // get the single digits that are to be added
        const double_t inDigit = (inIter < smallerNum.size()) ? smallerNum[inIter] : double_t{0};
        const double_t outDigit = (largerNum[outIter]-numBorrowed)-inDigit;
        
        if (SINGLE_BASE_MAX < outDigit) {
            largerNum[outIter] = (single_t)(outDigit+SINGLE_BASE_MAX+double_t{1});
            numBorrowed = 1;
        }
        else {
            largerNum[outIter] = (single_t)outDigit;
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

