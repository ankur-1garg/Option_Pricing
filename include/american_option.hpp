#pragma once

#include "Option.hpp"
#include <algorithm> // For std::max

class AmericanOption : public Option {
public:
    // Constructor that calls the base class constructor
    AmericanOption(double strike, double maturity, OptionType type)
        : Option(strike, maturity, type) {}

    // Payoff at expiry is the same as a European option
    double payoff(double spotPrice) const override;
};
