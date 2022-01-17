//
// Created by micha on 11.01.2022.
//

#include "simulation.hpp"
#include <stdexcept>

void simulate(Factory& factory, TimeOffset d, std::function<void (Factory&, Time)> rf){

    if(!factory.is_consistent()){throw std::logic_error("Sieć niespójna!");}

    for(TimeOffset current_turn = 1; current_turn <= d; current_turn++){
        factory.do_deliveries(current_turn);
        factory.do_package_passing();
        factory.do_work(current_turn);
        rf(factory, current_turn);
    }
}
