/*
Exercise 3.3.3, but using iterators

Read a sequence of words from cin and store the values a vector. After you’ve read all the words, process the vector and change each word to uppercase.
Print the transformed elements, eight words to a line.
*/

#include <iostream>
#include <locale>
#include <string>
#include <type_traits>
#include <vector>

#include "util.h"

using namespace std;

template <typename It, typename Fun>
void my_transform_inplace(It in_start, It in_end, Fun f)
{
    for (auto it = in_start; it != in_end; ++it) {
        f(*it);
    }
}

// chuck_size cannot be size_t according to '-Wconversion' warning, but difference_type is singed
// and chuck_size cannot be negative?
template <typename It, typename Fun>
void chuck_apply(It start, It end, Fun f, typename iterator_traits<It>::difference_type chunk_size)
{
    while (distance(start, end) >= chunk_size) {
        f(start, start + chunk_size);
        start += chunk_size;
    }
    f(start, end);
}

int main(int, char**)
{

    vector<string> words;
    string word;
    while (getline(cin, word)) {
        words.push_back(word);
    }

    my_transform_inplace(
        words.begin(),
        words.end(),
        [](string& word) {
            my_transform_inplace(
                word.begin(),
                word.end(),
                [](auto& c) {
                    c = toupper(c, locale());
                });
        });

    chuck_apply(
        words.begin(),
        words.end(),
        [](auto start, auto end) {
            cout << aa::join(start, end, ", ") << "\n";
        },
        8);
}