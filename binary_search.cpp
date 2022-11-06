#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

#include "util.h"

/** Find element with needle in a sorted sequence.
 * 
 * How to change it so it returns the first element found in a sequence, no the middle?
 * 0, 1, 3, 3, 3, 5, 9 -> return index 3 instead of 2.
 * 
**/
template <typename It>
auto binary_search(It start, It end, typename std::iterator_traits<It>::value_type needle)
{
    It not_found = end;
    while (start < end) {
        It current = start + (end - start) / 2;
        if (*current == needle) {
            return current;
        } else if (*current < needle) {
            start = current + 1;
        } else /* (*current > needle) */
        {
            end = current;
        }
    }
    return not_found;
}

int main(int, char**)
{
    using namespace std;

    vector<int> v { 3, 1, 5, 2, 9, 0, 3 };
    sort(v.begin(), v.end());

    cout << v << "\n";

    auto res = ::binary_search(v.begin(), v.end(), 2);
    if (res != v.end()) {
        cout << "result: " << *res << " at index: " << distance(v.begin(), res) << "\n";
    } else {
        cout << "Element not found\n";
    }

    res = ::binary_search(v.begin(), v.end(), 99);
    if (res != v.end()) {
        cout << "result: " << *res << " at index: " << distance(v.begin(), res) << "\n";
    } else {
        cout << "Element not found\n";
    }
}