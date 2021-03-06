//
// Created by micha on 11.01.2022.
//

#ifndef MAIN_CPP_REPORTS_HPP
#define MAIN_CPP_REPORTS_HPP

#include "factory.hpp"

void generate_structure_report(const Factory& factory, std::ostream& os);
void generate_simulation_turn_report(const Factory& factory, std::ostream& os, Time time);


class InterrvalReportNotifier{
public:
    InterrvalReportNotifier(TimeOffset to){to_ = to;}
    bool should_generate_report(Time t){
        if(t-1%to_){
        return false;
        }
        else{
            return true;
        }
    }
private:
    TimeOffset to_;
};


class SpecificTurnsReportNotifier{
public:
    SpecificTurnsReportNotifier(std::set<Time> turns){turns_ = turns;}
    bool should_generate_report(Time t) {
        for (auto it = turns_.cbegin(); it != turns_.cend(); it++) {
            if(*it == t){return true;}
        }
        return false;
    }
private:
    std::set<Time> turns_;
};

#endif //MAIN_CPP_REPORTS_HPP
