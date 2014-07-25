/* 
 * File:   bn_type_impl.h
 * Author: Miles Lacey
 *
 * Created on July 18, 2014, 12:45 PM
 */

///////////////////////////////////////////////////////////////////////////////
// Outputting to an ostream
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
std::ostream& operator << (std::ostream& ostr, const bn_type<base_single, base_double>& num) {
    if (num.getDescriptor() == BN_NEG) {
        ostr << '-';
    }
    else if (num.getDescriptor() == BN_POS_INF) {
        return ostr << "+INF";
    }
    else if (num.getDescriptor() == BN_NEG_INF) {
        return ostr << "-INF";
    }
    else if (num.getDescriptor() == BN_NAN) {
        return ostr << "NaN";
    }
    
    const typename bn_type<base_single, base_double>::container_type& numList = num.getData();
    
    // no elements available?
    if (numList.size() == 0) {
        return ostr << '0';
    }
    
    typename bn_type<base_single, base_double>::container_type::size_type iter = numList.size();
    while (iter--) {
        ostr << numList[iter];
    }

    return ostr;
}

///////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bn_type<base_single, base_double>::bn_type() {
}

///////////////////////////////////////////////////////////////////////////////
// Constructor with a number.
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bn_type<base_single, base_double>::bn_type(
    bn_desc_t desc,
    std::initializer_list<base_single> numList
) :
    descriptor{desc},
    numData{numList}
{}

///////////////////////////////////////////////////////////////////////////////
// Copy Constructor
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bn_type<base_single, base_double>::bn_type(const bn_type& num) :
    descriptor{num.descriptor},
    numData{num.numData}
{}

///////////////////////////////////////////////////////////////////////////////
// Move Operator
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bn_type<base_single, base_double>::bn_type(bn_type&& num) :
    descriptor{num.descriptor},
    numData{std::move(num.numData)}
{
    descriptor = num.descriptor;
}

///////////////////////////////////////////////////////////////////////////////
// Get the raw data contained within a bignum.
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline const typename bn_type<base_single, base_double>::container_type&
bn_type<base_single, base_double>::getData() const {
    return numData;
}

///////////////////////////////////////////////////////////////////////////////
// Find out more about a bignum.
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bn_desc_t bn_type<base_single, base_double>::getDescriptor() const {
    return descriptor;
}

