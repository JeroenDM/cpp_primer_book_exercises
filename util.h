#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace std {
// Extend std::to_string for std::string input as no-op.
inline string& to_string(string& s)
{
    return s;
}
}

namespace aa {

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

// assume output iterator can be incremented enough times.
template <typename It, typename Fun>
void my_transform(It in_start, It in_end, It out, Fun f)
{
    for (auto it = in_start; it != in_end; ++it, ++out) {
        (*out) = f(*it);
    }
}

} // namespace aa