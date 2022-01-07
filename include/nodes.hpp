//
// Created by michal on 04/01/2022.
//

#ifndef MAIN_CPP_NODES_HPP
#define MAIN_CPP_NODES_HPP
#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"

class IPackageReceiver{
    virtual void receive_package(Package&& p) = 0;
    virtual ElementID get_id() const = 0;
};

class ReceiverPreferences{
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg) : pg_(pg) {}
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    preferences_t& get_preferences() {}
};

class PackageSender : ReceiverPreferences{
public:
    PackageSender(PackageSender&&) = default;

    ReceiverPreferences receiver_preferences_;
    void send_package();
    std::optional<Package>& get_sending_buffer();
protected:
    void push_package(Package&&);
};

class Ramp : PackageSender{
public:
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {}
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() {return di_}
    ElementID get_id() {return id_}
    ElementID id_;
    TimeOffset di_;
};

class Worker : IPackageReceiver{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), q_(q) {}
    void do_work(Time t);
    TimeOffset get_processing_duration();
    Time get_package_processing_start_time();

    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
};

class Storehouse : IPackageReceiver{
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d) : id_(id), d_(d) {}
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
};
#endif //MAIN_CPP_NODES_HPP