///////////////////////////////////////////////////////////////////////////////
// Set the numerical descriptor for a bignum
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
void bn_type<base_single, base_double>::setDescriptor(bn_desc_t desc) {
    // fall-through the non-representable types and clear data if necessary
    switch (desc) {
        case bn_desc_t::BN_NAN:
        case bn_desc_t::BN_POS_INF:
        case bn_desc_t::BN_NEG_INF:
            numData.clear();
        default:
            descriptor = desc;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Determine if a bignum is positive
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bool bn_type<base_single, base_double>::isPositive() const {
    return descriptor == BN_POS || descriptor == BN_POS_INF;
}

///////////////////////////////////////////////////////////////////////////////
// Determine if a bignum is negative
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bool bn_type<base_single, base_double>::isNegative() const {
    return descriptor == BN_NEG || descriptor == BN_NEG_INF;
}

///////////////////////////////////////////////////////////////////////////////
// Determine if a bignum is infinite
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bool bn_type<base_single, base_double>::isInfinite() const {
    return descriptor == BN_POS_INF || descriptor == BN_NEG_INF;
}

///////////////////////////////////////////////////////////////////////////////
// Determine if a bignum is not a number.
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bool bn_type<base_single, base_double>::isNan() const {
    return descriptor == BN_NAN;
}

///////////////////////////////////////////////////////////////////////////////
// Resize a bignum to contain a specific number of digits
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline void bn_type<base_single, base_double>::resize(
    typename bn_type::container_type::size_type numDigits, base_single digits
) {
    numData.resize(numDigits, digits);
}

///////////////////////////////////////////////////////////////////////////////
// get the number of single digits
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline typename bn_type<base_single, base_double>::container_type::size_type
bn_type<base_single, base_double>::size() const {
    return numData.size();
}

///////////////////////////////////////////////////////////////////////////////
// push a number to the highest-order
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline void bn_type<base_single, base_double>::push_front(base_single digit) {
    numData.push_front(digit);
}

///////////////////////////////////////////////////////////////////////////////
// remove the number of highest magnitude from this
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline void bn_type<base_single, base_double>::pop_front() {
    numData.pop_front();
}

///////////////////////////////////////////////////////////////////////////////
// push a number into the lowest magnitude.
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline void bn_type<base_single, base_double>::push_back(base_single digit) {
    numData.push_back(digit);
}

///////////////////////////////////////////////////////////////////////////////
// remove the lowest-order digit
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline void bn_type<base_single, base_double>::pop_back() {
    numData.pop_back();
}

///////////////////////////////////////////////////////////////////////////////
// insert a digit into an arbitrary position
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline void bn_type<base_single, base_double>::push(
    base_single digit, typename bn_type::container_type::size_type pos
) {
    numData.insert(numData.begin()+pos, digit);
}

///////////////////////////////////////////////////////////////////////////////
// remove a digit from this number
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline void bn_type<base_single, base_double>::pop(typename bn_type::container_type::size_type pos) {
    numData.erase(numData.begin()+pos);
}

///////////////////////////////////////////////////////////////////////////////
// Reset this bignum
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline void bn_type<base_single, base_double>::clear() {
    descriptor = BN_POS;
    numData.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Array Subscripting
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline base_single& bn_type<base_single, base_double>::operator[](typename container_type::size_type iter) {
    BN_ASSERT(iter < numData.size());
    return numData[iter];
}

///////////////////////////////////////////////////////////////////////////////
// Array Subscripting (const)
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline base_single bn_type<base_single, base_double>::operator[](typename container_type::size_type iter) const {
    BN_ASSERT(iter < numData.size());
    return numData[iter];
}

///////////////////////////////////////////////////////////////////////////////
// Basic comparison
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bool bn_type<base_single, base_double>::operator==(const bn_type& num) const {
    if (this->descriptor != num.descriptor) {
        return false;
    }
    return absValIsEqual(this->numData, num.numData);
}

///////////////////////////////////////////////////////////////////////////////
// Basic "not" comparison
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bool bn_type<base_single, base_double>::operator!=(const bn_type& num) const {
    if (this->descriptor != num.descriptor) {
        return true;
    }
    return !absValIsEqual(this->numData, num.numData);
}
        
///////////////////////////////////////////////////////////////////////////////
 // Greater than operator
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bool bn_type<base_single, base_double>::operator > (const bn_type& num) const {
    if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
        return true;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
        return false;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_NEG) {
        return absValIsLessOrEqual(this->numData, num.numData);
    }
    
    // compare positive vs positive
    return absValIsGreater(this->numData, num.numData);
}

///////////////////////////////////////////////////////////////////////////////
// Greater than/equal to operator
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bool bn_type<base_single, base_double>::operator >= (const bn_type& num) const {
    if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
        return true;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
        return false;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_NEG) {
        return absValIsLess(this->numData, num.numData);
    }
    
    // compare positive vs positive
    return absValIsGreaterOrEqual(this->numData, num.numData);
}

///////////////////////////////////////////////////////////////////////////////
// Less than operator
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bool bn_type<base_single, base_double>::operator < (const bn_type& num) const {
    if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
        return false;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
        return true;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_NEG) {
        return absValIsGreater(this->numData, num.numData);
    }
    
    // compare positive vs positive
    return absValIsLess(this->numData, num.numData);
}

///////////////////////////////////////////////////////////////////////////////
// Less than/equal to operator
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bool bn_type<base_single, base_double>::operator <= (const bn_type& num) const {
    if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
        return false;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
        return true;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_NEG) {
        return absValIsGreater(this->numData, num.numData);
    }
    
    // compare positive vs positive
    return absValIsLessOrEqual(this->numData, num.numData);
}

