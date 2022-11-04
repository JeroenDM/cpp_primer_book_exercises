/**
 * 3.20 with iterators
 *
 * Read a set of integers into a vector. Print the sum of each pair of
 * adjacent elements. Change your program so that it prints the sum of the first and last
 * elements, followed by the sum of the second and second-to-last, and so on.
 * **/
#include <iostream>
#include <memory>
#include <vector>

#include "outside_in_adaptor.h"
#include "util.h"

using namespace std;

template <typename It, typename Fun>
void chuck_apply(It start, It end, Fun f, typename iterator_traits<It>::difference_type chunk_size)
{
    while (distance(start, end) >= chunk_size) {
        f(start, start + chunk_size);
        start += chunk_size;
    }
    f(start, end);
}

/** Shorter version of the obscenely long trait when we need to use it two times in function declaration. **/
template <typename It>
using Value = typename iterator_traits<It>::value_type;

template <typename It>
auto sum(It start, It end, Value<It> init = Value<It> { 0 })
{
    while (start != end) {
        init += *start;
        ++start;
    }
    return init;
}

template <typename It, typename Fun>
void outside_in_apply(It begin, It end, Fun f)
{
    // Calculate the last valid iterator.
    auto half = distance(begin, end) / 2;
    It last = begin;
    advance(last, half);

    // Make sure we can dereference the last value later on.
    --end;

    // Logic to jump around in the sequence.
    auto increment = [&](It& c) {
        if (distance(c, last) > 0) {
            c = end;
            ++begin;
        } else {
            c = begin;
            --end;
        }
    };

    // This is where the actual work is happening.
    It current = begin;
    while (current != last) {
        f(*current);
        increment(current);
    }
}

int main(int, char**)
{
    // An odd number of ints.
    std::vector<int> ints { 5, 2, 6, 3, 1, 6, 7, 12, 4, 5, 11 };

    std::cout << ints << "\n";

    std::vector<int> sums;
    sums.reserve(ints.size() / 2 + 1);

    chuck_apply(
        ints.begin(),
        ints.end(),
        [&sums](auto start, auto end) {
            sums.push_back(sum(start, end));
        },
        2);

    std::cout << sums << "\n";

    std::cout << "\nCrazy iterator adaptor:\n";

    for (int x : aa::OutsideInAdaptor(ints.begin(), ints.end())) {
        std::cout << "sum: " << x << "\n";
    }

    std::cout << "\nSimple generic algorithm:\n";

    outside_in_apply(
        ints.begin(),
        ints.end(),
        [](int x) { std::cout << "sum: " << x << "\n"; });
}