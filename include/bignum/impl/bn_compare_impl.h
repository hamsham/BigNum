


///////////////////////////////////////////////////////////////////////////////
// Equating implementation
///////////////////////////////////////////////////////////////////////////////
template <class container_type>
bool abs_val_is_eq(
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
template <class container_type>
bool abs_val_is_gt(
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
template <class container_type>
bool abs_val_is_ge(
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
template <class container_type>
bool abs_val_is_lt(
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
template <class container_type>
bool abs_val_is_le(
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