///////////////////////////////////////////////////////////////////////////////
// Copy assignment.
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bn_type<base_single, base_double>&
bn_type<base_single, base_double>::operator=(const bn_type& num) {
    descriptor = num.descriptor;
    numData = num.numData;
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Move assignment.
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bn_type<base_single, base_double>&
bn_type<base_single, base_double>::operator=(bn_type&& num) {
    descriptor = num.descriptor;
    num.descriptor = BN_POS;

    numData = std::move(num.numData);

    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Add.
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bn_type<base_single, base_double>
bn_type<base_single, base_double>::operator + (const bn_type& num) const {
    bn_type ret = *this;
    ret += num;
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Subtract.
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
inline bn_type<base_single, base_double>
bn_type<base_single, base_double>::operator - (const bn_type& num) const {
    bn_type ret = *this;
    ret -= num;
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Addition with assignment
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bn_type<base_single, base_double>&
bn_type<base_single, base_double>::operator +=(const bn_type& num) {
    // Make sure no unneeded calculations are performed
    if (!isComputable(descriptor)) {
        numData.clear();
        descriptor = num.descriptor;
        return *this;
    }
    
    // std::deque throws exceptions when a memory error occurs
    try {
        // add two positive numbers
        if (this->descriptor == BN_POS && num.descriptor == BN_POS) {
            absValAdd(numData, num.numData);
        }
        // add a negative to a positive
        else if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
            // make sure that only the larger number is added
            if (absValIsGreaterOrEqual(this->numData, num.numData)) {
                // subtract as normal
                absValSub(numData, num.numData);
                return *this;
            }
            else {
                bn_type tempNum = num;
                absValSub(tempNum.numData, numData);
                tempNum.descriptor = BN_NEG;
                *this = std::move(tempNum);
                return *this;
            }
        }
        // add a positive to a negative
        else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
            // make sure that only the larger number is added
            if (absValIsGreaterOrEqual(this->numData, num.numData)) {
                // subtract as normal
                absValSub(numData, num.numData);
                return *this;
            }
            else {
                bn_type tempNum = num;
                absValSub(tempNum.numData, numData);
                tempNum.descriptor = BN_POS;
                *this = std::move(tempNum);
                return *this;
            }
        }
        // add a negative to a negative
        else {
            absValAdd(numData, num.numData);
        }
    }
    catch(const std::exception& e) {
        // Mark the number as positive infinite as this was likely the cause of an allocation failure.
        descriptor = (num.descriptor == BN_POS) ? BN_POS_INF : BN_NEG_INF;
        
        numData.clear();
        
        throw e;
    }
    
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Addition implementation to two numbers with the same sign.
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
void bn_type<base_single, base_double>::absValAdd(
    container_type& outNum,
    const container_type& inNum
) {
    // numerical iterators
    typename container_type::size_type outIter = 0;
    typename container_type::size_type inIter = 0;
    
    // arithmetic remainder
    base_single remainder = 0;
    
    while (true) {
        // add a number to this object's container if necessary
        if (outIter == outNum.size()) {
            outNum.push_back(0);
        }
        
        // get the single digits that are to be added
        const base_double inDigit = (inIter < inNum.size()) ? inNum[inIter] : base_double{0};
        const base_double outDigit = outNum[outIter] + inDigit + remainder;
        
        // allow integer overflow to handle the resulting value.
        if (SINGLE_BASE_MAX < outDigit) {
            outNum[outIter] = outDigit-base_double{SINGLE_BASE_MAX}-base_double{1};
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

///////////////////////////////////////////////////////////////////////////////
// Subtraction with assignment
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bn_type<base_single, base_double>&
bn_type<base_single, base_double>::operator -=(const bn_type& num) {
    // Make sure no unneeded calculations are performed
    if (!isComputable(descriptor)) {
        numData.clear();
        descriptor = num.descriptor;
        return *this;
    }
    
    // std::deque throws exceptions when a memory error occurs
    try {
        // subtract two positive numbers
        if (this->descriptor == BN_POS && num.descriptor == BN_POS) {
            // make sure that only the larger number is added
            if (absValIsGreaterOrEqual(this->numData, num.numData)) {
                // subtract as normal
                absValSub(numData, num.numData);
            }
            else {
                bn_type tempNum = num;
                absValSub(tempNum.numData, numData);
                tempNum.descriptor = BN_NEG;
                *this = std::move(tempNum);
            }
        }
        // subtract a negative from a positive
        else if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
            absValAdd(numData, num.numData);
        }
        // subtract a positive from a negative
        else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
            absValAdd(numData, num.numData);
        }
        // subtract a negative from a negative
        else {
            // make sure that only the larger number is added
            if (absValIsGreaterOrEqual(this->numData, num.numData)) {
                // subtract as normal
                absValSub(numData, num.numData);
            }
            else {
                bn_type tempNum = num;
                absValSub(tempNum.numData, numData);
                tempNum.descriptor = BN_POS;
                *this = std::move(tempNum);
            }
        }
    }
    catch(const std::exception& e) {
        // Mark the number as positive infinite as this was likely the cause of an allocation failure.
        descriptor = (num.descriptor == BN_POS) ? BN_POS_INF : BN_NEG_INF;
        
        numData.clear();
        
        throw e;
    }
    
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Subtraction implementation
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
void bn_type<base_single, base_double>::absValSub(
    container_type& largerNum,
    const container_type& smallerNum
) {
    #ifdef BN_DEBUG
        if (largerNum.size() < smallerNum.size()
        || absValIsLess(largerNum, smallerNum)
        ) {
            throw bnUnderflow{};
        }
    #endif
    
    // numerical iterators
    typename container_type::size_type outIter = 0;
    typename container_type::size_type inIter = 0;
    
    // borrow/carry counter
    base_double numBorrowed = 0;
    
    while (true) {
        // get the single digits that are to be added
        const base_double inDigit = (inIter < smallerNum.size()) ? smallerNum[inIter] : base_double{0};
        const base_double outDigit = (largerNum[outIter]-numBorrowed)-inDigit;
        
        if (SINGLE_BASE_MAX < outDigit) {
            largerNum[outIter] = (base_single)(outDigit+base_double{SINGLE_BASE_MAX}+base_double{1});
            numBorrowed = 1;
        }
        else {
            largerNum[outIter] = (base_single)outDigit;
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
    typename container_type::size_type iter = largerNum.size();
    while (iter--) {
        if (0 ==largerNum[iter]) {
            largerNum.pop_back();
        }
        else {
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Equating implementation
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bool bn_type<base_single, base_double>::absValIsEqual(
    const container_type& num1,
    const container_type& num2
) {
    if (num1.size() != num2.size()) {
        return false;
    }
    
    // iterate from the numbers of greatest magnitude down to the lowest
    typename container_type::size_type i = num1.size();
    
    while (i--) {
        if (num1[i] != num2[i]) {
            return false;
        }
    }
    
    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Greater than implementation
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bool bn_type<base_single, base_double>::absValIsGreater(
    const container_type& num1,
    const container_type& num2
) {
    if (num1.size() > num2.size()) {
        return true;
    }
    if (num1.size() < num2.size()) {
        return false;
    }
    
    // iterate from the numbers of greatest magnitude down to the lowest
    typename container_type::size_type i = num1.size();
    
    while (i--) {
        if (num1[i] > num2[i]) {
            return true;
        }
    }
    
    return false;
}

///////////////////////////////////////////////////////////////////////////////
// Greater than or equal to implementation
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bool bn_type<base_single, base_double>::absValIsGreaterOrEqual(
    const container_type& num1,
    const container_type& num2
) {
    if (num1.size() > num2.size()) {
        return true;
    }
    if (num1.size() < num2.size()) {
        return false;
    }
    
    // iterate from the numbers of greatest magnitude down to the lowest
    typename container_type::size_type i = num1.size();
    
    while (i--) {
        if (num1[i] > num2[i]) {
            return true;
        }
        if (num1[i] < num2[i]) {
            return false;
        }
    }
    
    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Less than implementation
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bool bn_type<base_single, base_double>::absValIsLess(
    const container_type& num1,
    const container_type& num2
) {
    if (num1.size() < num2.size()) {
        return true;
    }
    if (num1.size() > num2.size()) {
        return false;
    }
    
    // iterate from the numbers of greatest magnitude down to the lowest
    typename container_type::size_type i = num1.size();
    
    while (i--) {
        if (num1[i] < num2[i]) {
            return true;
        }
    }
    
    return false;
}

///////////////////////////////////////////////////////////////////////////////
// Less than or equal to implementation
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bool bn_type<base_single, base_double>::absValIsLessOrEqual(
    const container_type& num1,
    const container_type& num2
) {
    if (num1.size() < num2.size()) {
        return true;
    }
    if (num1.size() > num2.size()) {
        return false;
    }
    
    // iterate from the numbers of greatest magnitude down to the lowest
    typename container_type::size_type i = num1.size();
    
    while (i--) {
        if (num1[i] < num2[i]) {
            return true;
        }
        if (num1[i] > num2[i]) {
            return false;
        }
    }
    
    return true;
}

///////////////////////////////////////////////////////////////////////////////
// Computation sanity check
///////////////////////////////////////////////////////////////////////////////
template <typename base_single, typename base_double>
bool bn_type<base_single, base_double>::isComputable(bn_desc_t desc) {
    switch(desc) {
        case BN_NAN:
        case BN_POS_INF:
        case BN_NEG_INF:
            return false;
        default:
            break;
    }
    
    return true;
}
