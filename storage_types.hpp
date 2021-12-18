//
// Created by michal on 14/12/2021.
//
#include <stack>
#include <list>
#include "package.hpp"

#ifndef POLPRODUKTY_STORAGE_TYPES_HPP
#define POLPRODUKTY_STORAGE_TYPES_HPP

enum PackageQueueType{FIFO, LIFO};

class IPackageStockpile {
public:
    //using std::list<Package>::const_iterator = const_iterator; jakos trzeba ten alias zrobic

    virtual void push() { stockpile_.push_back(Package&&); }
    virtual size_t size() const { return stockpile_.size(); }
    virtual bool empty() const { return stockpile_.size() == 0; }
    //iteratory/;
    std::list<Package>::const_iterator begin() const { return stockpile_.cbegin(); }
    std::list<Package>::const_iterator cbegin() const { return stockpile_.cbegin(); }
    std::list<Package>::const_iterator end() const { return stockpile_.cend(); }
    std::list<Package>::const_iterator cend() const { return stockpile_.cend(); }

    virtual ~IPackageStockpile() = default;

    std::list<Package> stockpile_;
};

class IPackageQueue: public IPackageStockpile {
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() {}
};

class PackageQueue: public IPackageQueue {
public:
    PackageQueue(PackageQueueType queue_type) : queue_type_(queue_type) {}

    PackageQueueType queue_type_;
    std::list<Package> queue_;
};

#endif //POLPRODUKTY_STORAGE_TYPES_HPP
