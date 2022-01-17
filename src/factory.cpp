//
// Created by michal on 04/01/2022.
//
#include <stdexcept>
#include <map>
#include "factory.hpp"

void Factory::do_work(Time time) {
    for (auto elem = worker_collection_.begin(); elem != worker_collection_.end(); elem++) {
        elem->do_work(time);
    }
}

void Factory::do_deliveries(Time time) {
    for (auto elem = ramp_collection_.begin(); elem != ramp_collection_.end(); elem++) {
        elem->deliver_goods(time);
    }
}

void Factory::do_package_passing() {
    for (auto elem = worker_collection_.begin(); elem != worker_collection_.end(); elem++) {
        elem->send_package();
    }
    for (auto elem = ramp_collection_.begin(); elem != ramp_collection_.end(); elem++) {
        elem->send_package();
    }
}

bool Factory::is_consistent() const {
    std::map<const PackageSender*, NodeColor> color;
    for (auto elem = worker_collection_.begin(); elem != worker_collection_.end(); elem++) {
        color.insert(std::pair<const PackageSender*, NodeColor>(dynamic_cast<const PackageSender*>(&*elem), NodeColor::NOTVISITED));
    }
    for (auto elem = ramp_collection_.begin(); elem != ramp_collection_.end(); elem++) {
        color.insert(std::pair<const PackageSender*, NodeColor>(dynamic_cast<const PackageSender *>(&*elem), NodeColor::NOTVISITED));
    }

    for (auto elem = ramp_collection_.begin(); elem != ramp_collection_.end(); elem++) {
        try {
            has_reachable_storehouse(dynamic_cast<const PackageSender *>(&*elem), color);
        }
        catch (std::invalid_argument&) {
            return false;
        }
    }
    return true;
}


bool Factory::has_reachable_storehouse(const PackageSender *sender, std::map<const PackageSender*, NodeColor>& node_colors) const {
    if (node_colors[sender] == NodeColor::VERIFIED) {
        return true;
    }
    node_colors[sender] = NodeColor::VISITED;

    if (sender->receiver_preferences_.get_preferences().empty()) {
        throw std::invalid_argument("Receivers are not defined");
    }

    bool has_other_receivers = false;
    for (auto &receiver : sender->receiver_preferences_.get_preferences()) {
        if (receiver.first->get_receiver_type() == ReceiverType::STOREHOUSE) {
            has_other_receivers = true;
        }
        else if (receiver.first->get_receiver_type() == ReceiverType::WORKER) {
            IPackageReceiver *receiver_ptr = receiver.first;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if (sendrecv_ptr == sender) {
                continue;
            }
            has_other_receivers = true;
            if (node_colors[sendrecv_ptr] == NodeColor::NOTVISITED) {
                has_reachable_storehouse(sendrecv_ptr, node_colors);
            }
        }
    }

    node_colors[sender] = NodeColor::VERIFIED;

    if (has_other_receivers) {
        return true;
    }
    else {
        throw std::invalid_argument("Receivers are not defined");
    }
}
