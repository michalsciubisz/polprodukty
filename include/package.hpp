//
// Created by michal on 14/12/2021.
//

#ifndef POLPRODUKTY_PACKAGE_HPP
#define POLPRODUKTY_PACKAGE_HPP

class Package {
public:
    Package(ElementID id) : id_(id) {}
    Package(Package&& p) //co tu se dzeje ziom
    {
        id = p.get_id();
        p.id = BLANK_ID;
    }
    operator = (Package&&) {return Package&;}
    ElementID get_id() {return query;}
    ~Package()

    ElementID id;
};

#endif //POLPRODUKTY_PACKAGE_HPP
