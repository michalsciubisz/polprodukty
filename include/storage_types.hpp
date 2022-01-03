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

    virtual void push(Package&& package) = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;

    const_iterator begin() const { return stockpile_.cbegin(); }
    const_iterator cbegin() const { return stockpile_.cbegin(); }
    const_iterator end() const { return stockpile_.cend(); }
    const_iterator cend() const { return stockpile_.cend(); }

    virtual ~IPackageStockpile() = default;

    std::list<Package> stockpile_;
};

class IPackageQueue: public IPackageStockpile {
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() const = 0;
};

class PackageQueue: public IPackageQueue {
public:
    PackageQueue(PackageQueueType queue_type) : queue_type_(queue_type) {}

    Package pop() override;
    PackageQueueType get_queue_type() const override { return queue_type_; }
    void push(Package&& package) override { queue_.emplace_back(std::move(package)); }
    size_t size() const override { return queue_.size(); }
    bool empty() const override { return queue_.size() == 0; }

    PackageQueueType queue_type_;
    std::list<Package> queue_;
};

#endif //POLPRODUKTY_STORAGE_TYPES_HPP
