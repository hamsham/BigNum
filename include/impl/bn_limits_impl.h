/* 
 * File:   bn_limits_impl.h
 * Author: A435534a
 *
 * Created on July 18, 2014, 9:28 PM
 */

#define BN_DEFINE_LIMITS(numType) \
    template<> \
    constexpr bn_limit_t bn_min_limit<numType>() { \
        return std::numeric_limits<numType>::min(); \
    } \
    \
    template<> \
    constexpr bn_limit_t bn_max_limit<numType>() { \
        return std::numeric_limits<numType>::max(); \
    }

BN_DEFINE_LIMITS(BN_UINT8)
BN_DEFINE_LIMITS(BN_UINT16)
BN_DEFINE_LIMITS(BN_UINT32)
BN_DEFINE_LIMITS(BN_UINT64)

#undef BN_DEFINE_LIMITS
