//
// Created by micha on 11.01.2022.
//

#ifndef MAIN_CPP_SIMULATION_HPP
#define MAIN_CPP_SIMULATION_HPP
#include "reports.hpp"

void simulate(Factory& factory, TimeOffset d, std::function<void (Factory&, Time)> rf);

#endif //MAIN_CPP_SIMULATION_HPP
