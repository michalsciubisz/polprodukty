//
// Created by michal on 14/12/2021.
//
#include "types.hpp"

#ifndef POLPRODUKTY_PACKAGE_HPP
#define POLPRODUKTY_PACKAGE_HPP
#include <set>

class Package {
public:
    Package() = default;
    Package(ElementID id) : id_(id) {}
    Package(Package&&) = default;

    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;// nie wiem jak to ma byc, to co zrobiłem tu jest chyba zgodnie z instrukcją ale co dalej? gdzie nadać to id skoro jest ten konstruktor taki

    Package& operator=(Package&&) = default;
    ElementID get_id() const { return id_; }
    ~Package() = default;

    ElementID id_;
};

#endif //POLPRODUKTY_PACKAGE_HPP
