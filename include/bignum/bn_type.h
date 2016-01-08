/* 
 * File:   bignum_type.h
 * Author: Miles Lacey
 *
 * Created on June 18, 2014, 1:30 PM
 */

#ifndef __BIGNUM_TYPE_H__
#define	__BIGNUM_TYPE_H__

#include <initializer_list>
#include <iostream>
#include <limits>
#include <cassert>

#include "bignum/bn_setup.h"
#include "bignum/bn_limits.h"
#include "bignum/bn_except.h"

///////////////////////////////////////////////////////////////////////////////
//          Enumerations
///////////////////////////////////////////////////////////////////////////////
/**
 * Descriptors that can be used to assist in identifying positive, negative,
 * infinite, or NaN bignums.
 * 
 * Integral values are used rather than bit fields in order to make state
 * handling much easier.
 */
enum bn_desc_t : int {
    BN_POS,
    BN_NEG,
    BN_NAN,
    BN_POS_INF,
    BN_NEG_INF
};

///////////////////////////////////////////////////////////////////////////////
//          Classes
///////////////////////////////////////////////////////////////////////////////
/**
 * Big Number Class
 * 
 * @note
 * Numerical data for this class is stored from the starting index of a deque
 * and progresses from low-values to high ones. It only prints in right-to-left
 * format (like base-10 decimal) when using ostreams.
 * 
 * @param limits_t
 * Any class specialization of the bn_limits_t structure.
 * 
 * @param container_t
 * A container which contains the union of members and methods found in between
 * an std::vector and std::deque.
 */
template <class limits_t, class container_t>
class bn_type final {
    /*
     * Friends
     */
    template <typename bs, typename bd>
    friend std::ostream& operator << (std::ostream&, const bn_type<bs, bd>&);
    
    /*
     * Public interface to non-member/static information.
     */
    public:
        /**
         * Storage container used by bignums
         */
        typedef container_t container_type;
        
        /**
         * Exposed single-precision type
         */
        typedef typename limits_t::base_single single_t;
        
        /**
         * Exposed double-precision type
         */
        typedef typename limits_t::base_double double_t;
        
        /**
         * Exposed single-precision type
         */
        typedef typename limits_t::base_single value_t;
        
        /**
         * Add a number into the first parameter.
         * This function is not designed to compare a bignum's descriptors.
         * 
         * @param The bignum_type where all numerical values will be
         * accumulated.
         * 
         * @param A number to add into the first.
         */
        static void absValAdd(container_type&, const container_type&);
        
        /**
         * Subtract a number from the first parameter.
         * The output parameter MUST be greater than the input, in both size and
         * numerical value.
         * This function is not designed to compare a bignum's descriptors.
         * 
         * @param The bignum_type where all numerical values will be
         * accumulated. This value MUST have an absolute value that is greater
         * than or equal to the second parameter.
         * 
         * @param A number to subtract from the first. This value MUST have an
         * absolute value that is less than or equal to the first parameter.
         */
        static void absValSub(container_type& largerNum, const container_type& smallerNum);
        
        /**
         * Compare the raw numerical data contained within a bignum.
         * This function is not designed to compare a bignum's descriptors.
         * 
         * @param const container_type&
         * 
         * @param const container_type&
         * 
         * @return TRUE if the two parameters are equal in numerical value,
         * FALSE if otherwise.
         */
        static bool absValIsEqual(const container_type&, const container_type&);
        
        /**
         * Determine if the first bignum container is greater than the second in
         * terms of numerical value.
         * This function is not designed to compare a bignum's descriptors.
         * 
         * @param const container_type&
         * 
         * @param const container_type&
         * 
         * @return TRUE if the first parameter is greater, in numerical value,
         * than the second parameter;
         * FALSE if otherwise.
         */
        static bool absValIsGreater(const container_type&, const container_type&);
        
        /**
         * Determine if the first bignum container is greater than or equal to
         * the second in terms of numerical value.
         * This function is not designed to compare a bignum's descriptors.
         * 
         * @param const container_type&
         * 
         * @param const container_type&
         * 
         * @return TRUE if the first parameter is greater, in numerical value,
         * than or equal to the second parameter;
         * FALSE if otherwise.
         */
        static bool absValIsGreaterOrEqual(const container_type&, const container_type&);
        
