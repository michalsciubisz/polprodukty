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
    if(not buffer_ && not q_->empty()){
        buffer_.emplace(q_->pop());
        ppst_ = time;
    }
    if (buffer_){
        if (time-ppst_ >= pd_-1) {
            push_package(std::move(buffer_.value()));
            buffer_ = std::nullopt;
        }
    }
}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    double receiver = pg_();
    double prob_sum = 0;
    for (const auto&[key, value] : preferences_) {
        prob_sum = prob_sum + value;
        if (receiver < prob_sum) {
            return key;
        }
    }
    return preferences_.begin()->first;
}

void Ramp::deliver_goods(Time t){
    if ((t + di_ - 1) % (di_) == 0)
    {
        push_package(Package());
    }
}

void PackageSender::send_package() {
    if (sending_buffer_ != std::nullopt)
    {
        receiver_preferences_.choose_receiver()->receive_package(std::move(sending_buffer_.value()));
        sending_buffer_ = std::nullopt;
    }
}