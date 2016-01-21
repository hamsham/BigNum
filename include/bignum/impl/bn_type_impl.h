/* 
 * File:   bn_type_impl.h
 * Author: Miles Lacey
 *
 * Created on July 18, 2014, 12:45 PM
 */

#include "bignum/bn_addition.h"
#include "bignum/bn_subtraction.h"
#include "bignum/bn_multiplication.h"

///////////////////////////////////////////////////////////////////////////////
// Outputting to an ostream
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
std::ostream& operator << (std::ostream& ostr, const bn_type<limits_t, container_t>& num) {
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
    
    const typename bn_type<limits_t, container_t>::container_type& numList = num.getData();
    
    // no elements available?
    if (numList.size() == 0) {
        return ostr << '0';
    }
    
    typename bn_type<limits_t, container_t>::container_type::size_type iter = numList.size();
    while (iter--) {
        ostr << numList[iter];
    }

    return ostr;
}

///////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
bn_type<limits_t, container_t>::bn_type() {
}

///////////////////////////////////////////////////////////////////////////////
// Constructor with a number.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
bn_type<limits_t, container_t>::bn_type(
    bn_desc_t desc,
    std::initializer_list<single_t> numList
) :
    descriptor{desc},
    numData{}
{
    typedef std::initializer_list<single_t> initializer_list;

    if (!numList.size()) {
       return; 
    }
    
    bool emptyDigit = true;
    unsigned numInvalidItems = 0;
    typename initializer_list::const_iterator iter;
    typename container_type::size_type outIndex = numData.size();
    
    for (iter = numList.begin(); iter != numList.end(); ++iter) {
        const typename initializer_list::value_type digit = *iter;
        
        // Check the input initializer list for zero-values. Leading
        // zero-values cannot be added to the internal container (although)
        // it's not prevented in the push_front methods).
        if (digit != single_t{limits_t::SINGLE_BASE_MIN} && emptyDigit) {
            ++numInvalidItems;
            emptyDigit = false;
        }
        else {
            continue;
        }
        
        // check to see if the internal container has been initialized.
        if (!emptyDigit && numData.empty()) {
            numData.resize(numList.size() - numInvalidItems);
            
            // stop more processing in the event that only zero-values had been
            // found in the input initializer.
            if (numData.empty()) {
                return;
            }
            else {
                outIndex = numData.size();
            }
        }
        
        // insert a digit!
        numData[--outIndex] = digit;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Copy Constructor
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bn_type<limits_t, container_t>::bn_type(const bn_type& num) :
    descriptor{num.descriptor},
    numData{num.numData}
{}

///////////////////////////////////////////////////////////////////////////////
// Move Operator
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bn_type<limits_t, container_t>::bn_type(bn_type&& num) :
    descriptor{num.descriptor},
    numData{std::move(num.numData)}
{
    descriptor = num.descriptor;
}

///////////////////////////////////////////////////////////////////////////////
// Get the raw data contained within a bignum.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline const typename bn_type<limits_t, container_t>::container_type&
bn_type<limits_t, container_t>::getData() const {
    return numData;
}

///////////////////////////////////////////////////////////////////////////////
// Find out more about a bignum.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bn_desc_t bn_type<limits_t, container_t>::getDescriptor() const {
    return descriptor;
}

///////////////////////////////////////////////////////////////////////////////
// Set the numerical descriptor for a bignum
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
void bn_type<limits_t, container_t>::setDescriptor(bn_desc_t desc) {
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
template <class limits_t, class container_t>
inline bool bn_type<limits_t, container_t>::isPositive() const {
    return descriptor == BN_POS || descriptor == BN_POS_INF;
}

///////////////////////////////////////////////////////////////////////////////
// Determine if a bignum is negative
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bool bn_type<limits_t, container_t>::isNegative() const {
    return descriptor == BN_NEG || descriptor == BN_NEG_INF;
}

///////////////////////////////////////////////////////////////////////////////
// Determine if a bignum is infinite
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bool bn_type<limits_t, container_t>::isInfinite() const {
    return descriptor == BN_POS_INF || descriptor == BN_NEG_INF;
}

///////////////////////////////////////////////////////////////////////////////
// Determine if a bignum is not a number.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bool bn_type<limits_t, container_t>::isNan() const {
    return descriptor == BN_NAN;
}

///////////////////////////////////////////////////////////////////////////////
// Resize a bignum to contain a specific number of digits
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void bn_type<limits_t, container_t>::resize(
    typename bn_type::container_type::size_type numDigits, single_t digits
) {
    numData.resize(numDigits, digits);
}

///////////////////////////////////////////////////////////////////////////////
// get the number of single digits
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline typename bn_type<limits_t, container_t>::container_type::size_type
bn_type<limits_t, container_t>::size() const {
    return numData.size();
}

///////////////////////////////////////////////////////////////////////////////
// push a number to the highest-order
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void bn_type<limits_t, container_t>::push_front(single_t digit) {
    numData.insert(numData.begin(), digit);
}

///////////////////////////////////////////////////////////////////////////////
// remove the number of highest magnitude from this
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void bn_type<limits_t, container_t>::pop_front() {
    numData.erase(numData.begin());
}

///////////////////////////////////////////////////////////////////////////////
// push a number into the lowest magnitude.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void bn_type<limits_t, container_t>::push_back(single_t digit) {
    numData.push_back(digit);
}

