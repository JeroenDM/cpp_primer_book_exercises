#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

#include <doctest/doctest.h>

template <typename I, typename Compare>
// requires I is a constant forward iterator
//          Compare is strict weak ordering on I::value_type
std::pair<I, I> minmax(I first, I last, Compare cmp)
{
    if (first == last) {
        return { last, last };
    }
    auto min_el = first;
    auto max_el = first;
    ++first;
    while (first != last) {
        if (cmp(*first, *min_el)) {
            min_el = first;
        } else if (!cmp(*first, *max_el)) {
            max_el = first;
        }
        ++first;
    }
    return { min_el, max_el };
}

TEST_CASE("constant")
{
    std::vector v { 2, 2, 2, 2, 2 };
    const auto& [min, max] = minmax(v.begin(), v.end(), std::less<int>());
    CHECK_EQ(min, v.begin());
    CHECK_EQ(max, v.end() - 1);
}

TEST_CASE("emtpy")
{
    std::vector<int> v;
    const auto& [min, max] = minmax(v.begin(), v.end(), std::less<int>());
    CHECK_EQ(min, v.begin());
    CHECK_EQ(max, v.end());
}

TEST_CASE("random")
{
    std::vector<int> v { 5, 2, 3, 1, 7, 2, 1, 4 };
    const auto& [min, max] = minmax(v.begin(), v.end(), std::less<int>());
    CHECK_EQ(min, v.begin() + 3);
    CHECK_EQ(max, v.begin() + 4);
}

TEST_CASE("increasing")
{
    std::vector<int> v { 1, 2, 3, 4, 5 };
    const auto& [min, max] = minmax(v.begin(), v.end(), std::less<int>());
    CHECK_EQ(min, v.begin());
    CHECK_EQ(max, v.end() - 1);
}

TEST_CASE("decreasing")
{
    std::vector<int> v { 5, 4, 3, 2, 1 };
    const auto& [min, max] = minmax(v.begin(), v.end(), std::less<int>());
    CHECK_EQ(min, v.end() - 1);
    CHECK_EQ(max, v.begin());
}