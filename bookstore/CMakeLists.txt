
find_package(Boost 1.74 REQUIRED COMPONENTS headers)

add_executable(bookstore bookstore.cpp)

target_link_libraries(bookstore PRIVATE Boost::headers)