//
// Created by michal on 04/01/2022.
//
#include <stdexcept>
#include <map>
#include <sstream>
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

//ParsedLineData parse_line(std::string line){
//    std::istringstream token_stream(line);
//    char delimiter = ' ';
//
//    std::string token;
//    ParsedLineData new_line;
//    std::vector<std::string> tokens;
//    while (std::getline(token_stream, token, delimiter)) {
//        tokens.push_back(token);
//    }
//
//    if (*tokens.begin() == "LOADING_RAMP") {
//        new_line.element_type = ParsedLineData::ElementType::RAMP;
//    }
//    else if (*tokens.begin() == "STOREHOUSE") {
//        new_line.element_type = ParsedLineData::ElementType::STOREHOUSE;
//    }
//    else if (*tokens.begin() == "WORKER") {
//        new_line.element_type = ParsedLineData::ElementType::WORKER;
//    }
//    else if (*tokens.begin() == "LINK") {
//        new_line.element_type = ParsedLineData::ElementType::LINK;
//    }
//    else {
//        throw std::logic_error("Wrong element type!");
//    }
//
//    for (auto elem = tokens.begin() + 1; elem != tokens.end(); elem++) {
//        std::string k_v;
//        std::istringstream token_stream_2(*elem);
//        std::vector<std::string> pairs;
//        while (std::getline(token_stream_2, k_v, '=')) {
//            pairs.push_back(k_v);
//        }
//        std::string key = pairs[0];
//        std::string value = pairs[1];
//        new_line.parameters.emplace(key, value);
//    }
//    return new_line;
//}

//PackageQueueType convert(std::string str) {
//    if (str == "LIFO") {
//        return LIFO;
//    }
//    else if (str == "FIFO") {
//        return FIFO;
//    }
//    else {
//        throw "Invalid queue type";
//    }
//}

//std::string convert_to_string(PackageQueueType queue_type) {
//    if (queue_type == FIFO) {
//        return "FIFO";
//    }
//    else if(queue_type == LIFO) {
//        return "LIFO";
//    }
//    else {
//        throw "Invalid queue type";
//    }
//}

//Factory load_factory_structure(std::istream& is) {
//    Factory factory;
//    std::string line;
//
//    while (std::getline(is, line)) {
//        if (!line.empty() and line.find(";") == std::string::npos) {
//            ParsedLineData data;
//            data = parse_line(line);
//
//            switch (data.element_type) {
//                case ParsedLineData::ElementType::RAMP: {
//                    ElementID id = static_cast<ElementID>(std::stoi(data.parameters.find("id")->second));
//                    TimeOffset time = static_cast<TimeOffset>(std::stoi(data.parameters.find("delivery-interval")->second));
//                    factory.add_ramp(Ramp(id, time));
//                    break;
//                }
//                case ParsedLineData::ElementType::WORKER: {
//                    ElementID id = static_cast<ElementID>(std::stoi(data.parameters.find("id")->second));
//                    TimeOffset time = static_cast<TimeOffset>(std::stoi(data.parameters.find("processing-time")->second));
//                    factory.add_worker(Worker(id, time, std::make_unique<PackageQueue>(convert(data.parameters.find("queue-type")->second))));
//                    break;
//                }
//                case ParsedLineData::ElementType::STOREHOUSE: {
//                    ElementID id = static_cast<ElementID>(std::stoi(data.parameters.find("id")->second));
//                    factory.add_storehouse(Storehouse(id));
//                    break;
//                }
//                case ParsedLineData::ElementType::LINK: {
//                    std::string k_v;
//                    std::stringstream token_stream(data.parameters.begin()->second);
//                    std::vector<std::string> f;
//                    char delimiter = '-';
//
//                    while (std::getline(token_stream, k_v, delimiter)) {
//                        f.push_back(k_v);
//                    }
//                    std::string k_v_2;
//                    std::stringstream token_stream_2(std::next(data.parameters.begin(), 1)->second);
//                    std::vector<std::string> s;
//
//                    while (std::getline(token_stream_2, k_v_2, delimiter)) {
//                        s.push_back(k_v_2);
//                    }
//
//                    ElementID id = static_cast<ElementID>(std::stoi(f[1]));
//                    ElementID id_2 = static_cast<ElementID>(std::stoi(s[1]));
//
//                    if (data.parameters.begin()->first == "src") {
//                        if (f[0] == "ramp") {
//                            Ramp& ramp = *(factory.find_ramp_by_id(id));
//                            ramp.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(id_2)));
//                        }
//                        else if (f[0] == "worker" and s[0] == "worker") {
//                            Worker& worker = *(factory.find_worker_by_id(id));
//                            worker.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(id_2)));
//                        }
//                        else if (f[0] == "worker" and s[0] == "store") {
//                            Worker& worker = *(factory.find_worker_by_id(id));
//                            worker.receiver_preferences_.add_receiver(&(*factory.find_storehouse_by_id(id_2)));
//                        }
//                    }
//                    else {
//                        if (s[0] == "ramp") {
//                            Ramp& ramp = *(factory.find_ramp_by_id(id_2));
//                            ramp.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(id)));
//                        }
//                        else if (s[0] == "worker" and f[0] == "worker") {
//                            Worker& worker = *(factory.find_worker_by_id(id_2));
//                            worker.receiver_preferences_.add_receiver(&(*factory.find_worker_by_id(id)));
//                        }
//                        else if (s[0] == "worker" and f[0] == "store") {
//                            Worker& worker = *(factory.find_worker_by_id(id_2));
//                            worker.receiver_preferences_.add_receiver(&(*factory.find_storehouse_by_id(id)));
//                        }
//                    }
//                    break;
//                }
//                default: {
//                    throw std::logic_error("Invalid data");
//                }
//            }
//        }
//    }
//    return factory;
//}

