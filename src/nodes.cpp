//
// Created by michal on 04/01/2022.
//
#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver* r){
    preferences_.insert({r, 0.0});
    for (const auto& [key, value] : preferences_) {
        preferences_[key] = 1/double(preferences_.size());
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    preferences_.erase(r);
    for (const auto& [key, value] : preferences_) {
        preferences_[key] = 1/double(preferences_.size());
    }
}

void Worker::do_work(Time time) {
 time++;
}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    return 0;
}

void Ramp::deliver_goods(Time t) {
t++;
}

void PackageSender::send_package() {

}