//
// Created by michal on 14/12/2021.
//
#include "storage_types.hpp"

Package PackageQueue::pop() {
    switch (queue_type_) {
        case FIFO:
            queue_.pop_back();
        case LIFO:
            queue_.pop_front();
    }
}