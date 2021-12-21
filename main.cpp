#include <iostream>
#include "package.hpp"

int main() {
    Package a;
    Package b;
    Package c;
    std::cout << a.get_id() << b.get_id() << c.get_id();
    return 0;

}
