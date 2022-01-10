//
// Created by michal on 14/12/2021.
//

#ifndef POLPRODUKTY_TYPES_HPP
#define POLPRODUKTY_TYPES_HPP

#include <functional>

using ElementID = unsigned int;
using Time = unsigned int;
using TimeOffset = unsigned int;
using ProbabilityGenerator = std::function<double()>;

#endif //POLPRODUKTY_TYPES_HPP
