/*
Look at the behaviour of std::vector<T>::swap.
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::string fmt_address(long long int count)
{
    return std::string("address_") + std::to_string(count);
}

std::string to_string(const int* ptr)
{
    static std::unordered_map<const int*, std::string> address_str;
    static long long int address_cnt { 0 };

    auto [it, inserted] = address_str.try_emplace(ptr, fmt_address(address_cnt));
    address_cnt += inserted;
    return it->second;
}

void print_vec_info(const std::vector<int>& vec)
{
    std::cout << "vector with size " << vec.size() << "/";
    std::cout << vec.capacity() << "\n";
    for (int a : vec) {
        std::cout << a << " ";
    }
    std::cout << "\n";
    std::cout << "address: " << ::to_string(&vec.front()) << "\n";
    std::cout << "--------------------\n";
}

int main(int, char**)
{
    using namespace std;

    vector<int> v1 { 1, 2, 3 };
    vector<int> v2 { 5, 6, 7, 9 };

    print_vec_info(v1);
    print_vec_info(v2);

    v1.swap(v2);

    print_vec_info(v1);
    print_vec_info(v2);
}
