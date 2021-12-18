//
// Created by michal on 14/12/2021.
//
#include "storage_types.hpp"

Package PackageQueue::pop() {
    switch (queue_type_) {
        case FIFO: {
            Package& popped = queue_.back();
            queue_.pop_back();
            return popped;
        }
        case LIFO:
            Package& popped = queue_.front();
            queue_.pop_front();
            return popped;
    }
}