#include <iostream>
#include "package.hpp"
#include "storage_types.hpp"

int main() {
    Package a;
    Package b;
    Package c;
    Package d;
    std::cout << a.get_id() << b.get_id() << c.get_id() << d.get_id() << '\n';
    {
        Package p1;
        std::cout << p1.get_id();
    }
    Package p2;
    std::cout<<p2.get_id();

    PackageQueue q(FIFO);
    std::cout << q.empty() << '\n';
    q.push(std::move(a));
    std::cout << q.size() << '\n';
    q.pop();
    std::cout << q.size();
    return 0;


}
