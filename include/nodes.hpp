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
#include <optional>


enum class ReceiverType {WORKER, STOREHOUSE};


class IPackageReceiver {
public:
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
    virtual ReceiverType get_receiver_type() const = 0;
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


    const_iterator begin() const { return preferences_.begin(); }
    const_iterator cbegin() const { return preferences_.cbegin(); }
    const_iterator end() const { return preferences_.end(); }
    const_iterator cend() const { return preferences_.cend(); }
private:
    ProbabilityGenerator pg_;
    preferences_t preferences_;
};

class PackageSender: public ReceiverPreferences {
public:
    PackageSender() {receiver_preferences_ = ReceiverPreferences();}
    PackageSender(PackageSender&&) = default;

    void send_package();
    const std::optional<Package>& get_sending_buffer() const { return sending_buffer_;}

    ReceiverPreferences receiver_preferences_;

private:
    std::optional<Package> sending_buffer_ = std::nullopt;

protected:
    void push_package(Package&& p) {sending_buffer_.emplace(std::move(p));}
};

class Ramp: public PackageSender {
public:

    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {}
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const {return di_;}
    ElementID get_id() {return id_;}
private:
    ElementID id_;
    TimeOffset di_;
};

class Worker: public PackageSender, public IPackageReceiver{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)) {}
    void do_work(Time t);
    TimeOffset get_processing_duration() const { return pd_; }
    Time get_package_processing_start_time() const { return ppst_; }
    void receive_package(Package&& p) override { q_->push(std::move(p));}
    ElementID get_id() const override { return id_; }

    IPackageStockpile::const_iterator begin() const override { return q_->begin(); }
    IPackageStockpile::const_iterator cbegin() const override { return q_->cbegin(); }
    IPackageStockpile::const_iterator end() const override { return q_->end(); }
    IPackageStockpile::const_iterator cend() const override { return q_->cend(); }
    ReceiverType get_receiver_type() const override { return ReceiverType::WORKER; };
private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
    Time ppst_;
    std::optional<Package> buffer_ = std::nullopt;
};

class Storehouse: public IPackageReceiver{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d= std::make_unique<PackageQueue>(PackageQueue(PackageQueueType::LIFO))) : id_(id), d_(std::move(d)) {}
    void receive_package(Package &&p) override { d_->push(std::move(p)); }
    ElementID get_id() const override { return id_; }

    IPackageStockpile::const_iterator begin() const override { return d_->begin(); }
    IPackageStockpile::const_iterator cbegin() const override { return d_->cbegin(); }
    IPackageStockpile::const_iterator end() const override { return d_->end(); }
    IPackageStockpile::const_iterator cend() const override { return d_->cend(); }
    ReceiverType get_receiver_type() const override { return ReceiverType::STOREHOUSE; };
private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
};
#endif //MAIN_CPP_NODES_HPP
