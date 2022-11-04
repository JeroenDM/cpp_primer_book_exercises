/*
Exercise 3.3.3, but using iterators

Write a program to print the size and contents of the vectors.
*/
#include <algorithm>
#include <iostream>
#include <vector>
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
}