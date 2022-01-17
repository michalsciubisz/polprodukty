//
// Created by michal on 14/12/2021.
//


#ifndef POLPRODUKTY_PACKAGE_HPP
#define POLPRODUKTY_PACKAGE_HPP
#include <set>
#include "types.hpp"

class Package {
public:
    Package(){
        if(!freed_IDs.empty()){
            id_=*freed_IDs.begin();
            assigned_IDs.insert(*freed_IDs.begin());
            freed_IDs.erase(freed_IDs.begin());
        }
        else {
            ElementID end_id = *assigned_IDs.rbegin();
            assigned_IDs.insert(end_id + 1);
            id_ = end_id + 1 ;
        }
    };
    Package(ElementID id) : id_(id) {}
    Package(const Package &p) { id_ = p.get_id(); };
    Package(Package&&) = default;

    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;// nie wiem jak to ma byc, to co zrobiłem tu jest chyba zgodnie z instrukcją ale co dalej? gdzie nadać to id skoro jest ten konstruktor taki

    Package& operator=(Package&&) = default;
    ElementID get_id() const { return id_; }
    ~Package() {
        assigned_IDs.erase(id_);
        freed_IDs.insert(get_id());
    }

    ElementID id_;
};

#endif //POLPRODUKTY_PACKAGE_HPP
