/*
Exercise 3.3.3, but using iterators

Write a program to print the size and contents of the vectors.
*/
#include <array>
#include <iostream>
#include <list>
#include <locale>
#include <string>
#include <utility> // pair
#include <vector>
#include "util.h"

using namespace std;

template <typename It>
std::string join(It start, It end, const std::string& c)
{
    std::string joined;
    for (auto it = start; it != end; ++it) {
        joined += std::to_string(*it);
        if (it != end - 1)
            joined += c;
    }
    return joined;
}

template <typename T>
void print_info(const std::vector<T>& vec)
{
    std::cout << "size: " << vec.size() << "\n";
    std::cout << join(vec.cbegin(), vec.cend(), ", ");
    std::cout << "\n-----------\n";
}

int main(int, char**)
{

    vector<int> v1 { 1, 2, 3 };
    vector<int> v2 { 5, 6, 7, 9 };

    print_info(v1);
    print_info(v2);

    string sentence { "my name is" };
    string camelized = sentence;
    for (
        auto [it, out] = pair { sentence.begin(), camelized.begin() };
        it != sentence.end() && out != camelized.end() && !isspace(*it);
        ++it, ++out) {
        *out = toupper(*it, locale());
    }
    cout << sentence << "\n";
    cout << camelized << "\n";

    // Excercise 9.6
    list<int> my_list { 1, 4, 2, 5 };

    auto start = my_list.begin(), end = my_list.end();
    // while (start < end) { // Compilation error
    while (start != end) {
        cout << *start << ", ";
        ++start;
    }
    cout << "\n";

    array<int, 5> aa {1, 2, 3, };
    for (auto x : aa) cout << x << "\n";

    vector<int> vva {3, 2};
    vector<int> vvb (3, 2);
    vector<int> vvc(aa.begin(), aa.end());
    cout << "a: " << vva << "\n";
    cout << "b: " << vvb << "\n";
    cout << "c: " << vvc << "\n";
}
