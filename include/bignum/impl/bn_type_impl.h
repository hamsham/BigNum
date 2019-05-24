/* 
 * File:   bn_type_impl.h
 * Author: Miles Lacey
 *
 * Created on July 18, 2014, 12:45 PM
 */

#include "bignum/bn_compare.h"
#include "bignum/bn_addition.h"
#include "bignum/bn_subtraction.h"
#include "bignum/bn_multiplication.h"
#include "bignum/bn_division.h"

///////////////////////////////////////////////////////////////////////////////
// Outputting to an ostream
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
std::ostream& operator << (std::ostream& ostr, const Bignum<limits_t, container_t>& num) {
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
    
    const typename Bignum<limits_t, container_t>::container_type& numList = num.getData();
    
    // no elements available?
    if (numList.size() == 0) {
        return ostr << '0';
    }
    
    typename Bignum<limits_t, container_t>::container_type::size_type iter = numList.size();
    while (iter--) {
        ostr << numList[iter];
    }

    return ostr;
}

///////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
Bignum<limits_t, container_t>::Bignum() {
}

///////////////////////////////////////////////////////////////////////////////
// Constructor with a number.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
Bignum<limits_t, container_t>::Bignum(
    bn_desc_t desc,
    std::initializer_list<bn_single> numList
) :
    descriptor{desc},
    numData{}
{
    if (!numList.size()) {
       return;
    }

    typename container_t::size_type leadingZeroes = 0;

    // count all of the digits, minus starting "zeroes"
    for (const auto val : numList) {
        if (val != (bn_single)limits_t::SINGLE_BASE_MIN)
        {
            break;
        }

        ++leadingZeroes;
    }

    numData.resize(numList.size() - leadingZeroes);
    typename container_t::size_type outIter = numData.size();

    for (const auto val : numList)
    {
        if (leadingZeroes)
        {
            --leadingZeroes;
            continue;
        }

        numData[--outIter] = val;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Copy Constructor
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline Bignum<limits_t, container_t>::Bignum(const Bignum& num) :
    descriptor{num.descriptor},
    numData{num.numData}
{}

///////////////////////////////////////////////////////////////////////////////
// Move Operator
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline Bignum<limits_t, container_t>::Bignum(Bignum&& num) :
    descriptor{num.descriptor},
    numData{std::move(num.numData)}
{
    descriptor = num.descriptor;
}

///////////////////////////////////////////////////////////////////////////////
// Get the raw data contained within a bignum.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline const typename Bignum<limits_t, container_t>::container_type&
Bignum<limits_t, container_t>::getData() const {
    return numData;
}

///////////////////////////////////////////////////////////////////////////////
// Find out more about a bignum.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bn_desc_t Bignum<limits_t, container_t>::getDescriptor() const {
    return descriptor;
}

///////////////////////////////////////////////////////////////////////////////
// Set the numerical descriptor for a bignum
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
void Bignum<limits_t, container_t>::setDescriptor(bn_desc_t desc) {
    // fall-through the non-representable types and clear data if necessary
    switch (desc) {
        case bn_desc_t::BN_NAN:
        case bn_desc_t::BN_POS_INF:
        case bn_desc_t::BN_NEG_INF:
            numData.clear();
            break;
        default:
            break;
    }

    descriptor = desc;
}

///////////////////////////////////////////////////////////////////////////////
// Determine if a bignum is positive
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bool Bignum<limits_t, container_t>::isPositive() const {
    return descriptor == BN_POS || descriptor == BN_POS_INF;
}

///////////////////////////////////////////////////////////////////////////////
// Determine if a bignum is negative
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bool Bignum<limits_t, container_t>::isNegative() const {
    return descriptor == BN_NEG || descriptor == BN_NEG_INF;
}

///////////////////////////////////////////////////////////////////////////////
// Determine if a bignum is infinite
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bool Bignum<limits_t, container_t>::isInfinite() const {
    return descriptor == BN_POS_INF || descriptor == BN_NEG_INF;
}

///////////////////////////////////////////////////////////////////////////////
// Determine if a bignum is not a number.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bool Bignum<limits_t, container_t>::isNan() const {
    return descriptor == BN_NAN;
}

///////////////////////////////////////////////////////////////////////////////
// Resize a bignum to contain a specific number of digits
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void Bignum<limits_t, container_t>::resize(
    typename Bignum::container_type::size_type numDigits, bn_single digits
) {
    numData.resize(numDigits, digits);
}

///////////////////////////////////////////////////////////////////////////////
// get the number of single digits
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline typename Bignum<limits_t, container_t>::container_type::size_type
Bignum<limits_t, container_t>::size() const {
    return numData.size();
}

///////////////////////////////////////////////////////////////////////////////
// push a number to the highest-order
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void Bignum<limits_t, container_t>::push_front(bn_single digit) {
    numData.insert(numData.begin(), digit);
}

