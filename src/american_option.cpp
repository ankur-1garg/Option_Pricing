#include "american_option.hpp"

// Implementation of the payoff function for AmericanOption

double AmericanOption::payoff(double spotPrice) const
{
    if (m_type == OptionType::Call)
    {
        return std::max(spotPrice - m_strike, 0.0);
    }
    else
    { // Put
        return std::max(m_strike - spotPrice, 0.0);
    }
}