///////////////////////////////////////////////////////////////////////////////
// remove the lowest-order digit
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void bn_type<limits_t, container_t>::pop_back() {
    numData.pop_back();
}

///////////////////////////////////////////////////////////////////////////////
// insert a digit into an arbitrary position
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void bn_type<limits_t, container_t>::push(
    single_t digit, typename bn_type::container_type::size_type pos
) {
    numData.insert(numData.begin()+pos, digit);
}

///////////////////////////////////////////////////////////////////////////////
// remove a digit from this number
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void bn_type<limits_t, container_t>::pop(typename bn_type::container_type::size_type pos) {
    numData.erase(numData.begin()+pos);
}

///////////////////////////////////////////////////////////////////////////////
// Reset this bignum
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void bn_type<limits_t, container_t>::clear() {
    descriptor = BN_POS;
    numData.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Array Subscripting
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline typename limits_t::base_single&
bn_type<limits_t, container_t>::operator[](typename container_type::size_type iter) {
    BN_ASSERT(iter < numData.size());
    return numData[iter];
}

///////////////////////////////////////////////////////////////////////////////
// Array Subscripting (const)
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline typename limits_t::base_single
bn_type<limits_t, container_t>::operator[](typename container_type::size_type iter) const {
    BN_ASSERT(iter < numData.size());
    return numData[iter];
}

///////////////////////////////////////////////////////////////////////////////
// Basic comparison
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bool bn_type<limits_t, container_t>::operator==(const bn_type& num) const {
    if (this->descriptor != num.descriptor) {
        return false;
    }
    return absValIsEqual(this->numData, num.numData);
}

///////////////////////////////////////////////////////////////////////////////
// Basic "not" comparison
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bool bn_type<limits_t, container_t>::operator!=(const bn_type& num) const {
    if (this->descriptor != num.descriptor) {
        return true;
    }
    return !absValIsEqual(this->numData, num.numData);
}
        
///////////////////////////////////////////////////////////////////////////////
 // Greater than operator
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
bool bn_type<limits_t, container_t>::operator > (const bn_type& num) const {
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
template <class limits_t, class container_t>
bool bn_type<limits_t, container_t>::operator >= (const bn_type& num) const {
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
template <class limits_t, class container_t>
bool bn_type<limits_t, container_t>::operator < (const bn_type& num) const {
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
template <class limits_t, class container_t>
bool bn_type<limits_t, container_t>::operator <= (const bn_type& num) const {
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
template <class limits_t, class container_t>
inline bn_type<limits_t, container_t>&
bn_type<limits_t, container_t>::operator=(const bn_type& num) {
    descriptor = num.descriptor;
    numData = num.numData;
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Move assignment.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bn_type<limits_t, container_t>&
bn_type<limits_t, container_t>::operator=(bn_type&& num) {
    descriptor = num.descriptor;
    num.descriptor = BN_POS;

    numData = std::move(num.numData);

    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Add.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bn_type<limits_t, container_t>
bn_type<limits_t, container_t>::operator + (const bn_type& num) const {
    bn_type ret = *this;
    ret += num;
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Subtract.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bn_type<limits_t, container_t>
bn_type<limits_t, container_t>::operator - (const bn_type& num) const {
    bn_type ret = *this;
    ret -= num;
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Subtract.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bn_type<limits_t, container_t>
bn_type<limits_t, container_t>::operator * (const bn_type& num) const {
    bn_type ret = *this;
    ret *= num;
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Addition with assignment
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
bn_type<limits_t, container_t>&
bn_type<limits_t, container_t>::operator +=(const bn_type& num) {
    
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
            absValAdd<limits_t, container_t>(numData, num.numData);
        }
        // add a negative to a positive
        else if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
            // make sure that only the larger number is added
            if (absValIsGreaterOrEqual(this->numData, num.numData)) {
                // subtract as normal
                absValSub<limits_t, container_t>(numData, num.numData);
                return *this;
            }
            else {
                bn_type tempNum = num;
                absValSub<limits_t, container_t>(tempNum.numData, numData);
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
                absValSub<limits_t, container_t>(numData, num.numData);
                return *this;
            }
            else {
                bn_type tempNum = num;
                absValSub<limits_t, container_t>(tempNum.numData, numData);
                tempNum.descriptor = BN_POS;
                *this = std::move(tempNum);
                return *this;
            }
        }
        // add a negative to a negative
        else {
            absValAdd<limits_t, container_t>(numData, num.numData);
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
// Subtraction with assignment
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
bn_type<limits_t, container_t>&
bn_type<limits_t, container_t>::operator -=(const bn_type& num) {
    
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
                absValSub<limits_t, container_t>(numData, num.numData);
            }
            else {
                bn_type tempNum = num;
                absValSub<limits_t, container_t>(tempNum.numData, numData);
                tempNum.descriptor = BN_NEG;
                *this = std::move(tempNum);
            }
        }
        // subtract a negative from a positive
        else if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
            absValAdd<limits_t, container_t>(numData, num.numData);
        }
        // subtract a positive from a negative
        else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
            absValAdd<limits_t, container_t>(numData, num.numData);
        }
        // subtract a negative from a negative
        else {
            // make sure that only the larger number is added
            if (absValIsGreaterOrEqual(this->numData, num.numData)) {
                // subtract as normal
                absValSub<limits_t, container_t>(numData, num.numData);
            }
            else {
                bn_type tempNum = num;
                absValSub<limits_t, container_t>(tempNum.numData, numData);
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
// Subtraction with assignment
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
bn_type<limits_t, container_t>&
bn_type<limits_t, container_t>::operator *=(const bn_type& num) {
    
    // Make sure no unneeded calculations are performed
    if (!isComputable(descriptor)) {
        numData.clear();
        descriptor = num.descriptor;
        return *this;
    }
    
    bn_type ret;
    
    // subtract a negative from a positive
    if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
        ret.descriptor = BN_NEG;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_NEG) {
        ret.descriptor = BN_POS;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
        ret.descriptor = BN_NEG;
    }
    else {
        ret.descriptor = BN_POS;
    }
    
    // std::deque throws exceptions when a memory error occurs
    try {
        ret.numData = std::move(mulStrassen<limits_t, container_t>(numData, num.numData));
        *this = std::move(ret);
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
// Equating implementation
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
bool bn_type<limits_t, container_t>::absValIsEqual(
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
template <class limits_t, class container_t>
bool bn_type<limits_t, container_t>::absValIsGreater(
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
template <class limits_t, class container_t>
bool bn_type<limits_t, container_t>::absValIsGreaterOrEqual(
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
template <class limits_t, class container_t>
bool bn_type<limits_t, container_t>::absValIsLess(
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
template <class limits_t, class container_t>
bool bn_type<limits_t, container_t>::absValIsLessOrEqual(
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
template <class limits_t, class container_t>
bool bn_type<limits_t, container_t>::isComputable(bn_desc_t desc) {
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
