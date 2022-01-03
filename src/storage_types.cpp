//
// Created by michal on 14/12/2021.
//
#include "storage_types.hpp"

Package PackageQueue::pop() {
    switch (queue_type_) {
        case FIFO: {
            Package popped = std::move(queue_.back());
            queue_.pop_back();
            return popped;
        }
        case LIFO: {
            Package popped = std::move(queue_.front());
            queue_.pop_front();
            return popped;
        }
        default:
            return 0;
    }
}