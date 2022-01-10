//
// Created by michal on 04/01/2022.
//

#ifndef MAIN_CPP_NODES_HPP
#define MAIN_CPP_NODES_HPP

#include <memory>
#include <map>
#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include "helpers.hpp"

enum class ReceiverType {RAMP, WORKER, STOREHOUSE};


class IPackageReceiver {
    virtual void receive_package(Package&& p) = 0;
    virtual ElementID get_id() const = 0;

    // W klasie IPackageReceiver nie musisz definiować nowych aliasów na typ std::list<Package>::const_iterator “od zera” –
    // możesz zdefiniować go w oparciu o alias IPackageStockpile::const_iterator
    // (albo skorzystać wprost z IPackageStockpile::const_iterator bezpośrednio w nagłówkach metod).
    // tylko do czego maja sie odnosic te itaratory?
    virtual IPackageStockpile::const_iterator begin() const = 0;
    virtual IPackageStockpile::const_iterator cbegin() const = 0;
    virtual IPackageStockpile::const_iterator end() const = 0;
    virtual IPackageStockpile::const_iterator cend() const = 0;
};

class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : pg_(pg) {}
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const preferences_t& get_preferences() const {return preferences_;}
    ProbabilityGenerator pg_;
    preferences_t preferences_;

};

class PackageSender: public ReceiverPreferences {
public:
    PackageSender() {receiver_preferences_ = ReceiverPreferences();}
    PackageSender(PackageSender&&) = default;

    void send_package();
    //std::optional<Package>& get_sending_buffer();

    ReceiverPreferences receiver_preferences_;

protected:
    void push_package(Package&&);
};

class Ramp: public PackageSender {
public:

    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {}
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const {return di_;}
    ElementID get_id() {return id_;}
    ElementID id_;
    TimeOffset di_;
};

class Worker: public PackageSender, public IPackageReceiver, public IPackageQueue {
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)) {}
    void do_work(Time t);
    TimeOffset get_processing_duration() { return pd_; }
    Time get_package_processing_start_time() { return id_; }

    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
};

class Storehouse: public IPackageReceiver, public IPackageStockpile {
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d) : id_(id), d_(std::move(d)) {}
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
    ElementID id() {return id_;}
};
#endif //MAIN_CPP_NODES_HPP