///////////////////////////////////////////////////////////////////////////////
// remove the number of highest magnitude from this
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void Bignum<limits_t, container_t>::pop_front() {
    numData.erase(numData.begin());
}

///////////////////////////////////////////////////////////////////////////////
// push a number into the lowest magnitude.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void Bignum<limits_t, container_t>::push_back(bn_single digit) {
    numData.push_back(digit);
}

///////////////////////////////////////////////////////////////////////////////
// remove the lowest-order digit
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void Bignum<limits_t, container_t>::pop_back() {
    numData.pop_back();
}

///////////////////////////////////////////////////////////////////////////////
// insert a digit into an arbitrary position
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void Bignum<limits_t, container_t>::push(
    bn_single digit, typename Bignum::container_type::size_type pos
) {
    numData.insert(numData.begin()+pos, digit);
}

///////////////////////////////////////////////////////////////////////////////
// remove a digit from this number
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void Bignum<limits_t, container_t>::pop(typename Bignum::container_type::size_type pos) {
    numData.erase(numData.begin()+pos);
}

///////////////////////////////////////////////////////////////////////////////
// Reset this bignum
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline void Bignum<limits_t, container_t>::clear() {
    descriptor = BN_POS;
    numData.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Array Subscripting
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline typename limits_t::base_single&
Bignum<limits_t, container_t>::operator[](typename container_type::size_type iter) {
    BN_ASSERT(iter < numData.size());
    return numData[iter];
}

///////////////////////////////////////////////////////////////////////////////
// Array Subscripting (const)
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline typename limits_t::base_single
Bignum<limits_t, container_t>::operator[](typename container_type::size_type iter) const {
    BN_ASSERT(iter < numData.size());
    return numData[iter];
}

///////////////////////////////////////////////////////////////////////////////
// Basic comparison
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bool Bignum<limits_t, container_t>::operator==(const Bignum& num) const {
    if (this->descriptor != num.descriptor) {
        return false;
    }
    return abs_val_is_eq<container_t>(this->numData, num.numData);
}

///////////////////////////////////////////////////////////////////////////////
// Basic "not" comparison
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline bool Bignum<limits_t, container_t>::operator!=(const Bignum& num) const {
    if (this->descriptor != num.descriptor) {
        return true;
    }
    return !abs_val_is_eq<container_t>(this->numData, num.numData);
}
        
///////////////////////////////////////////////////////////////////////////////
 // Greater than operator
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
bool Bignum<limits_t, container_t>::operator > (const Bignum& num) const {
    if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
        return true;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
        return false;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_NEG) {
        return abs_val_is_le<container_t>(this->numData, num.numData);
    }
    
    // compare positive vs positive
    return abs_val_is_gt<container_t>(this->numData, num.numData);
}

///////////////////////////////////////////////////////////////////////////////
// Greater than/equal to operator
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
bool Bignum<limits_t, container_t>::operator >= (const Bignum& num) const {
    if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
        return true;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
        return false;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_NEG) {
        return abs_val_is_lt<container_t>(this->numData, num.numData);
    }
    
    // compare positive vs positive
    return abs_val_is_ge<container_t>(this->numData, num.numData);
}

///////////////////////////////////////////////////////////////////////////////
// Less than operator
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
bool Bignum<limits_t, container_t>::operator < (const Bignum& num) const {
    if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
        return false;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
        return true;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_NEG) {
        return abs_val_is_gt<container_t>(this->numData, num.numData);
    }
    
    // compare positive vs positive
    return abs_val_is_lt<container_t>(this->numData, num.numData);
}

///////////////////////////////////////////////////////////////////////////////
// Less than/equal to operator
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
bool Bignum<limits_t, container_t>::operator <= (const Bignum& num) const {
    if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
        return false;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
        return true;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_NEG) {
        return abs_val_is_gt<container_t>(this->numData, num.numData);
    }
    
    // compare positive vs positive
    return abs_val_is_le<container_t>(this->numData, num.numData);
}

