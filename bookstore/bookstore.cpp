#include <iostream>
#include <string>
#include <string_view>

#include <boost/algorithm/string.hpp>
#include <boost/container/static_vector.hpp>

namespace ba = boost::algorithm;
namespace bc = boost::container;

struct BookInfo {
    std::string isbn;
    int amount;
    int price_cents;

    static BookInfo from(std::string_view x)
    {
        bc::static_vector<std::string, 3> parts;
        ba::split(parts, x, ba::is_space());
        return {
            parts.at(0),
            std::stoi(parts.at(1)),
            parse_price(parts.at(2)),
        };
    }

    static int parse_price(std::string_view x)
    {
        bc::static_vector<std::string, 2> parts;
        ba::split(parts, x, ba::is_any_of("."));
        return std::stoi(parts.at(0)) * 100 + std::stoi(parts.at(1));
    }
};

int main()
{
    std::cout << "Bookstore\n";

    auto book = BookInfo::from("0-201-70353-X 4 24.99");
    std::cout << "book isbn: " << book.isbn << '\n';
    std::cout << "book amount: " << book.amount << '\n';
    std::cout << "book price: " << book.price_cents << '\n';
}