//void save_factory_structure(Factory& factory, std::ostream& os) {
//    std::string save = "; == LOADING_RAMPS ==\n\n";
//    std::string link = "; == LINKS ==\n\n";
//
//    std::vector<ElementID> id_vector;
//    for (auto elem = factory.ramp_cbegin(); elem != factory.ramp_cend(); elem++) {
//        id_vector.push_back(elem->get_id());
//        std::sort(id_vector.begin(), id_vector.end());
//    }
//    for (auto id: id_vector) {
//        std::string ramp = "LOADING_RAMP id=" + std::to_string(factory.find_ramp_by_id(id)->get_id());
//        ramp += " delivery-interval=" + std::to_string(int(factory.find_ramp_by_id(id)->get_delivery_interval())) + "\n";
//        save += ramp;
//        std::map<IPackageReceiver*, double> preferences = factory.find_ramp_by_id(id)->receiver_preferences_.get_preferences();
//        std::vector<ElementID> work_id_vector;
//        std::vector<ElementID> store_id_vector;
//
//        for (auto elem = preferences.begin(); elem != preferences.end(); elem++) {
//            if (elem->first->get_receiver_type() == ReceiverType::WORKER) {
//                work_id_vector.push_back(elem->first->get_id()); }
//            else if (elem->first->get_receiver_type() == ReceiverType::STOREHOUSE) {
//                store_id_vector.push_back(elem->first->get_id()); }
//        }
//
//        std::sort(work_id_vector.begin(), work_id_vector.end());
//        std::sort(store_id_vector.begin(), store_id_vector.end());
//
//        for (auto w_id: work_id_vector) {
//            link += "LINK src=ramp-" + std::to_string(id);
//            link += " dest=worker-" + std::to_string(w_id) + "\n";
//        }
//
//        for (auto s_id: store_id_vector) {
//            link += "LINK src=ramp-" + std::to_string(id);
//            link += " dest=store-" + std::to_string(s_id) + "\n";
//        }
//        link += "\n";
//    }
//
//    save += "\n";
//    save += "; == WORKERS ==\n\n";
//
//    std::vector<ElementID> new_work_id_vector;
//    for (auto elem = factory.worker_cbegin(); elem != factory.worker_cend(); elem++) {
//        new_work_id_vector.push_back(elem->get_id());
//        std::sort(new_work_id_vector.begin(), new_work_id_vector.end());
//    }
//
//    for (auto id: new_work_id_vector) {
//        std::string work = "WORKER id=" + std::to_string(factory.find_worker_by_id(id)->get_id());
//        work += " processing-time=" + std::to_string(int(factory.find_worker_by_id(id)->get_processing_duration()));
//        work += " queue-type=" + convert_to_string(factory.find_worker_by_id(id)->get_queue()->get_queue_type()) + "\n";
//        save += work;
//
//        std::map<IPackageReceiver*, double> preferences = factory.find_worker_by_id(id)->receiver_preferences_.get_preferences();
//        std::vector<ElementID> work_id_vector;
//        std::vector<ElementID> store_id_vector;
//
//        for (auto elem = preferences.begin(); elem != preferences.end(); elem++) {
//            if (elem->first->get_receiver_type() == ReceiverType::WORKER) {
//                work_id_vector.push_back(elem->first->get_id());
//            }
//            else if(elem->first->get_receiver_type() == ReceiverType::STOREHOUSE) {
//                store_id_vector.push_back(elem->first->get_id());
//            }
//        }
//
//        std::sort(work_id_vector.begin(), work_id_vector.end());
//        std::sort(store_id_vector.begin(), store_id_vector.end());
//        for (auto w_id: work_id_vector) {
//            link += "LINK src=worker-" + std::to_string(id);
//            link += " dest=worker-" + std::to_string(w_id) + "\n";
//        }
//
//        for (auto s_id: store_id_vector) {
//            link += "LINK src=worker-" + std::to_string(id);
//            link += " dest=store-" + std::to_string(s_id) + "\n";
//        }
//        link += "\n";
//    }
//
//    save += "\n";
//    save += "; == STOREHOUSES ==\n\n";
//
//    std::vector<ElementID> new_store_id_vector;
//    for (auto elem = factory.storehouse_cbegin(); elem != factory.storehouse_cend(); elem++) {
//        new_store_id_vector.push_back(elem->get_id());
//        std::sort(new_store_id_vector.begin(), new_store_id_vector.end());
//    }
//
//    for (auto id: new_store_id_vector) {
//        std::string storehouse = "STOREHOUSE id=" + std::to_string(factory.find_storehouse_by_id(id)->get_id()) + "\n";
//        save += storehouse;
//    }
//
//    save += "\n" + link;
//    os << save;
//}