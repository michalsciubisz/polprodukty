#include <iostream>
#include "package.hpp"
#include "storage_types.hpp"

int main() {
    Package a;
    Package b;
    Package c;
    Package d;
    std::cout << a.get_id() << b.get_id() << c.get_id() << d.get_id() << '\n';

    PackageQueue q(FIFO);
    std::cout << q.empty() << '\n';
    q.push();
    q.push();
    std::cout << q.size() << '\n';
    q.pop();
    std::cout << q.size();
    return 0;


}
