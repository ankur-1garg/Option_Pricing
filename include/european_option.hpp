// include/european_option.hpp
#pragma once

#include "Option.hpp"
#include <algorithm> // For std::max

class EuropeanOption : public Option {
public:
    // Constructor that calls the base class constructor
    EuropeanOption(double strike, double maturity, OptionType type)
        : Option(strike, maturity, type) {}

    // Implementation of the payoff function
    double payoff(double spotPrice) const override;
};