        /**
         * Determine if the first bignum container is less than the second in
         * terms of numerical value.
         * This function is not designed to compare a bignum's descriptors.
         * 
         * @param const container_type&
         * 
         * @param const container_type&
         * 
         * @return TRUE if the first parameter is less, in numerical value,
         * than the second parameter;
         * FALSE if otherwise.
         */
        static bool absValIsLess(const container_type&, const container_type&);
        
        /**
         * Determine if the first bignum container is less than or equal to
         * the second in terms of numerical value.
         * This function is not designed to compare a bignum's descriptors.
         * 
         * @param const container_type&
         * 
         * @param const container_type&
         * 
         * @return TRUE if the first parameter is less, in numerical value,
         * than or equal to the second parameter;
         * FALSE if otherwise.
         */
        static bool absValIsLessOrEqual(const container_type&, const container_type&);
        
        /**
         * Determine if a number can be computed.
         * 
         * @param bn_desc_t
         * 
         * @return
         * This function returns false if the input parameter is positive
         * infinite, negative infinite, or NaN.
         */
        static bool isComputable(bn_desc_t);
    
    /*
     * Private member information
     */
    private:
        bn_desc_t descriptor = BN_POS;
        container_type numData = {};
    
    /*
     * Public member information
     */
    public:
        /**
         * Constructor
         */
        bn_type();
        
        /**
         * Constructor with a number.
         * The number input is NOT in base-10, but rather base-"single_t"
         */
        bn_type(bn_desc_t, std::initializer_list<single_t>);
        
        /**
         * Copy Constructor
         * 
         * @param A bignum that should be copied into this.
         */
        bn_type(const bn_type&);
        
        /**
         * Move Contructor
         * Moves all data from the input parameter into *this. No copies are
         * performed.
         * 
         * @param num
         */
        bn_type(bn_type&&);
        
        /**
         * Destructor
         * 
         * Frees all memory and dynamic resources used by *this.
         */
        ~bn_type() = default;
        
        /**
         * Get the raw data contained within a bignum.
         * 
         * @return A dynamically allocated container object used to manage the
         * memory of a bignum.
         */
        const container_type& getData() const;
        
        /**
         * Find out more about a bignum.
         * 
         * @return the enumerations used to describe a bignum.
         */
        bn_desc_t getDescriptor() const;
        
        /**
         * Set the descriptor of a number.
         * All memory will be cleared if the descriptor is set to NaN or +/-INF
         * 
         * @param bn_desc_t
         */
        void setDescriptor(bn_desc_t);
        
        /**
         * Determine if a bignum is positive
         * 
         * @return
         * TRUE if the bignum is positive or towards positive infinity,
         * FALSE if otherwise
         */
        bool isPositive() const;
        
        /**
         * Determine if a bignum is negative
         * 
         * @return
         * TRUE if the bignum is negative or towards negative infinity,
         * FALSE if otherwise.
         */
        bool isNegative() const;
        
        /**
         * Determine if a bignum is infinite
         * 
         * @return
         * TRUE if the bignum is towards either positive or negative infinity,
         * FALSE if otherwise.
         */
        bool isInfinite() const;
        
        /**
         * Determine if a bignum is not a number (that is, it can't be used in
         * any more calculations due to memory constraints).
         * 
         * @return
         * TRUE if the bignum is not a number,
         * FALSE if otherwise.
         */
        bool isNan() const;
        
        /**
         * Reserve a certain amount of memory for manipulating a certain amount
         * of digits
         */
        void resize(typename container_type::size_type numDigits, single_t digits = limits_t::SINGLE_BASE_MIN);
        
        /**
         * Get the size (number of digits) that are currently used.
         * 
         * @return an unsigned integral type.
         */
        typename container_type::size_type size() const;
        
        /**
         * Push a single digit to the position of highest magnitude within this
         * object's internal container.
         * 
         * @param single_t
         */
        void push_front(single_t digit);
        
        /**
         * Remove a single digit from the position of highest magnitude within
         * this object's internal container.
         */
        void pop_front();
        
        /**
         * Push a single digit to the position of lowest magnitude within this
         * object's internal container.
         * 
         * @param single_t
         */
        void push_back(single_t digit);
        
        
        /**
         * Remove a single digit from the position of lowest magnitude within
         * this object's internal container.
         */
        void pop_back();
        
        /**
         * Push a single digit to an arbitrary position within this container.
         * 
         * Keep in mind that this object's numbers increase in magnitude from
         * the lowest index to the highest.
         * 
         * @param single_t
         */
        void push(single_t digit, typename container_type::size_type pos);
        
