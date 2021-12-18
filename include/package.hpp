//
// Created by michal on 14/12/2021.
//
#include "types.hpp"

#ifndef POLPRODUKTY_PACKAGE_HPP
#define POLPRODUKTY_PACKAGE_HPP

class Package {
public:
    Package() = default;
    Package(ElementID id) : id_(id) {}
    Package(Package&& p) //co tu se dzeje ziom // nw, skad wzielo sie blank id? xdd
    {
        id_ = p.get_id();
        p.id_ = BLANK_ID;
    }
    Package& operator=(Package&&) = default;
    ElementID get_id() { return id_; }
    ~Package() = default;

    ElementID id_;
};

#endif //POLPRODUKTY_PACKAGE_HPP
