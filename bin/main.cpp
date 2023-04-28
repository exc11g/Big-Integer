#include <lib/number.h>
#include <iostream>


int main() {
    uint2022_t num = from_string("405238") * from_string("23424232");
    std::cout << num << std::endl;
    print_struct(num);
    return 0;
}
