//
// Created by michal on 04/01/2022.
//

#ifndef MAIN_CPP_FACTORY_HPP
#define MAIN_CPP_FACTORY_HPP

#include "types.hpp"
#include "nodes.hpp"

//struct ParsedLineData{
//    enum class ElementType{
//        RAMP,
//        WORKER,
//        STOREHOUSE,
//        LINK
//    } element_type;
//    std::map<std::string, std::string> parameters;
//};


enum class NodeColor
{
    NOTVISITED,
    VISITED,
    VERIFIED
};

template <class Node>
class NodeCollection
{

public:
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;
    void add(Node &&node) { collection_.push_back(std::move(node)); };
    void remove_by_id(ElementID id)
    {
        collection_.remove_if([id](Node &n)
                              { return n.get_id() == id; });
    };
    NodeCollection<Node>::iterator find_by_id(ElementID id)
    {
        return std::find_if(collection_.begin(), collection_.end(), [id](Node &n)
        { return n.get_id() == id; });
    };
    NodeCollection<Node>::const_iterator find_by_id(ElementID id) const
    {
        return std::find_if(collection_.cbegin(), collection_.cend(), [id](Node const &n)
        { return n.get_id() == id; });
    };
    const_iterator begin() const { return collection_.begin(); };
    const_iterator cbegin() const { return collection_.cbegin(); };
    const_iterator end() const { return collection_.end(); };
    const_iterator cend() const { return collection_.cend(); };
    iterator begin() { return collection_.begin(); };
    iterator end() { return collection_.end(); };

private:
    container_t collection_;
};

class Factory
{
private:
    NodeCollection<Ramp> ramp_collection_;
    NodeCollection<Worker> worker_collection_;
    NodeCollection<Storehouse> storehouse_collection_;
    template <class Node>
    void remove_receiver(NodeCollection<Node> &collection, ElementID id)
    {

        typename NodeCollection<Node>::iterator receiver = collection.find_by_id(id);

        for (auto &node : worker_collection_)
        {
            node.receiver_preferences_.remove_receiver(&*receiver);
        }
        for (auto &node : ramp_collection_)
        {
            node.receiver_preferences_.remove_receiver(&*receiver);
        }

        collection.remove_by_id(id);
    }
    bool has_reachable_storehouse(const PackageSender *sender, std::map<const PackageSender *, NodeColor> &node_colors) const;

public:
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const { return ramp_collection_.begin(); };
    NodeCollection<Ramp>::const_iterator ramp_begin() const { return ramp_collection_.begin(); };
    NodeCollection<Ramp>::const_iterator ramp_cend() const { return ramp_collection_.cend(); };
    NodeCollection<Ramp>::const_iterator ramp_end() const { return ramp_collection_.end(); };

    void add_ramp(Ramp &&r) { ramp_collection_.add(std::move(r)); };
    void remove_ramp(ElementID id) { ramp_collection_.remove_by_id(id); };
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) { return ramp_collection_.find_by_id(id); };
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const { return ramp_collection_.find_by_id(id); };

    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const { return storehouse_collection_.cbegin(); };
    NodeCollection<Storehouse>::const_iterator storehouse_begin() const { return storehouse_collection_.begin(); };
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const { return storehouse_collection_.cend(); };
    NodeCollection<Storehouse>::const_iterator storehouse_end() const { return storehouse_collection_.end(); };

    void add_storehouse(Storehouse &&s) { storehouse_collection_.add(std::move(s)); };
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) { return storehouse_collection_.find_by_id(id); };
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const { return storehouse_collection_.find_by_id(id); };

    NodeCollection<Worker>::const_iterator worker_cbegin() const { return worker_collection_.cbegin(); };
    NodeCollection<Worker>::const_iterator worker_begin() const { return worker_collection_.begin(); };
    NodeCollection<Worker>::const_iterator worker_cend() const { return worker_collection_.cend(); };
    NodeCollection<Worker>::const_iterator worker_end() const { return worker_collection_.end(); };

    void add_worker(Worker &&s) { worker_collection_.add(std::move(s)); };
    void remove_worker(ElementID id) { remove_receiver(worker_collection_, id); };
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) { return worker_collection_.find_by_id(id); };
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const { return worker_collection_.find_by_id(id); };

    bool is_consistent() const;
    void do_deliveries(Time time);
    void do_package_passing();
    void do_work(Time time);
};

//std::string convert_to_string(PackageQueueType queue_type);
//ParsedLineData parse_line(std::string line);
//PackageQueueType convert(std::string str);
//Factory load_factory_structure(std::istream& is);
//void save_factory_structure(Factory& factory, std::ostream& os);

#endif //MAIN_CPP_FACTORY_HPP