        /**
         * Remove a single digit from an arbitrary position within this
         * container.
         * 
         * Keep in mind that this object's numbers increase in magnitude from
         * the lowest index to the highest.
         * 
         * @param single_t
         */
        void pop(typename container_type::size_type pos);
        
        /**
         * Reset this object to it's original factory condition.
         */
        void clear();
        
        /**
         * Access a single digit from within this bignum and have the ability to
         * modify it in-place.
         * 
         * Keep in mind that this object's numbers increase in magnitude from
         * the lowest index to the highest.
         * 
         * @param iter
         * An unsigned integral type.
         * 
         * @return
         * A value of type "single_t."
         */
        single_t& operator[](typename container_type::size_type iter);
        
        
        /**
         * Access a single digit from within this bignum.
         * 
         * Keep in mind that this object's numbers increase in magnitude from
         * the lowest index to the highest.
         * 
         * @param iter
         * An unsigned integral type.
         * 
         * @return
         * A value of type "single_t."
         */
        single_t operator[](typename container_type::size_type iter) const;
        
        /**
         * Basic comparison
         * 
         * @param num
         * A bignum who's numbers should be compared to this.
         * 
         * @return TRUE if the input numberdata equals this number data,
         * FALSE if otherwise.
         */
        bool operator==(const bn_type&) const;
        
        /**
         * Basic "not" comparison
         * 
         * @param num
         * A bignum who's numbers should be compared to this.
         * 
         * @return FALSE if the input numberdata equals this number data,
         * TRUE if otherwise.
         */
        bool operator!=(const bn_type&) const;
        
        /**
         * Greater than operator
         * 
         * @param a bignum_type
         * 
         * @return TRUE if *this is greater than the parameter in terms of both
         * sign and numerical value.
         * FALSE if the input parameter is greater than or equal to *this.
         */
        bool operator > (const bn_type&) const;
        
        /**
         * Greater than/equal to operator
         * 
         * @param a bignum_type
         * 
         * @return TRUE if *this is greater than, or equal to, the parameter in
         * terms of both sign and numerical value.
         * FALSE if the input parameter is greater than to *this.
         */
        bool operator >= (const bn_type&) const;
        
        /**
         * Less than operator
         * 
         * @param a bignum_type
         * 
         * @return TRUE if *this is less than the parameter in terms of both
         * sign and numerical value.
         * FALSE if the input parameter is smaller than or equal to *this.
         */
        bool operator < (const bn_type&) const;
        
        /**
         * Less than/equal to operator
         * 
         * @param a bignum_type
         * 
         * @return TRUE if *this is less than the parameter in terms of both
         * sign and numerical value.
         * FALSE if the input parameter is smaller than *this.
         */
        bool operator <= (const bn_type&) const;
        
        /**
         * Copy assignment.
         * 
         * @param A bignum that will be copied into *this.
         * 
         * @return A reference to *this with the parameter value.
         */
        bn_type& operator=(const bn_type&);
        
        /**
         * Move assignment.
         * 
         * @param A bignum that will be moved into *this.
         * 
         * @return A reference to *this with the parameter value. The parameter
         * value is moved into this, preventing any copies in memory.
         */
        bn_type& operator=(bn_type&&);
        
        /**
         * Add.
         * 
         * @param A bignum that will be added to *this.
         * 
         * @return A copy of *this, with the parameter value added.
         */
        bn_type operator + (const bn_type&) const;
        
        /**
         * Subtract.
         * 
         * @param A bignum that will be subtracted from *this.
         * 
         * @return A copy of *this, with the parameter value subtracted.
         */
        bn_type operator - (const bn_type&) const;
        
        /**
         * Multiply.
         * 
         * @param A bignum that will be multiplied into *this.
         * 
         * @return A copy of *this, with the parameter value multiplied.
         */
        bn_type operator * (const bn_type&) const;
        
        /**
         * Add with assignment.
         * 
         * @param A bignum that will be added to *this.
         * 
         * @return A reference to *this.
         */
        bn_type& operator += (const bn_type&);
        
        /**
         * Subtract with assignment.
         * 
         * @param A bignum that will be subtracted from *this.
         * 
         * @return A reference to *this.
         */
        bn_type& operator -= (const bn_type&);
        
        /**
         * Multiplication with assignment.
         * 
         * @param A bignum that will be multiplied to *this.
         * 
         * @return A reference to *this.
         */
        bn_type& operator *= (const bn_type&);
};

#include "bignum/impl/bn_type_impl.h"

#endif	/* __BIGNUM_TYPE_H__ */