///////////////////////////////////////////////////////////////////////////////
// Copy assignment.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline Bignum<limits_t, container_t>&
Bignum<limits_t, container_t>::operator=(const Bignum& num) {
    descriptor = num.descriptor;
    numData = num.numData;
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Move assignment.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline Bignum<limits_t, container_t>&
Bignum<limits_t, container_t>::operator=(Bignum&& num) {
    descriptor = num.descriptor;
    num.descriptor = BN_POS;

    numData = std::move(num.numData);

    return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Add.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline Bignum<limits_t, container_t>
Bignum<limits_t, container_t>::operator + (const Bignum& num) const {
    Bignum ret = *this;
    ret += num;
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Subtract.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline Bignum<limits_t, container_t>
Bignum<limits_t, container_t>::operator - (const Bignum& num) const {
    Bignum ret = *this;
    ret -= num;
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Multiply.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline Bignum<limits_t, container_t>
Bignum<limits_t, container_t>::operator * (const Bignum& num) const {
    Bignum ret = *this;
    ret *= num;
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Divide.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
inline Bignum<limits_t, container_t>
Bignum<limits_t, container_t>::operator / (const Bignum& num) const {
    Bignum ret = *this;
    ret /= num;
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Addition with assignment
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
Bignum<limits_t, container_t>&
Bignum<limits_t, container_t>::operator +=(const Bignum& num) {
    
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
            abs_val_add<limits_t, container_t>(numData, num.numData);
        }
        // add a negative to a positive
        else if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
            // make sure that only the larger number is added
            if (abs_val_is_ge<container_t>(this->numData, num.numData)) {
                // subtract as normal
                abs_val_sub<limits_t, container_t>(numData, num.numData);
                return *this;
            }
            else {
                Bignum tempNum = num;
                abs_val_sub<limits_t, container_t>(tempNum.numData, numData);
                tempNum.descriptor = BN_NEG;
                *this = std::move(tempNum);
                return *this;
            }
        }
        // add a positive to a negative
        else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
            // make sure that only the larger number is added
            if (abs_val_is_ge<container_t>(this->numData, num.numData)) {
                // subtract as normal
                abs_val_sub<limits_t, container_t>(numData, num.numData);
                return *this;
            }
            else {
                Bignum tempNum = num;
                abs_val_sub<limits_t, container_t>(tempNum.numData, numData);
                tempNum.descriptor = BN_POS;
                *this = std::move(tempNum);
                return *this;
            }
        }
        // add a negative to a negative
        else {
            abs_val_add<limits_t, container_t>(numData, num.numData);
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
Bignum<limits_t, container_t>&
Bignum<limits_t, container_t>::operator -=(const Bignum& num) {
    
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
            if (abs_val_is_ge<container_t>(this->numData, num.numData)) {
                // subtract as normal
                abs_val_sub<limits_t, container_t>(numData, num.numData);
            }
            else {
                Bignum tempNum = num;
                abs_val_sub<limits_t, container_t>(tempNum.numData, numData);
                tempNum.descriptor = BN_NEG;
                *this = std::move(tempNum);
            }
        }
        // subtract a negative from a positive
        else if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
            container_t temp = abs_val_is_gt(numData, num.numData) ? numData : num.numData;
            abs_val_sub<limits_t, container_t>(temp, num.numData);
            numData = std::move(temp);
        }
        // subtract a positive from a negative
        else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
            container_t temp = abs_val_is_gt(numData, num.numData) ? numData : num.numData;
            abs_val_sub<limits_t, container_t>(temp, num.numData);
            numData = std::move(temp);
        }
        // subtract a negative from a negative
        else {
            // make sure that only the larger number is added
            if (abs_val_is_ge<container_t>(this->numData, num.numData)) {
                // subtract as normal
                abs_val_sub<limits_t, container_t>(numData, num.numData);
            }
            else {
                Bignum tempNum = num;
                abs_val_sub<limits_t, container_t>(tempNum.numData, numData);
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
// Multiplication with assignment
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
Bignum<limits_t, container_t>&
Bignum<limits_t, container_t>::operator *=(const Bignum& num) {

    // Make sure no unneeded calculations are performed
    if (!isComputable(descriptor)) {
        numData.clear();
        descriptor = num.descriptor;
        return *this;
    }

    Bignum ret;

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
        ret.numData = std::move(mul_strassen<limits_t, container_t>(numData, num.numData));
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
// Division with assignment
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
Bignum<limits_t, container_t>&
Bignum<limits_t, container_t>::operator /=(const Bignum& num) {

    // Make sure no unneeded calculations are performed
    if (!isComputable(descriptor)) {
        numData.clear();
        descriptor = num.descriptor;
        return *this;
    }

    static constexpr bn_double SINGLE_BASE_MIN = bn_min_limit<bn_single>();
    
    // subtract a negative from a positive
    if (this->descriptor == BN_POS && num.descriptor == BN_NEG) {
        descriptor = BN_NEG;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_NEG) {
        descriptor = BN_POS;
    }
    else if (this->descriptor == BN_NEG && num.descriptor == BN_POS) {
        descriptor = BN_NEG;
    }
    else {
        descriptor = BN_POS;
    }

    if (num.numData.size() == 1 && num.numData[0] == SINGLE_BASE_MIN)
    {
        numData.clear();
        descriptor = descriptor == BN_NEG ? BN_NEG_INF : BN_POS_INF;
        return *this;
    }

    if (num.numData.size() == 1 && num.numData[0] == (bn_single)1)
    {
        return *this;
    }

    if (numData.empty() || (numData.size() == 1 && numData[0] == SINGLE_BASE_MIN))
    {
        return *this;
    }

    // std::deque throws exceptions when a memory error occurs
    try {
        if (abs_val_is_gt(numData, num.numData))
        {
            abs_val_div<limits_t, container_t>(numData, num.numData);
        }
        else
        {
            numData = {bn_single{0}};
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
// Computation sanity check
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
bool Bignum<limits_t, container_t>::isComputable(bn_desc_t desc) {
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
