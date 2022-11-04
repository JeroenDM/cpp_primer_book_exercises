#pragma once

#include <iterator>

namespace aa {

namespace _impl {

    template <typename It>
    struct outside_in_iterator {
        using value_type = typename std::iterator_traits<It>::value_type;

        static It calculate_last_it(It begin, It end)
        {
            It last = begin;
            std::advance(last, std::distance(begin, end) / 2);
            return last;
        }

        outside_in_iterator(It begin, It end)
            : front_ { begin }
            , back_ { end }
            , last_ { calculate_last_it(begin, end) }
        {
            --back_;
        }

        static outside_in_iterator make_begin(It begin, It end)
        {
            outside_in_iterator it(begin, end);
            it.current_ = begin;
            return it;
        }

        static outside_in_iterator make_end(It begin, It end)
        {
            outside_in_iterator it(begin, end);
            it.current_ = it.last_;
            return it;
        }

        value_type& operator++()
        {
            if (distance(current_, last_) > 0) {
                current_ = back_;
                ++front_;
            } else if (distance(current_, last_) < 0) {
                current_ = front_;
                --back_;
            } else {
                current_ = last_; // TODO what should the behaviour be?
            }
            return *current_;
        }

        value_type& operator*()
        {
            return *current_;
        }

        bool operator!=(const outside_in_iterator& other) const
        {
            return current_ != other.current_;
        }

        It front_;
        It back_;
        It current_;
        It last_;
    };

}

template <typename It>
class OutsideInAdaptor {
public:
    using iterator = _impl::outside_in_iterator<It>;

    OutsideInAdaptor(It begin, It end)
        : front_ { begin }
        , back_ { end }
    {
    }

    iterator begin() { return iterator::make_begin(front_, back_); }
    iterator end() { return iterator::make_end(front_, back_); }

private:
    It front_;
    It back_;
};
}