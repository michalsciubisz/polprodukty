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
    using const_iterator = std::list<Package>::const_iterator;

    virtual void push() { stockpile_.push_back(Package&&); }
    virtual size_t size() const { return stockpile_.size(); }
    virtual bool empty() const { return stockpile_.size() == 0; }

    const_iterator begin() const { return stockpile_.cbegin(); }
    const_iterator cbegin() const { return stockpile_.cbegin(); }
    const_iterator end() const { return stockpile_.cend(); }
    const_iterator cend() const { return stockpile_.cend(); }

    virtual ~IPackageStockpile() = default;

    std::list<Package> stockpile_;
};

class IPackageQueue: public IPackageStockpile {
public:
    virtual Package pop() {}
    virtual PackageQueueType get_queue_type() const {}
};

class PackageQueue: public IPackageQueue {
public:
    PackageQueue(PackageQueueType queue_type) : queue_type_(queue_type) {}
    Package pop() override;
    PackageQueueType get_queue_type() const override { return queue_type_; }

    PackageQueueType queue_type_;
    std::list<Package> queue_;
};

#endif //POLPRODUKTY_STORAGE_TYPES_HPP
