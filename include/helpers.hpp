//
// Created by michal on 04/01/2022.
//

#ifndef MAIN_CPP_HELPERS_HPP
#define MAIN_CPP_HELPERS_HPP

#include <functional>
#include <random>

#include "types.hpp"

extern std::random_device rd;
extern std::mt19937 rng;

extern double default_probability_generator();

extern ProbabilityGenerator probability_generator;

#endif //MAIN_CPP_HELPERS_HPP
