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
    Package(Package&&) = default;
    Package& operator=(Package&&) = default;
    ElementID get_id() { return id_; }
    ~Package() = default;

    ElementID id_;
};

#endif //POLPRODUKTY_PACKAGE_HPP
