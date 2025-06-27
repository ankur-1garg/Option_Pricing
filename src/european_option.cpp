// src/european_option.cpp
#include "european_option.hpp"

double EuropeanOption::payoff(double spotPrice) const {
    if (m_type == OptionType::Call) {
        return std::max(spotPrice - m_strike, 0.0);
    } else { // Put
        return std::max(m_strike - spotPrice, 0.0);
    }
}