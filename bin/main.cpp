
#include <lib/number.h>
#include <iostream>

int main() {
    int2023_t value, value1, value2, value3, value4, value5, value6, value7;
    value1 = from_string("-3896");
    value2 = from_string("-1908");
    value3 = from_string("2");
//    value1 = from_string("8");
//    value2 = from_string("2");
//    value3 = from_string("4");
    value4 = value1 / value2;
//    bool ls = value == value2;
    std::cout << std::endl << value4 << std::endl << value3;
// 2**2023 - bin 1 бит - знак
    return 0;
}
