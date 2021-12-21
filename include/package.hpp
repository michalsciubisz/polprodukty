//
// Created by michal on 14/12/2021.
//
#include "types.hpp"

#ifndef POLPRODUKTY_PACKAGE_HPP
#define POLPRODUKTY_PACKAGE_HPP
#include <set>

class Package {
public:
    Package(){///trzeba jeszcze dodać mechanizm usuwania z tych list i nie wiem gdzie to ma byc implementowane, chyba w zrodlowym ale to niewazne
        if(freed_IDs.size()){
            auto lo = *freed_IDs.cbegin();
            for(auto it = freed_IDs.begin(); it!=freed_IDs.end(); it++) {
                if (*it < lo) {
                    lo = *it;
                }
            }
            id_=lo;
        }
        else {
            auto hig = *assigned_IDs.cbegin();
            for (auto it = assigned_IDs.begin(); it != assigned_IDs.end(); it++) {
                if (*it > hig) {
                    hig = *it;
                }
            }
            assigned_IDs.insert(hig + 1);
            id_ = hig + 1;
        }
    };
    Package(ElementID id) : id_(id) {}
    Package(Package&&) = default;

    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;// nie wiem jak to ma byc, to co zrobiłem tu jest chyba zgodnie z instrukcją ale co dalej? gdzie nadać to id skoro jest ten konstruktor taki

    Package& operator=(Package&&) = default;
    ElementID get_id() const { return id_; }
    ~Package() = default;

    ElementID id_;
    static ElementID next_id_;
};

#endif //POLPRODUKTY_PACKAGE_HPP
