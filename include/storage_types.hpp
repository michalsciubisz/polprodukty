//
// Created by michal on 14/12/2021.
//

#ifndef POLPRODUKTY_STORAGE_TYPES_HPP
#define POLPRODUKTY_STORAGE_TYPES_HPP

enum PackageQueueType{FIFO, LIFO};

class PackageQueue{
    PackageQueue(PackageQueueType queue_type) : queue_type_(queue_type) {}

    PackageQueueType queue_type_;
};

class IPackageQueue{
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() {}
};

class IPackageStockpile{
    void push(Package&&);
    bool empty() {query;}
    size_type size() {query;}
    /iteratory/;
    ~IPackageStockpile();
};

#endif //POLPRODUKTY_STORAGE_TYPES_HPP
