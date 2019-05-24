


///////////////////////////////////////////////////////////////////////////////
// Division implementation of numbers with the same sign.
///////////////////////////////////////////////////////////////////////////////
template <class limits_t, class container_t>
void abs_val_div(
    container_t& dividend,
    const container_t& divisor
) {
    typedef typename limits_t::base_single bn_single;
    typedef typename limits_t::base_double bn_double;
    
    // numerical limits
    static constexpr bn_double SINGLE_BASE_LIMIT = bn_max_limit<bn_single>() + (bn_double)1;
    static constexpr bn_double SINGLE_BASE_MAX = bn_max_limit<bn_single>();
    static constexpr bn_double SINGLE_BASE_MIN = bn_min_limit<bn_single>();
    
    const auto shift_left_1 = [](container_t& container)->void
    {
        if (container.empty())
        {
            return;
        }

        typename container_t::size_type curr = 0;
        typename container_t::value_type carry = 0;

        while (curr < container.size())
        {
            bn_single temp = (container[curr] * (bn_single)2) + carry;
            container[curr] = temp;
            carry = (bn_single)(temp > (bn_single)SINGLE_BASE_MAX ? 1 : 0);
            container[curr] = temp % (bn_single)SINGLE_BASE_LIMIT;
            ++curr;
        }

        if (carry)
        {
            container.push_back((bn_single)SINGLE_BASE_MIN + (bn_single)1);
        }
    };

    container_t res{{(bn_single)0}};

    while (abs_val_is_ge<container_t>(dividend, divisor))
    {
        container_t bsrch0 = divisor;
        container_t bsrch1 = divisor;
        container_t q{{(bn_single)1}};

        shift_left_1(bsrch1);

        while (abs_val_is_ge<container_t>(dividend, bsrch1))
        {
            bsrch0 = bsrch1;

            shift_left_1(bsrch1);
            shift_left_1(q);
        }

        abs_val_sub<limits_t, container_t>(dividend, bsrch0);

        if (res.size() >= q.size())
        {
            abs_val_add<limits_t, container_t>(res, q);
        }
        else
        {
            abs_val_add<limits_t, container_t>(q, res);
            res = std::move(q);
        }
    }

    dividend = std::move(res);

}
